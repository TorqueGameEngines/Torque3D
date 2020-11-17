using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace T3DSharpFramework.Engine.Structs
{
    public class LinearColorF : Generated.Structs.Global.LinearColorF
    {

        public LinearColorF(string s)
            : base(s) {
        }

        public LinearColorF(float r, float g, float b, float a = 1.0f)
        {
            Red = r;
            Green = g;
            Blue = b;
            Alpha = a;
        }

        public static LinearColorF WHITE = new LinearColorF(1.0f, 1.0f, 1.0f);
    }
}
