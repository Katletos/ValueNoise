 match =D3D_DEBUG_INFO , D3D_DEBUG_INFO
{
  D3D_SDK_VERSION   = 32
  D3D9b_SDK_VERSION = 31
  rept 0 \{
}
match ,
{
  D3D_SDK_VERSION   = 32 or $80000000
  D3D9b_SDK_VERSION = 31 or $80000000
}




; Number of the used video adapter (numbering starts from 0, the main video adapter is always numbered 0)

D3DADAPTER_DEFAULT = 0




;Device Type

D3DDEVTYPE_HAL     = 1
D3DDEVTYPE_REF     = 2
D3DDEVTYPE_SW      = 3
D3DDEVTYPE_NULLREF = 4




;Additional Device Features

D3DCREATE_FPU_PRESERVE                 = $00000002
D3DCREATE_MULTITHREADED                = $00000004
D3DCREATE_PUREDEVICE                   = $00000010
D3DCREATE_SOFTWARE_VERTEXPROCESSING    = $00000020
D3DCREATE_HARDWARE_VERTEXPROCESSING    = $00000040
D3DCREATE_MIXED_VERTEXPROCESSING       = $00000080
D3DCREATE_DISABLE_DRIVER_MANAGEMENT    = $00000100
D3DCREATE_ADAPTERGROUP_DEVICE          = $00000200
D3DCREATE_DISABLE_DRIVER_MANAGEMENT_EX = $00000400
D3DCREATE_NOWINDOWCHANGES              = $00000800

match =D3D_DISABLE_9EX , D3D_DISABLE_9EX
{
D3DCREATE_DISABLE_PSGP_THREADING       = $00002000
D3DCREATE_ENABLE_PRESENTSTATS          = $00004000
D3DCREATE_DISABLE_PRINTSCREEN          = $00008000
D3DCREATE_SCREENSAVER                  = $10000000
}



struct D3DPRESENT_PARAMETERS
       BackBufferWidth                  dd      ?
       BackBufferHeight                 dd      ?
       BackBufferFormat                 dd      ?
       BackBufferCount                  dd      ?
       MultiSampleType                  dd      ?
       MultiSampleQuality               dd      ?
       SwapEffect                       dd      ?
       hDeviceWindow                    dd      ?
       Windowed                         dd      ?
       EnableAutoDepthStencil           dd      ?
       AutoDepthStencilFormat           dd      ?
       Flags                            dd      ?
       FullScreen_RefreshRateInHz       dd      ?
       PresentationInterval             dd      ?
ends





D3DFMT_UNKNOWN = 0                                        
D3DMULTISAMPLE_NONE = 0

D3DSWAPEFFECT_DISCARD = 1
D3DSWAPEFFECT_FLIP    = 2
D3DSWAPEFFECT_COPY    = 3
D3DSWAPEFFECT_OVERLAY = 4
D3DSWAPEFFECT_FLIPEX  = 5                                        

D3DCLEAR_TARGET  = $00000001
D3DCLEAR_ZBUFFER = $00000002
D3DCLEAR_STENCIL = $00000004

MAGENTA = $00FF00FF




; FVF � Flexible Vertex Format Constants

D3DFVF_RESERVED0                        = $0001
D3DFVF_POSITION_MASK                    = $400E
D3DFVF_XYZ                              = $0002
D3DFVF_XYZRHW                           = $0004
D3DFVF_XYZB1                            = $0006
D3DFVF_XYZB2                            = $0008
D3DFVF_XYZB3                            = $000A
D3DFVF_XYZB4                            = $000C
D3DFVF_XYZB5                            = $000E
D3DFVF_XYZW                             = $4002
D3DFVF_NORMAL                           = $0010
D3DFVF_PSIZE                            = $0020
D3DFVF_DIFFUSE                          = $0040
D3DFVF_SPECULAR                         = $0080
D3DFVF_TEXCOUNT_MASK                    = $0F00
D3DFVF_TEXCOUNT_SHIFT                   = 8
D3DFVF_TEX0                             = $0000
D3DFVF_TEX1                             = $0100
D3DFVF_TEX2                             = $0200
D3DFVF_TEX3                             = $0300
D3DFVF_TEX4                             = $0400
D3DFVF_TEX5                             = $0500
D3DFVF_TEX6                             = $0600
D3DFVF_TEX7                             = $0700
D3DFVF_TEX8                             = $0800
D3DFVF_LASTBETA_UBYTE4                  = $1000
D3DFVF_LASTBETA_D3DCOLOR                = $8000
D3DFVF_RESERVED2                        = $6000

;

D3DPT_POINTLIST                         = 1
D3DPT_LINELIST                          = 2
D3DPT_LINESTRIP                         = 3
D3DPT_TRIANGLELIST                      = 4
D3DPT_TRIANGLESTRIP                     = 5
D3DPT_TRIANGLEFAN                       = 6


;SetRenderState

D3DRS_ZENABLE                   = 7
D3DRS_FILLMODE                  = 8
D3DRS_SHADEMODE                 = 9
D3DRS_CULLMODE                  = 22
D3DRS_POINTSIZE                 = 154



;

D3DFILL_POINT                           = 1
D3DFILL_WIREFRAME                       = 2
D3DFILL_SOLID                           = 3


;CreateVertexBuffer
D3DUSAGE_WRITEONLY                      = $00000008
D3DUSAGE_SOFTWAREPROCESSING             = $00000010
D3DUSAGE_DONOTCLIP                      = $00000020
D3DUSAGE_POINTS                         = $00000040
D3DUSAGE_RTPATCHES                      = $00000080
D3DUSAGE_NPATCHES                       = $00000100



D3DPOOL_DEFAULT                         = 0
D3DPOOL_MANAGED                         = 1
D3DPOOL_SYSTEMMEM                       = 2
D3DPOOL_SCRATCH                         = 3



D3DLOCK_READONLY                        = $00000010
D3DLOCK_DISCARD                         = $00002000
D3DLOCK_NOOVERWRITE                     = $00001000
D3DLOCK_NOSYSLOCK                       = $00000800
D3DLOCK_DONOTWAIT                       = $00004000
D3DLOCK_NO_DIRTY_UPDATE                 = $00008000


D3DFMT_INDEX16              =101
D3DFMT_INDEX32              =102


D3DRS_LIGHTING = 137
D3DRS_CULLMODE = 22

D3DCULL_NONE            = 1
D3DCULL_CW              = 2
D3DCULL_CCW             = 3

D3DTS_VIEW              = 2
D3DTS_PROJECTION        = 3
D3DTS_WORLD             = 256