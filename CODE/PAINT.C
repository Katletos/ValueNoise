proc Paint
     xor ebx, ebx
     comcall    [pD3DDevice], IDirect3DDevice9, Clear,\
                                                ebx, ebx, D3DCLEAR_TARGET, ebx, ebx, ebx
     comcall    [pD3DDevice], IDirect3DDevice9, BeginScene

     comcall    [pD3DDevice], IDirect3DDevice9, SetStreamSource,\
                                                ebx, [pVBuffer], ebx, sizeof.TVertex

     comcall    [pD3DDevice], IDirect3DDevice9, SetIndices,\
                                                [pIBuffer]

     comcall    [pD3DDevice], IDirect3DDevice9, DrawIndexedPrimitive,\
                                                D3DPT_TRIANGLELIST, ebx, ebx, 100, ebx, 162

     comcall    [pD3DDevice], IDirect3DDevice9, EndScene
     comcall    [pD3DDevice], IDirect3DDevice9, Present,\
                                                ebx, ebx, ebx, ebx
     ret
endp