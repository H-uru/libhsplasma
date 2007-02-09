#ifndef PLRENDERTARGET_H
#define PLRENDERTARGET_H

#include "../plGImage/plBitmap.h"
//#include "DirectXInfo.h"
//#include "UncompressedInfo.h"
//#include "plRenderTarget::__unnamed.h"

class plRenderTarget : public plBitmap {
  unsigned short fWidth; //this+0x24
  unsigned short fHeight; //this+0x26
  union
  {
	  struct
	  {
		  unsigned short fLeft; //this+0x0
		  unsigned short fTop; //this+0x2
		  unsigned short fRight; //this+0x4
		  unsigned short fBottom; //this+0x6
	  } fAbsolute;
	  struct
	  {
		  unsigned short fLeft; //this+0x0
		  unsigned short fTop; //this+0x2
		  unsigned short fRight; //this+0x4
		  unsigned short fBottom; //this+0x6
	  } fProportional;

  } fViewport; //this+0x28
  int fApplyTexQuality; //this+0x38
  int fProportionalViewport; //this+0x3c
  unsigned char fZDepth; //this+0x40
  unsigned char fStencilDepth; //this+0x41
  class plCubicRenderTarget * fParent; //this+0x44

public:
  const char * plRenderTarget::ClassName(){}
  unsigned short plRenderTarget::ClassIndex(){}
  static unsigned short Index(){}
  static class plRenderTarget * Create(){}
  static const class plRenderTarget * ConvertNoRef(const class plCreatable *){}
  static class plRenderTarget * plRenderTarget::ConvertNoRef(class plCreatable *){}
  static class plRenderTarget * Convert(class plCreatable *){}
  static int HasDerivedClass(unsigned short){}
  static int HasBaseClass(unsigned short){}
  class plCreatable * plRenderTarget::GetInterface(unsigned short){}
  const class plCreatable * plRenderTarget::GetConstInterface(unsigned short){}
  plRenderTarget(const class plRenderTarget &){}
  plRenderTarget(unsigned short, float, float, float, float, unsigned char, unsigned char, unsigned char){}
  plRenderTarget::plRenderTarget(unsigned short, unsigned short, unsigned short, unsigned char, unsigned char, unsigned char){}
  plRenderTarget::plRenderTarget(){}
  plRenderTarget::~plRenderTarget(){}
  void plRenderTarget::SetViewport(float, float, float, float){}
  void plRenderTarget::SetViewport(unsigned short, unsigned short, unsigned short, unsigned short){}
  unsigned short plRenderTarget::GetWidth(){}
  unsigned short plRenderTarget::GetHeight(){}
  unsigned char plRenderTarget::GetZDepth(){}
  unsigned char plRenderTarget::GetStencilDepth(){}
  unsigned short GetVPLeft(){}
  unsigned short GetVPTop(){}
  unsigned short GetVPRight(){}
  unsigned short GetVPBottom(){}
  float GetVPLeftProp(){}
  float GetVPTopProp(){}
  float GetVPRightProp(){}
  float GetVPBottomProp(){}
  int ViewIsProportional(){}
  class plCubicRenderTarget * plRenderTarget::GetParent(){}
  unsigned long plRenderTarget::GetTotalSize(){}
  int plRenderTarget::MsgReceive(class plMessage *){}
  void plRenderTarget::SetVisRegionName(char *){}
  void plRenderTarget::ApplyTextureQuality(int){}

private:
  static void plRenderTarget::SetClassIndex(unsigned short){}

protected:
  void plRenderTarget::SetKey(class plKey){}
  unsigned long plRenderTarget::Read(class hsStream *){}
  unsigned long plRenderTarget::Write(class hsStream *){}
};

#endif
