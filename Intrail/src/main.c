#include <Windows.h>
#include "generic_typedefs.h"

#define __PRNG_SEED ((__TIME__[7]) - '0') * 1 + (__TIME__[6] - '0') * 10 + (__TIME__[4] - '0') * 60 + (__TIME__[3] - '0') * 600 + (__TIME__[1] - '0') * 3600 + (__TIME__[0] - '0') * 3600 + ((__LINE__ * 10000) << 4)) 

HMODULE GetKernelFuck();

VOID APIENTRY Entry() {
	
}

HMODULE GetKernelFuck() {
#if _WIN64
	__asm {
		mov rax, dword ptr fs:[60h]
		mov rax, dword ptr [rax + 0Ch]
		mov rsi, dword ptr [rax + 1Ch]
		lodsd
		mov rax, dword ptr [rax + 08h]
	}
#else 
	__asm {
		mov eax, dword ptr fs : [30h]
		mov eax, dword ptr[eax + 0Ch]
		mov esi, dword ptr[eax + 1Ch]
		lodsd
		mov eax, dword ptr[eax + 08h]
}
#endif
}


