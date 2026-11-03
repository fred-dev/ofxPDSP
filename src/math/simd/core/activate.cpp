#include "activate.h"

#include "flags.h"

#include <cstdint>

#if defined(__SSE__) || defined(__x86_64__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)
#include <xmmintrin.h>
#define PDSP_DENORMAL_X86 1
#endif

// Sets the "flush to zero" (and on x86 "denormals are zero") modes of the
// floating point unit for the CALLING THREAD. Denormal numbers appear in the
// decaying tails of filters, delays and reverbs and can make each operation
// tens of times slower on x86. pdsp::Engine calls this from the audio thread
// at the start of every callback; the cost is a couple of register writes.
void ofx_activate_denormal_flush(){
#if defined(PDSP_DENORMAL_X86)
    // bit 15 = FTZ, bit 6 = DAZ
    _mm_setcsr(_mm_getcsr() | 0x8040);
#elif defined(__aarch64__) || defined(_M_ARM64)
  #if defined(_MSC_VER)
    // MSVC on ARM64: no inline assembly; denormals are handled in hardware.
  #else
    // FPCR bit 24 = FZ (flush denormal results/inputs to zero)
    uint64_t fpcr;
    __asm__ __volatile__("mrs %0, fpcr" : "=r"(fpcr));
    fpcr |= (uint64_t(1) << 24);
    __asm__ __volatile__("msr fpcr, %0" : : "r"(fpcr));
  #endif
#elif defined(__arm__) && defined(__ARM_FP)
    // 32 bit ARM VFP: FPSCR bit 24 = FZ
    uint32_t fpscr;
    __asm__ __volatile__("vmrs %0, fpscr" : "=r"(fpscr));
    fpscr |= (uint32_t(1) << 24);
    __asm__ __volatile__("vmsr fpscr, %0" : : "r"(fpscr));
#endif
}
