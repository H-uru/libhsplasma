#ifndef PLVIEWTRANSFORM_H
#define PLVIEWTRANSFORM_H

#include "hsMatrix44.h"
#include "hsGeometry3.h"

class plViewTransform {
  unsigned long fFlags; //this+0x0
  struct hsMatrix44 fCameraToWorld; //this+0x4
  struct hsMatrix44 fWorldToCamera; //this+0x48
  struct hsPoint3 fMin; //this+0x8c
  struct hsPoint3 fMax; //this+0x98
  unsigned short fWidth; //this+0xa4
  unsigned short fHeight; //this+0xa6
  struct hsPoint3 fViewPortX; //this+0xa8
  struct hsPoint3 fViewPortY; //this+0xb4
  struct hsPoint3 fMapMin; //this+0xc0
  struct hsPoint3 fMapMax; //this+0xcc
  struct hsMatrix44 fCameraToNDC; //this+0xd8
  struct hsMatrix44 fWorldToNDC; //this+0x11c

public:
  plViewTransform::plViewTransform(){}
  plViewTransform::~plViewTransform(){}
  void plViewTransform::Reset(){}
  int plViewTransform::GetOrthogonal(){}
  int plViewTransform::GetPerspective(){}
  int plViewTransform::GetViewPortRelative(){}
  const struct hsMatrix44 & plViewTransform::GetCameraToWorld(){}
  const struct hsMatrix44 & plViewTransform::GetWorldToCamera(){}
  const struct hsMatrix44 & plViewTransform::GetCameraToNDC(){}
  const struct hsMatrix44 & plViewTransform::GetWorldToNDC(){}
  struct hsPoint3 GetPosition(){}
  struct hsVector3 GetDirection(){}
  struct hsVector3 GetUp(){}
  struct hsVector3 GetAcross(){}
  unsigned short plViewTransform::GetScreenWidth(){}
  unsigned short plViewTransform::GetScreenHeight(){}
  void plViewTransform::GetViewPort(int &, int &, int &, int &){}
  void plViewTransform::GetViewPort(struct hsFloatPoint2 &, struct hsFloatPoint2 &){}
  int plViewTransform::GetViewPortWidth(){}
  int plViewTransform::GetViewPortHeight(){}
  int plViewTransform::GetViewPortLeft(){}
  int plViewTransform::GetViewPortTop(){}
  int plViewTransform::GetViewPortRight(){}
  int plViewTransform::GetViewPortBottom(){}
  float plViewTransform::GetViewPortLoX(){}
  float plViewTransform::GetViewPortLoY(){}
  float plViewTransform::GetViewPortHiX(){}
  float plViewTransform::GetViewPortHiY(){}
  struct hsPoint3 GetMapMin(){}
  struct hsPoint3 GetMapMax(){}
  void GetMapping(struct hsPoint3 &, struct hsPoint3 &){}
  float plViewTransform::GetFovX(){}
  float plViewTransform::GetFovY(){}
  float plViewTransform::GetFovXDeg(){}
  float plViewTransform::GetFovYDeg(){}
  float plViewTransform::GetOrthoWidth(){}
  float GetOrthoHeight(){}
  float plViewTransform::GetHither(){}
  float plViewTransform::GetYon(){}
  void plViewTransform::GetDepth(float &, float &){}
  void plViewTransform::SetCameraTransform(const struct hsMatrix44 &, const struct hsMatrix44 &){}
  void plViewTransform::SetOrthogonal(int){}
  void plViewTransform::SetPerspective(int){}
  void plViewTransform::SetWidth(float){}
  void plViewTransform::SetWidth(unsigned short){}
  void plViewTransform::SetHeight(float){}
  void plViewTransform::SetHeight(unsigned short){}
  void plViewTransform::SetScreenSize(unsigned short, unsigned short){}
  void plViewTransform::SetViewPort(unsigned short, unsigned short, unsigned short, unsigned short){}
  void plViewTransform::SetViewPort(float, float, float, float, int){}
  void plViewTransform::SetViewPort(const struct hsFloatPoint2 &, const struct hsFloatPoint2 &, int){}
  void SetMapping(const struct hsPoint3 &, const struct hsPoint3 &){}
  void SetMapMin(const struct hsPoint3 &){}
  void SetMapMax(const struct hsPoint3 &){}
  void SetDepth(const struct hsFloatPoint2 &){}
  void plViewTransform::SetDepth(float, float){}
  void plViewTransform::SetHither(float){}
  void plViewTransform::SetYon(float){}
  void plViewTransform::SetFovDeg(float, float){}
  void SetFovDeg(const struct hsFloatPoint2 &){}
  void plViewTransform::SetFovXDeg(float){}
  void plViewTransform::SetFovYDeg(float){}
  void SetFov(float, float){}
  void SetFov(const struct hsFloatPoint2 &){}
  void plViewTransform::SetFovX(float){}
  void plViewTransform::SetFovY(float){}
  void plViewTransform::SetHalfWidth(float){}
  void plViewTransform::SetHalfHeight(float){}
  void SetWidths(const struct hsFloatPoint2 &){}
  void plViewTransform::SetWidths(float, float){}
  void SetHeights(const struct hsFloatPoint2 &){}
  void plViewTransform::SetHeights(float, float){}
  void plViewTransform::SetView(const struct hsPoint3 &, const struct hsPoint3 &){}
  int plViewTransform::SetProjection(const class hsBounds3 &){}
  int plViewTransform::SetProjectionWorld(const class hsBounds3 &){}
  void PreMultCameraToNDC(const struct hsMatrix44 &){}
  void plViewTransform::PostMultCameraToNDC(const struct hsMatrix44 &){}
  void Recalc(){}
  int plViewTransform::Intersect(const class plViewTransform &){}
  int plViewTransform::Union(const class plViewTransform &){}
  struct hsVector3 ScreenToNDC(const struct hsVector3 &){}
  struct hsPoint3 ScreenToNDC(const struct hsPoint3 &){}
  struct hsScalarTriple plViewTransform::ScreenToNDC(const struct hsScalarTriple &){}
  struct hsVector3 ScreenToCamera(const struct hsVector3 &){}
  struct hsPoint3 plViewTransform::ScreenToCamera(const struct hsPoint3 &){}
  struct hsScalarTriple plViewTransform::ScreenToCamera(const struct hsScalarTriple &){}
  struct hsVector3 ScreenToWorld(const struct hsVector3 &){}
  struct hsPoint3 plViewTransform::ScreenToWorld(const struct hsPoint3 &){}
  struct hsVector3 NDCToScreen(const struct hsVector3 &){}
  struct hsPoint3 NDCToScreen(const struct hsPoint3 &){}
  struct hsScalarTriple plViewTransform::NDCToScreen(const struct hsScalarTriple &){}
  struct hsVector3 NDCToCamera(const struct hsVector3 &){}
  struct hsPoint3 NDCToCamera(const struct hsPoint3 &){}
  struct hsScalarTriple plViewTransform::NDCToCamera(const struct hsScalarTriple &){}
  struct hsVector3 NDCToWorld(const struct hsVector3 &){}
  struct hsPoint3 NDCToWorld(const struct hsPoint3 &){}
  struct hsVector3 CameraToScreen(const struct hsVector3 &){}
  struct hsPoint3 plViewTransform::CameraToScreen(const struct hsPoint3 &){}
  struct hsScalarTriple plViewTransform::CameraToScreen(const struct hsScalarTriple &){}
  struct hsVector3 CameraToNDC(const struct hsVector3 &){}
  struct hsPoint3 CameraToNDC(const struct hsPoint3 &){}
  struct hsScalarTriple plViewTransform::CameraToNDC(const struct hsScalarTriple &){}
  struct hsVector3 CameraToWorld(const struct hsVector3 &){}
  struct hsPoint3 plViewTransform::CameraToWorld(const struct hsPoint3 &){}
  struct hsVector3 WorldToScreen(const struct hsVector3 &){}
  struct hsPoint3 plViewTransform::WorldToScreen(const struct hsPoint3 &){}
  struct hsVector3 WorldToNDC(const struct hsVector3 &){}
  struct hsPoint3 WorldToNDC(const struct hsPoint3 &){}
  struct hsVector3 WorldToCamera(const struct hsVector3 &){}
  struct hsPoint3 plViewTransform::WorldToCamera(const struct hsPoint3 &){}
  struct hsVector3 NDCToMap(const struct hsVector3 &){}
  struct hsPoint3 NDCToMap(const struct hsPoint3 &){}
  struct hsScalarTriple plViewTransform::NDCToMap(const struct hsScalarTriple &){}
  struct hsVector3 CameraToMap(const struct hsVector3 &){}
  struct hsPoint3 CameraToMap(const struct hsPoint3 &){}
  struct hsScalarTriple CameraToMap(const struct hsScalarTriple &){}
  struct hsVector3 WorldToMap(const struct hsVector3 &){}
  struct hsPoint3 WorldToMap(const struct hsPoint3 &){}
  void plViewTransform::Read(class hsStream *){}
  void plViewTransform::Write(class hsStream *){}

protected:
  void plViewTransform::ISetCameraToNDC(){}
  int plViewTransform::ICameraToNDCSet(){}
  const struct hsMatrix44 & plViewTransform::ICheckCameraToNDC(){}
  void plViewTransform::ISetWorldToNDC(){}
  int plViewTransform::IWorldToNDCSet(){}
  const struct hsMatrix44 & plViewTransform::ICheckWorldToNDC(){}
  int plViewTransform::IGetMaxMinsFromBnd(const class hsBounds3 &, struct hsPoint3 &, struct hsPoint3 &){}
  void plViewTransform::InvalidateTransforms(){}
  int plViewTransform::IHasFlag(unsigned long){}
  void plViewTransform::ISetFlag(unsigned long, int){}
};

#endif
