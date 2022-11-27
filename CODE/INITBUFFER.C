        lea        edx, [pVBuffer]
        comcall    [pD3DDevice], IDirect3DDevice9, CreateVertexBuffer,\
                                                   sizeof.TVertex * VertexCount, D3DUSAGE_WRITEONLY,\
                                                   TVertex.FVF, D3DPOOL_DEFAULT, edx, nil

        ;Allocate memory
        invoke     GetProcessHeap
        invoke     HeapAlloc, eax, ebx, 256 * 4 ;int(4bytes) * 256
        mov        [pRandomData], eax
        invoke     GetProcessHeap
        invoke     HeapAlloc, eax, ebx, sizeof.TVertex * VertexCount ;dwBytes must be less than 0x7FFF8 for "non-growable" heap
        mov        [pVertexData], eax


        ;todo generate random
        ;
        ;

        ;
        ;generate vertexes
        mov        ecx, sizeof.TVertex * VertexCount
        mov        esi, Quad
        mov        edi, [pVertexData]
        rep movsb
        ;

        lea        edx, [pBufData]  ;is *pBufData point to mem in videocard?
        comcall    [pVBuffer], IDirect3DVertexBuffer9, Lock,\
                                                       0, sizeof.TVertex * VertexCount, edx,\
                                                       D3DLOCK_DISCARD
        ;Write data from memory to videocard buffer
        mov        ecx, sizeof.TVertex * VertexCount
        mov        esi, [pVertexData]
        mov        edi, [pBufData]
        rep movsb
        comcall    [pVBuffer], IDirect3DVertexBuffer9, Unlock