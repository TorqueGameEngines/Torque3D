namespace T3DSharpFramework.Engine.Structs
{
    public class RectF : Generated.Structs.Math.RectF
    {
        public RectF(string s)
            : base(s) {
        }

        public RectF(float x, float y, float width, float height)
        {
            Point = new Point2F(x, y);
            Extent = new Point2F(width, height);
        }

        public static RectF Zero = new RectF(0.0f, 0.0f, 0.0f, 0.0f);
    }
}
