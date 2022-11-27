     comcall    [pD3DDevice], IDirect3DDevice9, Clear,\
                                                ebx, ebx, D3DCLEAR_TARGET, ebx, ebx, ebx
     comcall    [pD3DDevice], IDirect3DDevice9, BeginScene
     comcall    [pD3DDevice], IDirect3DDevice9, DrawPrimitive,\
                                                D3DPT_TRIANGLELIST, ebx, 2 ;2 is a number of primitives, not vertex
     comcall    [pD3DDevice], IDirect3DDevice9, SetStreamSource,\
                                                ebx, [pVBuffer], ebx, sizeof.TVertex
     comcall    [pD3DDevice], IDirect3DDevice9, EndScene
     comcall    [pD3DDevice], IDirect3DDevice9, Present,\
                                                ebx, ebx, ebx, ebx