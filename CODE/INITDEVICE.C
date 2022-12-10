proc InitDevice
     invoke     Direct3DCreate9, D3D_SDK_VERSION
     mov        [pD3D], eax
     lea        edx, [pD3DDevice]
     comcall    eax, IDirect3D9, CreateDevice,\
                                 D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, [hwndDesc],\
                                 D3DCREATE_HARDWARE_VERTEXPROCESSING, d3dppDemo,\
                                 edx
     D3DRS_CULLMODE = 22
     comcall    [pD3DDevice], IDirect3DDevice9, SetFVF, TVertex.FVF
     comcall    [pD3DDevice], IDirect3DDevice9, SetRenderState, D3DRS_LIGHTING, ebx
     comcall    [pD3DDevice], IDirect3DDevice9, SetRenderState, D3DRS_CULLMODE, D3DCULL_NONE
     comcall    [pD3DDevice], IDirect3DDevice9, SetRenderState, D3DRS_FILLMODE, D3DFILL_WIREFRAME

     invoke     D3DXMatrixLookAtLH, matView, vecEye, vecAt, vecUp
     comcall    [pD3DDevice], IDirect3DDevice9, SetTransform, D3DTS_VIEW, matView

     fild       [rcClient.right]
     fidiv      [rcClient.bottom]
     fstp       [fAspect]

     invoke     D3DXMatrixPerspectiveFovLH, matProj, 1.57, [fAspect], 1.0, 1000000.0
     comcall    [pD3DDevice], IDirect3DDevice9, SetTransform, D3DTS_PROJECTION, matProj
     ret
endp


