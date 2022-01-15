.386
.MODEL FLAT, STDCALL

OPTION CASEMAP:NONE

INCLUDE C:\masm32\include\windows.inc 

.CODE

DllEntry PROC hInstDLL:HINSTANCE, reason:DWORD, reserved1:DWORD

mov	eax, TRUE 
ret

DllEntry ENDP


MyProc1 proc x: DWORD, y: DWORD
ret
MyProc1 endp

END DllEntry
