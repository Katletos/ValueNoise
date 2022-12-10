proc Paint
 ;    invoke     GetTickCount
 ;    sub        eax, esi
 ;    mov        [tmNow], eax

 ;    fild       [tmNow]
 ;    fidiv      [Divisor]
 ;    fldpi
 ;    fadd       st0, st0
 ;    fmulp
 ;    fstp       [fAngle]

 ;    stdcall    D3DXMatrixRotationY, matWorld, [fAngle]
 ;    comcall    [pD3DDevice], IDirect3DDevice9, SetTransform, D3DTS_WORLD, matWorld

     xor ebx, ebx
     comcall    [pD3DDevice], IDirect3DDevice9, Clear,\
                                                ebx, ebx, D3DCLEAR_TARGET, ebx, ebx, ebx
     comcall    [pD3DDevice], IDirect3DDevice9, BeginScene

     comcall    [pD3DDevice], IDirect3DDevice9, SetStreamSource,\
                                                ebx, [pVBuffer], ebx, sizeof.TVertex

     comcall    [pD3DDevice], IDirect3DDevice9, SetIndices,\
                                                [pIBuffer]

     comcall    [pD3DDevice], IDirect3DDevice9, DrawIndexedPrimitive,\
                                                D3DPT_TRIANGLELIST, ebx, ebx,\
                                                VertexCount, ebx, TriangleCount

     comcall    [pD3DDevice], IDirect3DDevice9, EndScene
     comcall    [pD3DDevice], IDirect3DDevice9, Present,\
                                                ebx, ebx, ebx, ebx
     ret
endp