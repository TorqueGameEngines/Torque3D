#include "runtime.h"

#include "codeBlock.h"
#include "console/script.h"
#include "console/runtime.h"
#include "core/volume.h"
#include "core/stream/fileStream.h"
#include "core/util/timeClass.h"


namespace TorqueScript
{
   // Buffer for expanding script filenames.
   static char scriptFilenameBuffer[1024];

   TorqueScriptRuntime::TorqueScriptRuntime()
   {
      Con::registerRuntime(0, this);
   }

   TorqueScriptRuntime::~TorqueScriptRuntime()
   {
   }

   Con::EvalResult TorqueScriptRuntime::evaluate(const char* string, bool echo, const char* fileName)
   {
      ConsoleStackFrameSaver stackSaver;
      stackSaver.save();

      if (echo)
      {
         if (string[0] == '%')
            Con::printf("%s", string);
         else
            Con::printf("%s%s", Con::getVariable("$Con::Prompt"), string);
      }

      if (fileName)
         fileName = StringTable->insert(fileName);

      CodeBlock* newCodeBlock = new CodeBlock();
      return std::move(newCodeBlock->compileExec(fileName, string, false, fileName ? -1 : 0));
   }

   Con::EvalResult TorqueScriptRuntime::evaluate(const char* script, S32 frame, bool echo, const char* fileName)
   {
      // Make sure we're passing a valid frame to the eval.
      if (frame > Script::gEvalState.getStackDepth())
         frame = Script::gEvalState.getStackDepth() - 1;
      if (frame < 0)
         frame = 0;

      // Local variables use their own memory management and can't be queried by just executing
      // TorqueScript, we have to go digging into the interpreter.
      S32 evalBufferLen = dStrlen(script);
      bool isEvaluatingLocalVariable = evalBufferLen > 0 && script[0] == '%';
      if (isEvaluatingLocalVariable)
      {
         // See calculation of current frame in pushing a reference frame for console exec, we need access
         // to the proper scope.
         //frame = gEvalState.getTopOfStack() - frame - 1;
         S32 stackIndex = Script::gEvalState.getStackDepth() - frame - 1;

         Script::gEvalState.pushDebugFrame(stackIndex);

         Dictionary& stackFrame = Script::gEvalState.getCurrentFrame();
         StringTableEntry functionName = stackFrame.scopeName;
         StringTableEntry namespaceName = stackFrame.scopeNamespace->mName;
         StringTableEntry varToLookup = StringTable->insert(script);

         S32 registerId = ((CodeBlock*)stackFrame.module)->variableRegisterTable.lookup(namespaceName, functionName, varToLookup);

         if (registerId == -1)
         {
            // ERROR, can't read the variable!
            return Con::EvalResult("variable not found");
         }

         const char* varResult = Script::gEvalState.getLocalStringVariable(registerId);

         Script::gEvalState.popFrame();

         ConsoleValue val;
         val.setString(varResult);

         return Con::EvalResult("variable not found");
      }

      // Execute the eval.
      CodeBlock* newCodeBlock = new CodeBlock();
      Con::EvalResult result = newCodeBlock->compileExec(NULL, script, false, frame);
      return result;
   }

   //------------------------------------------------------------------------------
   Con::EvalResult TorqueScriptRuntime::evaluatef(const char* string, ...)
   {
      char buffer[4096];
      va_list args;
      va_start(args, &string);
      dVsprintf(buffer, sizeof(buffer), string, args);
      va_end(args);
      return evaluate(buffer);
   }

   bool TorqueScriptRuntime::executeFile(const char* fileName, bool noCalls, bool journalScript)
   {
      bool journal = false;

      U32 execDepth = 0;
      U32 journalDepth = 1;

      execDepth++;
      if (journalDepth >= execDepth)
         journalDepth = execDepth + 1;
      else
         journal = true;

      bool ret = false;

      if (journalScript && !journal)
      {
         journal = true;
         journalDepth = execDepth;
      }

      // Determine the filename we actually want...
      Con::expandScriptFilename(scriptFilenameBuffer, sizeof(scriptFilenameBuffer), fileName);

      // since this function expects a script file reference, if it's a .dso
      // lets terminate the string before the dso so it will act like a .tscript
      if (dStrEndsWith(scriptFilenameBuffer, ".dso"))
      {
         scriptFilenameBuffer[dStrlen(scriptFilenameBuffer) - dStrlen(".dso")] = '\0';
      }

      // Figure out where to put DSOs
      StringTableEntry dsoPath = Con::getDSOPath(scriptFilenameBuffer);

      const char* ext = dStrrchr(scriptFilenameBuffer, '.');

      if (!ext)
      {
         // Try appending the default script extension and see if that succeeds

         if (executeFile(fileName + String("." TORQUE_SCRIPT_EXTENSION), noCalls, journalScript))
         {
            return true;
         }

         // We need an extension!
         Con::errorf(ConsoleLogEntry::Script, "exec: invalid script file name %s.", scriptFilenameBuffer);
         execDepth--;
         return false;
      }

      // Check Editor Extensions
      bool isEditorScript = false;

      // If the script file extension is '.ed.tscript' then compile it to a different compiled extension
      if (dStricmp(ext, "." TORQUE_SCRIPT_EXTENSION) == 0)
      {
         const char* ext2 = ext - 3;
         if (dStricmp(ext2, ".ed." TORQUE_SCRIPT_EXTENSION) == 0)
            isEditorScript = true;
      }
      else if (dStricmp(ext, ".gui") == 0)
      {
         const char* ext2 = ext - 3;
         if (dStricmp(ext2, ".ed.gui") == 0)
            isEditorScript = true;
      }

      StringTableEntry scriptFileName = StringTable->insert(scriptFilenameBuffer);

      // Is this a file we should compile? (anything in the prefs path should not be compiled)
      StringTableEntry prefsPath = Platform::getPrefsPath();
      bool compiled = dStricmp(ext, ".mis") && !journal && !Con::getBoolVariable("Scripts::ignoreDSOs");

      // [tom, 12/5/2006] stripBasePath() fucks up if the filename is not in the exe
      // path, current directory or prefs path. Thus, getDSOFilename() will also screw
      // up and so this allows the scripts to still load but without a DSO.
      if (Platform::isFullPath(Platform::stripBasePath(scriptFilenameBuffer)))
         compiled = false;

      // [tom, 11/17/2006] It seems to make sense to not compile scripts that are in the
      // prefs directory. However, getDSOPath() can handle this situation and will put
      // the dso along with the script to avoid name clashes with tools/game dsos.
      if ((dsoPath && *dsoPath == 0) || (prefsPath && prefsPath[0] && dStrnicmp(
         scriptFileName, prefsPath, dStrlen(prefsPath)) == 0))
         compiled = false;

      // If we're in a journaling mode, then we will read the script
      // from the journal file.
      if (journal && Journal::IsPlaying())
      {
         char fileNameBuf[256];
         bool fileRead = false;
         U32 fileSize;

         Journal::ReadString(fileNameBuf);
         Journal::Read(&fileRead);

         if (!fileRead)
         {
            Con::errorf(ConsoleLogEntry::Script, "Journal script read (failed) for %s", fileNameBuf);
            execDepth--;
            return false;
         }
         Journal::Read(&fileSize);
         char* script = new char[fileSize + 1];
         Journal::Read(fileSize, script);
         script[fileSize] = 0;
         Con::printf("Executing (journal-read) %s.", scriptFileName);

         CodeBlock *newCodeBlock = new CodeBlock();
         newCodeBlock->compileExec(scriptFileName, script, noCalls, 0);
         delete newCodeBlock;
         delete[] script;

         execDepth--;
         return true;
      }

      // Ok, we let's try to load and compile the script.
      Torque::FS::FileNodeRef scriptFile = Torque::FS::GetFileNode(scriptFileName);
      Torque::FS::FileNodeRef dsoFile;

      //    ResourceObject *rScr = gResourceManager->find(scriptFileName);
      //    ResourceObject *rCom = NULL;

      char nameBuffer[512];
      char* script = NULL;
      U32 version;

      Stream* compiledStream = NULL;
      Torque::Time scriptModifiedTime, dsoModifiedTime;

      // Check here for .edso
      bool edso = false;
      if (dStricmp(ext, ".edso") == 0 && scriptFile != NULL)
      {
         edso = true;
         dsoFile = scriptFile;
         scriptFile = NULL;

         dsoModifiedTime = dsoFile->getModifiedTime();
         dStrcpy(nameBuffer, scriptFileName, 512);
      }

      // If we're supposed to be compiling this file, check to see if there's a DSO
      if (compiled && !edso)
      {
         const char* filenameOnly = dStrrchr(scriptFileName, '/');
         if (filenameOnly)
            ++filenameOnly;
         else
            filenameOnly = scriptFileName;

         char pathAndFilename[1024];
         Platform::makeFullPathName(filenameOnly, pathAndFilename, sizeof(pathAndFilename), dsoPath);

         if (isEditorScript)
            dStrcpyl(nameBuffer, sizeof(nameBuffer), pathAndFilename, ".edso", NULL);
         else
            dStrcpyl(nameBuffer, sizeof(nameBuffer), pathAndFilename, ".dso", NULL);

         dsoFile = Torque::FS::GetFileNode(nameBuffer);

         if (scriptFile != NULL)
            scriptModifiedTime = scriptFile->getModifiedTime();

         if (dsoFile != NULL)
            dsoModifiedTime = dsoFile->getModifiedTime();
      }

      // Let's do a sanity check to complain about DSOs in the future.
      //
      // MM:   This doesn't seem to be working correctly for now so let's just not issue
      //    the warning until someone knows how to resolve it.
      //
      //if(compiled && rCom && rScr && Platform::compareFileTimes(comModifyTime, scrModifyTime) < 0)
      //{
      //Con::warnf("exec: Warning! Found a DSO from the future! (%s)", nameBuffer);
      //}

      // If we had a DSO, let's check to see if we should be reading from it.
      //MGT: fixed bug with dsos not getting recompiled correctly
      //Note: Using Nathan Martin's version from the forums since its easier to read and understand
      if (compiled && dsoFile != NULL && (scriptFile == NULL || (dsoModifiedTime >= scriptModifiedTime)))
      {
         //MGT: end
         compiledStream = FileStream::createAndOpen(nameBuffer, Torque::FS::File::Read);
         if (compiledStream)
         {
            // Check the version!
            compiledStream->read(&version);
            if (version != Con::DSOVersion)
            {
               Con::warnf("exec: Found an old DSO (%s, ver %d < %d), ignoring.", nameBuffer, version, Con::DSOVersion);
               delete compiledStream;
               compiledStream = NULL;
            }
         }
      }

      // If we're journalling, let's write some info out.
      if (journal && Journal::IsRecording())
         Journal::WriteString(scriptFileName);

      if (scriptFile != NULL && !compiledStream)
      {
         // If we have source but no compiled version, then we need to compile
         // (and journal as we do so, if that's required).

         void* data;
         U32 dataSize = 0;
         Torque::FS::ReadFile(scriptFileName, data, dataSize, true);

         if (journal && Journal::IsRecording())
            Journal::Write(bool(data != NULL));

         if (data == NULL)
         {
            Con::errorf(ConsoleLogEntry::Script, "exec: invalid script file %s.", scriptFileName);
            execDepth--;
            return false;
         }
         else
         {
            if (!dataSize)
            {
               execDepth--;
               return false;
            }

            script = (char*)data;

            if (journal && Journal::IsRecording())
            {
               Journal::Write(dataSize);
               Journal::Write(dataSize, data);
            }
         }

#ifndef TORQUE_NO_DSO_GENERATION
      if (compiled)
      {
         // compile this baddie.
#ifdef TORQUE_DEBUG
         Con::printf("Compiling %s...", scriptFileName);
#endif

         CodeBlock *code = new CodeBlock();
         code->compile(nameBuffer, scriptFileName, script);
         delete code;
         code = NULL;

         compiledStream = FileStream::createAndOpen(nameBuffer, Torque::FS::File::Read);
         if (compiledStream)
         {
            compiledStream->read(&version);
         }
         else
         {
            // We have to exit out here, as otherwise we get double error reports.
            delete[] script;
            execDepth--;
            return false;
         }
      }
#endif
      }
      else
      {
         if (journal && Journal::IsRecording())
            Journal::Write(bool(false));
      }

      if (compiledStream)
      {
         // Delete the script object first to limit memory used
         // during recursive execs.
         delete[] script;
         script = 0;

         // We're all compiled, so let's run it.
#ifdef TORQUE_DEBUG
         Con::printf("Loading compiled script %s.", nameBuffer);
#endif
         CodeBlock* code = new CodeBlock();
         code->read(scriptFileName, *compiledStream);
         delete compiledStream;
         code->exec(0, scriptFileName, NULL, 0, NULL, noCalls, NULL, 0);
         ret = true;
      }
      else if (scriptFile)
      {
         // No compiled script,  let's just try executing it
         // directly... this is either a mission file, or maybe
         // we're on a readonly volume.
#ifdef TORQUE_DEBUG
         Con::printf("Executing %s.", scriptFileName);
#endif

         CodeBlock *newCodeBlock = new CodeBlock();
         StringTableEntry name = StringTable->insert(scriptFileName);

         newCodeBlock->compileExec(name, script, noCalls, 0);
         ret = true;
      }
      else
      {
         // Don't have anything.
         Con::warnf(ConsoleLogEntry::Script, "Missing file: %s!", scriptFileName);
         ret = false;
      }

      delete[] script;
      execDepth--;
      return ret;
   }

   bool TorqueScriptRuntime::compile(const char* fileName, bool overrideNoDso)
   {
      Con::expandScriptFilename( scriptFilenameBuffer, sizeof( scriptFilenameBuffer ), fileName );

      // Figure out where to put DSOs
      StringTableEntry dsoPath = Con::getDSOPath(scriptFilenameBuffer);
      if(dsoPath && *dsoPath == 0)
         return false;

      // If the script file extention is '.ed.tscript' then compile it to a different compiled extention
      bool isEditorScript = false;
      const char *ext = dStrrchr( scriptFilenameBuffer, '.' );
      if( ext && ( dStricmp( ext, "." TORQUE_SCRIPT_EXTENSION) == 0 ) )
      {
         const char* ext2 = ext - 3;
         if( dStricmp( ext2, ".ed." TORQUE_SCRIPT_EXTENSION) == 0 )
            isEditorScript = true;
      }
      else if( ext && ( dStricmp( ext, ".gui" ) == 0 ) )
      {
         const char* ext2 = ext - 3;
         if( dStricmp( ext2, ".ed.gui" ) == 0 )
            isEditorScript = true;
      }

      const char *filenameOnly = dStrrchr(scriptFilenameBuffer, '/');
      if(filenameOnly)
         ++filenameOnly;
      else
         filenameOnly = scriptFilenameBuffer;

      char nameBuffer[512];

      if( isEditorScript )
         dStrcpyl(nameBuffer, sizeof(nameBuffer), dsoPath, "/", filenameOnly, ".edso", NULL);
      else
         dStrcpyl(nameBuffer, sizeof(nameBuffer), dsoPath, "/", filenameOnly, ".dso", NULL);

      void *data = NULL;
      U32 dataSize = 0;
      Torque::FS::ReadFile(scriptFilenameBuffer, data, dataSize, true);
      if(data == NULL)
      {
         Con::errorf(ConsoleLogEntry::Script, "compile: invalid script file %s.", scriptFilenameBuffer);
         return false;
      }

      const char *script = static_cast<const char *>(data);

#ifdef TORQUE_DEBUG
      Con::printf("Compiling %s...", scriptFilenameBuffer);
#endif

      CodeBlock *code = new CodeBlock();
      code->compile(nameBuffer, scriptFilenameBuffer, script, overrideNoDso);
      delete code;
      delete[] script;

      return true;
   }

}
