using System.Collections.Generic;

namespace T3DSharpGenerator.Model
{
    public class EngineClass : IEngineObject
    {
        public string Name { get; set; }
        public string ManagedType { get; set; }
        public string NativeReturnType { get; set; }
        public string NativeArgType { get; set; }
        public string Docs { get; set; }
        public IEngineObject SuperType { get; set; }
        public string SuperTypeName { get; set; }
        public bool IsAbstract { get; set; }
        public bool IsInstantiable { get; set; }
        public bool IsDisposable { get; set; }
        public bool IsSingleton { get; set; }
        public bool IsDatablock { get; set; }
        public bool IsSimObject { get; set; }
        public string Scope { get; set; }
        public List<Property> Properties { get; set; }
        public List<EngineFunction> Methods { get; set; }

        public EngineClass(string name) {
            Properties = new List<Property>();
            Methods = new List<EngineFunction>();

            Name = name;
            ManagedType = Name;
            NativeReturnType = "IntPtr";
            NativeArgType = "IntPtr";
        }
        
        public class Property
        {
            public string Name { get; set; }
            public string Docs { get; set; }
            public IEngineObject Type { get; set; }
            public int IndexedSize { get; set; }
            public string TypeName { get; set; }
            public string Group { get; set; }
            public string IsConstant { get; set; }
            public string IsTransient { get; set; }
            public string IsVisible { get; set; }

            public override bool Equals(object obj) {
                bool equals = true;
                if (!(obj is Property property)) {
                    return false;
                }

                equals &= Name.Equals(property.Name);
                return equals;
            }
        }

        public void Add(Property property) {
            Properties.Add(property);
        }

        public void Add(EngineFunction engineFunction) {
            Methods.Add(engineFunction);
        }

        public object ToLiquid() {
            return new {
                Name = Name,
                Docs = Docs,
                SuperType = SuperType,
                Scope = (string.IsNullOrEmpty(Scope) ? "Global" : Scope),
                IsAbstract = IsAbstract,
                IsDisposable = IsDisposable,
                IsInstantiable = IsInstantiable,
                IsSingleton = IsSingleton,
                IsSimObject = IsSimObject,
                IsDatablock = IsDatablock,
                
                Methods = Methods,
                Properties = Properties,
                
                ManagedType = ManagedType,
                NativeArgType = NativeArgType,
                NativeReturnType = NativeReturnType
            };
        }
    }
}