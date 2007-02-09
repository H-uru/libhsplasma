#ifndef PLCULLPOLY_H
#define PLCULLPOLY_H

#include "../../CoreLib/hsBitVector.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsGeometry3.h"

class plCullPoly {
  unsigned long fFlags; //this+0x0
  class hsBitVector fClipped; //this+0x4
  hsTArray<hsPoint3> fVerts; //this+0x10
  struct hsVector3 fNorm; //this+0x18
  float fDist; //this+0x24
  struct hsPoint3 fCenter; //this+0x28
  float fRadius; //this+0x34

public:
  const struct hsPoint3 & plCullPoly::GetCenter();
  float plCullPoly::GetRadius();
  void SetHole(int);
  void SetTwoSided(int);
  int plCullPoly::IsHole();
  int plCullPoly::IsTwoSided();
  class plCullPoly & plCullPoly::Init(const plCullPoly &);
  class plCullPoly & plCullPoly::Flip(const plCullPoly &);
  class plCullPoly & plCullPoly::InitFromVerts(unsigned long);
  float plCullPoly::ICalcRadius();
  class plCullPoly & plCullPoly::Transform(const struct hsMatrix44 &, const struct hsMatrix44 &, plCullPoly &);
  void plCullPoly::Read(class hsStream *, class hsResMgr *);
  void plCullPoly::Write(class hsStream *, class hsResMgr *);
  int DegenerateVert(const struct hsPoint3 &);
  int plCullPoly::Validate();
  plCullPoly(const plCullPoly &);
  plCullPoly::plCullPoly();
  plCullPoly::~plCullPoly();

private:

protected:
};

#endif
