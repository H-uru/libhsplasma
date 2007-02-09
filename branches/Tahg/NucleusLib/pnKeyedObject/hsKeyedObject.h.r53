#ifndef _HSKEYEDOBJECT_H
#define _HSKEYEDOBJECT_H

#include "plReceiver.h"

class hsKeyedObject : public plReceiver {
public:
    enum {
        kFlagPreventLoad = 0x1,
        kFlagPreventReset = 0x2,
        kFlagPreventInit = 0x4
    };

protected:
    plKey* myKey;
    unsigned int koFlags;

public:
    hsKeyedObject(PlasmaVer pv = pvUnknown);
    virtual ~hsKeyedObject();

    virtual short ClassIndex();

    virtual void read(hsStream * S);
    virtual void write(hsStream * S);

#ifdef Tahg
public:
    static unsigned short Index();
    static class hsKeyedObject * Create();
    static const class hsKeyedObject * ConvertNoRef(const class plCreatable *);
    static class hsKeyedObject * ConvertNoRef(class plCreatable *);
    static class hsKeyedObject * Convert(class plCreatable *);
    static int HasDerivedClass(unsigned short);
    static int HasBaseClass(unsigned short);
    class plCreatable * GetInterface(unsigned short);
    const class plCreatable * GetConstInterface(unsigned short);
    const class plKey & GetKey();
    const char * GetKeyName();
    void Validate();
    int IsFinal();
    int MsgReceive(class plMessage *);
    int SendRef(class plRefMsg *, enum plRefFlags::Type);
    class plKey RegisterAs(enum plFixedKeyId);
    void UnRegisterAs(enum plFixedKeyId);
    class plKey RegisterAsManual(class plUoid &, const char *);
    void UnRegisterAsManual(class plUoid &);
    class hsKeyedObject * GetSharedObject();

protected:
    void SetKey(class plKey);
    void UnRegister();
#endif
};

#endif

