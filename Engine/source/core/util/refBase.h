//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef _REFBASE_H_
#define _REFBASE_H_

#ifndef _PLATFORMASSERT_H_
#  include "platform/platformAssert.h"
#endif
#ifndef _TYPETRAITS_H_
#  include "platform/typetraits.h"
#endif

#include <memory>
#include <type_traits>
#include <atomic>

class WeakRefBase;

struct WeakControlBlock
{
   explicit WeakControlBlock(WeakRefBase* obj);
   ~WeakControlBlock();

   WeakRefBase* object;
};

/// Base class for objects which can be weakly referenced
/// (i.e., reference goes away when object is destroyed).
class WeakRefBase
{
public:
   WeakRefBase()
      : mControl(std::make_shared<WeakControlBlock>(this))
   {
   }

   virtual ~WeakRefBase();

   // Copy constructor
   WeakRefBase(const WeakRefBase&) = delete;
   WeakRefBase& operator=(const WeakRefBase&) = delete;
   WeakRefBase(WeakRefBase&&) = delete;
   WeakRefBase& operator=(WeakRefBase&&) = delete;

   std::weak_ptr<WeakControlBlock> getWeakControl()
   {
      return mControl;
   }

   std::shared_ptr<WeakControlBlock> getSharedControl()
   {
      return mControl;
   }

protected:

   std::shared_ptr<WeakControlBlock> mControl;
private:

};

template< typename T > class SimObjectPtr;

/// Weak reference pointer class.
/// Instances of this template class can be used as pointers to
/// instances of WeakRefBase and its subclasses.
/// When the object referenced by a WeakRefPtr instance is deleted,
/// the pointer to the object is set to NULL in the WeakRefPtr instance.
template <class T> class WeakRefPtr
{
public:
   WeakRefPtr() = default;
   WeakRefPtr(T* obj) { set(obj); }

   WeakRefPtr(const WeakRefPtr&) = default;
   WeakRefPtr& operator=(const WeakRefPtr&) = default;

	WeakRefPtr& operator=(T* obj)
	{
		set(obj);
		return *this;
	}

   bool isValid() const { return getPointer() != NULL; }
   bool isNull() const { return getPointer() == NULL; }
   
   [[nodiscard]] constexpr T* operator->()      const { return getPointer(); }
   [[nodiscard]] constexpr T& operator*()       const { return *getPointer(); }
   [[nodiscard]] constexpr operator T*()        const { return getPointer(); }
   
   /// Returns the pointer.
   [[nodiscard]] constexpr T* getPointer() const
   {
      auto ctrl = mWeak.lock();
      if (!ctrl || !ctrl->object)
         return NULL;
      return (T*)(ctrl->object);
   }

protected:
	void set(T* obj)
	{
      if (!obj)
      {
         mWeak.reset();
         return;
      }

      mWeak = obj->getWeakControl();
	}
private:
   template< typename > friend class SimObjectPtr;
   std::weak_ptr<WeakControlBlock> mWeak;
};

/// Base class for objects which can be strongly referenced
/// (i.e., as long as reference exists, object will exist,
/// when all strong references go away, object is destroyed).
class StrongRefBase : public WeakRefBase
{
   friend class StrongObjectRef;

public:
   StrongRefBase() = default;
   virtual ~StrongRefBase() = default;

   U32 getRefCount() const
   {
      return mRefCount.load(std::memory_order_relaxed);
   }

   virtual void destroySelf()
   {
      delete this;
   }

   void incRefCount()
   {
      mRefCount.fetch_add(1, std::memory_order_relaxed);
   }

   void decRefCount()
   {
      if (mRefCount.fetch_sub(1, std::memory_order_acq_rel) == 1)
      {
         std::atomic_thread_fence(std::memory_order_acquire);
         destroySelf();
      }
   }

protected:
   std::atomic<U32> mRefCount{ 0 };
};


/// Base class for StrongRefBase strong reference pointers.
class StrongObjectRef
{

public:
   /// Constructor, assigns from the object and increments its reference count if it's not NULL
   StrongObjectRef(StrongRefBase *object = NULL) : mObject( object ) { incRef(); }

   /// Destructor, dereferences the object, if there is one
   ~StrongObjectRef() { decRef(); }

   /// Assigns this reference object from an existing StrongRefBase instance
   void set(StrongRefBase *object)
   {
      if( mObject != object )
      {
         decRef();
         mObject = object;
         incRef();
      }
   }

protected:
   StrongRefBase *mObject; ///< the object this RefObjectRef references

   /// increments the reference count on the referenced object
   constexpr void incRef() const
   {
      if(mObject)
         mObject->incRefCount();
   }

   /// decrements the reference count on the referenced object
   constexpr void decRef() const
   {
      if(mObject)
         mObject->decRefCount();
   }
};

/// Reference counted object template pointer class
/// Instances of this template class can be used as pointers to
/// instances of StrongRefBase and its subclasses.  The object will not
/// be deleted until all of the StrongRefPtr instances pointing to it
/// have been destructed.
template <class T> class StrongRefPtr : protected StrongObjectRef
{
public:
   StrongRefPtr() : StrongObjectRef() {}
   StrongRefPtr(T *ptr) : StrongObjectRef(ptr) {}
   StrongRefPtr(const StrongRefPtr<T>& ref) : StrongObjectRef(ref.mObject) {}
   ~StrongRefPtr() = default;

   StrongRefPtr<T>& operator=(const StrongRefPtr<T>& ref)
   {
      set(ref.mObject);
      return *this;
   }
   StrongRefPtr<T>& operator=(T *ptr)
   {
      set(ptr);
      return *this;
   }

   [[nodiscard]] constexpr bool isNull()  const  { return mObject == NULL; }
   [[nodiscard]] constexpr bool isValid() const  { return mObject != NULL; }
   [[nodiscard]] T* operator->() const { return getPointer(); }
   T& operator*() const  { return *getPointer(); }
   operator T*() const { return getPointer(); }
   T* getPointer() const { return const_cast<T*>(static_cast<T* const>(mObject)); }
};

/// This oxymoron is a pointer that reference-counts the referenced
/// object but also NULLs out if the object goes away.
///
/// This is useful for situations where an object's lifetime is ultimately
/// governed by a superior entity but where individual objects may also die
/// independently of the superior entity.  All client code should use
/// StrongWeakRefs that keep object live as long as the superior entity doesn't
/// step in and kill them (in which case, the client code sees the reference
/// disappear).
template<class T>
class StrongWeakRefPtr
{
public:
   StrongWeakRefPtr() = default;

   StrongWeakRefPtr(T* ptr) { set(ptr); }

   StrongWeakRefPtr(const StrongWeakRefPtr& other)
   {
      set(other.getPointer());
   }

   StrongWeakRefPtr& operator=(const StrongWeakRefPtr& other)
   {
      if (this != &other)
         set(other.getPointer());
      return *this;
   }

   ~StrongWeakRefPtr()
   {
      release();
   }

	StrongWeakRefPtr& operator=(T* ptr)
	{
		set(ptr);
		return *this;
	}

   bool isValid() const { return getPointer() != NULL; }
   bool isNull() const { return getPointer() == NULL; }
	[[nodiscard]] bool operator==(T* ptr) const { return getPointer() == ptr; }
	[[nodiscard]] bool operator!=(T* ptr) const { return getPointer() != ptr; }
	[[nodiscard]] bool operator!() const { return isNull(); }

	[[nodiscard]] T* operator->() const { return getPointer(); }
	[[nodiscard]] T& operator*() const { return *getPointer(); }
	constexpr operator T* () const { return getPointer(); }

   [[nodiscard]] T* getPointer() const
   {
      return mControl ? static_cast<T*>(mControl->object) : NULL;
   }


private:
   std::shared_ptr<WeakControlBlock> mControl;
   T* mPtr = NULL;

   void set(T* ptr)
   {
      release();
      if (!ptr) return;

      if constexpr (std::is_base_of_v<StrongRefBase, T>)
      {
         mControl = ptr->getSharedControl();
      }
      else
      {
         mControl = ptr->getWeakControl().lock();
      }
      if (!mControl) return;

      mPtr = ptr;

      // Conditionally retain object lifetime if T supports intrusive refcount
      // runtime check: only strong ref if T inherits StrongRefBase
      if constexpr (std::is_base_of_v<StrongRefBase, T>)
      {
         T* live = getPointer();
         if (live)
            live->incRefCount();
      }
   }

   void release()
   {
      if (mPtr)
      {
         if constexpr (std::is_base_of_v<StrongRefBase, T>)
         {
            T* live = getPointer();
            if (live)
               live->decRefCount();
         }
      }

      mPtr = NULL;
      mControl.reset();
   }
};

template< typename T >
struct TypeTraits< WeakRefPtr< T > > : public _TypeTraits< WeakRefPtr< T > >
{
   typedef typename TypeTraits< T >::BaseType BaseType;
};
template< typename T >
struct TypeTraits< StrongRefPtr< T > > : public _TypeTraits< StrongRefPtr< T > >
{
   typedef typename TypeTraits< T >::BaseType BaseType;
};
template< typename T >
struct TypeTraits< StrongWeakRefPtr< T > > : public _TypeTraits< StrongWeakRefPtr< T > >
{
   typedef typename TypeTraits< T >::BaseType BaseType;
};

template< typename T >
[[nodiscard]] constexpr T& Deref( WeakRefPtr< T >& ref )
{
   return *ref;
}
template< typename T >
[[nodiscard]] constexpr T& Deref( StrongRefPtr< T >& ref )
{
   return *ref;
}
template< typename T >
[[nodiscard]] constexpr T& Deref( StrongWeakRefPtr< T >& ref )
{
   return *ref;
}

#endif
