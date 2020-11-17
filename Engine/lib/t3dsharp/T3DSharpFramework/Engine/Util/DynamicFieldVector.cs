using System;

namespace T3DSharpFramework.Engine.Util
{
    public class DynamicFieldVector<T>
    {
        public delegate T GetterFunction(string val);
        public delegate string SetterFunction(T obj);

        private readonly GetterFunction _GetterFunction;
        private readonly SetterFunction _SetterFunction;

        private readonly ISimObject _OwnerObject;
        private int _Count;
        private string _FieldName;

        public DynamicFieldVector(ISimObject pSimObject, string pFieldName, int pCount, GetterFunction pGetterFunction, SetterFunction pSetterFunction)
        {
            _OwnerObject = pSimObject;
            _FieldName = pFieldName;
            _Count = pCount;
            _GetterFunction = pGetterFunction;
            _SetterFunction = pSetterFunction;
        }


        public T this[int index] {
            get {
                //if (_OwnerObject.IsDead()) throw new Exceptions.SimObjectPointerInvalidException();
                if (index >= _Count)
                    throw new IndexOutOfRangeException();
                return _GetterFunction(_OwnerObject.GetFieldValue(_FieldName, index));
            }
            set {
                //if (_OwnerObject.IsDead()) throw new Exceptions.SimObjectPointerInvalidException();
                if (index >= _Count)
                    throw new IndexOutOfRangeException();
                _OwnerObject.SetFieldValue(_FieldName, _SetterFunction(value), index);
            }
        }
    }
}
