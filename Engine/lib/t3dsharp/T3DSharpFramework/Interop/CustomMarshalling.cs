using System;
using System.Globalization;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using T3DSharpFramework.Engine;

namespace T3DSharpFramework.Interop
{
   /// <summary>
   /// A static class to help ease marshalling strings between managed and
   /// unmanaged code.
   ///
   /// Some references for marshaling strings:
   /// http://stackoverflow.com/questions/1498931/marshalling-array-of-strings-to-char-in-c-sharp
   /// </summary>
   public static class StringMarshal
   {
      public static string IntPtrToUtf8String(IntPtr ptr)
      {
         int len = 0;

         // Locate null-termination
         while (Marshal.ReadByte(ptr, len) != 0)
         {
            ++len;
         }

         byte[] buffer = new byte[len];
         Marshal.Copy(ptr, buffer, 0, buffer.Length);
         return Encoding.UTF8.GetString(buffer);
      }

      public static IntPtr Utf8StringToIntPtr(string str)
      {
         int len = Encoding.UTF8.GetByteCount(str);
         byte[] buffer = new byte[len + 1];
         Encoding.UTF8.GetBytes(str, 0, str.Length, buffer, 0);
         IntPtr nativeUtf8 = Marshal.AllocHGlobal(buffer.Length);
         Marshal.Copy(buffer, 0, nativeUtf8, buffer.Length);
         return nativeUtf8;
      }

      public static string[] IntPtrToStringArray(IntPtr ptr, int count)
      {
         //convert the received pointer into a pointer array
         IntPtr[] stringPointers = new IntPtr[count];
         Marshal.Copy(ptr, stringPointers, 0, count);
         //convert the pointer array into a string array
         string[] strings = new string[count];
         for (int i = 0; i < count; i++)
         {
            if (stringPointers[i] == IntPtr.Zero)
            {
               strings[i] = null;
            }
            else
            {
               strings[i] = IntPtrToUtf8String(stringPointers[i]);
            }
         }

         return strings;
      }

      public static string[] IntPtrToAnsiStringArray(IntPtr ptr, int count)
      {
         //convert the received pointer into a pointer array
         IntPtr[] stringPointers = new IntPtr[count];
         Marshal.Copy(ptr, stringPointers, 0, count);
         //convert the pointer array into a string array
         string[] strings = new string[count];
         for (int i = 0; i < count; i++)
         {
            if (stringPointers[i] == IntPtr.Zero)
            {
               strings[i] = null;
            }
            else
            {
               strings[i] = Marshal.PtrToStringAnsi(stringPointers[i]);
            }
         }

         return strings;
      }


      /// <summary>
      /// Marshals an array of strings str into an array of heap allocated strings.
      /// </summary>
      /// <param name="str">An array of strings.</param>
      /// <returns>An array of int pointers to marshal to the native api.</returns>
      public static IntPtr[] StringArrayToIntPtrArray(string[] str)
      {
         int length = str.Length;
         IntPtr[] arr = new IntPtr[length];
         for (int i = 0; i < length; i++)
         {
            arr[i] = Utf8StringToIntPtr(str[i]);
         }

         return arr;
      }

      /// <summary>
      /// Frees an array of heap allocated data stored in an IntPtr array.
      /// </summary>
      /// <param name="arr">The array of int pointers.</param>
      public static void FreeIntPtrArray(IntPtr[] arr)
      {
         int length = arr.Length;
         for (int i = 0; i < length; i++)
         {
            Marshal.FreeHGlobal(arr[i]);
         }
      }

      public static IntPtr StringArrayToIntPtr(string[] array)
      {
         IntPtr unmanagedPointer = Marshal.AllocHGlobal(array.Length * IntPtr.Size);

         IntPtr[] ptrList = StringArrayToIntPtrArray(array);

         Marshal.Copy(ptrList, 0, unmanagedPointer, array.Length);
         return unmanagedPointer;
      }

      public static void FreeStringArray(IntPtr arrayPtr)
      {
         throw new NotImplementedException();
      }
   }

   public static class StructMarshal
   {
      public static IntPtr StructToIntPtr<T>(T _struct)
      {
         IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf<T>());
         Marshal.StructureToPtr(_struct, ptr, false);
         return ptr;
      }

      public static void FreeStructPtr<T>(IntPtr ptr)
      {
         Marshal.FreeHGlobal(ptr);
      }
   }

   public static class GenericMarshal
   {
      public static bool StringToBool(string str)
      {
         switch (str)
         {
            case "1":
               return true;
            case "0":
               return false;
            case "":
               return false;
            default:
               return bool.Parse(str);
         }
      }

      public static string ToString<T>(T obj)
      {
         bool found = false;
         string ret = null;
         if (obj is bool b)
         {
            found = true;
            ret = b ? "1" : "0";
         }
         else if (obj is bool[] bs)
         {
            found = true;
            ret = ToString(bs.Select(ToString).ToArray());
         }
         else if (obj is byte by)
         {
            found = true;
            ret = by.ToString(CultureInfo.InvariantCulture);
         }
         else if (obj is byte[] bytes)
         {
            found = true;
            ret = ToString(bytes.Select(ToString).ToArray());
         }
         else if (obj is double d)
         {
            found = true;
            ret = d.ToString(CultureInfo.InvariantCulture);
         }
         else if (obj is double[] doubles)
         {
            found = true;
            ret = ToString(doubles.Select(ToString).ToArray());
         }
         else if (typeof(T).IsEnum)
         {
            found = true;
            ret = obj.ToString();
         }
         else if (obj is float f)
         {
            found = true;
            ret = f.ToString(CultureInfo.InvariantCulture);
         }
         else if (obj is float[] floats)
         {
            found = true;
            ret = ToString(floats.Select(ToString).ToArray());
         }
         else if (obj is IEngineStruct @struct)
         {
            found = true;
            ret = @struct.ToString();
         }
         else if (obj is IEngineStruct[] @structs)
         {
            found = true;
            ret = ToString(@structs.Select(ToString).ToArray());
         }
         else if (obj is int i)
         {
            found = true;
            ret = i.ToString();
         }
         else if (obj is int[] ints)
         {
            found = true;
            ret = ToString(ints.Select(ToString).ToArray());
         }
         else if (obj is IntPtr ptr)
         {
            found = false;
         }
         else if (obj is ISimObject sim)
         {
            found = true;
            ret = ToString(sim.GetId());
         }
         else if (obj is ISimPersistID persistId)
         {
            found = true;
            ret = persistId.MarshalToString();
         }
         else if (obj is string s)
         {
            found = true;
            ret = s;
         }
         else if (obj is string[] strings)
         {
            found = true;
            ret = string.Join(" ", strings);
         }
         else if (obj is uint u)
         {
            found = true;
            ret = u.ToString();
         }
         else if (obj is uint[] uints)
         {
            found = true;
            ret = ToString(uints.Select(ToString).ToArray());
         }
         else if (obj == null)
         {
            found = true;
            ret = null;
         }

         if (found)
         {
            return ret;
         }

         throw new NotImplementedException();
      }

      public static T StringTo<T>(string s)
      {
         bool found = false;
         object ret = null;
         if (typeof(T) == typeof(string))
         {
            found = true;
            ret = s;
         }
         else if (typeof(T) == typeof(bool))
         {
            found = true;

            if (int.TryParse(s, out int parseResult)) {
               ret = parseResult > 0;
            } else {
               ret = bool.Parse(s);
            }
         }
         else if (typeof(T) == typeof(char))
         {
            found = true;
            ret = char.Parse(s);
         }
         else if (typeof(T) == typeof(int))
         {
            found = true;
            ret = int.Parse(s);
         }
         else if (typeof(T) == typeof(long))
         {
            found = true;
            ret = long.Parse(s);
         }
         else if (typeof(T) == typeof(float))
         {
            found = true;
            ret = float.Parse(s);
         }
         else if (typeof(T) == typeof(double))
         {
            found = true;
            ret = double.Parse(s);
         }
         else if (typeof(T).IsEnum)
         {
            found = true;
            ret = Enum.Parse(typeof(T), s);
         }
         else if (typeof(T).IsClass)
         {
            found = true;

            ConstructorInfo cinfo = typeof(T).GetConstructor(new[] {typeof(string)});
            if (cinfo != null)
            {
               ret = cinfo.Invoke(new object[] {s});
            }
            else
            {
               throw new NotImplementedException("No constructor that takes a string");
            }
         }

         if (found)
         {
            return (T) ret;
         }

         throw new NotImplementedException();
      }

      public static IntPtr ToPtr<T>(T[] array)
      {
         if (array is string[] strings)
         {
            return StringMarshal.StringArrayToIntPtr(strings);
         }


         int size = Marshal.SizeOf<T>();

         IntPtr unmanagedPointer = Marshal.AllocHGlobal(size * array.Length);

         for (int index = 0; index < array.Length; ++index)
         {
            IntPtr elementPointer = new IntPtr((long) unmanagedPointer + size * index);
            Marshal.StructureToPtr(array[index], elementPointer, false);
         }

         return unmanagedPointer;
      }

      public static T[] FromPtr<T>(IntPtr ptr, uint size, bool free)
      {
         return FromPtr<T>(ptr, (int) size, free);
      }

      public static T[] FromPtr<T>(IntPtr ptr, int size, bool free)
      {
         bool found = false;
         object ret = null;

         if (typeof(T) == typeof(byte))
         {
            byte[] managedArray = new byte[size];
            Marshal.Copy(ptr, managedArray, 0, size);
            ret = managedArray;
            found = true;
         }
         else if (typeof(T) == typeof(char))
         {
            char[] managedArray = new char[size];
            Marshal.Copy(ptr, managedArray, 0, size);
            ret = managedArray;
            found = true;
         }
         else if (typeof(T) == typeof(short))
         {
            short[] managedArray = new short[size];
            Marshal.Copy(ptr, managedArray, 0, size);
            ret = managedArray;
            found = true;
         }
         else if (typeof(T) == typeof(int))
         {
            int[] managedArray = new int[size];
            Marshal.Copy(ptr, managedArray, 0, size);
            ret = managedArray;
            found = true;
         }
         else if (typeof(T) == typeof(uint))
         {
            int[] iArr = FromPtr<int>(ptr, size, free);
            ret = iArr;
         }
         else if (typeof(T) == typeof(long))
         {
            long[] managedArray = new long[size];
            Marshal.Copy(ptr, managedArray, 0, size);
            ret = managedArray;
            found = true;
         }
         else if (typeof(T) == typeof(float))
         {
            float[] managedArray = new float[size];
            Marshal.Copy(ptr, managedArray, 0, size);
            ret = managedArray;
            found = true;
         }
         else if (typeof(T) == typeof(double))
         {
            double[] managedArray = new double[size];
            Marshal.Copy(ptr, managedArray, 0, size);
            ret = managedArray;
            found = true;
         }
         else if (typeof(T) == typeof(string))
         {
            ret = StringMarshal.IntPtrToStringArray(ptr, size);
            found = true;
         }
         else if (typeof(IEngineStruct).IsAssignableFrom(typeof(T)))
         {
            T[] result = new T[size];
            int structSize = Marshal.SizeOf<T>();
            for (int i = 0; i < size; ++i)
            {
               result[i] = Marshal.PtrToStructure<T>(new IntPtr(ptr.ToInt32() + i * structSize));
            }

            ret = result;
         }

         if (found)
         {
            if (free)
            {
               Marshal.FreeHGlobal(ptr);
            }
            return (T[]) ret;
         }

         throw new NotImplementedException();
      }
   }
}
