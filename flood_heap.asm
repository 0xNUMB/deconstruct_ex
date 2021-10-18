format PE GUI
entry entr

section '.idata' import data readable writeable

library kernel32, 'kernel32.dll',               \
        ntdll,    'ntdll.dll'

import kernel32,                                \
       GetProcessHeap, 'GetProcessHeap',        \
       ExitProcess,    'ExitProcess'

import ntdll,                                   \
       RtlAllocHeap,   'RtlAllocateHeap'


section '.data' data readable writeable

buf db 256 dup (0)


section '.code' executable readable writeable

entr:
invoke RtlAllocHeap, <invoke GetProcessHeap>, 0, 1024
mov ecx, [eax + 10]
invoke ExitProcess, 0