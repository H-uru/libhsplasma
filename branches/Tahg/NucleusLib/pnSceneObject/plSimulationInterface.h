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
    virtual ~plSimulationInterface();

    virtual unsigned short ClassIndex();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);

public:
    static unsigned short plSimulationInterface::Index();
    static class plSimulationInterface * Create();
    static const class plSimulationInterface * ConvertNoRef(const class plCreatable *);
    static class plSimulationInterface * ConvertNoRef(class plCreatable *);
    static class plSimulationInterface * Convert(class plCreatable *);
    static int HasDerivedClass(unsigned short);
    static int HasBaseClass(unsigned short);
    class plCreatable * GetInterface(unsigned short);
    const class plCreatable * GetConstInterface(unsigned short);
    void SetProperty(int, int);
    long GetNumProperties();
    void SetTransform(const struct hsMatrix44 &, const struct hsMatrix44 &);
    const class hsBounds3Ext GetLocalBounds();
    const class hsBounds3Ext GetWorldBounds();
    const class hsBounds3Ext GetMaxWorldBounds();
    void ClearLinearVelocity();
    bool MsgReceive(class plMessage *);
    void SetPhysical(class plPhysical *);
    void ReleaseData();
    class plPhysical * GetPhysical();

protected:
    void ISetSceneNode(class plKey);
};

#endif

