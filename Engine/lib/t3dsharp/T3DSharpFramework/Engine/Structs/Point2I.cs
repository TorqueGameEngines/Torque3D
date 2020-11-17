namespace T3DSharpFramework.Engine.Structs
{
    public class Point2I : Generated.Structs.Math.Point2I
    {
        public Point2I(string s)
            : base(s) {

        }

        public Point2I(int x, int y)
        {
            X = x;
            Y = y;
        }

        public static Point2I Zero = new Point2I(0, 0);
    }
}
