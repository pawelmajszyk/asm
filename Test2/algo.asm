.data
vec1 real4 0.393, 0.769, 0.189, 0.0
vec2 real4 0.349, 0.686, 0.168, 0.0
vec3 real4  0.272, 0.534, 0.131, 0.0
vecReal real4 0.0, 0.0, 0.0, 0.0
vecResult real4 0.0, 0.0, 0.0, 0.0
vecMaxBytes dword 255, 255, 255, 255 
masks db 0, 4, 8, 12, 12 dup (-1)

.code
MyProc1 proc var1:QWORD, var2:WORD, jmpAddress:WORD
push rdx;
push rax
push rcx
push rbp
push rdi
push rsi
push rbx

mov rbx,RCX
mov rcx,RDX
mov rsi, 0

        xor rcx,rcx   ; cx-register is the counter, set to 0
loop1:  pmovzxbd  xmm0, [rbx+rsi]   ; cast bytes from memory to ints in xmm0 register
        cvtdq2ps  xmm0, xmm0    ; cast ints to floats 
        movups xmm3,xmm0   ; save results to memory 
        
        sub     rsp, 4
        mov    [rsp], eax

      ;; first pixel
        movups    xmm2, [vec1]  ; move first vector of floats 
        MULPS     xmm0, xmm2    ; multiply temporart values with first vector
                 
        movshdup  xmm1, xmm0    ;
        addps     xmm0, xmm1
        movhlps   xmm1, xmm0
        addss     xmm0, xmm1
        movd     eax,xmm0
        sub     rsp, 4
        mov    [rsp], eax
      ;; second pixel
        movups    xmm0, xmm3
        xorps xmm1, xmm1
        movups    xmm2, [vec2]
        MULPS     xmm0, xmm2

        movshdup  xmm1, xmm0    ;
        addps     xmm0, xmm1
        movhlps   xmm1, xmm0
        addss     xmm0, xmm1
          movd     eax,xmm0
        sub     rsp, 4
        mov    [rsp], eax
      ;; third pixel
        movups    xmm0, xmm3
        movups    xmm2, [vec3]
        MULPS     xmm0, xmm2

        movshdup  xmm1, xmm0    ;
        addps     xmm0, xmm1
        movhlps   xmm1, xmm0
        addss     xmm0, xmm1
        movd     eax,xmm0
        sub     rsp, 4
        mov    [rsp], eax


        

       ;; casting floats to int
        movdqu  xmm0,  [rsp]
        add     rsp, 16 
        CVTPS2DQ xmm0, xmm0
        PMINUD  xmm0, [vecMaxBytes]

        pshufb  xmm0, [masks]
        movd    eax, xmm0
        mov     word ptr [rbx+rsi] , ax
        bswap   eax
        mov     byte ptr [rbx+rsi+2], ah

        add rsi, 3
        add rcx, 3      ; Increment
        cmp rcx,rdx    ; Compare cx to the limit
        jle loop1   ; Loop while less or equal
pop rbx
pop rsi
pop rdi
pop rbp
pop rcx
pop rax
pop rdx;
ret
MyProc1 endp
END
