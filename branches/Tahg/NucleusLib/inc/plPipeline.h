#ifndef PLPIPELINE_H
#define PLPIPELINE_H

#include "../../NucleusLib/pnFactory/plCreatable.h"
#include "plDisplayMode.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsColorOverride.h"
#include "../../PubUtilLib/plScene/plCullPoly.h"
#include "hsGMatState.h"
#include <vector>

class PipelineParams {
  int Width; //this+0x0
  int Height; //this+0x4
  int Windowed; //this+0x8
  int ColorDepth; //this+0xc
  int AntiAliasingAmount; //this+0x10
  int AnisotropicLevel; //this+0x14
  int TextureQuality; //this+0x18
  int VideoQuality; //this+0x1c
  int Shadows; //this+0x20
  int PlanarReflections; //this+0x24
  int VSync; //this+0x28

public:
  PipelineParams::PipelineParams(){}
};

class plPipeline : public plCreatable {
  class plDisplayMode fDesktopParams; //this+0x8

public:
  const char * plPipeline::ClassName(){}
  unsigned short plPipeline::ClassIndex(){}
  static unsigned short Index(){}
  static class plPipeline * Create(){}
  static const class plPipeline * ConvertNoRef(const class plCreatable * c){}
  static class plPipeline * ConvertNoRef(class plCreatable * c){}
  static class plPipeline * Convert(class plCreatable * c){}
  static int HasDerivedClass(unsigned short){}
  static int HasBaseClass(unsigned short){}
  class plCreatable * plPipeline::GetInterface(unsigned short hClass){}
  const class plCreatable * plPipeline::GetConstInterface(unsigned short hClass){}
  int PreRender(class plDrawable * drawable, hsTArray<short> & visList, class plVisMgr * visMgr){}
  int PrepForRender(class plDrawable * drawable, hsTArray<short> & visList, class plVisMgr * visMgr){}
  void Render(class plDrawable * drawable, const hsTArray<short> & visList){}
  void Draw(class plDrawable *){}
  class plTextFont * MakeTextFont(char *, unsigned short){}
  void CheckVertexBufferRef(class plGBufferGroup *, unsigned long){}
  void CheckIndexBufferRef(class plGBufferGroup *, unsigned long){}
  int OpenAccess(class plAccessSpan &, class plDrawableSpans *, const class plVertexSpan *, int){}
  int CloseAccess(class plAccessSpan &){}
  void CheckTextureRef(class plLayerInterface *){}
  void SetDefaultFogEnviron(class plFogEnvironment *){}
  const class plFogEnvironment & GetDefaultFogEnviron(){}
  void RegisterLight(class plLightInfo *){}
  void UnRegisterLight(class plLightInfo *){}
  void PushRenderRequest(class plRenderRequest *){}
  void PopRenderRequest(class plRenderRequest *){}
  void ClearRenderTarget(const struct hsColorRGBA *, const float *){}
  void ClearRenderTarget(class plDrawable *){}
  void SetClear(const struct hsColorRGBA *, const float *){}
  struct hsColorRGBA GetClearColor(){}
  float GetClearDepth(){}
  class hsGDeviceRef * MakeRenderTargetRef(class plRenderTarget *){}
  void PushRenderTarget(class plRenderTarget *){}
  class plRenderTarget * PopRenderTarget(){}
  unsigned long BeginRender(){}
  unsigned long EndRender(){}
  void RenderScreenElements(){}
  unsigned long BeginDrawable(class plDrawable *){}
  unsigned long EndDrawable(class plDrawable *){}
  void BeginVisMgr(class plVisMgr *){}
  void EndVisMgr(class plVisMgr *){}
  unsigned long IsFullScreen(){}
  unsigned long Width(){}
  unsigned long Height(){}
  unsigned long ColorDepth(){}
  void Resize(unsigned long, unsigned long){}
  unsigned long TestVisibleWorld(const class plSceneObject *){}
  unsigned long TestVisibleWorld(const class hsBounds3Ext &){}
  unsigned long HarvestVisible(class plSpaceTree *, hsTArray<short> &){}
  unsigned long SubmitOccluders(const hsTArray<plCullPoly const *> &){}
  void SetDebugFlag(unsigned long, int){}
  int IsDebugFlagSet(unsigned long){}
  void SetMaxCullNodes(unsigned short){}
  unsigned short GetMaxCullNodes(){}
  void LoadResources(){}
  void SetProperty(unsigned long, int){}
  int GetProperty(unsigned long){}
  unsigned long GetMaxLayersAtOnce(){}
  void SetDrawableTypeMask(unsigned long){}
  unsigned long GetDrawableTypeMask(){}
  void SetSubDrawableTypeMask(unsigned long){}
  unsigned long GetSubDrawableTypeMask(){}
  struct hsPoint3 GetViewPositionWorld(){}
  struct hsVector3 GetViewAcrossWorld(){}
  struct hsVector3 GetViewUpWorld(){}
  struct hsVector3 GetViewDirWorld(){}
  void GetViewAxesWorld(struct hsVector3 *){}
  void GetFOV(float &, float &){}
  void SetFOV(float, float){}
  void GetSize(float &, float &){}
  void SetSize(float, float){}
  void GetDepth(float &, float &){}
  void SetDepth(float, float){}
  void SetZBiasScale(float){}
  float GetZBiasScale(){}
  const struct hsMatrix44 & GetWorldToCamera(){}
  const struct hsMatrix44 & GetCameraToWorld(){}
  void SetWorldToCamera(const struct hsMatrix44 &, const struct hsMatrix44 &){}
  const struct hsMatrix44 & GetWorldToLocal(){}
  const struct hsMatrix44 & GetLocalToWorld(){}
  const class plViewTransform & GetViewTransform(){}
  void ScreenToWorldPoint(int, unsigned long, long *, long *, float, unsigned long, struct hsPoint3 *){}
  void RefreshMatrices(){}
  void RefreshScreenMatrices(){}
  class hsGMaterial * PushOverrideMaterial(class hsGMaterial *){}
  void PopOverrideMaterial(class hsGMaterial *){}
  class hsGMaterial * GetOverrideMaterial(){}
  class plLayerInterface * AppendLayerInterface(class plLayerInterface *, int){}
  class plLayerInterface * RemoveLayerInterface(class plLayerInterface *, int){}
  unsigned long GetMaterialOverrideOn(enum hsGMatState::StateIdx){}
  unsigned long GetMaterialOverrideOff(enum hsGMatState::StateIdx){}
  class hsGMatState PushMaterialOverride(enum hsGMatState::StateIdx, unsigned long, unsigned long){}
  class hsGMatState PushMaterialOverride(const class hsGMatState &, int){}
  void PopMaterialOverride(const class hsGMatState &, int){}
  const class hsGMatState & GetMaterialOverride(int){}
  class hsColorOverride PushColorOverride(const class hsColorOverride &){}
  void PopColorOverride(const class hsColorOverride &){}
  const class hsColorOverride & GetColorOverride(){}
  void SubmitShadowSlave(class plShadowSlave *){}
  void SubmitClothingOutfit(class plClothingOutfit *){}
  int plPipeline::SetGamma(const unsigned short * const table){}
  int plPipeline::SetGamma(float e){}
  int SetGamma(const unsigned short * const, const unsigned short * const, const unsigned short * const){}
  int SetGamma(float, float, float){}
  int CaptureScreen(class plMipmap *, bool, unsigned short, unsigned short){}
  class plMipmap * ExtractMipMap(class plRenderTarget *){}
  const char * GetErrorString(){}
  void GetSupportedDisplayModes(class std::vector<plDisplayMode,std::allocator<plDisplayMode> > *, int){}
  int GetMaxAnisotropicSamples(){}
  int GetMaxAntiAlias(int, int, int){}
  int plPipeline::GetDesktopWidth(){}
  int plPipeline::GetDesktopHeight(){}
  int plPipeline::GetDesktopColorDepth(){}
  struct PipelineParams * plPipeline::GetDefaultParams(){}
  void ResetDisplayDevice(int, int, int, int, int, int, int){}
  plPipeline(const class plPipeline &){}
  plPipeline::plPipeline(){}
  plPipeline::~plPipeline(){}

private:
  static void plPipeline::SetClassIndex(unsigned short){}
};

#endif
