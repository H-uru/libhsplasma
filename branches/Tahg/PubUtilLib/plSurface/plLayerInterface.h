#ifndef PLLAYERINTERFACE_H
#define PLLAYERINTERFACE_H

#include "../../NucleusLib/pnNetCommon/plSynchedObject.h"

class plLayerInterface : public plSynchedObject {
  class plLayerInterface * fUnderLay; //this+0x5c
  class plLayerInterface * fOverLay; //this+0x60
  unsigned long fOwnedChannels; //this+0x64
  unsigned long fPassThruChannels; //this+0x68
  struct hsMatrix44 * fTransform; //this+0x6c
  struct hsColorRGBA * fPreshadeColor; //this+0x70
  struct hsColorRGBA * fRuntimeColor; //this+0x74
  struct hsColorRGBA * fAmbientColor; //this+0x78
  float * fOpacity; //this+0x7c
  class plBitmap * * fTexture; //this+0x80
  class hsGMatState * fState; //this+0x84
  unsigned long * fUVWSrc; //this+0x88
  float * fLODBias; //this+0x8c
  struct hsColorRGBA * fSpecularColor; //this+0x90
  float * fSpecularPower; //this+0x94
  class plShader * * fVertexShader; //this+0x98
  class plShader * * fPixelShader; //this+0x9c
  struct hsMatrix44 * fBumpEnvXfm; //this+0xa0

public:
  plLayerInterface(const class plLayerInterface &){}
  plLayerInterface::plLayerInterface(){}
  plLayerInterface::~plLayerInterface(){}
  const char * plLayerInterface::ClassName(){}
  unsigned short plLayerInterface::ClassIndex(){}
  static unsigned short Index(){}
  static class plLayerInterface * Create(){}
  static const class plLayerInterface * plLayerInterface::ConvertNoRef(const class plCreatable *){}
  static class plLayerInterface * plLayerInterface::ConvertNoRef(class plCreatable *){}
  static class plLayerInterface * Convert(class plCreatable *){}
  static int HasDerivedClass(unsigned short){}
  static int HasBaseClass(unsigned short){}
  class plCreatable * plLayerInterface::GetInterface(unsigned short){}
  const class plCreatable * plLayerInterface::GetConstInterface(unsigned short){}
  class plLayerInterface * plLayerInterface::BottomOfStack(){}
  class plLayerInterface * plLayerInterface::TopOfStack(){}
  class plLayerInterface * plLayerInterface::GetUnderLay(){}
  class plLayerInterface * plLayerInterface::GetOverLay(){}
  const struct hsMatrix44 & plLayerInterface::GetTransform(){}
  const struct hsColorRGBA & plLayerInterface::GetPreshadeColor(){}
  const struct hsColorRGBA & plLayerInterface::GetRuntimeColor(){}
  const struct hsColorRGBA & plLayerInterface::GetAmbientColor(){}
  const struct hsColorRGBA & plLayerInterface::GetSpecularColor(){}
  float plLayerInterface::GetOpacity(){}
  class plBitmap * plLayerInterface::GetTexture(){}
  unsigned long plLayerInterface::GetUVWSrc(){}
  float plLayerInterface::GetLODBias(){}
  float plLayerInterface::GetSpecularPower(){}
  const class hsGMatState & plLayerInterface::GetState(){}
  unsigned long plLayerInterface::GetBlendFlags(){}
  unsigned long plLayerInterface::GetClampFlags(){}
  unsigned long plLayerInterface::GetShadeFlags(){}
  unsigned long plLayerInterface::GetZFlags(){}
  unsigned long plLayerInterface::GetMiscFlags(){}
  class plShader * plLayerInterface::GetVertexShader(){}
  class plShader * plLayerInterface::GetPixelShader(){}
  const struct hsMatrix44 & plLayerInterface::GetBumpEnvMatrix(){}
  void plLayerInterface::ClaimChannels(unsigned long){}
  unsigned long plLayerInterface::Eval(double, unsigned long, unsigned long){}
  class plLayerInterface * plLayerInterface::Attach(class plLayerInterface *){}
  class plLayerInterface * plLayerInterface::Detach(class plLayerInterface *){}
  class plLayerInterface * plLayerInterface::Remove(class plLayerInterface *){}
  class plLayerInterface * plLayerInterface::GetAttached(){}
  void plLayerInterface::AttachViaNotify(class plLayerInterface *){}
  int plLayerInterface::OwnChannel(unsigned long){}
  void plLayerInterface::Read(class hsStream *, class hsResMgr *){}
  void plLayerInterface::Write(class hsStream *, class hsResMgr *){}
  int plLayerInterface::MsgReceive(class plMessage *){}

private:
  static void plLayerInterface::SetClassIndex(unsigned short){}

protected:
  void plLayerInterface::IUnthread(){}
  void plLayerInterface::ISetPassThru(unsigned long){}
};

#endif
