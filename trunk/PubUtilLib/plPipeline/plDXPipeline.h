#ifndef PLDXPIPELINE_H
#define PLDXPIPELINE_H

#include "plPipeline.h"
#include "plDXGeneralSettings.h"
#include "plDXTweakSettings.h"
#include "plDXStencilSettings.h"
#include "hsTArray.h"
#include "hsGMatState.h"
#include "hsMatrix44.h"
#include "plDXViewSettings.h"
#include "hsBitVector.h"
#include "plDXFogSettings.h"
#include "plDXLightSettings.h"

class plDXPipeline : public 4plPipeline {
  class plDebugTextManager * fDebugTextMgr; //this+0x14
  class plDXPlateManager * fPlateMgr; //this+0x18
  struct IDirect3D9 * fD3DObject; //this+0x1c
  struct IDirect3DDevice9 * fD3DDevice; //this+0x20
  struct IDirect3DSurface9 * fD3DMainSurface; //this+0x24
  struct IDirect3DSurface9 * fD3DDepthSurface; //this+0x28
  struct IDirect3DSurface9 * fD3DBackBuff; //this+0x2c
  struct IDirect3DSurface9 *[0x2] fSharedDepthSurface; //this+0x30
  enum _D3DFORMAT[0x2] fSharedDepthFormat; //this+0x38
  unsigned long fVtxRefTime; //this+0x40
  unsigned long fNextDynVtx; //this+0x44
  unsigned long fDynVtxSize; //this+0x48
  struct IDirect3DVertexBuffer9 * fDynVtxBuff; //this+0x4c
  int fManagedAlloced; //this+0x50
  int fAllocUnManaged; //this+0x54
  class plDXGeneralSettings fSettings; //this+0x58
  class plDXTweakSettings fTweaks; //this+0x234
  class plDXStencilSettings fStencil; //this+0x260
  int fDeviceLost; //this+0x278
  int fDevWasLost; //this+0x27c
  class hsTArray<plCullPoly const *> fCullPolys; //this+0x280
  class hsTArray<plCullPoly const *> fCullHoles; //this+0x288
  class plDrawableSpans * fCullProxy; //this+0x290
  class plDXVertexBufferRef * fVtxBuffRefList; //this+0x294
  class plDXIndexBufferRef * fIdxBuffRefList; //this+0x298
  class plDXTextureRef * fTextureRefList; //this+0x29c
  class plTextFont * fTextFontRefList; //this+0x2a0
  class plDXRenderTargetRef * fRenderTargetRefList; //this+0x2a4
  class plDXVertexShader * fVShaderRefList; //this+0x2a8
  class plDXPixelShader * fPShaderRefList; //this+0x2ac
  class hsGMaterial * fCurrMaterial; //this+0x2b0
  class plLayerInterface * fCurrLay; //this+0x2b4
  unsigned long fCurrLayerIdx; //this+0x2b8
  unsigned long fCurrNumLayers; //this+0x2bc
  unsigned long fCurrRenderLayer; //this+0x2c0
  unsigned long fCurrLightingMethod; //this+0x2c4
  enum _D3DCULL fCurrCullMode; //this+0x2c8
  class hsGMatState fMatOverOn; //this+0x2cc
  class hsGMatState fMatOverOff; //this+0x2e0
  class hsTArray<hsGMaterial *> fOverrideMat; //this+0x2f4
  class hsGMaterial * fHoldMat; //this+0x2fc
  int fCurrD3DLiteState; //this+0x300
  struct hsMatrix44 fBumpDuMatrix; //this+0x304
  struct hsMatrix44 fBumpDvMatrix; //this+0x348
  struct hsMatrix44 fBumpDwMatrix; //this+0x38c
  class hsTArray<plLayerInterface *> fOverLayerStack; //this+0x3d0
  class plLayerInterface * fOverBaseLayer; //this+0x3d8
  class plLayerInterface * fOverAllLayer; //this+0x3dc
  class hsTArray<plLayerInterface *> fPiggyBackStack; //this+0x3e0
  long fMatPiggyBacks; //this+0x3e8
  long fActivePiggyBacks; //this+0x3ec
  unsigned int fCurrentAdapter; //this+0x3f0
  struct D3DEnum_DriverInfo * fCurrentDriver; //this+0x3f4
  struct D3DEnum_DeviceInfo * fCurrentDevice; //this+0x3f8
  struct D3DEnum_ModeInfo * fCurrentMode; //this+0x3fc
  class hsGDeviceRef *[0x8] fLayerRef; //this+0x400
  class hsGMatState[0x8] fLayerState; //this+0x420
  class hsGMatState[0x8] fOldLayerState; //this+0x4c0
  unsigned long[0x8] fLayerTransform; //this+0x560
  float[0x8] fLayerLODBias; //this+0x580
  unsigned long[0x8] fLayerUVWSrcs; //this+0x5a0
  unsigned long[0x8] fLayerXformFlags; //this+0x5c0
  unsigned long fLastEndingStage; //this+0x5e0
  int fTexturing; //this+0x5e4
  int fForceMatHandle; //this+0x5e8
  unsigned long fInSceneDepth; //this+0x5ec
  unsigned long fTextUseTime; //this+0x5f0
  unsigned long fEvictTime; //this+0x5f4
  unsigned long fManagedSeen; //this+0x5f8
  unsigned long fManagedCutoff; //this+0x5fc
  double fTime; //this+0x600
  unsigned long fFrame; //this+0x608
  unsigned long fRenderCnt; //this+0x60c
  class plDXViewSettings fView; //this+0x610
  class hsBitVector fDebugFlags; //this+0x90c
  unsigned long fDebugSpanGraphY; //this+0x918
  class plDXFogSettings fCurrFog; //this+0x91c
  class plDXLightSettings fLights; //this+0x948
  class hsTArray<plShadowSlave *> fShadows; //this+0x9b0
  class hsTArray<plRenderTarget *> fRenderTargetPool512; //this+0x9b8
  class hsTArray<plRenderTarget *> fRenderTargetPool256; //this+0x9c0
  class hsTArray<plRenderTarget *> fRenderTargetPool128; //this+0x9c8
  class hsTArray<plRenderTarget *> fRenderTargetPool64; //this+0x9d0
  class hsTArray<plRenderTarget *> fRenderTargetPool32; //this+0x9d8
  unsigned long[0xa] fRenderTargetNext; //this+0x9e0
  class plDXTextureRef * fULutTextureRef; //this+0xa08
  class plRenderTarget *[0xa] fBlurScratchRTs; //this+0xa0c
  class plRenderTarget *[0xa] fBlurDestRTs; //this+0xa34
  struct IDirect3DVertexBuffer9 *[0xa] fBlurVBuffers; //this+0xa5c
  unsigned long fBlurVSHandle; //this+0xa84
  class hsTArray<plClothingOutfit *> fClothingOutfits; //this+0xa88
  class plDrawableSpans * fBoundsSpans; //this+0xa90
  class hsGMaterial * fBoundsMat; //this+0xa94
  class hsTArray<unsigned long> fBSpansToDelete; //this+0xa98
  class plStatusLogDrawer * fLogDrawer; //this+0xaa0
  int fVSync; //this+0xaa4
  int fForceDeviceReset; //this+0xaa8

public:
  void plDXPipeline(const class plDXPipeline &){}
  void plDXPipeline::plDXPipeline(struct HWND__ *, const class hsG3DDeviceModeRecord *){}
  void plDXPipeline::~plDXPipeline(){}
  const char * plDXPipeline::ClassName(){}
  unsigned short plDXPipeline::ClassIndex(){}
  static unsigned short Index(){}
  static class plDXPipeline * Create(){}
  static const class plDXPipeline * ConvertNoRef(const class plCreatable *){}
  static class plDXPipeline * plDXPipeline::ConvertNoRef(class plCreatable *){}
  static class plDXPipeline * Convert(class plCreatable *){}
  static int HasDerivedClass(unsigned short){}
  static int HasBaseClass(unsigned short){}
  class plCreatable * plDXPipeline::GetInterface(unsigned short){}
  const class plCreatable * plDXPipeline::GetConstInterface(unsigned short){}
  struct IDirect3DDevice9 * plDXPipeline::GetD3DDevice(){}
  int plDXPipeline::PreRender(class plDrawable *, class hsTArray<short> &, class plVisMgr *){}
  int plDXPipeline::PrepForRender(class plDrawable *, class hsTArray<short> &, class plVisMgr *){}
  void plDXPipeline::Render(class plDrawable *, const class hsTArray<short> &){}
  void plDXPipeline::Draw(class plDrawable *){}
  void plDXPipeline::PushRenderRequest(class plRenderRequest *){}
  void plDXPipeline::PopRenderRequest(class plRenderRequest *){}
  void plDXPipeline::ResetDisplayDevice(int, int, int, int, int, int, int){}
  void plDXPipeline::ClearRenderTarget(const struct hsColorRGBA *, const float *){}
  void plDXPipeline::ClearRenderTarget(class plDrawable *){}
  void plDXPipeline::SetClear(const struct hsColorRGBA *, const float *){}
  struct hsColorRGBA plDXPipeline::GetClearColor(){}
  float plDXPipeline::GetClearDepth(){}
  class hsGDeviceRef * plDXPipeline::MakeRenderTargetRef(class plRenderTarget *){}
  class hsGDeviceRef * plDXPipeline::SharedRenderTargetRef(class plRenderTarget *, class plRenderTarget *){}
  void plDXPipeline::PushRenderTarget(class plRenderTarget *){}
  class plRenderTarget * plDXPipeline::PopRenderTarget(){}
  unsigned long plDXPipeline::BeginRender(){}
  unsigned long plDXPipeline::EndRender(){}
  void plDXPipeline::RenderScreenElements(){}
  unsigned long plDXPipeline::BeginDrawable(class plDrawable *){}
  unsigned long plDXPipeline::EndDrawable(class plDrawable *){}
  void plDXPipeline::BeginVisMgr(class plVisMgr *){}
  void plDXPipeline::EndVisMgr(class plVisMgr *){}
  unsigned long plDXPipeline::IsFullScreen(){}
  unsigned long plDXPipeline::Width(){}
  unsigned long plDXPipeline::Height(){}
  unsigned long plDXPipeline::ColorDepth(){}
  void plDXPipeline::Resize(unsigned long, unsigned long){}
  unsigned long plDXPipeline::TestVisibleWorld(const class plSceneObject *){}
  unsigned long plDXPipeline::TestVisibleWorld(const class hsBounds3Ext &){}
  unsigned long plDXPipeline::HarvestVisible(class plSpaceTree *, class hsTArray<short> &){}
  unsigned long plDXPipeline::SubmitOccluders(const class hsTArray<plCullPoly const *> &){}
  void plDXPipeline::SetDebugFlag(unsigned long, int){}
  int plDXPipeline::IsDebugFlagSet(unsigned long){}
  void plDXPipeline::SetMaxCullNodes(unsigned short){}
  unsigned short plDXPipeline::GetMaxCullNodes(){}
  void plDXPipeline::LoadResources(){}
  void plDXPipeline::SetProperty(unsigned long, int){}
  int plDXPipeline::GetProperty(unsigned long){}
  unsigned long plDXPipeline::GetMaxLayersAtOnce(){}
  void plDXPipeline::SetDrawableTypeMask(unsigned long){}
  unsigned long plDXPipeline::GetDrawableTypeMask(){}
  void plDXPipeline::SetSubDrawableTypeMask(unsigned long){}
  unsigned long plDXPipeline::GetSubDrawableTypeMask(){}
  class plTextFont * plDXPipeline::MakeTextFont(char *, unsigned short){}
  void plDXPipeline::CheckVertexBufferRef(class plGBufferGroup *, unsigned long){}
  void plDXPipeline::CheckIndexBufferRef(class plGBufferGroup *, unsigned long){}
  int plDXPipeline::OpenAccess(class plAccessSpan &, class plDrawableSpans *, const class plVertexSpan *, int){}
  int plDXPipeline::CloseAccess(class plAccessSpan &){}
  void plDXPipeline::CheckTextureRef(class plLayerInterface *){}
  static void plDXPipeline::FreeManagedTexture(unsigned long){}
  static void AllocManagedTexture(unsigned long){}
  static void plDXPipeline::FreeManagedVertex(unsigned long){}
  static void plDXPipeline::AllocManagedVertex(unsigned long){}
  static short plDXPipeline::GetDXBitDepth(enum _D3DFORMAT){}
  void plDXPipeline::SetDefaultFogEnviron(class plFogEnvironment *){}
  const class plFogEnvironment & plDXPipeline::GetDefaultFogEnviron(){}
  struct hsPoint3 plDXPipeline::GetViewPositionWorld(){}
  struct hsVector3 plDXPipeline::GetViewAcrossWorld(){}
  struct hsVector3 plDXPipeline::GetViewUpWorld(){}
  struct hsVector3 plDXPipeline::GetViewDirWorld(){}
  void plDXPipeline::GetViewAxesWorld(struct hsVector3 *){}
  void plDXPipeline::GetFOV(float &, float &){}
  void plDXPipeline::SetFOV(float, float){}
  void plDXPipeline::GetSize(float &, float &){}
  void plDXPipeline::SetSize(float, float){}
  void plDXPipeline::GetDepth(float &, float &){}
  void plDXPipeline::SetDepth(float, float){}
  float plDXPipeline::GetZBiasScale(){}
  void plDXPipeline::SetZBiasScale(float){}
  const struct hsMatrix44 & plDXPipeline::GetWorldToCamera(){}
  const struct hsMatrix44 & plDXPipeline::GetCameraToWorld(){}
  void plDXPipeline::SetWorldToCamera(const struct hsMatrix44 &, const struct hsMatrix44 &){}
  void plDXPipeline::SetViewTransform(const class plViewTransform &){}
  const class plViewTransform & plDXPipeline::GetViewTransform(){}
  const struct hsMatrix44 & plDXPipeline::GetWorldToLocal(){}
  const struct hsMatrix44 & plDXPipeline::GetLocalToWorld(){}
  void plDXPipeline::ScreenToWorldPoint(int, unsigned long, long *, long *, float, unsigned long, struct hsPoint3 *){}
  void plDXPipeline::RefreshMatrices(){}
  void plDXPipeline::RefreshScreenMatrices(){}
  void plDXPipeline::RegisterLight(class plLightInfo *){}
  void plDXPipeline::UnRegisterLight(class plLightInfo *){}
  class hsGMaterial * plDXPipeline::PushOverrideMaterial(class hsGMaterial *){}
  void plDXPipeline::PopOverrideMaterial(class hsGMaterial *){}
  class hsGMaterial * plDXPipeline::GetOverrideMaterial(){}
  class plLayerInterface * plDXPipeline::AppendLayerInterface(class plLayerInterface *, int){}
  class plLayerInterface * plDXPipeline::RemoveLayerInterface(class plLayerInterface *, int){}
  class plLayerInterface * plDXPipeline::PushPiggyBackLayer(class plLayerInterface *){}
  class plLayerInterface * plDXPipeline::PopPiggyBackLayer(class plLayerInterface *){}
  unsigned long plDXPipeline::GetMaterialOverrideOn(enum hsGMatState::StateIdx){}
  unsigned long plDXPipeline::GetMaterialOverrideOff(enum hsGMatState::StateIdx){}
  class hsGMatState plDXPipeline::PushMaterialOverride(enum hsGMatState::StateIdx, unsigned long, unsigned long){}
  class hsGMatState plDXPipeline::PushMaterialOverride(const class hsGMatState &, int){}
  void plDXPipeline::PopMaterialOverride(const class hsGMatState &, int){}
  const class hsGMatState & plDXPipeline::GetMaterialOverride(int){}
  class hsColorOverride plDXPipeline::PushColorOverride(const class hsColorOverride &){}
  void plDXPipeline::PopColorOverride(const class hsColorOverride &){}
  const class hsColorOverride & plDXPipeline::GetColorOverride(){}
  void plDXPipeline::SubmitShadowSlave(class plShadowSlave *){}
  void plDXPipeline::SubmitClothingOutfit(class plClothingOutfit *){}
  int plDXPipeline::SetGamma(const unsigned short * const, const unsigned short * const, const unsigned short * const){}
  int plDXPipeline::SetGamma(float, float, float){}
  int plDXPipeline::CaptureScreen(class plMipmap *, bool, unsigned short, unsigned short){}
  class plMipmap * plDXPipeline::ExtractMipMap(class plRenderTarget *){}
  const char * plDXPipeline::GetErrorString(){}
  int ManagedAlloced(){}
  void plDXPipeline::GetSupportedColorDepths(class hsTArray<int> &){}
  void plDXPipeline::GetSupportedDisplayModes(class std::vector<plDisplayMode,std::allocator<plDisplayMode> > *, int){}
  int plDXPipeline::GetMaxAnisotropicSamples(){}
  int plDXPipeline::GetMaxAntiAlias(int, int, int){}
  void * __vecDelDtor(unsigned int){}

private:
  static void plDXPipeline::SetClassIndex(unsigned short){}

protected:
  void plDXPipeline::IBeginAllocUnManaged(){}
  void plDXPipeline::IEndAllocUnManaged(){}
  void plDXPipeline::ICheckTextureUsage(){}
  void plDXPipeline::ICheckVtxUsage(){}
  void plDXPipeline::ICheckVBUsage(class plDXVertexBufferRef *){}
  int plDXPipeline::IRefreshDynVertices(class plGBufferGroup *, class plDXVertexBufferRef *){}
  int plDXPipeline::ICheckAuxBuffers(const class plAuxSpan *){}
  int plDXPipeline::ICheckDynBuffers(class plDrawableSpans *, class plGBufferGroup *, const class plSpan *){}
  void plDXPipeline::ICheckStaticVertexBuffer(class plDXVertexBufferRef *, class plGBufferGroup *, unsigned long){}
  void plDXPipeline::ICheckIndexBuffer(class plDXIndexBufferRef *){}
  void plDXPipeline::IFillStaticVertexBufferRef(class plDXVertexBufferRef *, class plGBufferGroup *, unsigned long){}
  void plDXPipeline::IFillIndexBufferRef(class plDXIndexBufferRef *, class plGBufferGroup *, unsigned long){}
  void plDXPipeline::ISetupVertexBufferRef(class plGBufferGroup *, unsigned long, class plDXVertexBufferRef *){}
  void plDXPipeline::ISetupIndexBufferRef(class plGBufferGroup *, unsigned long, class plDXIndexBufferRef *){}
  void plDXPipeline::ICreateDynamicBuffers(){}
  void plDXPipeline::IReleaseDynamicBuffers(){}
  void plDXPipeline::IAddBoundsSpan(class plDrawableSpans *, const class hsBounds3Ext *, unsigned long){}
  void plDXPipeline::IAddNormalsSpan(class plDrawableSpans *, class plIcicle *, class plDXVertexBufferRef *, unsigned long){}
  int plDXPipeline::IFlipSurface(){}
  long plDXPipeline::IGetBufferD3DFormat(unsigned char){}
  unsigned long plDXPipeline::IGetBufferFormatSize(unsigned char){}
  void plDXPipeline::IGetVisibleSpans(class plDrawableSpans *, class hsTArray<short> &, class plVisMgr *){}
  void plDXPipeline::IRenderSpans(class plDrawableSpans *, const class hsTArray<short> &){}
  int plDXPipeline::ILoopOverLayers(const class plRenderPrimFunc &, class hsGMaterial *, const class plSpan &){}
  void plDXPipeline::IRenderBufferSpan(const class plIcicle &, class hsGDeviceRef *, class hsGDeviceRef *, class hsGMaterial *, unsigned long, unsigned long, unsigned long, unsigned long){}
  void plDXPipeline::IRenderAuxSpan(const class plSpan &, const class plAuxSpan *){}
  void plDXPipeline::IRenderAuxSpans(const class plSpan &){}
  void plDXPipeline::IGetVSFogSet(float * const){}
  void plDXPipeline::ISetFogParameters(const class plSpan *, const class plLayerInterface *){}
  class hsGDeviceRef * plDXPipeline::IMakeLightRef(class plLightInfo *){}
  void plDXPipeline::IScaleD3DLight(class plDXLightRef *, float){}
  void plDXPipeline::ICalcLighting(const class plLayerInterface *, const class plSpan *){}
  void plDXPipeline::IDisableSpanLights(){}
  void plDXPipeline::IRestoreSpanLights(){}
  void plDXPipeline::ISelectLights(class plSpan *, int, int){}
  void plDXPipeline::IEnableLights(class plSpan *){}
  void plDXPipeline::IMakeLightLists(class plVisMgr *){}
  void plDXPipeline::ICheckLighting(class plDrawableSpans *, class hsTArray<short> &, class plVisMgr *){}
  void plDXPipeline::inlEnsureLightingOff(){}
  void plDXPipeline::inlEnsureLightingOn(){}
  void plDXPipeline::IRenderProjection(const class plRenderPrimFunc &, class plLightInfo *){}
  void plDXPipeline::IRenderProjections(const class plRenderPrimFunc &){}
  void plDXPipeline::IRenderProjectionEach(const class plRenderPrimFunc &, class hsGMaterial *, int, const class plSpan &){}
  void plDXPipeline::IRenderOverWire(const class plRenderPrimFunc &, class hsGMaterial *, const class plSpan &){}
  int plDXPipeline::ISkipBumpMap(class hsGMaterial *, unsigned long &, const class plSpan *){}
  void plDXPipeline::ISetBumpMatrices(const class plLayerInterface *, const class plSpan *){}
  const struct hsMatrix44 & plDXPipeline::IGetBumpMatrix(unsigned long){}
  const class hsGMatState & plDXPipeline::ICompositeLayerState(int, class plLayerInterface *){}
  long plDXPipeline::IHandleMaterial(class hsGMaterial *, unsigned long, const class plSpan *){}
  void plDXPipeline::IHandleFirstTextureStage(class plLayerInterface *){}
  void plDXPipeline::IHandleShadeMode(){}
  void plDXPipeline::IHandleZMode(){}
  void plDXPipeline::IHandleMiscMode(){}
  void plDXPipeline::IHandleTextureStage(unsigned long, class plLayerInterface *){}
  void plDXPipeline::IHandleFirstStageBlend(){}
  void plDXPipeline::IHandleBumpEnv(int, unsigned long){}
  void plDXPipeline::IHandleStageBlend(int){}
  void plDXPipeline::IHandleStageClamp(int){}
  void plDXPipeline::IHandleStageTransform(int, class plLayerInterface *){}
  void plDXPipeline::IHandleTextureMode(class plLayerInterface *){}
  void plDXPipeline::IUseTextureRef(int, class hsGDeviceRef *, class plLayerInterface *){}
  void plDXPipeline::IStageStop(unsigned long){}
  unsigned long plDXPipeline::ILayersAtOnce(class hsGMaterial *, unsigned long){}
  int plDXPipeline::ICanEatLayer(class plLayerInterface *){}
  void plDXPipeline::ISetLayer(unsigned long){}
  void plDXPipeline::IBottomLayer(){}
  class plLayerInterface * plDXPipeline::IPushOverBaseLayer(class plLayerInterface *){}
  class plLayerInterface * plDXPipeline::IPopOverBaseLayer(class plLayerInterface *){}
  class plLayerInterface * plDXPipeline::IPushOverAllLayer(class plLayerInterface *){}
  class plLayerInterface * plDXPipeline::IPopOverAllLayer(class plLayerInterface *){}
  int plDXPipeline::ISetNumActivePiggyBacks(){}
  void plDXPipeline::IPushPiggyBacks(class hsGMaterial *){}
  void plDXPipeline::IPopPiggyBacks(){}
  void plDXPipeline::IPushProjPiggyBack(class plLayerInterface *){}
  void plDXPipeline::IPopProjPiggyBacks(){}
  void plDXPipeline::ISetPipeConsts(class plShader *){}
  HRESULT plDXPipeline::ISetShaders(class plShader *, class plShader *){}
  int plDXPipeline::StencilEnable(int){}
  void plDXPipeline::StencilSetCompareFunc(unsigned char, unsigned long){}
  void plDXPipeline::StencilSetMask(unsigned long, unsigned long){}
  void plDXPipeline::StencilSetOps(unsigned char, unsigned char, unsigned char){}
  int plDXPipeline::StencilGetCaps(class plStencilCaps *){}
  class hsGDeviceRef * plDXPipeline::MakeTextureRef(class plLayerInterface *, class plMipmap *){}
  void plDXPipeline::IReloadTexture(class plDXTextureRef *){}
  void plDXPipeline::IFillD3DTexture(class plDXTextureRef *){}
  void plDXPipeline::IFillD3DCubeTexture(class plDXCubeTextureRef *){}
  void plDXPipeline::IGetD3DTextureFormat(class plBitmap *, enum _D3DFORMAT &, unsigned long &){}
  void plDXPipeline::IFormatTextureData(unsigned long, unsigned long, struct hsColor32 * const, void *){}
  void * plDXPipeline::IGetPixelScratch(unsigned long){}
  class hsGDeviceRef * plDXPipeline::IMakeCubicTextureRef(class plLayerInterface *, class plCubicEnvironmap *){}
  int plDXPipeline::IProcessMipmapLevels(class plMipmap *, unsigned long &, unsigned long * &, unsigned long &, unsigned long &, void * &, int){}
  struct IDirect3DTexture9 * plDXPipeline::IMakeD3DTexture(class plDXTextureRef *, enum _D3DFORMAT){}
  struct IDirect3DCubeTexture9 * plDXPipeline::IMakeD3DCubeTexture(class plDXTextureRef *, enum _D3DFORMAT){}
  void plDXPipeline::IMakeOcclusionSnap(){}
  int plDXPipeline::IAvatarSort(class plDrawableSpans *, const class hsTArray<short> &){}
  void plDXPipeline::IBlendVertsIntoBuffer(class plSpan *, struct hsMatrix44 *, int, unsigned char *, unsigned char, unsigned long, unsigned char *, unsigned long, unsigned long, unsigned short){}
  int plDXPipeline::ISoftwareVertexBlend(class plDrawableSpans *, const class hsTArray<short> &){}
  void ILinkDevRef(class plDXDeviceRef *, class plDXDeviceRef * *){}
  void IUnlinkDevRef(class plDXDeviceRef *){}
  unsigned long plDXPipeline::inlGetD3DColor(const struct hsColorRGBA &){}
  struct _D3DCOLORVALUE plDXPipeline::inlPlToD3DColor(const struct hsColorRGBA &, float){}
  void plDXPipeline::IAddErrorMessage(char *){}
  void plDXPipeline::ISetErrorMessage(char *){}
  void plDXPipeline::IGetD3DError(){}
  void plDXPipeline::IShowErrorMessage(char *){}
  int plDXPipeline::ICreateFail(char *){}
  void plDXPipeline::IFPUCheck(){}
  void plDXPipeline::IInvalidateState(){}
  void plDXPipeline::IInitDeviceState(){}
  void plDXPipeline::IClearMembers(){}
  void plDXPipeline::ISetCaps(){}
  void plDXPipeline::IRestrictCaps(const class hsG3DDeviceRecord &){}
  void plDXPipeline::ISetGraphicsCapability(unsigned long){}
  int plDXPipeline::IFindDepthFormat(struct _D3DPRESENT_PARAMETERS_ &){}
  int plDXPipeline::IFindCompressedFormats(){}
  int plDXPipeline::IFindLuminanceFormats(){}
  int plDXPipeline::ITextureFormatAllowed(enum _D3DFORMAT){}
  void plDXPipeline::ISetCurrentDriver(struct D3DEnum_DriverInfo *){}
  void plDXPipeline::ISetCurrentDevice(struct D3DEnum_DeviceInfo *){}
  void plDXPipeline::ISetCurrentMode(struct D3DEnum_ModeInfo *){}
  unsigned long plDXPipeline::ICreateMaster(){}
  unsigned long plDXPipeline::ICreateDevice(int){}
  int plDXPipeline::ICreateNormalSurfaces(){}
  int plDXPipeline::ICreateDeviceObjects(){}
  void plDXPipeline::IReleaseDeviceObjects(){}
  int plDXPipeline::ICreateDynDeviceObjects(){}
  void plDXPipeline::IReleaseDynDeviceObjects(){}
  void plDXPipeline::IReleaseShaders(){}
  int plDXPipeline::IResetDevice(){}
  void plDXPipeline::ISetViewport(){}
  void IUpdateViewVectors(){}
  void plDXPipeline::IRefreshCullTree(){}
  void plDXPipeline::ISetAnisotropy(int){}
  struct D3DXMATRIX & plDXPipeline::IMatrix44ToD3DMatrix(struct D3DXMATRIX &, const struct hsMatrix44 &){}
  void plDXPipeline::ITransformsToD3D(){}
  struct hsMatrix44 plDXPipeline::IGetCameraToNDC(){}
  void plDXPipeline::IProjectionMatrixToD3D(){}
  void plDXPipeline::IWorldToCameraToD3D(){}
  void plDXPipeline::ILocalToWorldToD3D(){}
  void plDXPipeline::ISavageYonHack(){}
  void plDXPipeline::ISetLocalToWorld(const struct hsMatrix44 &, const struct hsMatrix44 &){}
  void plDXPipeline::ISetCullMode(int){}
  int plDXPipeline::IIsViewLeftHanded(){}
  int plDXPipeline::IGetClearViewPort(struct _D3DRECT &){}
  class plViewTransform & plDXPipeline::IGetViewTransform(){}
  void plDXPipeline::IUpdateViewFlags(){}
  void plDXPipeline::ISetupTransforms(class plDrawableSpans *, const class plSpan &, struct hsMatrix44 &){}
  void plDXPipeline::IDrawPlate(class plPlate *){}
  void plDXPipeline::ISetRenderTarget(class plRenderTarget *){}
  int plDXPipeline::IPrepRenderTargetInfo(class plRenderTarget *, enum _D3DFORMAT &, enum _D3DFORMAT &, enum _D3DRESOURCETYPE &){}
  int plDXPipeline::IFindRenderTargetInfo(class plRenderTarget *, enum _D3DFORMAT &, enum _D3DRESOURCETYPE &){}
  static const char * plDXPipeline::IGetDXFormatName(enum _D3DFORMAT){}
  void plDXPipeline::IClearShadowSlaves(){}
  void plDXPipeline::IPreprocessShadows(){}
  int plDXPipeline::IPrepShadowCaster(const class plShadowCaster *){}
  void plDXPipeline::IRenderShadowCasterSpan(class plShadowSlave *, class plDrawableSpans *, const class plIcicle &){}
  void ISetupShadowCastTextureStages(class plShadowSlave *){}
  int plDXPipeline::IRenderShadowCaster(class plShadowSlave *){}
  void plDXPipeline::ISetupShadowLight(class plShadowSlave *){}
  class plDXLightRef * plDXPipeline::INextShadowLight(class plShadowSlave *){}
  int plDXPipeline::IPushShadowCastState(class plShadowSlave *){}
  int plDXPipeline::IPopShadowCastState(class plShadowSlave *){}
  class plDXTextureRef * plDXPipeline::IGetULutTextureRef(){}
  int plDXPipeline::ICreateBlurVBuffers(){}
  void plDXPipeline::IReleaseBlurVBuffers(){}
  void plDXPipeline::IMakeRenderTargetPools(){}
  void plDXPipeline::IResetRenderTargetPools(){}
  class plRenderTarget * plDXPipeline::IFindRenderTarget(unsigned long &, unsigned long &, int){}
  void plDXPipeline::IReleaseRenderTargetPools(){}
  void plDXPipeline::IAttachSlaveToReceivers(int, class plDrawableSpans *, const class hsTArray<short> &){}
  void plDXPipeline::IAttachShadowsToReceivers(class plDrawableSpans *, const class hsTArray<short> &){}
  int plDXPipeline::IAcceptsShadow(const class plSpan *, class plShadowSlave *){}
  int plDXPipeline::IReceivesShadows(const class plSpan *, class hsGMaterial *){}
  void plDXPipeline::ISetShadowFromGroup(class plDrawableSpans *, const class plSpan *, class plLightInfo *){}
  void plDXPipeline::IRenderShadowsOntoSpan(const class plRenderPrimFunc &, const class plSpan *, class hsGMaterial *){}
  void plDXPipeline::ISetupShadowRcvTextureStages(class hsGMaterial *){}
  void plDXPipeline::ISetShadowLightState(class hsGMaterial *){}
  void plDXPipeline::IDisableLightsForShadow(){}
  void plDXPipeline::IEnableShadowLight(class plShadowSlave *){}
  void plDXPipeline::ISetupShadowSlaveTextures(class plShadowSlave *){}
  int plDXPipeline::ISetBlurQuadToRender(class plRenderTarget *){}
  void plDXPipeline::IRenderBlurBackToShadowMap(class plRenderTarget *, class plRenderTarget *, class plRenderTarget *){}
  void plDXPipeline::IRenderBlurFromShadowMap(class plRenderTarget *, class plRenderTarget *, float){}
  void plDXPipeline::IBlurSetRenderTarget(class plRenderTarget *){}
  int plDXPipeline::IGetScratchRenderTarget(class plRenderTarget *){}
  void plDXPipeline::IBlurShadowMap(class plShadowSlave *){}
  void plDXPipeline::IPreprocessAvatarTextures(){}
  void plDXPipeline::IDrawClothingQuad(float, float, float, float, float, float, class plMipmap *){}
  void plDXPipeline::IClearClothingOutfits(){}
  void plDXPipeline::IPrintDeviceInitError(){}
  void plDXPipeline::IResetToDefaults(struct _D3DPRESENT_PARAMETERS_ *){}
};

#endif
