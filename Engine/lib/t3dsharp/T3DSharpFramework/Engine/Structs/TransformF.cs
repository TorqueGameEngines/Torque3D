namespace T3DSharpFramework.Engine.Structs
{
    public class TransformF : Generated.Structs.Math.TransformF
    {
        public TransformF(string s)
            : base(s)
        {
        }

        public TransformF(Point3F pos, AngAxisF orientation, bool hasRotation = true)
        {
            Position = pos;
            Orientation = orientation;
            HasRotation = hasRotation;
        }

        public TransformF(Generated.Structs.Math.TransformF transformF) {
            
        }
    }
}
