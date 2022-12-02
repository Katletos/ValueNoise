proc grad,\
     x, y

     mov   ecx, [pRandomData]
     mov   edx, [y]
     mov   eax, edx
     sar   eax, 31
     shr   eax, 24
     add   edx, eax
     movzx edx, dl
     sub   edx, eax
     mov   eax, edx
     mov   edx, [ecx+eax*4]
     mov   eax, [x]
     add   edx, eax
     mov   eax, edx
     sar   eax, 31
     shr   eax, 24
     add   edx, eax
     movzx edx, dl
     sub   edx, eax
     mov   eax, edx
     mov   eax, [ecx+eax*4]
     ret
endp

proc smooth_inter,\
     x, y, s

     fld   DWORD [s]
     fmul  st, st0
     fmul  DWORD [s]
     fld   DWORD [s]
     fld   DWORD [six]
     fmulp st1, st
     fld   DWORD [fifteen]
     fsubp st1, st
     fmul  DWORD [s]
     fld   DWORD [ten]
     faddp st1, st
     fmulp st1, st
     fld   DWORD  [y]
     fsub  DWORD  [x]
     fmulp st1, st
     fadd  DWORD  [x]
     ret
endp

proc noise2d,\
     x, y

     sub    esp, 52
     fld    DWORD [ebp+8]
     fnstcw WORD [ebp-50]
     movzx  eax, WORD [ebp-50]
     or     ah, 12
     mov    WORD  [ebp-52], ax
     fldcw  WORD  [ebp-52]
     fistp  DWORD [ebp-4]
     fldcw  WORD  [ebp-50]
     fld    DWORD [ebp+12]
     fldcw  WORD  [ebp-52]
     fistp  DWORD [ebp-8]
     fldcw  WORD  [ebp-50]
     fild   DWORD [ebp-4]
     fld    DWORD [ebp+8]
     fsubrp st1, st
     fstp   DWORD [ebp-12]
     fild   DWORD [ebp-8]
     fld    DWORD [ebp+12]
     fsubrp st1, st
     fstp   DWORD [ebp-16]
     push   DWORD [ebp-8]
     push   DWORD [ebp-4]
     call   grad

     mov    DWORD [ebp-20], eax
     mov    eax, DWORD [ebp-4]
     add    eax, 1
     push   DWORD [ebp-8]
     push   eax
     call   grad

     mov    DWORD [ebp-24], eax
     mov    eax, DWORD [ebp-8]
     add    eax, 1
     push   eax
     push   DWORD [ebp-4]
     call   grad

     mov    DWORD [ebp-28], eax
     mov    eax, DWORD [ebp-8]
     lea    edx, [eax+1]
     mov    eax, DWORD [ebp-4]
     add    eax, 1
     push   edx
     push   eax
     call   grad

     mov    DWORD [ebp-32], eax
     fild   DWORD [ebp-24]
     fild   DWORD [ebp-20]
     fxch   st1
     push   DWORD [ebp-12]
     lea    esp,  [esp-4]
     fstp   DWORD [esp]
     lea    esp,  [esp-4]
     fstp   DWORD [esp]
     call   smooth_inter

     fstp   DWORD [ebp-36]
     fild   DWORD [ebp-32]
     fild   DWORD [ebp-28]
     fxch   st1
     push   DWORD [ebp-12]
     lea    esp,  [esp-4]
     fstp   DWORD [esp]
     lea    esp,  [esp-4]
     fstp   DWORD [esp]
     call   smooth_inter

     fstp   DWORD [ebp-40]
     push   DWORD [ebp-16]
     push   DWORD [ebp-40]
     push   DWORD [ebp-36]
     call   smooth_inter
     ret
endp

;;   return value on fpu stack
proc perlin2d,\
     x, y, freq, depth

     sub    esp, 32
     fld    DWORD [x]
     fmul   DWORD [freq]
     fstp   DWORD [ebp-4]
     fld    DWORD [y]
     fmul   DWORD [freq]
     fstp   DWORD [ebp-8]
     fld1
     fstp   DWORD [ebp-12]
     fldz
     fstp   DWORD [ebp-16]
     fldz
     fstp   DWORD [ebp-20]
     mov    DWORD [ebp-24], 0
     jmp .for_cmp

.for_body:
     fld    DWORD [ebp-12]
     fld    DWORD [thfs]
     fmulp  st1, st
     fld    DWORD [ebp-20]
     faddp  st1, st
     fstp   DWORD [ebp-20]
     push   DWORD [ebp-8]
     push   DWORD [ebp-4]
     call   noise2d

     fmul   DWORD [ebp-12]
     fld    DWORD [ebp-16]
     faddp  st1, st
     fstp   DWORD [ebp-16]
     fld    DWORD [ebp-12]
     fld    DWORD [two]
     fdivp  st1, st
     fstp   DWORD [ebp-12]
     fld    DWORD [ebp-4]
     fadd   st, st0
     fstp   DWORD [ebp-4]
     fld    DWORD [ebp-8]
     fadd   st, st0
     fstp   DWORD [ebp-8]
     add    DWORD [ebp-24], 1
.for_cmp:
     mov    eax, DWORD [ebp-24]
     cmp    eax, DWORD [depth]
     jl .for_body

     fld    DWORD [ebp-16]
     fdiv   DWORD [ebp-20]
     ret
endp