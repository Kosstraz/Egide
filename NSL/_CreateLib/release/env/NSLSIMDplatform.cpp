#include "NSLSIMDplatform.h"
#include <iostream>

void	print_compatibleSIMD()
{
#if defined(INTEL)
	std::cout << "\n\tIntel Processor: " << std::endl;
# if defined(SSE4_2)
	std::cout << "sse4.2" << std::endl;
# endif
# if defined(SSE4_1)
	std::cout << "sse4.1" << std::endl;
# endif
# if defined(SSSE3)
	std::cout << "ssse3" << std::endl;
# endif
# if defined(SSE3)
	std::cout << "sse3" << std::endl;
# endif
# if defined(SSE2)
	std::cout << "sse2" << std::endl;
# endif
# if defined(SSE)
	std::cout << "sse" << std::endl;
# endif
# if defined(MMX)
	std::cout << "mmx" << std::endl;
# endif
# if defined(AVX512VL)
	std::cout << "AVX512VL" << std::endl;
# endif
# if defined(AVX512BW)
	std::cout << "AVX512BW" << std::endl;
# endif
# if defined(AVX512DQ)
	std::cout << "AVX512DQ" << std::endl;
# endif
# if defined(AVX512CD)
	std::cout << "AVX512CD" << std::endl;
# endif
# if defined(AVX512F)
	std::cout << "AVX512F" << std::endl;
# endif
# if defined(AVX2)
	std::cout << "AVX2" << std::endl;
# endif
# if defined(AVX)
	std::cout << "AVX" << std::endl;
# endif
# if defined(FMA)
	std::cout << "FMA" << std::endl;
# endif
# if defined(SVML)
	std::cout << "SVML" << std::endl;
# endif
#elif defined(ARM)
	std::cout << "\n\tARM Processor: " << std::endl;
# if defined(NEON)
	std::cout << "Neon" << std::endl;
# endif
#elif defined(RISCVPROC)
# if defined(RISCVSIMD)
	std::cout << "Riscv" << std::endl;
# endif
#endif
}
