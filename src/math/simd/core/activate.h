
#ifndef OFX_SIMDFLOATS_ACTIVATE_H_INCLUDED
#define OFX_SIMDFLOATS_ACTIVATE_H_INCLUDED


#include "flags.h"

#ifdef OFX_SIMD_USE_SSE
#include <mmintrin.h>
#include <xmmintrin.h>
#endif



// Enables flush-to-zero for denormal floats on the calling thread (x86 SSE,
// ARM64 and 32 bit ARM VFP). pdsp::Engine calls it in every audio callback.
void ofx_activate_denormal_flush();
   




#endif  // OFX_SIMDFLOATS_ACTIVATE_H_INCLUDED
