function QuestionText::onURL(%this, %url)
{
   if(firstword(%url)!$="RPGDialog" && firstword(%url)!$="RPGDialogLink")
   {
      gotoWebPage( %url );
   }
   else if(firstword(%url)$="RPGDialogLink")
   {
      editQuestionLink(restwords(%url));
   }
}

function initSaveAsPhase1()
{
   getSaveFilename("*.dlq", initSaveAsPhase2,$RPGDialog::currentDLQ);
}

function initSaveAsPhase2(%QuestionFile)
{
   if(strPos(strlwr(%QuestionFile),".dlq")>=0)
   {
      $RPGDialog::SaveAsDLQ=%QuestionFile;
      if(!isFile(%QuestionFile))
      {
         schedule(20,0,"getSaveFilename","*.dla",initSaveAsPhase3,$RPGDialog::currentDLA);
      }
      else
      {
         MessageBoxYesNo("Warning","File already exists, overwrite?","schedule(20,0,getSaveFilename,\"*.dla\",initSaveAsPhase3,$RPGDialog::currentDLA);","schedule(20,0,getSaveFilename,\"*.dlq\",initSaveAsPhase2,$RPGDialog::currentDLQ);");
      }
   }
   else
   {
      MessageBoxOK("Error","File must have .dlq extension");
   }
}

function initSaveAsPhase3(%ActionFile)
{
   %testFileName=$RPGDialog::SaveAsDLQ;
   while(%i<=20)
   {
      %nextPos=strPos(%testFileName,"/");
      if(%nextPos<0)
      {
         %testFileName=getSubStr(%testFileName,0,strPos(%testFileName,".dlq"))@".dla";
         %i=21;
      }
      else
      {
         %testFileName=getSubStr(%testFileName,%nextPos+1,strLen(%testFileName));
      }
      %i++;
   }

   if(strPos(strlwr(%ActionFile),".dla")>=0)
   {
      if(strPos(%ActionFile,%testFileName)>=0)
      {
         $RPGDialog::SaveAsDLA=%ActionFile;
         if(!isFile(%ActionFile))
         {
            initSaveAsPhase4();
         }
         else
         {
            MessageBoxYesNo("Warning","File already exists, overwrite?","initSaveAsPhase4();","schedule(20,0,getSaveFilename,\"*.dla\",initSaveAsPhase3,$RPGDialog::currentDLA);");
         }
      }
      else
      {
         MessageBoxOK("Error","Dla and Dlq filenames must be equal, but may be stored in different folders.");
      }
   }
   else
   {
      MessageBoxOK("Error","File must have .dla extension");
   }
}

function initSaveAsPhase4()
{
   $RPGDialog::currentDLQ=$RPGDialog::SaveAsDLQ;
   $RPGDialog::currentDLA=$RPGDialog::SaveAsDLA;
   saveScript();
}

function initNewScript()
{
   NewScriptQuestion.setvalue($RPGDialogEditorPref::QuestionPath@"new.dlq");
   NewScriptAction.setvalue($RPGDialogEditorPref::ActionPath@"new.dla");
   Canvas.pushDialog(NewScriptPopup);
}

function newScript()
{
   %QuestionFile=NewScriptQuestion.getvalue();
   %ActionFile=NewScriptAction.getvalue();
   
   %testFileName=%QuestionFile;
   while(%i<=20)
   {
      %nextPos=strPos(%testFileName,"/");
      if(%nextPos<0)
      {
         %testFileName=getSubStr(%testFileName,0,strPos(%testFileName,".dlq"))@".dla";
         %i=21;
      }
      else
      {
         %testFileName=getSubStr(%testFileName,%nextPos+1,strLen(%testFileName));
      }
      %i++;
   }
   
   if(strPos(%ActionFile,%testFileName)>=0)
   {
      %extensionCheck=strPos(%QuestionFile,".dlq");
      if(%extensionCheck<0)
      {
         %QuestionFile=%QuestionFile@".dlq";
      }
   
      %extensionCheck=strPos(%ActionFile,".dla");
      if(%extensionCheck<0)
      {
         %ActionFile=%ActionFile@".dla";
      }
   
      if(!isFile(%QuestionFile))
      {
         if(!isFile(%ActionFile))
         {
            Canvas.popDialog(NewScriptPopup);
            
            if(TextScript.getvalue()!$="Current Q. Script:")
            {
               for(%i=1;%i<=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0];%i++)
               {
                  (Answer@%i).delete();
                  (Action@%i).delete();
                  (editAnswer@%i@Button).delete();
                  (moveAnswer@%i@UpButton).delete();
                  (moveAnswer@%i@DownButton).delete();
               }
            }

            deleteVariables("$RPGDialog::*");//delete all obsolete globals and reset the 2 that are needed.
            $RPGDialog::currentDLQ=%QuestionFile;
            $RPGDialog::currentDLA=%ActionFile;
            TextScript.settext("Current Q. Script: "@$RPGDialog::currentDLQ);
            TextScript2.settext("Current A. Script: "@$RPGDialog::currentDLA);
            TextQuestionNumber.settext("Question: 0/0");
            QuestionText.settext("");
            Canvas.setContent(MainEditorScreenGui);
         }
         else
            MessageBoxOK("Error","Cannot create question script file");
      }
      else
      {
         MessageBoxOK("Error","Cannot create action script file");
      }
   }
   else
   {
      MessageBoxOK("Error","Dla and Dlq filenames must be equal, but may be stored in different folders.");
   }
}

function LoadScript(%qScriptName)
{
   $RPGDialog::currentDLQ=%qScriptName;
   %aScriptName=strReplace(%qScriptName,".dlq",".dla");
   $RPGDialog::currentDLA=%aScriptName;
   if(!isFile(%aScriptName))
   {
      %path=%qScriptName;
      while(%i<=20)
      {
         %nextPos=strPos(%path,"/");
         if(%nextPos<0)
         {
            %aScriptFileName=getSubStr(%path,0,strPos(%path,".dlq"))@".dla";
            %i=21;
         }
         else
         {
            %path=getSubStr(%path,%nextPos+1,strLen(%path));
         }
         %i++;
      }
      %aScriptName=$RPGDialogEditorPref::ActionPath@%aScriptFileName;
      $RPGDialog::currentDLA=%aScriptName;
      if(!isFile(%aScriptName))
      {
         MessageBoxOK("Error","Couldn't find "@%aScriptFileName@" on the default dla folder nor on the same directory as the dlq.");
      }
   }
   if(TextScript.getvalue()!$="Current Q. Script:")
   {
      for(%i=1;%i<=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0];%i++)
      {
         (Answer@%i).delete();
         (Action@%i).delete();
         (editAnswer@%i@Button).delete();
         (moveAnswer@%i@UpButton).delete();
         (moveAnswer@%i@DownButton).delete();         
      }
   }
   
   deleteVariables("$RPGDialog::*");//delete all obsolete globals and reset the 2 that are needed.
   $RPGDialog::currentDLQ=%qScriptName;
   $RPGDialog::currentDLA=%aScriptName;

   %file = new FileObject();
   if(isfile(%qScriptName) && %file.openForRead(%qScriptName))
   {
      while(!%file.isEOF())
      {
         $RPGDialog::Questions++;
         
         %line=%file.readLine();
         %answerStart=strPos(%line,"<AnswerStart>");
         %question=getSubStr(%line,0,%answerStart);
         %soundStart=strPos(%question, "~Sound:");
         if(%soundStart>=0)
         {
            $RPGDialog::QuestionSound[$RPGDialog::Questions]=getSubStr(%question,%soundStart+7,strLen(%question));
            %question=getSubStr(%question, 0, %soundStart);
         }
         $RPGDialog::Question[$RPGDialog::Questions]=%question;
         
         %lineLinks=%line;
         %i=1;
         while(%i<=$RPGDialogEditorPref::MaxOptions)
         {
            %QuestionLinkHeaderSize=strlen("<a:RPGDialogLink "@%i@">");
            %QuestionLinkStart=strpos(%lineLinks,"<a:RPGDialogLink "@%i@">");
            %lineLinks=getSubStr(%lineLinks,%QuestionLinkStart+%QuestionLinkHeaderSize,strlen(%lineLinks));
            %QuestionLinkEnd=strpos(%lineLinks,"</a>");

            if(%QuestionLinkStart<0||%QuestionLinkEnd<0)
            {
               %i=$RPGDialogEditorPref::MaxOptions+1;
            }
            else
            {
               $RPGDialog::QuestionLink[$RPGDialog::Questions,%i]=getSubStr(%lineLinks,0,%QuestionLinkEnd);
               $RPGDialog::QuestionLink[$RPGDialog::Questions,0]=%i;//use this to store how many answers are avaible for this question link.
               %i++;
            }
         }

         %i=1;
         while(%i<=$RPGDialogEditorPref::MaxOptions)
         {
            %AnswerHeaderSize=strlen("<a:RPGDialog "@%i@">");
            %AnswerStart=strpos(%line,"<a:RPGDialog "@%i@">");
            %line=getSubStr(%line,%AnswerStart+%AnswerHeaderSize,strlen(%line));
            %AnswerEnd=strpos(%line,"</a>");

            if(%AnswerStart<0||%AnswerEnd<0)
            {
               %i=$RPGDialogEditorPref::MaxOptions+1;
            }
            else
            {
               $RPGDialog::Answer[$RPGDialog::Questions,%i]=getSubStr(%line,0,%AnswerEnd);
               $RPGDialog::Answer[$RPGDialog::Questions,0]=%i;//use this to store how many answers are avaible for this question.
               %i++;
            }
         }
         
      }
   }
   %file.close();
   if(isfile(%aScriptName) && %file.openForRead(%aScriptName))
   {
      while(!%file.isEOF())
      {
         %Actions++;
         %line=%line2=%file.readLine();

         %i=1;
         while(%i<=$RPGDialogEditorPref::MaxOptions)
         {
            %ActionHeaderSize=strlen("<QL"@%i@">");
            %ActionStart=strpos(%line,"<QL"@%i@">");
            %line=getSubStr(%line,%ActionStart+%ActionHeaderSize,strlen(%line));
            %ActionEnd=strpos(%line,"<END>")+5;

            if(%ActionStart<0||%ActionEnd<0)
            {
               %i=$RPGDialogEditorPref::MaxOptions+1;
            }
            else
            {
               $RPGDialog::QuestionLinkAction[%Actions,%i]=getSubStr(%line,0,%ActionEnd);
               $RPGDialog::QuestionLinkAction[%Actions,0]=%i;//use this to store how many actions are avaible for this question.
               %i++;
            }
         }

         %i=1;
         while(%i<=$RPGDialogEditorPref::MaxOptions)
         {
            %ActionHeaderSize=strlen("<"@%i@">");
            %ActionStart=strpos(%line2,"<"@%i@">");
            %line2=getSubStr(%line2,%ActionStart+%ActionHeaderSize,strlen(%line2));
            %ActionEnd=strpos(%line2,"<END>")+5;

            if(%ActionStart<0||%ActionEnd<0)
            {
               %i=$RPGDialogEditorPref::MaxOptions+1;
            }
            else
            {
               $RPGDialog::Action[%Actions,%i]=getSubStr(%line2,0,%ActionEnd);
               $RPGDialog::Action[%Actions,0]=%i;//use this to store how many actions are avaible for this question.
               %i++;
            }
         }
      }
      if($RPGDialog::Questions>0)
      {
         $RPGDialog::CurrentQuestion=1;
         TextQuestionNumber.settext("Question: 1/"@$RPGDialog::Questions);
         QuestionText.settext($RPGDialog::Question[1]);
      }
      else
      {
         $RPGDialog::CurrentQuestion=0;
         TextQuestionNumber.settext("Question: 0/0");
         QuestionText.settext("");
      }
      TextScript.settext("Current Q. Script: "@$RPGDialog::currentDLQ);
      TextScript2.settext("Current A. Script: "@$RPGDialog::currentDLA);
      
      for(%i=1;%i<=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0];%i++)
      {
         OptionsControl.add(new GuiMLTextCtrl(Answer@%i)
         {
            profile = "GuiMLTextEditProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "2 2";
            extent = "390 40";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            lineSpacing = "2";
            allowColorChars = "1";
            maxChars = "-1";
         });
         
         OptionsControl.add(new GuiMLTextCtrl(Action@%i)
         {
            profile = "GuiMLTextEditProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "400 2";
            extent = "300 14";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            lineSpacing = "2";
            allowColorChars = "1";
            maxChars = "-1";
         });
         
         OptionsControl.add(new GuiButtonCtrl(editAnswer@%i@Button)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "700 2";
            extent = "54 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Edit A."@%i;
            groupNum = "-1";
            buttonType = "PushButton";
            command = "EditAnswer("@%i@");";
         });
         OptionsControl.add(new GuiButtonCtrl(moveAnswer@%i@UpButton)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "700 17";
            extent = "21 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Up";
            groupNum = "-1";
            buttonType = "PushButton";
            command = "MoveAnswerUp("@%i@");";
         });
         if(%i==1)            
            (moveAnswer@%i@UpButton).setvisible(0);
         else
            (moveAnswer@%i@UpButton).setvisible(1);
         OptionsControl.add(new GuiButtonCtrl(moveAnswer@%i@DownButton)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "721 17";
            extent = "33 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Down";
            groupNum = "-1";
            buttonType = "PushButton";
            command = "MoveAnswerDown("@%i@");";
         });
         if(%i==$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0])            
            (moveAnswer@%i@DownButton).setvisible(0);
         else
            (moveAnswer@%i@DownButton).setvisible(1);
         
         (Answer@%i).settext($RPGDialog::Answer[$RPGDialog::CurrentQuestion,%i]);
         (Action@%i).settext($RPGDialog::Action[$RPGDialog::CurrentQuestion,%i]);
      }
      Canvas.setContent(MainEditorScreenGui);
      RefreshOptions();
   }
   %file.close();
   %file.delete();
}

function SaveScript()
{
   %qScriptName=$RPGDialog::currentDLQ;
   %aScriptName=$RPGDialog::currentDLA;
   
   %file = new FileObject();
   if(%file.openForWrite(%qScriptName))
   {
      for(%i=1;%i<=$RPGDialog::Questions;%i++)
      {
         if($RPGDialog::QuestionSound[%i]!$="")
         {
            %line=$RPGDialog::Question[%i]@"~Sound:"@$RPGDialog::QuestionSound[%i]@"<AnswerStart>";
         }
         else
         {
            %line=$RPGDialog::Question[%i]@"<AnswerStart>";
         }
         
         for(%f=1;%f<=$RPGDialog::Answer[%i,0];%f++)
         {
            %line=%line@"<a:RPGDialog "@%f@">"@$RPGDialog::Answer[%i,%f]@"</a><BR>";
         }
         %file.writeLine(%line);
      }
   }
   %file.close();
   if(%file.openForWrite(%aScriptName))
   {
      for(%i=1;%i<=$RPGDialog::Questions;%i++)
      {
         %line="";
         for(%f=1;%f<=$RPGDialog::QuestionLinkAction[%i,0];%f++)
         {
            %line=%line@"<QL"@%f@">"@$RPGDialog::QuestionLinkAction[%i,%f];
         }

         for(%f=1;%f<=$RPGDialog::Action[%i,0];%f++)
         {
            %line=%line@"<"@%f@">"@$RPGDialog::Action[%i,%f];
         }
         %file.writeLine(%line);
      }
   }
   %file.close();
   %file.delete();
}

function NextQuestion()
{
   if($RPGDialog::CurrentQuestion<$RPGDialog::Questions)
   {
      $RPGDialog::CurrentQuestion++;
      QuestionText.settext($RPGDialog::Question[$RPGDialog::CurrentQuestion]);
      TextQuestionNumber.settext("Question: "@$RPGDialog::CurrentQuestion@"/"@$RPGDialog::Questions);
      
      for(%i=1;%i<=$RPGDialog::Answer[$RPGDialog::CurrentQuestion-1,0];%i++)
      {
         (Answer@%i).delete();
         (Action@%i).delete();
         (editAnswer@%i@Button).delete();
         (moveAnswer@%i@UpButton).delete();
         (moveAnswer@%i@DownButton).delete();         
      }
      
      for(%i=1;%i<=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0];%i++)
      {
         OptionsControl.add(new GuiMLTextCtrl(Answer@%i)
         {
            profile = "GuiMLTextEditProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "2 2";
            extent = "390 40";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            lineSpacing = "2";
            allowColorChars = "1";
            maxChars = "-1";
         });

         OptionsControl.add(new GuiMLTextCtrl(Action@%i)
         {
            profile = "GuiMLTextEditProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "400 2";
            extent = "300 40";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            lineSpacing = "2";
            allowColorChars = "1";
            maxChars = "-1";
         });
         
         OptionsControl.add(new GuiButtonCtrl(editAnswer@%i@Button)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "700 2";
            extent = "54 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Edit A."@%i;
            groupNum = "-1";
            buttonType = "PushButton";
            command = "EditAnswer("@%i@");";
         });      
         OptionsControl.add(new GuiButtonCtrl(moveAnswer@%i@UpButton)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "700 17";
            extent = "21 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Up";
            groupNum = "-1";
            buttonType = "PushButton";
            command = "MoveAnswerUp("@%i@");";
         });
         if(%i==1)            
            (moveAnswer@%i@UpButton).setvisible(0);
         else
            (moveAnswer@%i@UpButton).setvisible(1);
         OptionsControl.add(new GuiButtonCtrl(moveAnswer@%i@DownButton)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "721 17";
            extent = "33 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Down";
            groupNum = "-1";
            buttonType = "PushButton";
            command = "MoveAnswerDown("@%i@");";
         });
         if(%i==$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0])            
            (moveAnswer@%i@DownButton).setvisible(0);
         else
            (moveAnswer@%i@DownButton).setvisible(1);

         (Answer@%i).settext($RPGDialog::Answer[$RPGDialog::CurrentQuestion,%i]);
         (Action@%i).settext($RPGDialog::Action[$RPGDialog::CurrentQuestion,%i]);
      }
      RefreshOptions();     
   }
}

function PreviousQuestion()
{
   if($RPGDialog::CurrentQuestion>1)
   {
      $RPGDialog::CurrentQuestion--;
      QuestionText.settext($RPGDialog::Question[$RPGDialog::CurrentQuestion]);
      TextQuestionNumber.settext("Question: "@$RPGDialog::CurrentQuestion@"/"@$RPGDialog::Questions);

      for(%i=1;%i<=$RPGDialog::Answer[$RPGDialog::CurrentQuestion+1,0];%i++)
      {
         (Answer@%i).delete();
         (Action@%i).delete();
         (editAnswer@%i@Button).delete();
         (moveAnswer@%i@UpButton).delete();
         (moveAnswer@%i@DownButton).delete();
      }

      for(%i=1;%i<=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0];%i++)
      {
         OptionsControl.add(new GuiMLTextCtrl(Answer@%i)
         {
            profile = "GuiMLTextEditProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "2 2";
            extent = "390 40";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            lineSpacing = "2";
            allowColorChars = "1";
            maxChars = "-1";
         });

         OptionsControl.add(new GuiMLTextCtrl(Action@%i)
         {
            profile = "GuiMLTextEditProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "400 2";
            extent = "300 40";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            lineSpacing = "2";
            allowColorChars = "1";
            maxChars = "-1";
         });
         
         OptionsControl.add(new GuiButtonCtrl(editAnswer@%i@Button)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "700 2";
            extent = "54 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Edit A."@%i;
            groupNum = "-1";
            buttonType = "PushButton";
            command = "EditAnswer("@%i@");";
         });
         OptionsControl.add(new GuiButtonCtrl(moveAnswer@%i@UpButton)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "700 17";
            extent = "21 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Up";
            groupNum = "-1";
            buttonType = "PushButton";
            command = "MoveAnswerUp("@%i@");";
         });
         if(%i==1)            
            (moveAnswer@%i@UpButton).setvisible(0);
         else
            (moveAnswer@%i@UpButton).setvisible(1);
         OptionsControl.add(new GuiButtonCtrl(moveAnswer@%i@DownButton)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "721 17";
            extent = "33 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Down";
            groupNum = "-1";
            buttonType = "PushButton";
            command = "MoveAnswerDown("@%i@");";
         });
         if(%i==$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0])            
            (moveAnswer@%i@DownButton).setvisible(0);
         else
            (moveAnswer@%i@DownButton).setvisible(1);               

         (Answer@%i).settext($RPGDialog::Answer[$RPGDialog::CurrentQuestion,%i]);
         (Action@%i).settext($RPGDialog::Action[$RPGDialog::CurrentQuestion,%i]);       
      }
      RefreshOptions();
   }
}

function GotoQuestion(%Question)
{
   if(%Question<=$RPGDialog::Questions && %Question>0)
   {
      for(%i=1;%i<=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0];%i++)
      {
         if((Answer@%i).extent!$="")
            (Answer@%i).delete();
         if((Action@%i).extent!$="")
            (Action@%i).delete();
         if((editAnswer@%i@Button).extent!$="")
            (editAnswer@%i@Button).delete();
         if((moveAnswer@%i@UpButton).extent!$="")
            (moveAnswer@%i@UpButton).delete();
         if((moveAnswer@%i@DownButton).extent!$="")            
            (moveAnswer@%i@DownButton).delete();            
      }
      
      $RPGDialog::CurrentQuestion=%Question;
      QuestionText.settext($RPGDialog::Question[$RPGDialog::CurrentQuestion]);
      TextQuestionNumber.settext("Question: "@$RPGDialog::CurrentQuestion@"/"@$RPGDialog::Questions);

      for(%i=1;%i<=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0];%i++)
      {
         OptionsControl.add(new GuiMLTextCtrl(Answer@%i)
         {
            profile = "GuiMLTextEditProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "2 2";
            extent = "390 40";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            lineSpacing = "2";
            allowColorChars = "1";
            maxChars = "-1";
         });

         OptionsControl.add(new GuiMLTextCtrl(Action@%i)
         {
            profile = "GuiMLTextEditProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "400 2";
            extent = "300 40";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            lineSpacing = "2";
            allowColorChars = "1";
            maxChars = "-1";
         });

         OptionsControl.add(new GuiButtonCtrl(editAnswer@%i@Button)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "700 2";
            extent = "54 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Edit A."@%i;
            groupNum = "-1";
            buttonType = "PushButton";
            command = "EditAnswer("@%i@");";
         });
         OptionsControl.add(new GuiButtonCtrl(moveAnswer@%i@UpButton)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "700 17";
            extent = "21 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Up";
            groupNum = "-1";
            buttonType = "PushButton";
            command = "MoveAnswerUp("@%i@");";
         });
         if(%i==1)            
            (moveAnswer@%i@UpButton).setvisible(0);
         else
            (moveAnswer@%i@UpButton).setvisible(1);
         OptionsControl.add(new GuiButtonCtrl(moveAnswer@%i@DownButton)
         {
            profile = "GuiButtonProfile";
            horizSizing = "right";
            vertSizing = "bottom";
            position = "721 17";
            extent = "33 15";
            minExtent = "8 2";
            visible = "1";
            helpTag = "0";
            text = "Down";
            groupNum = "-1";
            buttonType = "PushButton";
            command = "MoveAnswerDown("@%i@");";
         });
         if(%i==$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0])            
            (moveAnswer@%i@DownButton).setvisible(0);
         else
            (moveAnswer@%i@DownButton).setvisible(1);

         (Answer@%i).settext($RPGDialog::Answer[$RPGDialog::CurrentQuestion,%i]);
         (Action@%i).settext($RPGDialog::Action[$RPGDialog::CurrentQuestion,%i]);
      }
      RefreshOptions();
   }
}

function RefreshOptions()
{
   for(%i=1;%i<=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0];%i++)
   {
      %ActionText=(Action1).gettext();
      %ActionText=strReplace(%ActionText,"<END>","");  
      Action1.settext(%ActionText);           
      if(%i>1)
      {
         (Answer@%i).resize(2,
                            2+(restWords((Answer@(%i-1)).getPosition()))+42,
                            firstWord((Answer@%i).getExtent()),
                            restWords((Answer@%i).getExtent()));
         %ActionText=(Action@%i).gettext();
         %ActionText=strReplace(%ActionText,"<END>","");  
         (Action@%i).settext(%ActionText);                          
         (Action@%i).resize(400,
                            restWords((Answer@%i).getPosition()),
                            firstWord((Action@%i).getExtent()),
                            restWords((Action@%i).getExtent()));
                            
         (editAnswer@%i@Button).resize(700,
                                       restWords((Answer@%i).getPosition()),
                                       firstWord((editAnswer@%i@Button).getExtent()),
                                       restWords((editAnswer@%i@Button).getExtent()));
                                       
         (moveAnswer@%i@UpButton).resize(700,
                                       restWords((Answer@%i).getPosition())+17,
                                       firstWord((moveAnswer@%i@UpButton).getExtent()),
                                       restWords((moveAnswer@%i@UpButton).getExtent()));
                                       
         (moveAnswer@%i@DownButton).resize(721,
                                       restWords((Answer@%i).getPosition())+17,
                                       firstWord((moveAnswer@%i@DownButton).getExtent()),
                                       restWords((moveAnswer@%i@DownButton).getExtent()));                                       
      }

      OptionsControl.resize(firstWord(OptionsControl.getPosition()),
                            restWords(OptionsControl.getPosition()),
                            firstWord(OptionsControl.getExtent()),
                            restWords((moveAnswer@%i@DownButton).getPosition())+restWords((moveAnswer@%i@DownButton).GetExtent()));
   }
  (moveAnswer@$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0]@DownButton).setvisible(0);
}

function setDefaultQuestionPath(%Path)
{
   $RPGDialogEditorPref::QuestionPath=%path;
}

function setDefaultActionPath(%Path)
{
   $RPGDialogEditorPref::ActionPath=%path;
}

function savePrefs()
{
   echo("Exporting editor prefs");
   export("$RPGDialogEditorPref::*", "~/prefs.cs", False);
}

function editQuestion()
{
   if($RPGDialog::Questions>0)
   {
      QuestionEdit.settext($RPGDialog::Question[$RPGDialog::CurrentQuestion]);
      $RPGDialog::NewQuestion=false;
      PopulateSoundList($RPGDialog::QuestionSound[$RPGDialog::CurrentQuestion]);
      Canvas.setContent(EditQuestionGui);
   }
}

function newQuestion()
{
   QuestionEdit.settext("");
   $RPGDialog::NewQuestion=true;
   PopulateSoundList($RPGDialog::QuestionSound[$RPGDialog::CurrentQuestion]);
   Canvas.setContent(EditQuestionGui);
}

function newAnswer()
{
   if($RPGDialog::Questions>0)
   {
      AnswerEdit.settext("");
      ActionEdit.settext("");
      $RPGDialog::NewAnswer=true;
      Canvas.setContent(EditAnswerGui);
   }
}

function confirmQuestionEdit()
{
   if(!$RPGDialog::NewQuestion)
   {
      $RPGDialog::Question[$RPGDialog::CurrentQuestion]=QuestionEdit.gettext();
      QuestionText.settext($RPGDialog::Question[$RPGDialog::CurrentQuestion]);
      
      $RPGDialog::QuestionSound[$RPGDialog::CurrentQuestion]=QuestionEditSound.getValue();
      
      Canvas.setContent(MainEditorScreenGui);
   }
   else
   {
      $RPGDialog::Questions++;
      
      $RPGDialog::Question[$RPGDialog::Questions]=QuestionEdit.gettext();
      
      $RPGDialog::Answer[$RPGDialog::Questions,0]=1;
      $RPGDialog::Action[$RPGDialog::Questions,0]=1;
      
      $RPGDialog::Answer[$RPGDialog::Questions,1]="Continue...";
      $RPGDialog::Action[$RPGDialog::Questions,1]="CloseQuestion()";

      $RPGDialog::QuestionSound[$RPGDialog::CurrentQuestion]=QuestionEditSound.getValue();
      
      GotoQuestion($RPGDialog::Questions);
      Canvas.setContent(MainEditorScreenGui);
   }
   $RPGDialog::NewQuestion=false;
}

function cancelQuestionEdit()
{
   for(%i=1;%i<=$RPGDialog::QuestionLink[$RPGDialog::Questions+1,0];%i++)
   {
      $RPGDialog::QuestionLink[$RPGDialog::Questions+1,%i]="";
      $RPGDialog::QuestionLinkAction[$RPGDialog::Questions+1,%i]="";
   }
   $RPGDialog::QuestionLink[$RPGDialog::Questions+1,0]=0;
   $RPGDialog::QuestionLinkAction[$RPGDialog::Questions+1,0]=0;
   $RPGDialog::NewQuestion=false;
   Canvas.setContent(MainEditorScreenGui);
}

function deleteQuestion()
{
   if($RPGDialog::Questions>0)
   {
      $RPGDialog::Messages="";
      while($RPGDialog::Answer[$RPGDialog::CurrentQuestion,0]!=0)
      {
         deleteAnswer(1);
      }
   
      for(%i=1;%i<$RPGDialog::CurrentQuestion;%i++) //Process actions that are before the question being deleted and update them as necessary
      {
         for(%f=1;%f<=$RPGDialog::QuestionLink[%i,0];%f++)
         {
            $RPGDialog::QuestionLinkAction[%i,%f]=updateAction($RPGDialog::QuestionLinkAction[%i,%f],%i,"Question Link "@%f);
         }

         for(%f=1;%f<=$RPGDialog::Answer[%i,0];%f++)
         {
            $RPGDialog::Action[%i,%f]=updateAction($RPGDialog::Action[%i,%f],%i,"Answer "@%f);
         }
      }
   
      for(%i=$RPGDialog::CurrentQuestion;%i<$RPGDialog::Questions;%i++) //Now process the questions, answer and actions that are after the question being deleted, moving them to their new place and updating the actions as necessary.
      {
         $RPGDialog::Question[%i]=$RPGDialog::Question[%i+1];
         $RPGDialog::QuestionSound[%i]=$RPGDialog::QuestionSound[%i+1];
         $RPGDialog::QuestionLink[%i,0]=$RPGDialog::QuestionLink[%i+1];
         $RPGDialog::QuestionLinkAction[%i,0]=$RPGDialog::QuestionLink[%i+1];
         $RPGDialog::Answer[%i,0]=$RPGDialog::Answer[%i+1,0];
         $RPGDialog::Action[%i,0]=$RPGDialog::Action[%i+1,0];
      
         for(%f=1;%f<=$RPGDialog::Answer[%i,0];%f++)
         {
            $RPGDialog::Answer[%i,%f]=$RPGDialog::Answer[%i+1,%f];
            $RPGDialog::Action[%i,%f]=updateAction($RPGDialog::Action[%i+1,%f],%i,"Answer "@%f);
         }
      
         for(%f=1;%f<=$RPGDialog::QuestionLink[%i,0];%f++)
         {
            $RPGDialog::QuestionLink[%i,%f]=$RPGDialog::QuestionLink[%i+1,%f];
            $RPGDialog::QuestionLinkAction[%i,%f]=updateAction($RPGDialog::QuestionLinkAction[%i+1,%f],%i,"Question Link "@%f);
         }
      }
      $RPGDialog::Questions--;
   
      if($RPGDialog::CurrentQuestion>$RPGDialog::Questions)
         $RPGDialog::CurrentQuestion--;
      
      if($RPGDialog::Messages!$="")
         MessageBoxOK("Warning",$RPGDialog::Messages);
      
      GotoQuestion($RPGDialog::CurrentQuestion);
   }
}

function updateAction(%action,%currentQuestion,%currentAnswer)
{
   %command=getSubStr(%action,0,strPos(%action,"("));
   %args=getSubStr(%action,strPos(%action,"(")+1,strLen(%action));

   %i=1;
   while(%i<=1000) //just a max number of args to prevent the program from going into an infinite loop if something goes wrong.
   {
      if(strPos(%args,",")>=0)
      {
         %arg[%i]=getSubStr(%args,0,strPos(%args,","));
         %args=getSubStr(%args,strPos(%args,",")+1,strLen(%args));
      }
      else
      {
         %arg[%i]=getSubStr(%args,0,strPos(%args,")"));
         %arg[0]=%i; //use arg[0] to store how many args are avaible
         %i=1001;
      }
      %i++;
   }
   
   switch$(%command)
   {
      case "GotoQuestion":
         if(%arg[1]==$RPGDialog::CurrentQuestion)
         {
            %arg[1]="QUESTION DELETED";
            warn("Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!");
            $RPGDialog::Messages=$RPGDialog::Messages@"Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!\n";
         }
         else if(%arg[1]>%currentQuestion)
            %arg[1]--;

      case "ChangeStartQuestion":
         if(%arg[1]==$RPGDialog::CurrentQuestion)
         {
            %arg[1]="QUESTION DELETED";
            warn("Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!");
            $RPGDialog::Messages=$RPGDialog::Messages@"Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!\n";
         }
         else if(%arg[1]>%currentQuestion)
            %arg[1]--;

      case "ChangeStartQuestionAndOpen":
         if(%arg[1]==$RPGDialog::CurrentQuestion)
         {
            %arg[1]="QUESTION DELETED";
            warn("Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!");
            $RPGDialog::Messages=$RPGDialog::Messages@"Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!\n";
         }
         else if(%arg[1]>%currentQuestion)
            %arg[1]--;

      case "ChangeStartQuestionAndGoto":
         if(%arg[1]==$RPGDialog::CurrentQuestion)
         {
            %arg[1]="QUESTION DELETED";
            warn("Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!");
            $RPGDialog::Messages=$RPGDialog::Messages@"Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!\n";
         }
         else if(%arg[1]>%currentQuestion)
            %arg[1]--;
            
         if(%arg[2]==$RPGDialog::CurrentQuestion)
         {
            %arg[2]="QUESTION DELETED";
            warn("Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!");
            $RPGDialog::Messages=$RPGDialog::Messages@"Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!\n";
         }
         else if(%arg[2]>%currentQuestion)
            %arg[2]--;

      case "ChangePortraitAndGoto":
         if(%arg[2]==$RPGDialog::CurrentQuestion)
         {
            %arg[2]="QUESTION DELETED";
            warn("Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!");
            $RPGDialog::Messages=$RPGDialog::Messages@"Question "@%currentQuestion@"/"@%currentAnswer@" needs updating!\n";
         }
         else if(%arg[2]>%currentQuestion)
            %arg[2]--;
   }
   
   if(%arg[0]>0)
   {
      %args=%arg[1];
      for(%i=2;%i<=%arg[0];%i++)
      {
         %args=%args@","@%arg[%i];
      }
   }
   else
      %args="";
      
   return(%command@"("@%args@")");
}

function editAnswer(%answerNumber)
{
   %ActionText=$RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber];
   %ActionText=strReplace(%ActionText,"<END>","");
   AnswerEdit.settext($RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber]);
   ActionEdit.settext(%ActionText);
   $RPGDialog::EditAnswerNumber=%answerNumber;
   Canvas.setContent(EditAnswerGui);
}

function moveAnswerUp(%answerNumber)
{
   if(%answerNumber>1 && $RPGDialog::Answer[$RPGDialog::CurrentQuestion,0]>1)
   {
      %tempAnswer=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber];
      %tempAction=$RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber];
      
      $RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber]=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber-1];
      $RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber]=$RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber-1];
      
      $RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber-1]=%tempAnswer;
      $RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber-1]=%tempAction;

      (Answer@%answerNumber).settext($RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber]);
      (Action@%answerNumber).settext($RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber]);
      (Answer@%answerNumber-1).settext($RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber-1]);
      (Action@%answerNumber-1).settext($RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber-1]);
      RefreshOptions();
   }
}

function moveAnswerDown(%answerNumber)
{
   if(%answerNumber<$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0] && $RPGDialog::Answer[$RPGDialog::CurrentQuestion,0]>1)
   {
      %tempAnswer=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber];
      %tempAction=$RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber];
      
      $RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber]=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber+1];
      $RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber]=$RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber+1];
      
      $RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber+1]=%tempAnswer;
      $RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber+1]=%tempAction;
      
      (Answer@%answerNumber).settext($RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber]);
      (Action@%answerNumber).settext($RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber]);
      (Answer@%answerNumber+1).settext($RPGDialog::Answer[$RPGDialog::CurrentQuestion,%answerNumber+1]);
      (Action@%answerNumber+1).settext($RPGDialog::Action[$RPGDialog::CurrentQuestion,%answerNumber+1]);
      RefreshOptions();
   }
}

function editQuestionLink(%questionLinkNumber)
{
   AnswerEdit.settext($RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion,%questionLinkNumber]);
   ActionEdit.settext($RPGDialog::QuestionLinkAction[$RPGDialog::CurrentQuestion,%questionLinkNumber]);
   $RPGDialog::EditAnswerNumber="QL"@%questionLinkNumber;

   Canvas.setContent(EditAnswerGui);
}

function confirmAnswerEdit()
{
   %QuestionLinkCheck=getSubStr($RPGDialog::EditAnswerNumber,0,2);
   if(%QuestionLinkCheck$="QL")
   {
      if(AnswerEdit.gettext()!$="")
      {
         %QuestionLinkNumber=getSubStr($RPGDialog::EditAnswerNumber,2,strLen($RPGDialog::EditAnswerNumber));
         %questionText=strReplace(QuestionText.gettext(),$RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion,%questionLinkNumber],AnswerEdit.gettext());
         $RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion,%QuestionLinkNumber]=AnswerEdit.gettext();
         %ActionText=ActionEdit.getvalue();
         %ActionText=%ActionText@"<END>";                  
         $RPGDialog::QuestionLinkAction[$RPGDialog::CurrentQuestion,%QuestionLinkNumber]=%ActionText;
         $RPGDialog::Question[$RPGDialog::CurrentQuestion]=%questionText;
         QuestionText.setText(%questionText);
         GotoQuestion($RPGDialog::CurrentQuestion);
         Canvas.setContent(MainEditorScreenGui);
      }
      else //if new value is blank then delete question link
      {
         MessageBoxYesNo( "Delete Question Link", "Do you really want to delete this question link?", "deleteAnswer("@$RPGDialog::EditAnswerNumber@");", "");
      }
   }
   else
   {
      if(!$RPGDialog::NewAnswer)
      {
         if(AnswerEdit.gettext()!$="")
         {
            $RPGDialog::Answer[$RPGDialog::CurrentQuestion,$RPGDialog::EditAnswerNumber]=AnswerEdit.gettext();
            %ActionText=ActionEdit.getvalue();
            %ActionText=%ActionText@"<END>";
            $RPGDialog::Action[$RPGDialog::CurrentQuestion,$RPGDialog::EditAnswerNumber]=%ActionText;
            (Answer@$RPGDialog::EditAnswerNumber).settext($RPGDialog::Answer[$RPGDialog::CurrentQuestion,$RPGDialog::EditAnswerNumber]);
            (Action@$RPGDialog::EditAnswerNumber).settext($RPGDialog::Action[$RPGDialog::CurrentQuestion,$RPGDialog::EditAnswerNumber]);

            RefreshOptions();
            Canvas.setContent(MainEditorScreenGui);
         }
         else //if new value is blank then delete answer
         {
            MessageBoxYesNo( "Delete Answer", "Do you really want to delete this answer?", "deleteAnswer("@$RPGDialog::EditAnswerNumber@");", "");
         }
      }
      else
      {
         $RPGDialog::Answer[$RPGDialog::CurrentQuestion,0]++;
         $RPGDialog::Action[$RPGDialog::CurrentQuestion,0]++;

         $RPGDialog::Answer[$RPGDialog::CurrentQuestion,$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0]]=AnswerEdit.gettext();
         $RPGDialog::Action[$RPGDialog::CurrentQuestion,$RPGDialog::Action[$RPGDialog::CurrentQuestion,0]]=ActionEdit.getvalue();

         $RPGDialog::NewAnswer=false;

         GotoQuestion($RPGDialog::CurrentQuestion);
         Canvas.setContent(MainEditorScreenGui);
      }
   }
   $RPGDialog::EditAnswerNumber=0;
}

function deleteAnswer(%AnswerNumber)
{
   %QuestionLinkCheck=getSubStr(%AnswerNumber,0,2);
   if(%QuestionLinkCheck$="QL")
   {
      %QuestionLinkNumber=getSubStr(%AnswerNumber,2,strLen(%AnswerNumber));
      %QuestionLink=$RPGDialog::Question[$RPGDialog::CurrentQuestion];
      %QuestionLinkStart=strpos(%QuestionLink,"<a:RPGDialogLink "@%QuestionLinkNumber@">");
      %QuestionLink=getSubStr(%QuestionLink,%QuestionLinkStart,strlen(%QuestionLink));
      %QuestionLinkEnd=strpos(%QuestionLink,"</a>")+4;

      %Answer=getSubStr(%QuestionLink,0,%QuestionLinkEnd);
      %Question=strReplace($RPGDialog::Question[$RPGDialog::CurrentQuestion],%Answer,"");

      for(%i=%QuestionLinkNumber;%i<=$RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion,0];%i++)
      {
         $RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion,%i]=$RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion,%i+1];
         $RPGDialog::QuestionLinkAction[$RPGDialog::CurrentQuestion,%i]=$RPGDialog::QuestionLinkAction[$RPGDialog::CurrentQuestion,%i+1];
         %Question=strReplace(%Question,"<a:RPGDialogLink "@%i+1@">","<a:RPGDialogLink "@%i@">");
      }
      
      $RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion,0]--;
      $RPGDialog::QuestionLinkAction[$RPGDialog::CurrentQuestion,0]--;
      $RPGDialog::Question[$RPGDialog::CurrentQuestion]=%Question;
   }
   else
   {
      for(%i=%answerNumber;%i<$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0];%i++)
      {
         $RPGDialog::Answer[$RPGDialog::CurrentQuestion,%i]=$RPGDialog::Answer[$RPGDialog::CurrentQuestion,%i+1];
         $RPGDialog::Action[$RPGDialog::CurrentQuestion,%i]=$RPGDialog::Action[$RPGDialog::CurrentQuestion,%i+1];
      }
   
      (Answer@$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0]).delete();
      (Action@$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0]).delete();
      (editAnswer@$RPGDialog::Answer[$RPGDialog::CurrentQuestion,0]@Button).delete();
   
      $RPGDialog::Answer[$RPGDialog::CurrentQuestion,0]--;
      $RPGDialog::Action[$RPGDialog::CurrentQuestion,0]--;
   }
   RefreshOptions();
   Canvas.setContent(MainEditorScreenGui);
}

function PopulateActionList()
{
   %file = new FileObject();
   if(isfile($RPGDialogEditorPref::MainMod@"/server/scripts/core/RPGDialog.cs") && %file.openForRead($RPGDialogEditorPref::MainMod@"/server/scripts/core/RPGDialog.cs"))
   {
      while(!%file.isEOF())
      {
         %i++;
         %line=%file.readLine();
         if(strPos(%line,"//<ActionList>")>=0)
         {
            ActionList.addrow(%i,getSubStr(%line,14,strLen(%line)),%i);
         }
      }
   }
   %file.close();
   %file.delete();
}

function PopulateQuestionOptionsList()
{
   QuestionOptionsList.addrow(1,"<a:RPGDialogLink #>New Question Link</a>",1);
   QuestionOptionsList.addrow(2,"<<Name>>",2);
   QuestionOptionsList.addrow(3,"<<PlayerName>>",3);
}

function PopulateSoundList(%value)
{
   QuestionEditSound.clear();
   QuestionEditSound.add(%value,1);
   QuestionEditSound.setSelected(1);
   %file = new FileObject();
   if(isfile($RPGDialogEditorPref::MainMod@"/client/scripts/RPGDialogAudioProfiles.cs") && %file.openForRead($RPGDialogEditorPref::MainMod@"/client/scripts/RPGDialogAudioProfiles.cs"))
   {
      %i=2;
      while(!%file.isEOF())
      {
         %line=%file.readLine();
         if(strPos(%line,"new AudioProfile(")>=0)
         {
            %start=strPos(%line,"(")+1;
            %end=strPos(%line,")")-%start;
            QuestionEditSound.add(getSubStr(%line,%start,%end),%i);
         }
         %i++;
      }
   }
   %file.close();
   %file.delete();
}


function ActionList::onSelect(%this)
{
   %text=ActionEdit.getvalue()@%this.getRowTextById(%this.getSelectedID());
   ActionEdit.settext(%text);
}

function QuestionOptionsList::onSelect(%this)
{
   if(%this.getSelectedID()==1)
   {
      %text=%this.getRowTextById(%this.getSelectedID());
      if($RPGDialog::NewQuestion)
      {
         $RPGDialog::QuestionLink[$RPGDialog::Questions+1,0]++;
         $RPGDialog::QuestionLinkAction[$RPGDialog::Questions+1,0]++;
         $RPGDialog::QuestionLink[$RPGDialog::Questions+1,$RPGDialog::QuestionLink[$RPGDialog::Questions+1,0]]="New Question Link";
         $RPGDialog::QuestionLinkAction[$RPGDialog::Questions+1,$RPGDialog::QuestionLinkAction[$RPGDialog::Questions+1,0]]="CloseDialog()";
         %text=strReplace(%text,"#",$RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion+1,0]);
      }
      else
      {
         $RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion,0]++;
         $RPGDialog::QuestionLinkAction[$RPGDialog::CurrentQuestion,0]++;
         $RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion,$RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion,0]]="New Question Link";
         $RPGDialog::QuestionLinkAction[$RPGDialog::CurrentQuestion,$RPGDialog::QuestionLinkAction[$RPGDialog::CurrentQuestion,0]]="CloseDialog()";
         %text=strReplace(%text,"#",$RPGDialog::QuestionLink[$RPGDialog::CurrentQuestion,0]);
      }
      QuestionEdit.addtext(%text@" ",true);
      return;
   }
   %text=%this.getRowTextById(%this.getSelectedID());
   QuestionEdit.addtext(%text,true);
}

function initSetPaths()
{
   MainMod.setValue($RPGDialogEditorPref::mainMod);
   QuestionScriptPath.setValue($RPGDialogEditorPref::QuestionPath);
   ActionScriptPath.setValue($RPGDialogEditorPref::ActionPath);
   PortraitsPath.setValue($RPGDialogEditorPref::PortraitsPath);
   Canvas.pushDialog(SetPathsPopup);
}

function SetPaths()
{
   $RPGDialogEditorPref::mainMod=MainMod.getValue();
   $RPGDialogEditorPref::QuestionPath=QuestionScriptPath.getValue();
   $RPGDialogEditorPref::ActionPath=ActionScriptPath.getValue();
   $RPGDialogEditorPref::PortraitsPath=PortraitsPath.getValue();
   echo("Exporting RPGDialog editor prefs");
   export("$RPGDialogEditorPref::*", "~/RPGDialogEditor/prefs.cs", False);
   Canvas.popDialog(SetPathsPopup);
}
