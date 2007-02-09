#ifndef HSMATRIX44_H
#define HSMATRIX44_H

#include "hsGeometry3.h"

struct hsMatrix44 {
  float fMap[4][4]; //this+0x0
  unsigned long fFlags; //this+0x40

public:
  hsMatrix44::hsMatrix44(const struct hsScalarTriple &, const class hsQuat &){}
  hsMatrix44::hsMatrix44();
  void hsMatrix44::DecompRigid(struct hsScalarTriple &, class hsQuat &){}
  static const struct hsMatrix44 & hsMatrix44::IdentityMatrix(){ return hsMatrix44(); }
  static void hsMatrix44::MakeEnvMapMatrices(const struct hsPoint3 &, struct hsMatrix44 *, struct hsMatrix44 *){}
  static void hsMatrix44::MakeCameraMatrices(const struct hsPoint3 &, const struct hsPoint3 &, const struct hsVector3 &, struct hsMatrix44 &, struct hsMatrix44 &){}
  struct hsMatrix44 & hsMatrix44::Translate(const struct hsVector3 *){}
  struct hsMatrix44 & hsMatrix44::Scale(const struct hsVector3 *){}
  struct hsMatrix44 & hsMatrix44::Rotate(int, float){}
  struct hsMatrix44 & hsMatrix44::Reset(int){}
  struct hsMatrix44 & hsMatrix44::MakeTranslateMat(const struct hsVector3 *){}
  struct hsMatrix44 & hsMatrix44::MakeScaleMat(const struct hsVector3 *){}
  struct hsMatrix44 & hsMatrix44::MakeRotateMat(int, float){}
  struct hsMatrix44 & hsMatrix44::Make(const struct hsPoint3 *, const struct hsPoint3 *, const struct hsVector3 *){}
  struct hsMatrix44 & hsMatrix44::MakeUpPreserving(const struct hsPoint3 *, const struct hsPoint3 *, const struct hsVector3 *){}
  struct hsMatrix44 & hsMatrix44::MakeCamera(const struct hsPoint3 *, const struct hsPoint3 *, const struct hsVector3 *){}
  struct hsMatrix44 & hsMatrix44::MakeCameraUpPreserving(const struct hsPoint3 *, const struct hsPoint3 *, const struct hsVector3 *){}
  int hsMatrix44::GetParity(){}
  float hsMatrix44::GetDeterminant(){}
  struct hsMatrix44 * hsMatrix44::GetInverse(struct hsMatrix44 *){}
  struct hsMatrix44 * hsMatrix44::GetTranspose(struct hsMatrix44 *){}
  struct hsMatrix44 * hsMatrix44::GetAdjoint(struct hsMatrix44 *){}
  const struct hsPoint3 hsMatrix44::GetTranslate(){}
  struct hsPoint3 * hsMatrix44::GetTranslate(struct hsPoint3 *){}
  struct hsVector3 * hsMatrix44::GetTranslate(struct hsVector3 *){}
  const struct hsVector3 hsMatrix44::GetAxis(int){}
  void hsMatrix44::GetAxis(struct hsVector3 *, struct hsVector3 *, struct hsVector3 *){}
  void hsMatrix44::GetAxisFromCamera(struct hsVector3 *, struct hsVector3 *, struct hsVector3 *){}
  struct hsMatrix44 & hsMatrix44::SetTranslate(const struct hsScalarTriple *){}
  struct hsMatrix44 & hsMatrix44::SetScale(const struct hsVector3 *){}
  struct hsMatrix44 & hsMatrix44::SetRotate(int, float){}
  struct hsVector3 hsMatrix44::RemoveScale(){}
  void hsMatrix44::MakeXRotation(float){}
  void hsMatrix44::MakeYRotation(float){}
  void hsMatrix44::MakeZRotation(float){}
  struct hsMatrix44 hsMatrix44::operator*(const struct hsMatrix44 &){}
  struct hsVector3 hsMatrix44::operator*(const struct hsVector3 &){}
  struct hsPoint3 hsMatrix44::operator*(const struct hsPoint3 &){}
  struct hsPoint3 * hsMatrix44::MapPoints(long, struct hsPoint3 *){}
  unsigned long hsMatrix44::IsIdentity(){}
  void hsMatrix44::NotIdentity(){}
  int hsMatrix44::operator==(const struct hsMatrix44 &){}
  int hsMatrix44::operator!=(const struct hsMatrix44 &){}
  void hsMatrix44::Read(class hsStream *){}
  void hsMatrix44::Write(class hsStream *){}
};

#endif
