#ifndef _PLOBJINTERFACE_H
#define _PLOBJINTERFACE_H

#include "../../CoreLib/hsBitVector.h"
#include "../pnNetCommon/plSynchedObject.h"
#include "../pnMessage/plMessage.h"

class plObjInterface : public plSynchedObject {
private:
    plKey * Owner;
    hsBitVector Properties;

public:
    plObjInterface(PlasmaVer pv = pvUnknown);

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);

  class plSceneObject * fOwner; //this+0x5c
  class hsBitVector fProps; //this+0x60

public:
  plObjInterface(const class plObjInterface &);
  plObjInterface::plObjInterface();
  plObjInterface::~plObjInterface();
  const char * plObjInterface::ClassName();
  virtual unsigned short plObjInterface::ClassIndex();
  static unsigned short Index();
  static class plObjInterface * Create();
  static const class plObjInterface * plObjInterface::ConvertNoRef(const class plCreatable *);
  static class plObjInterface * plObjInterface::ConvertNoRef(class plCreatable *);
  static class plObjInterface * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int HasBaseClass(unsigned short);
  class plCreatable * plObjInterface::GetInterface(unsigned short);
  const class plCreatable * plObjInterface::GetConstInterface(unsigned short);
  int plObjInterface::MsgReceive(class plMessage *);
  const class plSceneObject * plObjInterface::GetOwner();
  class plKey plObjInterface::GetOwnerKey();
  class plKey plObjInterface::GetSceneNode();
  void plObjInterface::SetProperty(int, int);
  int plObjInterface::GetProperty(int);
  long GetNumProperties();
  void SetTransform(const struct hsMatrix44 &, const struct hsMatrix44 &);
  void plObjInterface::Read(class hsStream *, class hsResMgr *);
  void plObjInterface::Write(class hsStream *, class hsResMgr *);
  void plObjInterface::ReleaseData();

private:
  static void plObjInterface::SetClassIndex(unsigned short);

protected:
  void plObjInterface::ISetSceneNode(class plKey);
  class plSceneObject * plObjInterface::IGetOwner();
  void plObjInterface::ISetOwner(class plSceneObject *);
  void plObjInterface::ISetAllProperties(const class hsBitVector &);
  class plDrawInterface * IGetOwnerDrawInterface();
  class plSimulationInterface * IGetOwnerSimulationInterface();
  class plCoordinateInterface * IGetOwnerCoordinateInterface();
  class plAudioInterface * IGetOwnerAudioInterface();

};

#endif

