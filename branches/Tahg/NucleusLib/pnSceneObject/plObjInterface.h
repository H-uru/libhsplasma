#ifndef _PLOBJINTERFACE_H
#define _PLOBJINTERFACE_H

#include "../../CoreLib/hsBitVector.h"
#include "../pnNetCommon/plSynchedObject.h"
#include "../pnMessage/plMessage.h"

class plObjInterface : public plSynchedObject {
public:
    plKey* Owner;
    hsBitVector Props;

public:
    plObjInterface(PlasmaVer pv = pvUnknown);
    virtual ~plObjInterface();

    virtual unsigned short ClassIndex();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);

#ifdef Tahg
public:
    static unsigned short Index();
    static plObjInterface * Create();
    static const plObjInterface * ConvertNoRef(const class plCreatable *);
    static class plObjInterface * ConvertNoRef(class plCreatable *);
    static class plObjInterface * Convert(class plCreatable *);
    static int HasDerivedClass(unsigned short);
    static int HasBaseClass(unsigned short);
    class plCreatable * GetInterface(unsigned short);
    const class plCreatable * GetConstInterface(unsigned short);
    bool MsgReceive(class plMessage *);
    const class plSceneObject * GetOwner();
    class plKey GetOwnerKey();
    class plKey GetSceneNode();
    void SetProperty(int, int);
    int GetProperty(int);
    long GetNumProperties();
    void SetTransform(const struct hsMatrix44 &, const struct hsMatrix44 &);
    void ReleaseData();

protected:
    void ISetSceneNode(class plKey);
    class plSceneObject * IGetOwner();
    void ISetOwner(class plSceneObject *);
    void ISetAllProperties(const class hsBitVector &);
    class plDrawInterface * IGetOwnerDrawInterface();
    class plSimulationInterface * IGetOwnerSimulationInterface();
    class plCoordinateInterface * IGetOwnerCoordinateInterface();
    class plAudioInterface * IGetOwnerAudioInterface();
#endif
};

#endif

