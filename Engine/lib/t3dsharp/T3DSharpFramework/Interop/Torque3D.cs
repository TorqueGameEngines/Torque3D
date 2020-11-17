using System;
using System.IO;
using System.Runtime.InteropServices;
using T3DSharpFramework.Engine;

namespace T3DSharpFramework.Interop
{
    public static class Torque3D
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate string CallFunction(
            IntPtr nameSpace, IntPtr name, IntPtr argv, int argc, [MarshalAs(UnmanagedType.I1)] out bool result);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate string CallMethod(IntPtr className
            , IntPtr classNamespace
            , uint obj
            , IntPtr name
            , IntPtr argv
            , int argc
            , [MarshalAs(UnmanagedType.I1)] out bool result);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate bool IsMethod(IntPtr className, IntPtr methodName);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void MainEntryPoint();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int TorqueMain(int pArgc, string[] pArgv, IntPtr pHInstance);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate bool torque_engineinit(int argc, string[] argv);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int torque_enginetick();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int torque_getreturnstatus();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate bool torque_engineshutdown();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SetCallbacks(
            IntPtr pFunctionPtr, IntPtr pMethodPtr, IntPtr pIsMethodPtr, IntPtr pMainPtr);

        public static string LibraryName;
        public static IntPtr Torque3DLibHandle;
        public static IDllLoadUtils DllLoadUtils;

        public static void Initialize(string[] args, Libraries libraryNames) {
            DllLoadUtils = Platform.IsLinux()
                ? (IDllLoadUtils) new DllLoadUtilsLinux()
                : new DllLoadUtilsWindows();

            string platformMain;
            if (Platform.IsLinux()) {
                //platformMain = "torque_unixmain";
                platformMain = "TorqueMain";
                LibraryName = IntPtr.Size == 8 ? libraryNames.Linux64bit : libraryNames.Linux32bit;
            }
            else if (Platform.IsOSX()) {
                //platformMain = "torque_macmain";
                platformMain = "TorqueMain";
                LibraryName = IntPtr.Size == 8 ? libraryNames.OSX64bit : libraryNames.OSX32bit;
            }
            else {
                //platformMain = "torque_winmain";
                platformMain = "TorqueMain";
                LibraryName = IntPtr.Size == 8 ? libraryNames.Windows64bit : libraryNames.Windows32bit;
            }

            Torque3DLibHandle = DllLoadUtils.LoadLibrary(LibraryName);
            if (Torque3DLibHandle == IntPtr.Zero) {
                throw new Exception("Unable to load " + (IntPtr.Size == 8 ? "64" : "32") + " bit dll: " + LibraryName + ", in directory: " + Directory.GetCurrentDirectory());
            }

            var mainHandle = DllLoadUtils.GetProcAddress(Torque3DLibHandle, platformMain);
            var setCallbacksHandle = DllLoadUtils.GetProcAddress(Torque3DLibHandle, "SetCallbacks");
            var engineInitHandle = DllLoadUtils.GetProcAddress(Torque3DLibHandle, "torque_engineinit");
            var engineTickHandle = DllLoadUtils.GetProcAddress(Torque3DLibHandle, "torque_enginetick");
            var getReturnStatusHandle = DllLoadUtils.GetProcAddress(Torque3DLibHandle, "torque_getreturnstatus");
            var engineShutdownHandle = DllLoadUtils.GetProcAddress(Torque3DLibHandle, "torque_engineshutdown");

            var setCallbacks = (SetCallbacks) Marshal.GetDelegateForFunctionPointer(
                setCallbacksHandle, typeof(SetCallbacks));

            //var main = (TorqueMain)Marshal.GetDelegateForFunctionPointer(
            //   mainHandle, typeof(TorqueMain));

            var engineInit = (torque_engineinit) Marshal.GetDelegateForFunctionPointer(
                engineInitHandle, typeof(torque_engineinit));

            var engineTick = (torque_enginetick) Marshal.GetDelegateForFunctionPointer(
                engineTickHandle, typeof(torque_enginetick));

            //var engineGetReturnStatus = (torque_getreturnstatus)Marshal.GetDelegateForFunctionPointer(
            //   getReturnStatusHandle, typeof(torque_getreturnstatus));

            var engineShutdown = (torque_engineshutdown) Marshal.GetDelegateForFunctionPointer(
                engineShutdownHandle, typeof(torque_engineshutdown));

            CallFunction callDelegate = CallFunctionDelegate;
            CallMethod methodDelegate = CallMethodDelegate;
            IsMethod isMethodDelegate = IsMethodDelegate;
            IntPtr mainEntryPointPtr = IntPtr.Zero;
            if (Initializer.GetScriptEntry() != null)
                mainEntryPointPtr =
                    Marshal.GetFunctionPointerForDelegate(
                        (MainEntryPoint) Initializer.GetScriptEntry().CreateDelegate(typeof(MainEntryPoint)));

            setCallbacks(Marshal.GetFunctionPointerForDelegate(callDelegate)
                , Marshal.GetFunctionPointerForDelegate(methodDelegate)
                , Marshal.GetFunctionPointerForDelegate(isMethodDelegate)
                , mainEntryPointPtr);

            if (!engineInit(args.Length, args)) return;

            while (engineTick() > 0) {
            }

            SimDictionary.Shutdown();

            engineShutdown();

            SimDictionary.Shutdown();

            DllLoadUtils.FreeLibrary(Torque3DLibHandle);
        }

        public static string CallFunctionDelegate(IntPtr nameSpace, IntPtr name, IntPtr argv, int argc,
            out bool result) {
            string _nameSpace = Marshal.PtrToStringAnsi(nameSpace);
            string _name = Marshal.PtrToStringAnsi(name);
            string[] strings = null;
            if (argv != IntPtr.Zero)
                strings = StringMarshal.IntPtrToAnsiStringArray(argv, argc);
            return EngineCallbacks.CallScriptFunction(_nameSpace, _name, strings, out result);
        }

        public static string CallMethodDelegate(IntPtr className, IntPtr classNamespace, uint obj, IntPtr name,
            IntPtr argv, int argc,
            out bool result) {
            string _className = Marshal.PtrToStringAnsi(className);
            string _classNamespace = Marshal.PtrToStringAnsi(classNamespace);
            string _name = Marshal.PtrToStringAnsi(name);

            UnknownSimObject objectBaseWrapper = Sim.FindObjectById<UnknownSimObject>(obj);
            string[] strings = { };
            if (argv != IntPtr.Zero)
                strings = StringMarshal.IntPtrToAnsiStringArray(argv, argc);
            string strRes = EngineCallbacks.CallScriptMethod(_className, _classNamespace, objectBaseWrapper, _name, strings,
                out result);
            return strRes;
        }

        public static bool IsMethodDelegate(IntPtr className, IntPtr methodName) {
            string _className = Marshal.PtrToStringAnsi(className);
            string _methodName = Marshal.PtrToStringAnsi(methodName);
            return EngineCallbacks.IsMethod(_className, _methodName);
        }

        public struct Libraries
        {
            public string Linux32bit;
            public string Linux64bit;
            public string Windows32bit;
            public string Windows64bit;
            public string OSX32bit;
            public string OSX64bit;
        }
    }
}
