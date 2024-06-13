#pragma once

#define _HEADER_FILES_ 0
#define _CLASS_VER_ 1

#if _HEADER_FILES_ == 0
#include "BarrierCondVar/linearBarrier.h"
#include "BarrierCondVar/cyclicBarrier.h"
#elif A == 1
#include "BarrierSemMux/linearBarrier.h"
#include "BarrierSemMux/cyclicBarrier.h"
#endif


#if _CLASS_VER_ == 0
#define Barrier linearBarrier
#elif _CLASS_VER_ == 1
#define Barrier cyclicBarrier
#endif