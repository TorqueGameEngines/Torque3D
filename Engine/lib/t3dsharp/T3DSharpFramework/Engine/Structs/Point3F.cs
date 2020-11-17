namespace T3DSharpFramework.Engine.Structs
{
    public class Point3F : Generated.Structs.Math.Point3F
    {
        public Point3F(string s)
            : base(s) {
        }

        public Point3F(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public static implicit operator MatrixF(Point3F p)
        {
            return new MatrixF(p);
        }

        public static implicit operator Generated.Structs.Math.MatrixF(Point3F p)
        {
            return new MatrixF(p);
        }

        public static Point3F Zero = new Point3F(0.0f, 0.0f, 0.0f);
    }
}
