;include 'macro\proc32.inc'

proc    Random.Init

        invoke  GetTickCount
        mov     [PrevRandom], eax
        ret
endp

proc    Random.Get uses ecx edx, dMin, dMax

        mov     eax, [PrevRandom]

        mov     ecx, 29
        mul     ecx
        add     eax, 47

        mov     [PrevRandom], eax

        mov     ecx, [dMax]
        mov     edx, [dMin]
        sub     ecx, edx
        inc     ecx
        xor     edx, edx
        div     ecx

        mov     eax, edx
        add     eax, [dMin]

        ret
endp

proc    Random.GetFloat uses edx

        stdcall Random.Get, 0, 100000

        push    eax
        fild    dword [esp]

        push    100000
        fidiv   dword [esp]

        push    2
        fimul   dword [esp]
        pop     eax

        push    1
        fisub   dword [esp]
        pop     eax

        fstp    dword [esp]
        pop     eax
        pop     edx

        ret
endp

