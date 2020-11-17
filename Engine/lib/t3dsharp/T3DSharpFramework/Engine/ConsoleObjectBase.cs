using System;

namespace T3DSharpFramework.Engine
{
    public class ConsoleObjectBase : IDisposable
    {
        public ConsoleObjectBase(bool pRegister = false) {
            CreateObjectPtr();
            if (this is ISimObject sim) {
                if (pRegister) {
                    sim.RegisterObject();
                }

                SimDictionary.RegisterObject(sim);
            }
        }

        public ConsoleObjectBase(ConsoleObjectBase pObj) {
            SetPointerFromObject(pObj);
        }

        public ConsoleObjectBase(IntPtr pObj) {
            SetPointer(pObj);
        }

        public IntPtr ObjectPtr { get; protected set; }

        public void SetPointerFromObject(ConsoleObjectBase pObj)
        {
            ObjectPtr = pObj.ObjectPtr;

            if (this is ISimObject sim && !SimDictionary.Contains(sim)) {
                SimDictionary.RegisterObject(sim);
            }

        }

        public void SetPointer(IntPtr pObjPtr) {
            ObjectPtr = pObjPtr;

            if (this is ISimObject sim) {
                SimDictionary.RegisterObject(sim);
            }
        }

        public T As<T>() where T : ConsoleObjectBase {
            if (this is ISimObject sim) {
                return (T) SimDictionary.CreateInstance(typeof(T), sim);
            }

            throw new NotImplementedException();
        }

        public ConsoleObjectBase As(Type t) {
            if (!typeof(ConsoleObjectBase).IsAssignableFrom(t)) return null;

            if (this is ISimObject sim) {
                return (ConsoleObjectBase) SimDictionary.CreateInstance(t, sim);
            } else if (this is UnknownSimObject unk) {
                return (ConsoleObjectBase) SimDictionary.CreateInstance(t, unk);
            }

            throw new NotImplementedException();
        }

        public bool IsDead() {
            return SimDictionary.IsDead(ObjectPtr);
        }

        #region IDisposable

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool pDisposing) {
            SimDictionary.UnregisterObjectPtr(ObjectPtr);
        }

        ~ConsoleObjectBase() {
            Dispose(false);
        }

        #endregion

        protected virtual void CreateObjectPtr() {
            throw new NotImplementedException();
        }

        public string Name = null;
        public string GetName() => null;

        public int GetId() => -1;

        #region Implicits and operators

        public static bool operator ==(ConsoleObjectBase obj, string str) {
            if (str == null) return ReferenceEquals(obj, null);
            if (ReferenceEquals(obj, null)) return false;
            return obj.Name == str || obj.GetId().ToString().Equals(str);
        }

        public static bool operator !=(ConsoleObjectBase obj, string str) {
            return !(obj == str);
        }

        public static bool operator ==(ConsoleObjectBase obj, object other) {
            if (ReferenceEquals(other, null)) return ReferenceEquals(obj, null);
            if (ReferenceEquals(obj, null)) return false;
            if (other is string str) {
                return obj.Name == str || obj.GetId().ToString().Equals(str);
            }

            ConsoleObjectBase sobj = other as ConsoleObjectBase;
            if (sobj != null)
                return obj.ObjectPtr == sobj.ObjectPtr;
            return obj.Equals(other);
        }

        public static bool operator !=(ConsoleObjectBase obj, object other) {
            return !(obj == other);
        }

        #endregion
    }
}
