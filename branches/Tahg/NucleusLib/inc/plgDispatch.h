#ifndef _PLGDISPATCH_H
#define _PLGDISPATCH_H

#include "../pnFactory/plCreatable.h"

class plDispatchBase : public plCreatable {
public:
    const char * plDispatchBase::ClassName();
    unsigned short plDispatchBase::ClassIndex();
    static unsigned short Index();
    static class plDispatchBase * Create();
    static const class plDispatchBase * ConvertNoRef(const class plCreatable *);
    static class plDispatchBase * ConvertNoRef(class plCreatable *);
    static class plDispatchBase * Convert(class plCreatable *);
    static int HasDerivedClass(unsigned short);
    static int HasBaseClass(unsigned short);
    class plCreatable * plDispatchBase::GetInterface(unsigned short);
    const class plCreatable * plDispatchBase::GetConstInterface(unsigned short);
    void RegisterForType(unsigned short, const class plKey &);
    void RegisterForExactType(unsigned short, const class plKey &){}
    void UnRegisterForType(unsigned short, const class plKey &);
    void UnRegisterForExactType(unsigned short, const class plKey &){}
    void UnRegisterAll(const class plKey &);
    int MsgSend(class plMessage *, int);
    void MsgQueue(class plMessage *);
    void MsgQueueProcess();
    void MsgQueueOnOff(int);
    int SetMsgBuffering(int);
    plDispatchBase(const class plDispatchBase &);
    plDispatchBase::plDispatchBase();
    plDispatchBase::~plDispatchBase();

private:
    static void plDispatchBase::SetClassIndex(unsigned short);
};

class plgDispatch {
public:
	static plDispatchBase * Dispatch();
};

#endif

