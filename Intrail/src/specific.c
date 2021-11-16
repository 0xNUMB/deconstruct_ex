#include <Windows.h>
#include <ntdef.h>

typedef struct {
	ANSI_STRING ProcName, *ProcNamePtr;
	FARPROC fnExp;
	NTSTATUS stat;
	LPVOID map;
	ULONG ordinal;
} specGetPrcAddress;

// Shit code
FARPROC WINAPI __GetPrcAddress(HMODULE hModule, LPCWSTR lpPrcName) {
	specGetPrcAddress *specGetPA;

	ANSI_STRING PrcName = specGetPA->ProcName;
	ANSI_STRING *PrcNamePtr = specGetPA->ProcNamePtr;
	LPVOID hMapped = specGetPA->map;
	FARPROC fnPtr = specGetPA->fnExp;
	ULONG sOrdinal = specGetPA->ordinal;
	NTSTATUS ntStat = specGetPA->stat;

	fnPtr = NULL;
	sOrdinal = 0;

	if(hModule != NULL) {
		hMapped = BaseMapModuleHandle(hModule, FALSE);

		if((lpPrcName != NULL) && ((ULONG_PTR)lpPrcName > MAXUSHORT)) {
			RtlInitAnsiString(PrcName, (LPCWSTR)lpPrcName);
			PrcNamePtr = &PrcName;
		}
	} else {
		sOrdinal = PtrToUlong(lpPrcName);
	}

	ntStat = LdrGetProcedureAddress(hMapped, PrcNamePtr, sOrdinal, (PVOID *)&fnPtr);

	if(ntStat == NULL) {
		BaseSetLastNTError(ntStat);
		return NULL;
	}

	return fnPtr;
}