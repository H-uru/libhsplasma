#ifndef PLNODEREFMSG_H
#define PLNODEREFMSG_H

#include "plRefMsg.h"

class plNodeRefMsg : public plGenRefMsg {
public:
    plNodeRefMsg(plNodeRefMsg&);
    plNodeRefMsg(const plKey&, unsigned char, signed char, signed char);
    plNodeRefMsg();
    ~plNodeRefMsg();
   
    virtual unsigned short ClassIndex();
    
    static unsigned short Index();
    static class plNodeRefMsg * Create();
    static const class plNodeRefMsg * ConvertNoRef(const class plCreatable *);
    static class plNodeRefMsg * ConvertNoRef(class plCreatable *);
    static class plNodeRefMsg * Convert(class plCreatable *);
    static int HasDerivedClass(unsigned short);
    static int HasBaseClass(unsigned short);
    class plCreatable * GetInterface(unsigned short);
    const class plCreatable * GetConstInterface(unsigned short);
};

#endif
