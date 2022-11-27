     mov        esi, eax
     invoke     Direct3DCreate9, D3D_SDK_VERSION
     mov        [pD3D], eax
     lea        edx, [pD3DDevice]
     comcall    eax, IDirect3D9, CreateDevice,\
                                 D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, esi,\
                                 D3DCREATE_HARDWARE_VERTEXPROCESSING, d3dppDemo,\
                                 edx
     comcall    [pD3DDevice], IDirect3DDevice9, SetFVF, TVertex.FVF
;     comcall    [pD3DDevice], IDirect3DDevice9, SetRenderState, D3DRS_FILLMODE, D3DFILL_WIREFRAME
;     comcall    [pD3DDevice], IDirect3DDevice9, SetRenderState, D3DRS_POINTSIZE, 5.0