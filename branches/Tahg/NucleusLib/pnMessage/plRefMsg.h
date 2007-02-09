#ifndef PLREFMSG_H
#define PLREFMSG_H

#include "plMessage.h"

class plRefMsg : public plMessage {
    class hsKeyedObject * fRef;
    class hsKeyedObject * fOldRef;
    unsigned char fContext;

public:
    plRefMsg(plRefMsg& src);
    plRefMsg(plKey&, unsigned char);
    plRefMsg(PlasmaVer pv = pvUnknown);
    ~plRefMsg();
    
    virtual unsigned short ClassIndex();

    void read(hsStream* S);
    void write(hsStream* S);

    static unsigned short Index();
    static class plRefMsg * Create();
    static const class plRefMsg * ConvertNoRef(const class plCreatable *);
    static class plRefMsg * ConvertNoRef(class plCreatable *);
    static class plRefMsg * Convert(class plCreatable *);
    static int HasDerivedClass(unsigned short);
    static int HasBaseClass(unsigned short);
    class plCreatable * GetInterface(unsigned short);
    const class plCreatable * GetConstInterface(unsigned short);
    class plRefMsg & SetRef(class hsKeyedObject *);
    class hsKeyedObject * GetRef();
    class plRefMsg & SetOldRef(class hsKeyedObject *);
    class hsKeyedObject * GetOldRef();
    class plRefMsg & SetContext(unsigned char);
    unsigned char GetContext();
};

class plGenRefMsg : public plRefMsg {
    signed char fType;
    long fWhich;

public:
    plGenRefMsg(const class plGenRefMsg &);
    plGenRefMsg(const class plKey &, unsigned char, long, signed char);
    plGenRefMsg(PlasmaVer pv = pvUnknown);
    plGenRefMsg::~plGenRefMsg();
    
    virtual unsigned short ClassIndex();
    
    void read(hsStream* S);
    void write(hsStream* S);
    
    static unsigned short Index();
    static class plGenRefMsg * Create();
    static const class plGenRefMsg * ConvertNoRef(const class plCreatable *);
    static class plGenRefMsg * plGenRefMsg::ConvertNoRef(class plCreatable *);
    static class plGenRefMsg * Convert(class plCreatable *);
    static int HasDerivedClass(unsigned short);
    static int plGenRefMsg::HasBaseClass(unsigned short);
    class plCreatable * plGenRefMsg::GetInterface(unsigned short);
    const class plCreatable * plGenRefMsg::GetConstInterface(unsigned short);
};

#endif
