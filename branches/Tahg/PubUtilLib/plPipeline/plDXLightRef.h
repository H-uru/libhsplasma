#ifndef PLDXLIGHTREF_H
#define PLDXLIGHTREF_H

#include "plDXDeviceRef.h"
#include <D3D9.h>

class plDXLightRef : public plDXDeviceRef {
  class plLightInfo * fOwner; //this+0x18
  struct _D3DLIGHT9 fD3DInfo; //this+0x1c
  unsigned long fD3DIndex; //this+0x84
  float fScale; //this+0x88
  class plDXLightSettings * fParentSettings; //this+0x8c
  struct IDirect3DDevice9 * fD3DDevice; //this+0x90

public:
  void plDXLightRef::Link(class plDXLightRef * *){}
  class plDXLightRef * GetNext(){}
  plDXLightRef(const class plDXLightRef &){}
  plDXLightRef::plDXLightRef(){}
  plDXLightRef::~plDXLightRef(){}
  void plDXLightRef::Release(){}
  void plDXLightRef::UpdateD3DInfo(struct IDirect3DDevice9 *, class plDXLightSettings *){}
};

#endif
