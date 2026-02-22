#include "refBase.h"

WeakRefBase::~WeakRefBase()
{
   if (mControl)
      mControl->object = nullptr;
}

WeakControlBlock::WeakControlBlock(WeakRefBase* obj)
   : object(obj)
{
}

WeakControlBlock::~WeakControlBlock()
{

}
