using System;
using System.Runtime.InteropServices;
using T3DSharpFramework.Interop;

namespace T3DSharpFramework.Engine
{
    public class UnknownSimObject : ConsoleObjectBase, ISimObject
    {
        public void SetPointerFromObject(ISimObject pObj)
        {
            if (!SimDictionary.Contains(pObj)) SimDictionary.RegisterObject(pObj);
            ObjectPtr = pObj.ObjectPtr;
        }

        public T As<T>() where T : class, ISimObject
        {
            return (T)SimDictionary.CreateInstance(typeof(T), this);
        }

        public ISimObject As(Type t)
        {
            if (!typeof(ISimObject).IsAssignableFrom(t)) return null;
            return (ISimObject)SimDictionary.CreateInstance(t, this);
        }

        public string Name { get => GetName(); set => throw new NotImplementedException(); }

        public bool RegisterObject()
        {
            throw new NotImplementedException();
        }

        /// <description>
        /// Return the value of the given field on this object.
        /// </description>
        /// <param name="fieldName">The name of the field.  If it includes a field index, the index is parsed out.</param>
        /// <param name="index">Optional parameter to specify the index of an array field separately.</param>
        /// <returns>The value of the given field or "" if undefined.</returns>
        public string GetFieldValue(string fieldName, int index = -1)
        {
            InternalUnsafeMethods.GetFieldValue__Args _args = new InternalUnsafeMethods.GetFieldValue__Args()
            {
                fieldName = fieldName,
                index = index,
            };
            IntPtr _engineResult = InternalUnsafeMethods.GetFieldValue()(ObjectPtr, _args);
            return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Set the value of the given field on this object.
        /// </description>
        /// <param name="fieldName">The name of the field to assign to.  If it includes an array index, the index will be parsed out.</param>
        /// <param name="value">The new value to assign to the field.</param>
        /// <param name="index">Optional argument to specify an index for an array field.</param>
        /// <returns>True.</returns>
        public bool SetFieldValue(string fieldName, string value, int index = -1)
        {
            InternalUnsafeMethods.SetFieldValue__Args _args = new InternalUnsafeMethods.SetFieldValue__Args()
            {
                fieldName = fieldName,
                value = value,
                index = index,
            };
            bool _engineResult = InternalUnsafeMethods.SetFieldValue()(ObjectPtr, _args);
            return _engineResult;
        }

        /// <description>
        /// Get the name of the class namespace assigned to this object.
        /// </description>
        /// <returns>The name of the 'class' namespace.</returns>
        public string GetClassNamespace()
        {
            InternalUnsafeMethods.GetClassNamespace__Args _args = new InternalUnsafeMethods.GetClassNamespace__Args() {
            };
            IntPtr _engineResult = InternalUnsafeMethods.GetClassNamespace()(ObjectPtr, _args);
            return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the name of the C++ class which the object is an instance of.
        /// </description>
        /// <returns>The name of the C++ class of the object.</returns>
        public string GetClassName() {
             InternalUnsafeMethods.GetClassName__Args _args = new InternalUnsafeMethods.GetClassName__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetClassName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the global name of the object.
        /// </description>
        /// <returns>The global name assigned to the object.</returns>
        public string GetName() {
             InternalUnsafeMethods.GetName__Args _args = new InternalUnsafeMethods.GetName__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the underlying unique numeric ID of the object.
        /// </description>
        /// <remarks> Object IDs are unique only during single engine runs.
        /// </remarks>
        /// <returns>The unique numeric ID of the object.</returns>
        public int GetId() {
             InternalUnsafeMethods.GetId__Args _args = new InternalUnsafeMethods.GetId__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetId()(ObjectPtr, _args);
             return _engineResult;
        }

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods
        {

         [StructLayout(LayoutKind.Sequential)]
         internal struct SetFieldValue__Args
         {
            [MarshalAs(UnmanagedType.LPUTF8Str)]
            internal string fieldName;
            [MarshalAs(UnmanagedType.LPUTF8Str)]
            internal string value;
            internal int index;
         }

         [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
         [return: MarshalAs(UnmanagedType.I1)]
         internal delegate bool _SetFieldValue(IntPtr _this, SetFieldValue__Args args);
         private static _SetFieldValue _SetFieldValueFunc;
         internal static _SetFieldValue SetFieldValue()
         {
            if (_SetFieldValueFunc == null)
            {
               _SetFieldValueFunc =
                   (_SetFieldValue)Marshal.GetDelegateForFunctionPointer(
                       Torque3D.DllLoadUtils.GetProcAddress(
                           Torque3D.Torque3DLibHandle,
                           "fnSimObject_setFieldValue"), typeof(_SetFieldValue));
            }

            return _SetFieldValueFunc;
         }

         [StructLayout(LayoutKind.Sequential)]
         internal struct GetFieldValue__Args
         {
            [MarshalAs(UnmanagedType.LPUTF8Str)]
            internal string fieldName;
            internal int index;
         }

         [UnmanagedFunctionPointer(CallingConvention.Cdecl)]

         internal delegate IntPtr _GetFieldValue(IntPtr _this, GetFieldValue__Args args);
         private static _GetFieldValue _GetFieldValueFunc;
         internal static _GetFieldValue GetFieldValue()
         {
            if (_GetFieldValueFunc == null)
            {
               _GetFieldValueFunc =
                   (_GetFieldValue)Marshal.GetDelegateForFunctionPointer(
                       Torque3D.DllLoadUtils.GetProcAddress(
                           Torque3D.Torque3DLibHandle,
                           "fnSimObject_getFieldValue"), typeof(_GetFieldValue));
            }

            return _GetFieldValueFunc;
         }

         [StructLayout(LayoutKind.Sequential)]
         internal struct GetClassNamespace__Args
         {
         }

         [UnmanagedFunctionPointer(CallingConvention.Cdecl)]

         internal delegate IntPtr _GetClassNamespace(IntPtr _this, GetClassNamespace__Args args);
         private static _GetClassNamespace _GetClassNamespaceFunc;
         internal static _GetClassNamespace GetClassNamespace()
         {
            if (_GetClassNamespaceFunc == null)
            {
               _GetClassNamespaceFunc =
                   (_GetClassNamespace)Marshal.GetDelegateForFunctionPointer(
                       Torque3D.DllLoadUtils.GetProcAddress(
                           Torque3D.Torque3DLibHandle,
                           "fnSimObject_getClassNamespace"), typeof(_GetClassNamespace));
            }

            return _GetClassNamespaceFunc;
         }

         [StructLayout(LayoutKind.Sequential)]
         internal struct GetClassName__Args
         {
         }

         [UnmanagedFunctionPointer(CallingConvention.Cdecl)]

         internal delegate IntPtr _GetClassName(IntPtr _this, GetClassName__Args args);
         private static _GetClassName _GetClassNameFunc;
         internal static _GetClassName GetClassName()
         {
            if (_GetClassNameFunc == null)
            {
               _GetClassNameFunc =
                   (_GetClassName)Marshal.GetDelegateForFunctionPointer(
                       Torque3D.DllLoadUtils.GetProcAddress(
                           Torque3D.Torque3DLibHandle,
                           "fnSimObject_getClassName"), typeof(_GetClassName));
            }

            return _GetClassNameFunc;
         }

         [StructLayout(LayoutKind.Sequential)]
         internal struct GetName__Args
         {
         }

         [UnmanagedFunctionPointer(CallingConvention.Cdecl)]

         internal delegate IntPtr _GetName(IntPtr _this, GetName__Args args);
         private static _GetName _GetNameFunc;
         internal static _GetName GetName()
         {
            if (_GetNameFunc == null)
            {
               _GetNameFunc =
                   (_GetName)Marshal.GetDelegateForFunctionPointer(
                       Torque3D.DllLoadUtils.GetProcAddress(
                           Torque3D.Torque3DLibHandle,
                           "fnSimObject_getName"), typeof(_GetName));
            }

            return _GetNameFunc;
         }

         [StructLayout(LayoutKind.Sequential)]
         internal struct GetId__Args
         {
         }

         [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
         internal delegate int _GetId(IntPtr _this, GetId__Args args);
         private static _GetId _GetIdFunc;
         internal static _GetId GetId()
         {
            if (_GetIdFunc == null)
            {
               _GetIdFunc =
                   (_GetId)Marshal.GetDelegateForFunctionPointer(
                       Torque3D.DllLoadUtils.GetProcAddress(
                           Torque3D.Torque3DLibHandle,
                           "fnSimObject_getId"), typeof(_GetId));
            }

            return _GetIdFunc;
         }
      }
        #endregion
      }
   }
