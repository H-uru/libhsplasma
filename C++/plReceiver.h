#ifndef _PLRECEIVER_H
#define _PLRECEIVER_H

#include "plCreatable.h"
#include "NucleusLib/pnKeyedObject/plKey.h"
//#include "NucleusLib/pnMessage/plMessage.h"

class plReceiver : public plCreatable {
protected:
    plKey key;

    virtual void read(hsStream * S);
    virtual void write(hsStream * S);

public:
    plReceiver();
    ~plReceiver();

    plKey * getKey();
    void setKey(plKey * k);

    //virtual bool msgReceive(plMessage * msg);

    virtual const char* getTypeName();
    virtual const int getTypeNum();
};

#endif

