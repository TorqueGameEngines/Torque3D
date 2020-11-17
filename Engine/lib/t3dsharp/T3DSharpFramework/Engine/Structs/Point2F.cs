namespace T3DSharpFramework.Engine.Structs
{
    public class Point2F : Generated.Structs.Math.Point2F
    {
        public Point2F(string s)
            : base(s) {

        }

        public Point2F(float x, float y)
        {
            X = x;
            Y = y;
        }

        public static Point2F Zero = new Point2F(0, 0);
    }
}
