#include "refBase.h"

WeakRefBase::~WeakRefBase()
{
   if (mControl)
      mControl->object = NULL;
}

WeakControlBlock::WeakControlBlock(WeakRefBase* obj)
   : object(obj)
{
}

WeakControlBlock::~WeakControlBlock()
{

}

