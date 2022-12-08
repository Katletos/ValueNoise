proc InitRandomData
    ;Create buffer with random data for perlin noise
    stdcall Random.Init

    invoke  GetProcessHeap
    invoke  HeapAlloc, eax, ebx, 256 * 4 ;int(4bytes) * 256 dwBytes must be less than 0x7FFF8 for "non-growable" heap
    mov     [pRandomData], eax

    mov     edx, eax
    xor     ecx, ecx
.RndLoop:
    stdcall Random.Get, 1, 255      ;don't use ecx, edx
    mov     [edx + ecx * 4], eax
    add     ecx, 1
    cmp     ecx, 256
    jl .RndLoop
    ret
endp

proc InitVBuffer
    lea        edx, [pVBuffer]
    comcall    [pD3DDevice], IDirect3DDevice9, CreateVertexBuffer,\
                                               sizeof.TVertex * VertexCount, D3DUSAGE_WRITEONLY,\ ;vertexcount=  100
                                               TVertex.FVF, D3DPOOL_DEFAULT, edx, nil
    lea        edx, [pVBufData]  ;is *pBufData point to mem in videocard?  write vertexes into pBufData
    comcall    [pVBuffer], IDirect3DVertexBuffer9, Lock,\
                                                   0, sizeof.TVertex * VertexCount, edx,\            ;vertexcount = 100
                                                   D3DLOCK_DISCARD
    stdcall    WriteVertexes

    comcall    [pVBuffer], IDirect3DVertexBuffer9, Unlock
    ret
endp

proc  WriteVertexes
    locals
        xoff    dd      ?
        yoff    dd      ?
        x       dd      ?
        y       dd      ?
        noise   dd      ?
    endl

    mov     edx, [pVBufData]

    fldz
    fstp    DWORD [xoff]
    mov     DWORD [x], 0

    jmp .x_for_cmp
.x_for_body:
    fldz
    fstp    DWORD [yoff]
    mov     DWORD [y], 0
    jmp .y_for_cmp
.y_for_body:
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov     eax, [xoff]
    mov     [edx + TVertex.x], eax

    mov     ecx, [yoff]
    mov     [edx + TVertex.y], ecx

    ;stdcall perlin2d, eax, ecx, [freq], [depth]
    fld1
    fstp    DWORD [edx + TVertex.z]

    fld1
    fstp    DWORD [edx + TVertex.rhw]

  ;  mov     eax, [two]
  ;  mov     ecx, [two]
    stdcall perlin2d, eax, ecx, [freq], [depth]
 ;   stdcall  Random.GetFloat
    push    eax
    fld     DWORD [esp]
    fmul    [F255]
    fistp   DWORD [esp]
    pop     eax
 ;   mov     ecx, eax
 ;   shl     ecx, 8
 ;   add     eax, ecx
 ;   shl     ecx, 8
 ;   add     eax, ecx
 ;   or      eax, $00000000

    mov     DWORD [edx + TVertex.color], eax

    add     edx, sizeof.TVertex
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    fld     DWORD [yoff]
    fld     DWORD [delta]
    faddp   st1, st
    fstp    DWORD [yoff]
    add     DWORD [y], 1
.y_for_cmp:
    cmp     DWORD [y], 9
    jle .y_for_body
    fld     DWORD [xoff]
    fld     DWORD [delta]
    faddp   st1, st
    fstp    DWORD [xoff]
    add     DWORD [x], 1
.x_for_cmp:
    cmp     DWORD [x], 9
    jle .x_for_body
    ret
endp

proc InitIBuffer
     lea        edx, [pIBuffer]
     comcall    [pD3DDevice], IDirect3DDevice9, CreateIndexBuffer,\
                                                4*TriangleCount*3, 0,\
                                                D3DFMT_INDEX32, D3DPOOL_MANAGED, edx, 0
     cmp        eax, 0
     jne        0

     lea        edx, [pIBufData]
     comcall    [pIBuffer], IDirect3DIndexBuffer9, Lock,\
                                                    0, 4*TriangleCount*3, edx,\   ;vertexcount = 100
                                                    D3DLOCK_DISCARD
     cmp        eax, 0
     jne        0
     stdcall    WriteIndexes
     comcall    [pIBuffer], IDirect3DIndexBuffer9, Unlock
     ret
endp


proc WriteIndexes
     locals
        x       dd      ?
        i       dd      ?
     endl

     mov        edx, [pIBufData]
     xor        eax, eax
     mov        [x], 0
     jmp .WhileCmp
.WhileBody:
     mov        [i], 0
.ForBody:
     mov        ecx, [x]
     mov        DWORD [edx + eax * 4 + 0], ecx

     add        ecx, 1
     mov        DWORD [edx + eax * 4 + 4], ecx

     add        ecx, 9
     mov        DWORD [edx + eax * 4 + 8], ecx

     add        eax, 3
     add        [x], 1
     add        [i], 1
.ForCmp:
     cmp        [i], 9
     jl  .ForBody
     add        [x], 1

.WhileCmp:
     cmp        [x], XTriangleCount
     jle  .WhileBody


     mov        [x], 1
     jmp .WhileCmp1
.WhileBody1:
     mov        [i], 0
.ForBody1:
     mov        ecx, [x]
     mov        [edx + eax * 4 + 0], ecx

     add        ecx, 10
     mov        [edx + eax * 4 + 4], ecx

     add        ecx, -1
     mov        [edx + eax * 4 + 8], ecx

     add        eax, 3
     add        [x], 1
     add        [i], 1
.ForCmp1:
     cmp        [i], 9
     jl  .ForBody1
     add        [x], 1

.WhileCmp1:
     cmp        [x], XTriangleCount + 1;81
     jl  .WhileBody1
.penis:
     ret
endp


