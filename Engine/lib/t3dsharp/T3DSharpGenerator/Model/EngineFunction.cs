using System.Collections.Generic;

namespace T3DSharpGenerator.Model
{
    public class EngineFunction
    {
        public string Name { get; set; }
        public string Docs { get; set; }
        public string Scope { get; set; }
        public bool IsCallback { get; set; }
        public bool IsVariadic { get; set; }
        public bool IsStatic { get; set; }
        public bool IsOverride { get; set; }
        public IEngineObject ReturnType { get; set; }
        public string ReturnTypeName { get; set; }
        public string Symbol { get; set; }
        public List<Argument> Arguments { get; set; }

        public EngineFunction(string name) {
            Arguments = new List<Argument>();

            Name = name;
            
            // Default to static.
            IsStatic = true;
        }

        public class Argument
        {
            public string Name { get; set; }
            public IEngineObject Type { get; set; }
            public string TypeName { get; set; }
            public string DefaultValue { get; set; }
            public bool IsVariadic { get; set; }
            public int Offset { get; set; }
        }

        public void Add(Argument arg) {
            Arguments.Add(arg);
        }
    }
}