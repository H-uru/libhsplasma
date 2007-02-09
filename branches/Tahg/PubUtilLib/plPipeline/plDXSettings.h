#ifndef PLDXSETTINGS_H
#define PLDXSETTINGS_H

#include <d3d9.h>
#include "../../CoreLib/hsMatrix44.h"
#include "../../CoreLib/plViewTransform.h"
#include "plFogEnvironment.h"
#include "plCullTree.h"
#include "plRenderTarget.h"

class plDXViewSettings {
  unsigned long fRenderState; //this+0x0
  class plRenderRequest * fRenderRequest; //this+0x4
  unsigned long fDrawableTypeMask; //this+0x8
  unsigned long fSubDrawableTypeMask; //this+0xc
  unsigned long fClearColor; //this+0x10
  float fClearDepth; //this+0x14
  class plFogEnvironment fDefaultFog; //this+0x18
  class plCullTree fCullTree; //this+0x48
  int fCullTreeDirty; //this+0xd0
  unsigned short fCullMaxNodes; //this+0xd4
  unsigned char fXformResetFlags; //this+0xd6
  int fLocalToWorldLeftHanded; //this+0xd8
  int fWorldToCamLeftHanded; //this+0xdc
  struct hsVector3 fDirection; //this+0xe0
  struct hsVector3 fUp; //this+0xec
  struct hsVector3 fAcross; //this+0xf8
  struct hsPoint3 fWorldPos; //this+0x104
  int fViewVectorsDirty; //this+0x110
  struct hsMatrix44 fLocalToWorld; //this+0x114
  struct hsMatrix44 fWorldToLocal; //this+0x158
  class plViewTransform fTransform; //this+0x19c

public:
  const struct hsMatrix44 & GetLocalToWorld(){}
  const struct hsMatrix44 & GetWorldToLocal(){}
  const struct hsMatrix44 & plDXViewSettings::GetWorldToCamera(){}
  const struct hsMatrix44 & plDXViewSettings::GetCameraToWorld(){}
  int plDXViewSettings::IsPerspective(){}
  void plDXViewSettings::Reset(){}
  plDXViewSettings::plDXViewSettings(const class plDXViewSettings &){}
  plDXViewSettings::plDXViewSettings(){}
  plDXViewSettings::~plDXViewSettings(){}
};

class plDXGeneralSettings {
  int fFullscreen; //this+0x0
  struct HWND__ * fHWnd; //this+0x4
  unsigned long fColorDepth; //this+0x8
  unsigned char fNumAASamples; //this+0xc
  unsigned long fD3DCaps; //this+0x10
  unsigned long fBoardKluge; //this+0x14
  unsigned long fStageEnd; //this+0x18
  unsigned long fMaxNumLights; //this+0x1c
  unsigned long fMaxNumProjectors; //this+0x20
  unsigned long fMaxLayersAtOnce; //this+0x24
  unsigned long fMaxPiggyBacks; //this+0x28
  long fBoundsDrawLevel; //this+0x2c
  unsigned long fProperties; //this+0x30
  unsigned long fClearColor; //this+0x34
  unsigned char fMaxAnisotropicSamples; //this+0x38
  struct _D3DPRESENT_PARAMETERS_ fPresentParams; //this+0x3c
  int fVeryAnnoyingTextureInvalidFlag; //this+0x74
  int fNoGammaCorrect; //this+0x78
  int fMaxUVWSrc; //this+0x7c
  int fCantProj; //this+0x80
  int fLimitedProj; //this+0x84
  int fBadManaged; //this+0x88
  int fShareDepth; //this+0x8c
  int fCurrAnisotropy; //this+0x90
  int fIsIntel; //this+0x94
  struct IDirect3DSurface9 * fCurrD3DMainSurface; //this+0x98
  struct IDirect3DSurface9 * fCurrD3DDepthSurface; //this+0x9c
  hsTArray<plDXViewSettings> fViewStack; //this+0xa0
  hsTArray<plRenderTarget *> fRenderTargets; //this+0xa8
  class plRenderTarget * fCurrRenderTarget; //this+0xb0
  class plRenderTarget * fCurrBaseRenderTarget; //this+0xb4
  class plDXDeviceRef * fCurrRenderTargetRef; //this+0xb8
  class plDXVertexBufferRef * fCurrVertexBuffRef; //this+0xbc
  class plDXIndexBufferRef * fCurrIndexBuffRef; //this+0xc0
  unsigned long fOrigWidth; //this+0xc4
  unsigned long fOrigHeight; //this+0xc8
  struct IDirect3DVertexShader9 * fCurrVertexShader; //this+0xcc
  struct IDirect3DPixelShader9 * fCurrPixelShader; //this+0xd0
  unsigned long fCurrFVFFormat; //this+0xd4
  HRESULT fDXError; //this+0xd8
  char fErrorStr[0x100]; //this+0xdc

public:
  void plDXGeneralSettings::Reset(){}
  plDXGeneralSettings(const class plDXGeneralSettings &){}
  plDXGeneralSettings::plDXGeneralSettings(){}
  plDXGeneralSettings::~plDXGeneralSettings(){}
};

class plDXTweakSettings {
  float fDefaultPerspLayerScale; //this+0x0
  float fPerspLayerScale; //this+0x4
  float fPerspLayerTrans; //this+0x8
  float fDefaultLODBias; //this+0xc
  float fFogExpApproxStart; //this+0x10
  float fFogExp2ApproxStart; //this+0x14
  float fFogEndBias; //this+0x18
  float fExp2FogKnee; //this+0x1c
  float fExp2FogKneeVal; //this+0x20
  float fExpFogKnee; //this+0x24
  float fExpFogKneeVal; //this+0x28

public:
  void plDXTweakSettings::Reset(){}
};

class plDXStencilSettings {
  unsigned char fDepth; //this+0x0
  int fEnabled; //this+0x4
  unsigned char fCmpFunc; //this+0x8
  unsigned char fFailOp; //this+0x9
  unsigned char fPassOp; //this+0xa
  unsigned char fPassButZFailOp; //this+0xb
  unsigned long fRefValue; //this+0xc
  unsigned long fMask; //this+0x10
  unsigned long fWriteMask; //this+0x14

public:
  void plDXStencilSettings::Reset(){}
};

class plDXFogSettings {
  class plFogEnvironment * fEnvPtr; //this+0x0
  enum _D3DFOGMODE fMode; //this+0x4
  unsigned char fIsVertex; //this+0x8
  unsigned char fIsShader; //this+0x9
  unsigned long fHexColor; //this+0xc
  float fStart; //this+0x10
  float fEnd; //this+0x14
  float fDensity; //this+0x18
  struct hsColorRGBA fColor; //this+0x1c

public:
  void plDXFogSettings::Reset(){}
};

#endif
