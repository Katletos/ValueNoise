; Ёквивалент D3DXMatrixPerspectiveFovLH
proc Matrix.D3DXMatrixPerspectiveFovLH uses edi,\
     pDest, fovY, Aspect, zn, zf


     stdcall    Memory.Zero, [pDest], sizeof.D3DMATRIX

     fld        [fovY]
     fld1
     fst        [eax + D3DMATRIX._34]
     fadd       st0, st0
     fdivp
     fptan
     fdivrp
     fst        [eax + D3DMATRIX._22]
     fdiv       [Aspect]
     fstp       [eax + D3DMATRIX._11]

     fld        [zn]            ; => [zn]
     fld        [zf]            ; => [zn] [zf]
     fld        st0             ; => [zn] [zf] [zf]
     fsub       st0, st2        ; => [zn] [zf] [zf - zn]
     fdivp                      ; => [zn] [zf / (zf - zn)]
     fst        [eax + D3DMATRIX._33]
     fmulp                      ; => [zn * zf / (zf - zn)]
     fchs                       ; => [-zn * zf / (zf - zn)]
     fstp       [eax + D3DMATRIX._43]
     ret
endp

proc Matrix.D3DXMatrixRotationY,\
     pDest, Angle

        stdcall    Memory.Zero, [pDest], sizeof.D3DMATRIX

        fld     [Angle]                 ; [A]
        fcos                            ; [cos A]
        fst     [eax + D3DMATRIX._11]
        fstp    [eax + D3DMATRIX._33]
        fld1                            ; [1]
        fst     [eax + D3DMATRIX._22]
        fstp    [eax + D3DMATRIX._44]
        fld     [Angle]                 ; [A]
        fsin                            ; [sin A]
        fst     [eax + D3DMATRIX._31]
        fchs
        fstp    [eax + D3DMATRIX._13]

        ret
endp

proc Matrix.D3DXMatrixRotationX,\
     pDest, Angle

        stdcall    Memory.Zero, [pDest], sizeof.D3DMATRIX

        fld     [Angle]                 ; [A]
        fcos                            ; [cos A]
        fst     [eax + D3DMATRIX._22]
        fstp    [eax + D3DMATRIX._33]
        fld1                            ; [1]
        fst     [eax + D3DMATRIX._11]
        fstp    [eax + D3DMATRIX._44]
        fld     [Angle]                 ; [A]
        fsin                            ; [sin A]
        fst     [eax + D3DMATRIX._23]
        fchs
        fstp    [eax + D3DMATRIX._32]

        ret
endp

proc Matrix.D3DXMatrixRotationZ,\
     pDest, Angle

        stdcall    Memory.Zero, [pDest], sizeof.D3DMATRIX

        fld     [Angle]                 ; [A]
        fcos                            ; [cos A]
        fst     [eax + D3DMATRIX._11]
        fstp    [eax + D3DMATRIX._22]
        fld1                            ; [1]
        fst     [eax + D3DMATRIX._33]
        fstp    [eax + D3DMATRIX._44]
        fld     [Angle]                 ; [A]
        fsin                            ; [sin A]
        fst     [eax + D3DMATRIX._12]
        fchs
        fstp    [eax + D3DMATRIX._21]

        ret
endp

proc Memory.Zero uses edi,\
     pDest, size

        xor     eax, eax
        mov     ecx, [size]
        mov     edi, [pDest]
        rep stosb

        mov     eax, [pDest]

        ret
endp
