using System;
using System.Linq;
using System.Runtime.InteropServices;
using T3DSharpFramework.Engine;
using T3DSharpFramework.Generated.Structs.Math;
using T3DSharpFramework.Interop;

namespace T3DSharpFramework.Generated.Structs.Math {

    /// 
    public class RotationF : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public float x;
            [FieldOffset(4)] public float y;
            [FieldOffset(8)] public float z;
            [FieldOffset(12)] public float w;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }
        public float W { get; set; }

        public RotationF() { }

        public RotationF(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public RotationF(string s) {
            string[] strings = s.Split(' ');
            X = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(0).Take(1)));
            Y = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(1).Take(1)));
            Z = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(2).Take(1)));
            W = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(3).Take(1)));
        }

        public void Alloc() {
            internalStruct.x = X;

            internalStruct.y = Y;

            internalStruct.z = Z;

            internalStruct.w = W;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            X = internalStruct.x;

            Y = internalStruct.y;

            Z = internalStruct.z;

            W = internalStruct.w;

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(X);
            s += " " + GenericMarshal.ToString(Y);
            s += " " + GenericMarshal.ToString(Z);
            s += " " + GenericMarshal.ToString(W);
            return s.Substring(1);
        }
    }


    /// 
    public class EaseF : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public int dir;
            [FieldOffset(4)] public int type;
            [FieldOffset(8)] public IntPtr param;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public int Dir { get; set; }
        public int Type { get; set; }
        public float[] Param { get; set; }

        public EaseF() { }

        public EaseF(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public EaseF(string s) {
            string[] strings = s.Split(' ');
            Dir = GenericMarshal.StringTo<int>(string.Join(' ', strings.Skip(0).Take(1)));
            Type = GenericMarshal.StringTo<int>(string.Join(' ', strings.Skip(1).Take(1)));
            Param = GenericMarshal.StringTo<float[]>(string.Join(' ', strings.Skip(2).Take(1)));
        }

        public void Alloc() {
            internalStruct.dir = Dir;

            internalStruct.type = Type;

            internalStruct.param = GenericMarshal.ToPtr(Param);

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            Dir = internalStruct.dir;

            Type = internalStruct.type;

            Param = GenericMarshal.FromPtr<float>(internalStruct.param, 2, true);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(Dir);
            s += " " + GenericMarshal.ToString(Type);
            s += " " + GenericMarshal.ToString(Param);
            return s.Substring(1);
        }
    }


    /// 
    public class Box3F : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public Point3F.InternalStruct minExtents;
            [FieldOffset(12)] public Point3F.InternalStruct maxExtents;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public Point3F MinExtents { get; set; }
        public Point3F MaxExtents { get; set; }

        public Box3F() { }

        public Box3F(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public Box3F(string s) {
            string[] strings = s.Split(' ');
            MinExtents = GenericMarshal.StringTo<Point3F>(string.Join(' ', strings.Skip(0).Take(3)));
            MaxExtents = GenericMarshal.StringTo<Point3F>(string.Join(' ', strings.Skip(3).Take(3)));
        }

        public void Alloc() {
            MinExtents.Alloc();
            internalStruct.minExtents = MinExtents.internalStruct;

            MaxExtents.Alloc();
            internalStruct.maxExtents = MaxExtents.internalStruct;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            MinExtents?.Free();
            MinExtents = new Point3F(internalStruct.minExtents);

            MaxExtents?.Free();
            MaxExtents = new Point3F(internalStruct.maxExtents);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(MinExtents);
            s += " " + GenericMarshal.ToString(MaxExtents);
            return s.Substring(1);
        }
    }


    /// 
    public class TransformF : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public Point3F.InternalStruct position;
            [FieldOffset(12)] public AngAxisF.InternalStruct orientation;
            [FieldOffset(28)] public bool hasRotation;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public Point3F Position { get; set; }
        public AngAxisF Orientation { get; set; }
        public bool HasRotation { get; set; }

        public TransformF() { }

        public TransformF(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public TransformF(string s) {
            string[] strings = s.Split(' ');
            Position = GenericMarshal.StringTo<Point3F>(string.Join(' ', strings.Skip(0).Take(3)));
            Orientation = GenericMarshal.StringTo<AngAxisF>(string.Join(' ', strings.Skip(3).Take(4)));
            HasRotation = GenericMarshal.StringTo<bool>(string.Join(' ', strings.Skip(7).Take(1)));
        }

        public void Alloc() {
            Position.Alloc();
            internalStruct.position = Position.internalStruct;

            Orientation.Alloc();
            internalStruct.orientation = Orientation.internalStruct;

            internalStruct.hasRotation = HasRotation;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            Position?.Free();
            Position = new Point3F(internalStruct.position);

            Orientation?.Free();
            Orientation = new AngAxisF(internalStruct.orientation);

            HasRotation = internalStruct.hasRotation;

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(Position);
            s += " " + GenericMarshal.ToString(Orientation);
            s += " " + GenericMarshal.ToString(HasRotation);
            return s.Substring(1);
        }
    }


    /// 
    public class AngAxisF : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public Point3F.InternalStruct axis;
            [FieldOffset(12)] public float angle;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public Point3F Axis { get; set; }
        public float Angle { get; set; }

        public AngAxisF() { }

        public AngAxisF(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public AngAxisF(string s) {
            string[] strings = s.Split(' ');
            Axis = GenericMarshal.StringTo<Point3F>(string.Join(' ', strings.Skip(0).Take(3)));
            Angle = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(3).Take(1)));
        }

        public void Alloc() {
            Axis.Alloc();
            internalStruct.axis = Axis.internalStruct;

            internalStruct.angle = Angle;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            Axis?.Free();
            Axis = new Point3F(internalStruct.axis);

            Angle = internalStruct.angle;

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(Axis);
            s += " " + GenericMarshal.ToString(Angle);
            return s.Substring(1);
        }
    }


    /// 
    public class MatrixF : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public IntPtr m;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public float[] M { get; set; }

        public MatrixF() { }

        public MatrixF(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public MatrixF(string s) {
            string[] strings = s.Split(' ');
            M = GenericMarshal.StringTo<float[]>(string.Join(' ', strings.Skip(0).Take(1)));
        }

        public void Alloc() {
            internalStruct.m = GenericMarshal.ToPtr(M);

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            M = GenericMarshal.FromPtr<float>(internalStruct.m, 16, true);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(M);
            return s.Substring(1);
        }
    }


    /// 
    public class RectF : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public Point2F.InternalStruct point;
            [FieldOffset(8)] public Point2F.InternalStruct extent;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public Point2F Point { get; set; }
        public Point2F Extent { get; set; }

        public RectF() { }

        public RectF(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public RectF(string s) {
            string[] strings = s.Split(' ');
            Point = GenericMarshal.StringTo<Point2F>(string.Join(' ', strings.Skip(0).Take(2)));
            Extent = GenericMarshal.StringTo<Point2F>(string.Join(' ', strings.Skip(2).Take(2)));
        }

        public void Alloc() {
            Point.Alloc();
            internalStruct.point = Point.internalStruct;

            Extent.Alloc();
            internalStruct.extent = Extent.internalStruct;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            Point?.Free();
            Point = new Point2F(internalStruct.point);

            Extent?.Free();
            Extent = new Point2F(internalStruct.extent);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(Point);
            s += " " + GenericMarshal.ToString(Extent);
            return s.Substring(1);
        }
    }


    /// 
    public class RectI : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public Point2I.InternalStruct point;
            [FieldOffset(8)] public Point2I.InternalStruct extent;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public Point2I Point { get; set; }
        public Point2I Extent { get; set; }

        public RectI() { }

        public RectI(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public RectI(string s) {
            string[] strings = s.Split(' ');
            Point = GenericMarshal.StringTo<Point2I>(string.Join(' ', strings.Skip(0).Take(2)));
            Extent = GenericMarshal.StringTo<Point2I>(string.Join(' ', strings.Skip(2).Take(2)));
        }

        public void Alloc() {
            Point.Alloc();
            internalStruct.point = Point.internalStruct;

            Extent.Alloc();
            internalStruct.extent = Extent.internalStruct;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            Point?.Free();
            Point = new Point2I(internalStruct.point);

            Extent?.Free();
            Extent = new Point2I(internalStruct.extent);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(Point);
            s += " " + GenericMarshal.ToString(Extent);
            return s.Substring(1);
        }
    }


    /// 
    public class Point4F : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public float x;
            [FieldOffset(4)] public float y;
            [FieldOffset(8)] public float z;
            [FieldOffset(12)] public float w;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }
        public float W { get; set; }

        public Point4F() { }

        public Point4F(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public Point4F(string s) {
            string[] strings = s.Split(' ');
            X = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(0).Take(1)));
            Y = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(1).Take(1)));
            Z = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(2).Take(1)));
            W = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(3).Take(1)));
        }

        public void Alloc() {
            internalStruct.x = X;

            internalStruct.y = Y;

            internalStruct.z = Z;

            internalStruct.w = W;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            X = internalStruct.x;

            Y = internalStruct.y;

            Z = internalStruct.z;

            W = internalStruct.w;

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(X);
            s += " " + GenericMarshal.ToString(Y);
            s += " " + GenericMarshal.ToString(Z);
            s += " " + GenericMarshal.ToString(W);
            return s.Substring(1);
        }
    }


    /// 
    public class Point3F : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public float x;
            [FieldOffset(4)] public float y;
            [FieldOffset(8)] public float z;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }

        public Point3F() { }

        public Point3F(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public Point3F(string s) {
            string[] strings = s.Split(' ');
            X = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(0).Take(1)));
            Y = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(1).Take(1)));
            Z = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(2).Take(1)));
        }

        public void Alloc() {
            internalStruct.x = X;

            internalStruct.y = Y;

            internalStruct.z = Z;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            X = internalStruct.x;

            Y = internalStruct.y;

            Z = internalStruct.z;

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(X);
            s += " " + GenericMarshal.ToString(Y);
            s += " " + GenericMarshal.ToString(Z);
            return s.Substring(1);
        }
    }


    /// 
    public class Point3I : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public int x;
            [FieldOffset(4)] public int y;
            [FieldOffset(8)] public int z;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public int X { get; set; }
        public int Y { get; set; }
        public int Z { get; set; }

        public Point3I() { }

        public Point3I(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public Point3I(string s) {
            string[] strings = s.Split(' ');
            X = GenericMarshal.StringTo<int>(string.Join(' ', strings.Skip(0).Take(1)));
            Y = GenericMarshal.StringTo<int>(string.Join(' ', strings.Skip(1).Take(1)));
            Z = GenericMarshal.StringTo<int>(string.Join(' ', strings.Skip(2).Take(1)));
        }

        public void Alloc() {
            internalStruct.x = X;

            internalStruct.y = Y;

            internalStruct.z = Z;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            X = internalStruct.x;

            Y = internalStruct.y;

            Z = internalStruct.z;

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(X);
            s += " " + GenericMarshal.ToString(Y);
            s += " " + GenericMarshal.ToString(Z);
            return s.Substring(1);
        }
    }


    /// 
    public class Point2F : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public float x;
            [FieldOffset(4)] public float y;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public float X { get; set; }
        public float Y { get; set; }

        public Point2F() { }

        public Point2F(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public Point2F(string s) {
            string[] strings = s.Split(' ');
            X = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(0).Take(1)));
            Y = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(1).Take(1)));
        }

        public void Alloc() {
            internalStruct.x = X;

            internalStruct.y = Y;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            X = internalStruct.x;

            Y = internalStruct.y;

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(X);
            s += " " + GenericMarshal.ToString(Y);
            return s.Substring(1);
        }
    }


    /// 
    public class Point2I : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public int x;
            [FieldOffset(4)] public int y;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public int X { get; set; }
        public int Y { get; set; }

        public Point2I() { }

        public Point2I(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public Point2I(string s) {
            string[] strings = s.Split(' ');
            X = GenericMarshal.StringTo<int>(string.Join(' ', strings.Skip(0).Take(1)));
            Y = GenericMarshal.StringTo<int>(string.Join(' ', strings.Skip(1).Take(1)));
        }

        public void Alloc() {
            internalStruct.x = X;

            internalStruct.y = Y;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            X = internalStruct.x;

            Y = internalStruct.y;

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(X);
            s += " " + GenericMarshal.ToString(Y);
            return s.Substring(1);
        }
    }
}
