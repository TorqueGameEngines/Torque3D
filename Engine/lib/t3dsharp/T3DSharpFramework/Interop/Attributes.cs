using System;

namespace T3DSharpFramework.Interop
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ConsoleClassAttribute : Attribute
    {
        public string ConsoleName { get; private set; }

        public ConsoleClassAttribute(string pConsoleName = null) {
            ConsoleName = pConsoleName;
        }
    }

    [AttributeUsage(AttributeTargets.Method)]
    public class ConsoleFunctionAttribute : Attribute
    {
        public string FunctionName { get; private set; }

        public ConsoleFunctionAttribute(string pFunctionName = null) {
            FunctionName = pFunctionName;
        }
    }

    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptEntryPoint : Attribute
    {
    }
}
