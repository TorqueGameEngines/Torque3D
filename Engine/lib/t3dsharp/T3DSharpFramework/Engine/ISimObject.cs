using System;

namespace T3DSharpFramework.Engine
{
    public interface ISimObject : IDisposable
    {
        IntPtr ObjectPtr { get; }
        void SetPointerFromObject(ISimObject pObj);
        void SetPointer(IntPtr pObjPtr);
        T As<T>() where T : class, ISimObject;
        ISimObject As(Type t);
        bool IsDead();
        string Name { get; set; }
        string GetName();
        int GetId();
        bool RegisterObject();
        string GetFieldValue(string name, int index);
        bool SetFieldValue(string fieldName, string value, int index);
    }
}
