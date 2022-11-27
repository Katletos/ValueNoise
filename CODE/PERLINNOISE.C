proc noise2d uses ebx esi edi\
             x, y, pHash

     mov     eax, [y]
     div     256

     mov     ebx,


        mov     ebx,


endp

proc Lerp_QunticCurve\
              x,y,t, result
; x+(ttt(t(6t-15)+10))(y-x)
;neeed mem(ten, six and ect) and calc optimization
;+- 3 instractions
     finit
     fld    qword [t]
     fild   [six]
     fmulp
     fild         [fifteen]
     fsubp
     fld    qword [t]
     fmulp
     fild         [ten]
     faddp
     fld    qword [t]
     fmul   st1, st0
     fmul   st1, st0
     fmulp
     fld    qword [y]
     fld    qword [x]
     fsubp
     fmulp
     fld    qword [x]
     faddp
     fst    qword [result]
endp

proc noise2d

endp