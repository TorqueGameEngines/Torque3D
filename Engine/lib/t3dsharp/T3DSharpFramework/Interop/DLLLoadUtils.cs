using System;
using System.Runtime.InteropServices;

namespace T3DSharpFramework.Interop
{
    public interface IDllLoadUtils
    {
        IntPtr LoadLibrary(string fileName);
        void FreeLibrary(IntPtr handle);
        IntPtr GetProcAddress(IntPtr dllHandle, string name);
    }

    public static class Platform
    {
        public static bool IsLinux() {
            var p = (int) Environment.OSVersion.Platform;
            return (p == 4) || (p == 6) || (p == 128);
        }

        public static bool IsOSX() {
            return false;
        }
    }

    public class DllLoadUtilsWindows : IDllLoadUtils
    {
        void IDllLoadUtils.FreeLibrary(IntPtr handle) {
            FreeLibrary(handle);
        }

        IntPtr IDllLoadUtils.GetProcAddress(IntPtr dllHandle, string name) {
            return GetProcAddress(dllHandle, name);
        }

        IntPtr IDllLoadUtils.LoadLibrary(string fileName) {
            return LoadLibrary(fileName);
        }

        [DllImport("kernel32")]
        private static extern IntPtr LoadLibrary(string fileName);

        [DllImport("kernel32.dll")]
        private static extern int FreeLibrary(IntPtr handle);

        [DllImport("kernel32.dll")]
        private static extern IntPtr GetProcAddress(IntPtr handle, string procedureName);
    }

    internal class DllLoadUtilsLinux : IDllLoadUtils
    {
        public IntPtr LoadLibrary(string fileName) {
            return dlopen(fileName, RTLD_NOW);
        }

        public void FreeLibrary(IntPtr handle) {
            dlclose(handle);
        }

        public IntPtr GetProcAddress(IntPtr dllHandle, string name) {
            // clear previous errors if any
            dlerror();
            var res = dlsym(dllHandle, name);
            var errPtr = dlerror();
            if (errPtr != IntPtr.Zero) {
                throw new Exception("dlsym: " + Marshal.PtrToStringAnsi(errPtr));
            }

            return res;
        }

        const int RTLD_NOW = 2;

        [DllImport("libdl.so")]
        private static extern IntPtr dlopen(String fileName, int flags);

        [DllImport("libdl.so")]
        private static extern IntPtr dlsym(IntPtr handle, String symbol);

        [DllImport("libdl.so")]
        private static extern int dlclose(IntPtr handle);

        [DllImport("libdl.so")]
        private static extern IntPtr dlerror();
    }
}
