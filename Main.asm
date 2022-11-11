format PE GUI 4.0
entry WinMain
include 'win32w.inc'


proc DemoWindow.WindowProc uses ebx esi edi,\
     hWnd, uMsg, wParam, lParam
     cmp     [uMsg], WM_DESTROY
     je      .WMDestroy
.Default:
     invoke  DefWindowProc, [hWnd], [uMsg], [wParam], [lParam]
     jmp     .EndProc
.WMDestroy:
     invoke  PostQuitMessage, 0
     jmp     .Default
.EndProc:
     ret
endp



proc WinMain
     locals
        Msg             MSG
        pD3D            dd      ?
        pD3DDevice      dd      ?
     endl

     xor     ebx, ebx
     invoke  RegisterClassEx, DemoWindow.wcexClass
     invoke  ShowCursor, ebx
     invoke  CreateWindowExW, ebx, DemoWindow.szClassName, ebx, WS_POPUP or WS_VISIBLE or WS_MAXIMIZE,\
                             ebx, ebx, ebx, ebx, ebx, ebx, ebx, ebx

     mov     esi, eax
     invoke  Direct3DCreate9, D3D_SDK_VERSION
     mov     [pD3D], eax
     lea     edx, [pD3DDevice]
     comcall eax, IDirect3D9, CreateDevice, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, esi,\
                                            D3DCREATE_HARDWARE_VERTEXPROCESSING, d3dppDemo,\
                                            edx
     lea     edi, [Msg]
.MsgLoop:
     invoke  PeekMessage, edi, ebx, ebx, ebx, PM_REMOVE
     test    eax, eax
     jnz     .ProcessMessage
     invoke  GetTickCount
     comcall [pD3DDevice], IDirect3DDevice9, Clear, ebx, ebx, D3DCLEAR_TARGET, eax, ebx, ebx
     comcall [pD3DDevice], IDirect3DDevice9, Present, ebx, ebx, ebx, ebx
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



ImageBase = $ - rva $
nil       = 0

DemoWindow.szClassName    du              'Demo', 0
DemoWindow.wcexClass      WNDCLASSEX      sizeof.WNDCLASSEX, CS_GLOBALCLASS,\
                                          DemoWindow.WindowProc, 0, 0, ImageBase,\
                                          0, 0, 0, nil, DemoWindow.szClassName, 0