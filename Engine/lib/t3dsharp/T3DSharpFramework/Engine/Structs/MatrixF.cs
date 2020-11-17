namespace T3DSharpFramework.Engine.Structs
{
    public class MatrixF : Generated.Structs.Math.MatrixF
    {
        public MatrixF(string s)
            :base(s) {
        }

        public MatrixF(Point3F pos)
        {
            M = new float[16];

            M[0] = pos.X;
            M[4] = pos.Y;
            M[8] = pos.Z;
            M[12] = 1.0f;
        }
    }
}
