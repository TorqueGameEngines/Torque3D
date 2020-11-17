using System;
using System.Linq;
using System.Runtime.InteropServices;
using T3DSharpFramework.Engine;
using T3DSharpFramework.Generated.Structs.Math;
using T3DSharpFramework.Interop;

namespace T3DSharpFramework.Generated.Structs.Global {

    /// 
    public class ByteRange : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;


        public ByteRange() { }

        public ByteRange(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public ByteRange(string s) {
            string[] strings = s.Split(' ');
        }

        public void Alloc() {
            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            return s.Substring(1);
        }
    }


    /// 
    public class Polyhedron : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(32)] public Point3FVector.InternalStruct pointList;
            [FieldOffset(0)] public PlaneFVector.InternalStruct planeList;
            [FieldOffset(64)] public EdgeVector.InternalStruct edgeList;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public Point3FVector PointList { get; set; }
        public PlaneFVector PlaneList { get; set; }
        public EdgeVector EdgeList { get; set; }

        public Polyhedron() { }

        public Polyhedron(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public Polyhedron(string s) {
            string[] strings = s.Split(' ');
            PointList = GenericMarshal.StringTo<Point3FVector>(string.Join(' ', strings.Skip(0).Take(3)));
            PlaneList = GenericMarshal.StringTo<PlaneFVector>(string.Join(' ', strings.Skip(3).Take(3)));
            EdgeList = GenericMarshal.StringTo<EdgeVector>(string.Join(' ', strings.Skip(6).Take(3)));
        }

        public void Alloc() {
            PointList.Alloc();
            internalStruct.pointList = PointList.internalStruct;

            PlaneList.Alloc();
            internalStruct.planeList = PlaneList.internalStruct;

            EdgeList.Alloc();
            internalStruct.edgeList = EdgeList.internalStruct;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            PointList?.Free();
            PointList = new Point3FVector(internalStruct.pointList);

            PlaneList?.Free();
            PlaneList = new PlaneFVector(internalStruct.planeList);

            EdgeList?.Free();
            EdgeList = new EdgeVector(internalStruct.edgeList);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(PointList);
            s += " " + GenericMarshal.ToString(PlaneList);
            s += " " + GenericMarshal.ToString(EdgeList);
            return s.Substring(1);
        }
    }


    /// 
    public class StringVector : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public uint elementCount;
            [FieldOffset(4)] public uint arraySize;
            [FieldOffset(8)] public IntPtr array;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public uint ElementCount { get; set; }
        public uint ArraySize { get; set; }
        public string[] Array { get; set; }

        public StringVector() { }

        public StringVector(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public StringVector(string s) {
            string[] strings = s.Split(' ');
            ElementCount = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(0).Take(1)));
            ArraySize = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(1).Take(1)));
            Array = GenericMarshal.StringTo<string[]>(string.Join(' ', strings.Skip(2).Take(1)));
        }

        public void Alloc() {
            internalStruct.elementCount = ElementCount;

            internalStruct.arraySize = ArraySize;

            internalStruct.array = GenericMarshal.ToPtr(Array);

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            ElementCount = internalStruct.elementCount;

            ArraySize = internalStruct.arraySize;

            Array = GenericMarshal.FromPtr<string>(internalStruct.array, ElementCount, true);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(ElementCount);
            s += " " + GenericMarshal.ToString(ArraySize);
            s += " " + GenericMarshal.ToString(Array);
            return s.Substring(1);
        }
    }


    /// 
    public class EdgeVector : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public uint elementCount;
            [FieldOffset(4)] public uint arraySize;
            [FieldOffset(8)] public IntPtr array;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public uint ElementCount { get; set; }
        public uint ArraySize { get; set; }
        public Edge[] Array { get; set; }

        public EdgeVector() { }

        public EdgeVector(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public EdgeVector(string s) {
            string[] strings = s.Split(' ');
            ElementCount = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(0).Take(1)));
            ArraySize = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(1).Take(1)));
            Array = GenericMarshal.StringTo<Edge[]>(string.Join(' ', strings.Skip(2).Take(1)));
        }

        public void Alloc() {
            internalStruct.elementCount = ElementCount;

            internalStruct.arraySize = ArraySize;

            internalStruct.array = GenericMarshal.ToPtr(Array);

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            ElementCount = internalStruct.elementCount;

            ArraySize = internalStruct.arraySize;

            Array = GenericMarshal.FromPtr<Edge>(internalStruct.array, ElementCount, true);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(ElementCount);
            s += " " + GenericMarshal.ToString(ArraySize);
            s += " " + GenericMarshal.ToString(Array);
            return s.Substring(1);
        }
    }


    /// 
    public class PlaneFVector : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public uint elementCount;
            [FieldOffset(4)] public uint arraySize;
            [FieldOffset(8)] public IntPtr array;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public uint ElementCount { get; set; }
        public uint ArraySize { get; set; }
        public PlaneF[] Array { get; set; }

        public PlaneFVector() { }

        public PlaneFVector(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public PlaneFVector(string s) {
            string[] strings = s.Split(' ');
            ElementCount = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(0).Take(1)));
            ArraySize = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(1).Take(1)));
            Array = GenericMarshal.StringTo<PlaneF[]>(string.Join(' ', strings.Skip(2).Take(1)));
        }

        public void Alloc() {
            internalStruct.elementCount = ElementCount;

            internalStruct.arraySize = ArraySize;

            internalStruct.array = GenericMarshal.ToPtr(Array);

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            ElementCount = internalStruct.elementCount;

            ArraySize = internalStruct.arraySize;

            Array = GenericMarshal.FromPtr<PlaneF>(internalStruct.array, ElementCount, true);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(ElementCount);
            s += " " + GenericMarshal.ToString(ArraySize);
            s += " " + GenericMarshal.ToString(Array);
            return s.Substring(1);
        }
    }


    /// 
    public class Point3FVector : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public uint elementCount;
            [FieldOffset(4)] public uint arraySize;
            [FieldOffset(8)] public IntPtr array;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public uint ElementCount { get; set; }
        public uint ArraySize { get; set; }
        public Point3F[] Array { get; set; }

        public Point3FVector() { }

        public Point3FVector(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public Point3FVector(string s) {
            string[] strings = s.Split(' ');
            ElementCount = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(0).Take(1)));
            ArraySize = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(1).Take(1)));
            Array = GenericMarshal.StringTo<Point3F[]>(string.Join(' ', strings.Skip(2).Take(1)));
        }

        public void Alloc() {
            internalStruct.elementCount = ElementCount;

            internalStruct.arraySize = ArraySize;

            internalStruct.array = GenericMarshal.ToPtr(Array);

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            ElementCount = internalStruct.elementCount;

            ArraySize = internalStruct.arraySize;

            Array = GenericMarshal.FromPtr<Point3F>(internalStruct.array, ElementCount, true);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(ElementCount);
            s += " " + GenericMarshal.ToString(ArraySize);
            s += " " + GenericMarshal.ToString(Array);
            return s.Substring(1);
        }
    }


    /// 
    public class FloatVector : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public uint elementCount;
            [FieldOffset(4)] public uint arraySize;
            [FieldOffset(8)] public IntPtr array;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public uint ElementCount { get; set; }
        public uint ArraySize { get; set; }
        public float[] Array { get; set; }

        public FloatVector() { }

        public FloatVector(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public FloatVector(string s) {
            string[] strings = s.Split(' ');
            ElementCount = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(0).Take(1)));
            ArraySize = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(1).Take(1)));
            Array = GenericMarshal.StringTo<float[]>(string.Join(' ', strings.Skip(2).Take(1)));
        }

        public void Alloc() {
            internalStruct.elementCount = ElementCount;

            internalStruct.arraySize = ArraySize;

            internalStruct.array = GenericMarshal.ToPtr(Array);

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            ElementCount = internalStruct.elementCount;

            ArraySize = internalStruct.arraySize;

            Array = GenericMarshal.FromPtr<float>(internalStruct.array, ElementCount, true);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(ElementCount);
            s += " " + GenericMarshal.ToString(ArraySize);
            s += " " + GenericMarshal.ToString(Array);
            return s.Substring(1);
        }
    }


    /// 
    public class IntVector : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public uint elementCount;
            [FieldOffset(4)] public uint arraySize;
            [FieldOffset(8)] public IntPtr array;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public uint ElementCount { get; set; }
        public uint ArraySize { get; set; }
        public int[] Array { get; set; }

        public IntVector() { }

        public IntVector(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public IntVector(string s) {
            string[] strings = s.Split(' ');
            ElementCount = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(0).Take(1)));
            ArraySize = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(1).Take(1)));
            Array = GenericMarshal.StringTo<int[]>(string.Join(' ', strings.Skip(2).Take(1)));
        }

        public void Alloc() {
            internalStruct.elementCount = ElementCount;

            internalStruct.arraySize = ArraySize;

            internalStruct.array = GenericMarshal.ToPtr(Array);

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            ElementCount = internalStruct.elementCount;

            ArraySize = internalStruct.arraySize;

            Array = GenericMarshal.FromPtr<int>(internalStruct.array, ElementCount, true);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(ElementCount);
            s += " " + GenericMarshal.ToString(ArraySize);
            s += " " + GenericMarshal.ToString(Array);
            return s.Substring(1);
        }
    }


    /// 
    public class BoolVector : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public uint elementCount;
            [FieldOffset(4)] public uint arraySize;
            [FieldOffset(8)] public IntPtr array;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public uint ElementCount { get; set; }
        public uint ArraySize { get; set; }
        public bool[] Array { get; set; }

        public BoolVector() { }

        public BoolVector(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public BoolVector(string s) {
            string[] strings = s.Split(' ');
            ElementCount = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(0).Take(1)));
            ArraySize = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(1).Take(1)));
            Array = GenericMarshal.StringTo<bool[]>(string.Join(' ', strings.Skip(2).Take(1)));
        }

        public void Alloc() {
            internalStruct.elementCount = ElementCount;

            internalStruct.arraySize = ArraySize;

            internalStruct.array = GenericMarshal.ToPtr(Array);

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            ElementCount = internalStruct.elementCount;

            ArraySize = internalStruct.arraySize;

            Array = GenericMarshal.FromPtr<bool>(internalStruct.array, ElementCount, true);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(ElementCount);
            s += " " + GenericMarshal.ToString(ArraySize);
            s += " " + GenericMarshal.ToString(Array);
            return s.Substring(1);
        }
    }


    /// <description>
    /// RGBA color quadruple in 32bit floating-point precision per channel.
    /// </description>
    public class LinearColorF : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public float red;
            [FieldOffset(4)] public float green;
            [FieldOffset(8)] public float blue;
            [FieldOffset(12)] public float alpha;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public float Red { get; set; }
        public float Green { get; set; }
        public float Blue { get; set; }
        public float Alpha { get; set; }

        public LinearColorF() { }

        public LinearColorF(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public LinearColorF(string s) {
            string[] strings = s.Split(' ');
            Red = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(0).Take(1)));
            Green = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(1).Take(1)));
            Blue = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(2).Take(1)));
            Alpha = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(3).Take(1)));
        }

        public void Alloc() {
            internalStruct.red = Red;

            internalStruct.green = Green;

            internalStruct.blue = Blue;

            internalStruct.alpha = Alpha;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            Red = internalStruct.red;

            Green = internalStruct.green;

            Blue = internalStruct.blue;

            Alpha = internalStruct.alpha;

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(Red);
            s += " " + GenericMarshal.ToString(Green);
            s += " " + GenericMarshal.ToString(Blue);
            s += " " + GenericMarshal.ToString(Alpha);
            return s.Substring(1);
        }
    }


    /// <description>
    /// RGBA color quadruple in 8bit integer precision per channel.
    /// </description>
    public class ColorI : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public byte red;
            [FieldOffset(1)] public byte green;
            [FieldOffset(2)] public byte blue;
            [FieldOffset(3)] public byte alpha;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public byte Red { get; set; }
        public byte Green { get; set; }
        public byte Blue { get; set; }
        public byte Alpha { get; set; }

        public ColorI() { }

        public ColorI(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public ColorI(string s) {
            string[] strings = s.Split(' ');
            Red = GenericMarshal.StringTo<byte>(string.Join(' ', strings.Skip(0).Take(1)));
            Green = GenericMarshal.StringTo<byte>(string.Join(' ', strings.Skip(1).Take(1)));
            Blue = GenericMarshal.StringTo<byte>(string.Join(' ', strings.Skip(2).Take(1)));
            Alpha = GenericMarshal.StringTo<byte>(string.Join(' ', strings.Skip(3).Take(1)));
        }

        public void Alloc() {
            internalStruct.red = Red;

            internalStruct.green = Green;

            internalStruct.blue = Blue;

            internalStruct.alpha = Alpha;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            Red = internalStruct.red;

            Green = internalStruct.green;

            Blue = internalStruct.blue;

            Alpha = internalStruct.alpha;

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(Red);
            s += " " + GenericMarshal.ToString(Green);
            s += " " + GenericMarshal.ToString(Blue);
            s += " " + GenericMarshal.ToString(Alpha);
            return s.Substring(1);
        }
    }


    /// 
    public class UUID : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public uint a;
            [FieldOffset(4)] public ushort b;
            [FieldOffset(6)] public ushort c;
            [FieldOffset(8)] public byte d;
            [FieldOffset(9)] public byte e;
            [FieldOffset(10)] public IntPtr f;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public uint A { get; set; }
        public ushort B { get; set; }
        public ushort C { get; set; }
        public byte D { get; set; }
        public byte E { get; set; }
        public byte[] F { get; set; }

        public UUID() { }

        public UUID(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public UUID(string s) {
            string[] strings = s.Split(' ');
            A = GenericMarshal.StringTo<uint>(string.Join(' ', strings.Skip(0).Take(1)));
            B = GenericMarshal.StringTo<ushort>(string.Join(' ', strings.Skip(1).Take(1)));
            C = GenericMarshal.StringTo<ushort>(string.Join(' ', strings.Skip(2).Take(1)));
            D = GenericMarshal.StringTo<byte>(string.Join(' ', strings.Skip(3).Take(1)));
            E = GenericMarshal.StringTo<byte>(string.Join(' ', strings.Skip(4).Take(1)));
            F = GenericMarshal.StringTo<byte[]>(string.Join(' ', strings.Skip(5).Take(1)));
        }

        public void Alloc() {
            internalStruct.a = A;

            internalStruct.b = B;

            internalStruct.c = C;

            internalStruct.d = D;

            internalStruct.e = E;

            internalStruct.f = GenericMarshal.ToPtr(F);

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            A = internalStruct.a;

            B = internalStruct.b;

            C = internalStruct.c;

            D = internalStruct.d;

            E = internalStruct.e;

            F = GenericMarshal.FromPtr<byte>(internalStruct.f, 6, true);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(A);
            s += " " + GenericMarshal.ToString(B);
            s += " " + GenericMarshal.ToString(C);
            s += " " + GenericMarshal.ToString(D);
            s += " " + GenericMarshal.ToString(E);
            s += " " + GenericMarshal.ToString(F);
            return s.Substring(1);
        }
    }


    /// 
    public class Edge : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public IntPtr face;
            [FieldOffset(8)] public IntPtr vertex;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public uint[] Face { get; set; }
        public uint[] Vertex { get; set; }

        public Edge() { }

        public Edge(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public Edge(string s) {
            string[] strings = s.Split(' ');
            Face = GenericMarshal.StringTo<uint[]>(string.Join(' ', strings.Skip(0).Take(1)));
            Vertex = GenericMarshal.StringTo<uint[]>(string.Join(' ', strings.Skip(1).Take(1)));
        }

        public void Alloc() {
            internalStruct.face = GenericMarshal.ToPtr(Face);

            internalStruct.vertex = GenericMarshal.ToPtr(Vertex);

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            Face = GenericMarshal.FromPtr<uint>(internalStruct.face, 2, true);

            Vertex = GenericMarshal.FromPtr<uint>(internalStruct.vertex, 2, true);

            if (internalStructPtr != IntPtr.Zero) {
                StructMarshal.FreeStructPtr<InternalStruct>(internalStructPtr);
            }
            internalStructPtr = IntPtr.Zero;
        }

        public override string ToString() {
            string s = "";
            s += " " + GenericMarshal.ToString(Face);
            s += " " + GenericMarshal.ToString(Vertex);
            return s.Substring(1);
        }
    }


    /// 
    public class PlaneF : IEngineStruct {
        [StructLayout(LayoutKind.Explicit)]
        public struct InternalStruct {
            [FieldOffset(0)] public float x;
            [FieldOffset(4)] public float y;
            [FieldOffset(8)] public float z;
            [FieldOffset(12)] public float d;
        }

        public InternalStruct internalStruct;

        public IntPtr internalStructPtr;

        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }
        public float D { get; set; }

        public PlaneF() { }

        public PlaneF(InternalStruct data) {
            internalStruct = data;
			Free();
        }

        public PlaneF(string s) {
            string[] strings = s.Split(' ');
            X = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(0).Take(1)));
            Y = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(1).Take(1)));
            Z = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(2).Take(1)));
            D = GenericMarshal.StringTo<float>(string.Join(' ', strings.Skip(3).Take(1)));
        }

        public void Alloc() {
            internalStruct.x = X;

            internalStruct.y = Y;

            internalStruct.z = Z;

            internalStruct.d = D;

            internalStructPtr = StructMarshal.StructToIntPtr(internalStruct);
        }

        public void Free() {
            X = internalStruct.x;

            Y = internalStruct.y;

            Z = internalStruct.z;

            D = internalStruct.d;

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
            s += " " + GenericMarshal.ToString(D);
            return s.Substring(1);
        }
    }
}
