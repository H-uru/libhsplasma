#ifndef _PLSIMULATIONINTERFACE_H
#define _PLSIMULATIONINTERFACE_H

#include "plObjInterface.h"

class plSimulationInterface : public plObjInterface {
protected:
    hsBitVector SimFlags;
    int Unknown;
    plKey * Physical;

public:
    plSimulationInterface(PlasmaVer pv = pvUnknown);

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);

	class plPhysical * fPhysical; //this+0x6c

public:
  plSimulationInterface(const class plSimulationInterface &);
  plSimulationInterface::plSimulationInterface();
  plSimulationInterface::~plSimulationInterface();
  const char * plSimulationInterface::ClassName();
  virtual unsigned short plSimulationInterface::ClassIndex();
  static unsigned short plSimulationInterface::Index();
  static class plSimulationInterface * Create();
  static const class plSimulationInterface * ConvertNoRef(const class plCreatable *);
  static class plSimulationInterface * plSimulationInterface::ConvertNoRef(class plCreatable *);
  static class plSimulationInterface * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int HasBaseClass(unsigned short);
  class plCreatable * plSimulationInterface::GetInterface(unsigned short);
  const class plCreatable * plSimulationInterface::GetConstInterface(unsigned short);
  void plSimulationInterface::Read(class hsStream *, class hsResMgr *);
  void plSimulationInterface::Write(class hsStream *, class hsResMgr *);
  void plSimulationInterface::SetProperty(int, int);
  long plSimulationInterface::GetNumProperties();
  void plSimulationInterface::SetTransform(const struct hsMatrix44 &, const struct hsMatrix44 &);
  const class hsBounds3Ext GetLocalBounds();
  const class hsBounds3Ext GetWorldBounds();
  const class hsBounds3Ext GetMaxWorldBounds();
  void plSimulationInterface::ClearLinearVelocity();
  int plSimulationInterface::MsgReceive(class plMessage *);
  void plSimulationInterface::SetPhysical(class plPhysical *);
  void plSimulationInterface::ReleaseData();
  class plPhysical * plSimulationInterface::GetPhysical();

private:
  static void plSimulationInterface::SetClassIndex(unsigned short);

protected:
  void plSimulationInterface::ISetSceneNode(class plKey);

};

#endif

