using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace T3DSharpFramework.Engine.Structs
{
    public class ColorI : Generated.Structs.Global.ColorI
    {
        private ColorI()
        {
        }

        public ColorI(string s)
            : base(s)
        {
        }

        public ColorI(byte r, byte g, byte b, byte a = 255)
        {
            Red = r;
            Green = g;
            Blue = b;
            Alpha = a;
        }

        public ColorI(int r, int g, int b, int a = 255)
        {
            Red = (byte) r;
            Green = (byte) g;
            Blue = (byte) b;
            Alpha = (byte) a;
        }

        public static ColorI WHITE = new ColorI(255, 255, 255);
        public static ColorI BLACK = new ColorI(0, 0, 0);
    }
}
