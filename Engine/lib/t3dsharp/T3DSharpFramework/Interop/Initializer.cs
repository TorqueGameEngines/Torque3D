using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

namespace T3DSharpFramework.Interop
{
    public class Initializer
    {
        private static MethodInfo mScriptEntryPointMethodInfo = null;

        public static MethodInfo GetScriptEntry() {
            return mScriptEntryPointMethodInfo;
        }

        public static void InitializeTypeDictionaries(string path) {
            Assembly assembly = Assembly.LoadFrom(path);
            InitializeTypeDictionaries(assembly.GetTypes());
        }

        public static void InitializeTypeDictionaries(IEnumerable<Type> types) {
            foreach (Type type in types) {
                IEnumerable<ConsoleClassAttribute> attributes =
                    type.GetCustomAttributes<ConsoleClassAttribute>(false);
                if (attributes.Any()) {
                    EngineCallbacks.RegisterType(attributes.First().ConsoleName ?? type.Name, type);
                }

                foreach (MethodInfo methodInfo in type.GetMethods()) {
                    IEnumerable<ConsoleFunctionAttribute> functionAttributes =
                        methodInfo.GetCustomAttributes<ConsoleFunctionAttribute>(false);
                    if (functionAttributes.Any())
                        EngineCallbacks.RegisterFunction(functionAttributes.First().FunctionName ?? methodInfo.Name,
                            methodInfo);

                    IEnumerable<ScriptEntryPoint> entryAttribute =
                        methodInfo.GetCustomAttributes<ScriptEntryPoint>(false);

                    if (!entryAttribute.Any()) continue;

                    if (methodInfo.IsStatic && !methodInfo.GetParameters().Any() &&
                        methodInfo.ReturnType == typeof(void)) {
                        mScriptEntryPointMethodInfo = methodInfo;
                    }
                    else {
                        Console.WriteLine("ScriptEntry method: " + methodInfo.Name +
                                          " did not match the necessary signature.");
                    }
                }
            }
        }
    }
}
