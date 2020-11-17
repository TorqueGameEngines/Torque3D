namespace T3DSharpGenerator.Model
{
    public class EnginePrimitive : IEngineObject
    {
        public EnginePrimitive(string name) {
            Name = name;
        }
        
        public string Name { get; set; }
        public string Docs { get; set; }
        public string Scope { get; set; }
        public string Size { get; set; }
        
        public string ManagedType { get; set; }
        public string NativeReturnType { get; set; }
        public string NativeArgType { get; set; }

        public override string ToString() {
            return $"{Name} - {Docs}";
        }
    }
}