.data
vec1 real4 0.393, 0.769, 0.189, 0.0
vec2 real4 0.349, 0.686, 0.168, 0.0
vec3 real4  0.272, 0.534, 0.131, 0.0
vecReal real4 0.0, 0.0, 0.0, 0.0
vecResult real4 0.0, 0.0, 0.0, 0.0

.code
MyProc1 proc var1:QWORD, var2:WORD, jmpAddress:WORD
mov rbx,RCX
mov rcx,RDX
mov r10, 0

pmovzxbd  xmm0, [rbx]   ; or SX to sign-extend  (Byte to DWord)
cvtdq2ps  xmm0, xmm0 
movups [vecReal],xmm0

movups    xmm2, [vec1]
MULPS     xmm0, xmm2

movshdup  xmm1, xmm0
addps     xmm0, xmm1
movhlps   xmm1, xmm0
addss     xmm0, xmm1
VMOVSS    [vecResult+4], xmm1

         xor rcx,rcx   ; cx-register is the counter, set to 0
loop1:  mov dword ptr[RBX + r10], 255           ; Whatever you wanna do goes here, should not change cx
        mov dword ptr[RBX+ r10 + 1], 0
        mov dword ptr [RBX+ r10+2], 255 
        add r10, 3
        add rcx, 3      ; Increment
        cmp rcx,rdx    ; Compare cx to the limit
        jle loop1   ; Loop while less or equal

ret
MyProc1 endp
END
