using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using T3DSharpFramework.Engine;

namespace T3DSharpFramework.Interop
{
    internal class EngineCallbacks {
        private static BindingFlags bindingFlags =
            BindingFlags.Default | BindingFlags.Public | BindingFlags.Instance | BindingFlags.Static |
            BindingFlags.IgnoreCase;

        private static readonly Dictionary<string, Type>
            ClassTypeDictionary = new Dictionary<string, Type>(StringComparer.OrdinalIgnoreCase);

        private static readonly Dictionary<string, MethodInfo>
            FunctionDictionary = new Dictionary<string, MethodInfo>(StringComparer.OrdinalIgnoreCase);

        public static void RegisterType(string className, Type classType) {
            ClassTypeDictionary.Add(className, classType);
        }

        public static void RegisterFunction(string functionName, MethodInfo methodInfo) {
            FunctionDictionary.Add(functionName, methodInfo);
        }

        public static void Clear() {
            ClassTypeDictionary.Clear();
            FunctionDictionary.Clear();
        }

        public static Type GetObjectType(string className, string classNamespace, ISimObject objectBaseWrapper) {
            string objectName = objectBaseWrapper?.GetName();
            if (objectName != null && ClassTypeDictionary.ContainsKey(objectName)) {
                return ClassTypeDictionary[objectName];
            }

            if (classNamespace != null && ClassTypeDictionary.ContainsKey(classNamespace)) {
                return ClassTypeDictionary[classNamespace];
            }

            if (className != null && ClassTypeDictionary.ContainsKey(className)) {
                return ClassTypeDictionary[className];
            }

            if (objectName != null && SimDictionary.Find(objectName) != null) {
                return SimDictionary.Find(objectName).GetType();
            }

            if (objectBaseWrapper != null && SimDictionary.Find(objectBaseWrapper.GetId()) != null) {
                return SimDictionary.Find(objectBaseWrapper.GetId()).GetType();
            }

            if (objectBaseWrapper != null && ClassTypeDictionary.ContainsKey(objectBaseWrapper.GetType().Name)) {
                return ClassTypeDictionary[objectBaseWrapper.GetType().Name];
            }

            return null;
        }

        public static string CallScriptFunction(string pFunctionNamespace, string pFunctionName, object[] args,
            out bool found) {
            if (pFunctionNamespace != null) {
                ISimObject obj = Sim.FindObjectByName<UnknownSimObject>(pFunctionNamespace);
                Type type = GetObjectType(null, pFunctionNamespace, obj);

                if (type == null) {
                    found = false;
                    return null;
                }

                return CallNamespaceMethod(type, obj, pFunctionName, args, out found);
            }

            if (!FunctionDictionary.ContainsKey(pFunctionName)) {
                found = false;
                return null;
            }

            found = true;
            MethodInfo methodInfo = FunctionDictionary[pFunctionName];

            return InvokeMethod(methodInfo, null, args, out found);
        }

        public static string CallScriptMethod(string className, string classNamespace, ISimObject objectBaseWrapper,
            string methodName, object[] args, out bool found) {
            Type type = GetObjectType(className, classNamespace, objectBaseWrapper);

            if (type == null) {
                found = false;
                return null;
            }

            return CallNamespaceMethod(type, objectBaseWrapper, methodName, args, out found);
        }

        private static string CallNamespaceMethod(Type namespaceClass, ISimObject objectBaseWrapper, string methodName,
            object[] args, out bool found) {
            // TODO: Ensure callbackMethod is most recent override of method. (e.g. GameConnection re-defining delete)
            MethodInfo callbackMethod = namespaceClass
                .GetMethods(bindingFlags)
                .FirstOrDefault(x => x.Name.ToLowerInvariant().Equals(methodName.ToLowerInvariant()));
            if (callbackMethod != null) {
                ISimObject simObj = null;
                if (!callbackMethod.IsStatic)
                    simObj = (ISimObject) SimDictionary.CreateInstance(namespaceClass, objectBaseWrapper);
                return InvokeMethod(callbackMethod, simObj, args, out found);
            }

            found = false;
            return null;
        }

        private static string InvokeMethod(MethodInfo callbackMethod, ISimObject obj, object[] args, out bool found) {
            if (obj != null
                && !callbackMethod.DeclaringType.GetCustomAttributes<ConsoleClassAttribute>().Any()) {
                found = false;
                return null;
            }

            ParameterInfo[] parameterInfos = callbackMethod.GetParameters();
            object[] _args = new object[parameterInfos.Length];
            for (int i = 0; i < _args.Length; i++) {
                if (parameterInfos[i].GetCustomAttributes(typeof(ParamArrayAttribute), false).Length > 0) {
                    string[] parms = new string[Math.Max(args.Length - i, 0)];
                    for (int j = 0; j < args.Length - i; j++) {
                        parms[j] = (string) args[i + j];
                    }

                    _args[i] = parms;
                    break;
                }

                if (i < args.Length) {
                    _args[i] = ConvertArgFromString(parameterInfos[i].ParameterType, (string) args[i]);
                }
                else if (parameterInfos[i].HasDefaultValue) _args[i] = parameterInfos[i].DefaultValue;
                else throw new ArgumentException("Not enough arguments provided");
            }

            found = true;

            if (callbackMethod.ReturnType == typeof(bool))
                return (bool) callbackMethod.Invoke(obj, _args) ? "1" : "0";
            if (callbackMethod.ReturnType == typeof(string))
                return (string) callbackMethod.Invoke(obj, _args);
            else if (callbackMethod.ReturnType != typeof(void))
                return callbackMethod.Invoke(obj, _args).ToString();
            callbackMethod.Invoke(obj, _args);
            return null;
        }

        private static object ConvertArgFromString(Type objType, string obj) {
            if (typeof(ISimObject).IsAssignableFrom(objType)) {
                return Sim.FindObject<UnknownSimObject>(obj).As(objType);
            }

            if (objType == typeof(int)) return int.Parse(obj);
            if (objType == typeof(uint)) return uint.Parse(obj);
            if (objType == typeof(float)) return float.Parse(obj);
            if (objType == typeof(double)) return double.Parse(obj);
            if (objType == typeof(bool)) return GenericMarshal.StringToBool(obj);
            if (objType.IsEnum) {
                if (string.IsNullOrEmpty(obj)) {
                    return Enum.Parse(objType, "0", true);
                }

                return Enum.Parse(objType, obj, true);
            }

            ConstructorInfo cinfo = objType.GetConstructor(new[] {typeof(string)});
            if (cinfo != null) return cinfo.Invoke(new object[] {obj});

            return obj;
        }

        public static bool IsMethod(string className, string methodName) {
            if (className == null)
                return FunctionDictionary.ContainsKey(methodName);

            UnknownSimObject obj = Sim.FindObjectByName<UnknownSimObject>(className);

            if (obj == null) {
                if (!ClassTypeDictionary.ContainsKey(className)) {
                    return false;
                }

                MethodInfo method = ClassTypeDictionary[className]
                    .GetMethod(methodName, bindingFlags);
                return method != null && method.DeclaringType.GetCustomAttributes<ConsoleClassAttribute>().Any();
            }

            Type type = GetObjectType(obj.GetClassName(), obj.GetClassNamespace(), obj);

            return type != null &&
                   type.GetMethod(methodName, bindingFlags) !=
                   null;
        }
    }
}
