format PE GUI 4.0
entry WinMain
include 'win32w.inc'
        
proc WinMain
     locals
        Msg             MSG
        pD3D            dd      ?
        pD3DDevice      dd      ?
        EDIT            du  'EDIT', 0
     endl

     ;Use standard lpClassName
     xor     ebx, ebx
     lea edx, [EDIT]
     ;Create window
     invoke  CreateWindowEx, ebx, edx, ebx, WS_POPUP or WS_MAXIMIZE or WS_VISIBLE,\
                             ebx, ebx, ebx, ebx, ebx, ebx, ebx, ebx
     ;Hide cursor
     invoke  ShowCursor, ebx

     mov     esi, eax
     invoke  Direct3DCreate9, D3D_SDK_VERSION
     mov     [pD3D], eax
     lea     edx, [pD3DDevice]
;     comcall eax, IDirect3D9, CreateDevice, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, esi,\
;                                            D3DCREATE_HARDWARE_VERTEXPROCESSING, d3dppDemo,\
;                                            edx

     ;Chose vertex format
;     comcall    [pD3DDevice], IDirect3DDevice9, SetFVF, D3DFVF_XYZRHW

     lea     edi, [Msg]
.MsgLoop:
     invoke  PeekMessage, edi, ebx, ebx, ebx, PM_REMOVE
     test    eax, eax
     jnz     .ProcessMessage
;     comcall [pD3DDevice], IDirect3DDevice9, BeginScene
;     comcall [pD3DDevice], IDirect3DDevice9, DrawPrimitiveUP,\
;                                           D3DPT_TRIANGLELIST, 2, Quad, sizeof.TVertex
;     comcall [pD3DDevice], IDirect3DDevice9, Present, ebx, ebx, ebx, ebx
;     comcall [pD3DDevice], IDirect3DDevice9, EndScene
     jmp     .MsgLoop
.ProcessMessage:
     cmp     [Msg.message], WM_QUIT
     je      .EndMsgLoop
     invoke  DispatchMessage, edi
     jmp     .MsgLoop
.EndMsgLoop:
     comcall [pD3DDevice], IDirect3DDevice9, Release
     comcall [pD3D], IDirect3D9, Release
     invoke  ExitProcess, ebx
endp



data import

                  struct TVertex
       x        dd      ?
       y        dd      ?
       z        dd      ?
       rhw      dd      ?
     ends

      Quad   TVertex                 100.0, 100.0, 0.0, 1.0
       TVertex                 200.0, 100.0, 0.0, 1.0
       TVertex                 200.0, 200.0, 0.0, 1.0
       TVertex                 200.0, 200.0, 0.0, 1.0
       TVertex                 100.0, 200.0, 0.0, 1.0
       TVertex                 100.0, 100.0, 0.0, 1.0



        library kernel32, 'kernel32.dll',\
                gdi32,    'gdi32.dll',\
                user32,   'user32.dll',\
                d3d9,     'd3d9.dll'

        include 'api\kernel32.inc'
        include 'api\gdi32.inc'
        include 'api\user32.inc'
        include '%myinclude%\API\d3d9.inc'
        
        include '%myinclude%\EQUATES\d3d9.inc'
end data