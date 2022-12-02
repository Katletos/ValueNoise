format PE GUI 4.0
entry WinMain
include 'win32w.inc'

proc WinMain
    xor     ebx, ebx
    invoke  RegisterClassExW, DemoWindow.wcexClass
    invoke  ShowCursor, ebx
    invoke  CreateWindowExW, ebx, DemoWindow.szClassName, ebx,\
                             WS_POPUP or WS_VISIBLE or WS_MAXIMIZE,\
                             ebx, ebx, ebx, ebx, ebx, ebx, ebx, ebx

    include '%myinclude%\code\initdevice.c'
    include '%myinclude%\code\initbuffer.c'

    lea     edi, [Msg]
.MsgLoop:
    invoke  PeekMessage, edi, ebx, ebx, ebx, PM_REMOVE
    test    eax, eax
    jz      .MsgLoop
    invoke  TranslateMessage, edi
    invoke  DispatchMessage, edi
    jmp     .MsgLoop
.EndMsgLoop:
endp


proc DemoWindow.WindowProc uses ebx esi edi,\
                           hWnd, uMsg, wParam, lParam
    xor     ebx, ebx
    mov     eax, [uMsg]

    cmp     eax, WM_CREATE
    je      .Create
    cmp     eax, WM_PAINT
    je      .Paint
    cmp     eax, WM_KEYDOWN
    je      .KeyDown
    cmp     eax, WM_DESTROY
    je      .Destroy

    invoke  DefWindowProc, [hWnd], [uMsg], [wParam], [lParam]
    jmp     .Return

.Create:
        ;move here inits
       ; include '%myinclude%\code\initdevice.c'
       ; include '%myinclude%\code\initbuffer.c'
    jmp     .ReturnZero
.Paint:
    include '%myinclude%\code\paint.c'
       ; invoke  InvalidateRect, [hWnd], ebx, ebx
    jmp     .ReturnZero
.KeyDown:
    cmp     [wParam], VK_ESCAPE
    jne     .ReturnZero
.Destroy:
    comcall [pD3D], IDirect3D9, Release
    comcall [pD3DDevice], IDirect3DDevice9, Release
    comcall [pVBuffer], IDirect3DVertexBuffer9, Release
    comcall [pVBuffer], IDirect3DVertexBuffer9, Release
    invoke  ExitProcess, ebx
.ReturnZero:
        xor     eax, eax
.Return:
        ret
endp

Msg             MSG

include          '%myinclude%\data\initdevice.d'
include          '%myinclude%\data\initbuffer.d'
include          '%myinclude%\random\random.d'
include          '%myinclude%\random\random.c'
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





;EyeV     dd      ?
;AtV      dd      ?
;UpV      dd      ?

;fovY     dd      ?
;Aspect   dd      ?


;ToScreenCoordinates     w       0       0               0
;                        0       h       0               0
;                        0       0       zf/(zf-zn)      1
;                        0       0       -zn*zf/(zf-zn)  0

;h = ctg(fovY/2)
;w = h / Aspect


ImageBase = $ - rva $
nil       = 0

DemoWindow.szClassName    du              'Demo', 0
DemoWindow.wcexClass      WNDCLASSEX      sizeof.WNDCLASSEX, CS_GLOBALCLASS,\
                                          DemoWindow.WindowProc, 0, 0, ImageBase,\
                                          0, 0, 0, nil, DemoWindow.szClassName, 0




struct D3DMATRIX
       _11      dd      ?
       _12      dd      ?
       _13      dd      ?
       _14      dd      ?
       _21      dd      ?
       _22      dd      ?
       _23      dd      ?
       _24      dd      ?
       _31      dd      ?
       _32      dd      ?
       _33      dd      ?
       _34      dd      ?
       _41      dd      ?
       _42      dd      ?
       _43      dd      ?
       _44      dd      ?
ends

;D3DTS_VIEW              = 2
;D3DTS_PROJECTION        = 3
;D3DTS_WORLD             = 256




struct TVertex
       x        dd      ?
       y        dd      ?
       z        dd      ?
       rhw      dd      ?
       color    dd      ?
ends

Quad            TVertex                 100.0, 100.0, 0.0, 1.0, $00292929
                TVertex                 200.0, 100.0, 0.0, 1.0, $00262626
                TVertex                 200.0, 200.0, 0.0, 1.0, $00404040
                TVertex                 200.0, 200.0, 0.0, 1.0, $00404040
                TVertex                 100.0, 200.0, 0.0, 1.0, $00454545
                TVertex                 100.0, 100.0, 0.0, 1.0, $00292929
VertexCount     = ($ - Quad) / sizeof.TVertex

TVertex.FVF = D3DFVF_XYZRHW or D3DFVF_DIFFUSE

;zaxis = normal(At – Eye)
;xaxis = normal(cross(Up, zaxis))
;yaxis = cross(zaxis, xaxis)

;WorldAxis       xaxis.x           yaxis.x           zaxis.x           0
;                xaxis.y           yaxis.y           zaxis.y           0
;                xaxis.z           yaxis.z           zaxis.z           0
;                -dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1
