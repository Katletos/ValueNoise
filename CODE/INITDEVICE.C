proc InitDevice
     invoke     Direct3DCreate9, D3D_SDK_VERSION
     mov        [pD3D], eax
     lea        edx, [pD3DDevice]
     comcall    eax, IDirect3D9, CreateDevice,\
                                 D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, [hwndDesc],\
                                 D3DCREATE_HARDWARE_VERTEXPROCESSING, d3dppDemo,\
                                 edx
     comcall    [pD3DDevice], IDirect3DDevice9, SetFVF, TVertex.FVF
     ;d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting
     D3DRS_LIGHTING = 137
     D3DRS_CULLMODE = 22
     D3DCULL_NONE = 1
   ;  comcall    [pD3DDevice], IDirect3DDevice9, SetRenderState, D3DRS_LIGHTING, 0
   ;  comcall    [pD3DDevice], IDirect3DDevice9, SetRenderState, D3DRS_CULLMODE, D3DCULL_NONE

   ;  invoke     D3DXMatrixLookAtLH, matView, vecEye, vecAt, vecUp
   ;  comcall    [pD3DDevice], IDirect3DDevice9, SetTransform, D3DTS_VIEW, matView
   ;  invoke     D3DXMatrixPerspectiveFovLH, matProj, 1.57, 1.0, 1.0, 100.0
   ;  comcall    [pD3DDevice], IDirect3DDevice9, SetTransform, D3DTS_PROJECTION, matProj

     ;d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
     ret
endp
;     comcall    [pD3DDevice], IDirect3DDevice9, SetRenderState, D3DRS_FILLMODE, D3DFILL_WIREFRAME
;     comcall    [pD3DDevice], IDirect3DDevice9, SetRenderState, D3DRS_POINTSIZE, 5.0