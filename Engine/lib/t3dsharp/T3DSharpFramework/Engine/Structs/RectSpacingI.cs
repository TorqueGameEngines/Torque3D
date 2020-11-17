namespace T3DSharpFramework.Engine.Structs
{
    public class RectSpacingI : Generated.Structs.Gui.RectSpacingI
    {
        public RectSpacingI(string s)
            : base(s) {
        }

        public RectSpacingI(int leftPadding, int rightPadding, int topPadding, int bottomPadding)
        {
            LeftPadding = leftPadding;
            RightPadding = rightPadding;
            TopPadding = topPadding;
            BottomPadding = bottomPadding;
        }
    }
}
