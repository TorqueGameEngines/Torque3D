//-----------------------------------------------------------------------------
// Copyright (C) 2024 tgemit contributors.
// See AUTHORS file and git repository for contributor information.
//
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "core/frameAllocator.h"

thread_local ManagedAlignedBufferAllocator<U32> FrameAllocator::smFrameAllocator;

#ifdef TORQUE_MEM_DEBUG
thread_local dsize_t FrameAllocator::smMaxAllocationBytes = 0;
#endif

