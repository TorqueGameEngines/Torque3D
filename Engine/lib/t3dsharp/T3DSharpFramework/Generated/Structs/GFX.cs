using System;
using System.Linq;
using System.Runtime.InteropServices;
using T3DSharpFramework.Engine;
using T3DSharpFramework.Generated.Structs.Math;
using T3DSharpFramework.Interop;

namespace T3DSharpFramework.Generated.Structs.GFX {

    /// <description>
    /// Descriptor for a specific video mode.
    /// </description>
    public class GFXVideoMode : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public Point2I.InternalStruct resolution;
            [FieldOffset(8)] public uint bitDepth;
            [FieldOffset(12)] public uint refreshRate;
            [FieldOffset(16)] public bool fullScreen;
            [FieldOffset(17)] public bool wideScreen;
            [FieldOffset(20)] public uint antialiasLevel;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public Point2I Resolution { get; set; }
        public uint BitDepth { get; set; }
        public uint RefreshRate { get; set; }
        public bool FullScreen { get; set; }
        public bool WideScreen { get; set; }
        public uint AntialiasLevel { get; set; }

        public GFXVideoMode() { }

        public GFXVideoMode(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public GFXVideoMode(string s) {
            string[] strings = s.Split(' ');
            Resolution = GenericMarshal.StringTo<Point2I>(string.Join(' ', strings.Skip(0).Take(2)));
            BitDepth = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(2).Take(1)));
            RefreshRate = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(3).Take(1)));
            FullScreen = GenericMarshal.StringTo<bool>(string.Join(' ', strings.Skip(4).Take(1)));
            WideScreen = GenericMarshal.StringTo<bool>(string.Join(' ', strings.Skip(5).Take(1)));
            AntialiasLevel = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(6).Take(1)));
        }

        public void Alloc() {
            Resolution.Alloc();
            internalStruct.resolution = Resolution.internalStruct;

            internalStruct.bitDepth = BitDepth;

            internalStruct.refreshRate = RefreshRate;

            internalStruct.fullScreen = FullScreen;

            internalStruct.wideScreen = WideScreen;

            internalStruct.antialiasLevel = AntialiasLevel;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            Resolution?.Free();
            Resolution = new Point2I(internalStruct.resolution);

            BitDepth = internalStruct.bitDepth;

            RefreshRate = internalStruct.refreshRate;

            FullScreen = internalStruct.fullScreen;

            WideScreen = internalStruct.wideScreen;

            AntialiasLevel = internalStruct.antialiasLevel;

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(Resolution);
            s += " " + GenericMarshal.ToString(BitDepth);
            s += " " + GenericMarshal.ToString(RefreshRate);
            s += " " + GenericMarshal.ToString(FullScreen);
            s += " " + GenericMarshal.ToString(WideScreen);
            s += " " + GenericMarshal.ToString(AntialiasLevel);
            return s.Substring(1);
        }
    }
}
