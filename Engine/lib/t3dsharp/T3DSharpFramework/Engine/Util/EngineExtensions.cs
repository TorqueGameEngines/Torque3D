using System;
using T3DSharpFramework.Generated.Functions;
using T3DSharpFramework.Generated.Structs.Math;

namespace T3DSharpFramework.Engine.Util
{
    public static class EngineExtensions
    {
        public static string Tag(this String str)
        {
            return Global.AddTaggedString(str);
        }
        public static string Detag(this String str)
        {
            return Global.Detag(str);
        }
        public static string OrDefault(this String str, string defaultValue)
        {
            return string.IsNullOrWhiteSpace(str) ? defaultValue : str;
        }

        public static string ColorEscape(this String str)
        {
            for (int i = 0; i < 10; i++)
            {
                str = str.Replace("\\c" + i, System.Text.Encoding.UTF8.GetString(new[] { Text.COLOR[i] }));
            }
            str = str.Replace("\\cp", System.Text.Encoding.UTF8.GetString(new[] { Text.COLOR_PUSH }));
            str = str.Replace("\\co", System.Text.Encoding.UTF8.GetString(new[] { Text.COLOR_POP }));
            str = str.Replace("\\cr", System.Text.Encoding.UTF8.GetString(new[] { Text.COLOR_RESET }));
            return str;
        }

        public static MatrixF ToMatrix(this Point3F point) {
           var matrixF = new MatrixF();

           matrixF.M = new float[16];

           matrixF.M[0] = point.X;
           matrixF.M[4] = point.Y;
           matrixF.M[8] = point.Z;
           matrixF.M[12] = 1.0f;
           return matrixF;
        }
    }
}
