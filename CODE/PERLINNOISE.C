proc grad uses ecx edx,\
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
     mov   edx, [ecx + eax * 4]
     mov   eax, [x]
     add   edx, eax
     mov   eax, edx
     sar   eax, 31
     shr   eax, 24
     add   edx, eax
     movzx edx, dl
     sub   edx, eax
     mov   eax, edx
     mov   eax, [ecx + eax * 4]
     ret
endp

proc smooth_inter,\
     x, y, s

     finit
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

     push  eax
     fstp  DWORD [esp]
     pop   eax
     ret
endp

proc noise2d,\
     x, y   ;both float, return float in eax

     locals
        x_int   dd      ?
        y_int   dd      ?
        x_int1  dd      ?
        y_int1  dd      ?
        x_frac  dd      ?
        y_frac  dd      ?
        s       dd      ?
        t       dd      ?
        u       dd      ?
        v       dd      ?
        low     dd      ?
        high    dd      ?
     endl

     finit
     fld    DWORD [x]
     frndint
     fistp  DWORD [x_int]
     fld    DWORD [x]
     fisub  DWORD [x_int]
     fstp   [x_frac]

     fld    DWORD [y]
     frndint
     fistp  DWORD [y_int]
     fld    DWORD [y]
     fisub  DWORD [y_int]
     fstp   [y_frac]

     stdcall grad, [x_int], [y_int]
     mov    [s], eax
     fild   [s]
     fstp   [s]

     fld1
     fiadd  [x_int]
     fistp  [x_int1]
     stdcall grad, [x_int1], [y_int]
     mov    [t], eax
     fild   [t]
     fstp   [t]

     fld1
     fiadd  [y_int]
     fistp  [y_int1]
     stdcall grad, [x_int], [y_int1]
     mov    [u], eax
     fild   [u]
     fstp   [u]

     stdcall grad, [x_int1], [y_int1]
     mov    [v], eax
     fild   [v]
     fstp   [v]


     stdcall   smooth_inter, [s], [t], [x_frac]
     mov    [low], eax

     stdcall   smooth_inter, [u], [v], [x_frac]
     mov    [high], eax

     stdcall   smooth_inter, [low], [high], [y_frac]
     ret
endp

proc perlin2d,\
     x, y, frequency, depth

     locals
        xa          dd      ?
        ya          dd      ?
        amplitude   dd      1.0
        fin         dd      0.0
        divide      dd      0.0
        i           dd      0
     endl

     finit
     fld   [x]
     fmul  [frequency]
     fstp  [xa]

     fld   [y]
     fmul  [frequency]
     fstp  [ya]

     jmp .for_cmp

.for_body:
     fld    DWORD [amplitude]
     fmul   DWORD [thfs]
     fadd   DWORD [divide]
     fstp   DWORD [divide]

     stdcall noise2d, [xa], [ya]
     push   eax
     fld    DWORD [esp]
     pop    eax
     fmul   [amplitude]
     fadd   [fin]
     fstp   [fin]

     fld    [amplitude]
     fdiv   [two]
     fstp   [amplitude]

     fld    [xa]
     fmul   [two]
     fstp   [xa]

     fld    [ya]
     fdiv   [two]
     fstp   [ya]

     add    [i], 1
.for_cmp:
     mov    eax, DWORD [i]
     cmp    eax, DWORD [depth]
     jl .for_body

     fld    DWORD [fin]
     fdiv   DWORD [divide]

     push   eax
     fstp   DWORD [esp]
     pop    eax
     ret
endp