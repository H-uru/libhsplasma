#ifndef _PLRECEIVER_H
#define _PLRECEIVER_H

#include "PRP/plCreatable.h"
#include "PRP/Message/plMessage.h"
#include "plKey.h"

/**
 * \brief Base class that can receive plMessages.
 *
 * Within the Plasma game engines, any class that can receive (and handle)
 * a plMessage is derived from this class.  Specifically, it implements
 * a MsgReceive() function that handles the message that was thrown at it.
 * In libPlasma, this functionality is not necessary, so its only real
 * purpose here is to reserve the plReceiver Class Index.
 */
DllClass plReceiver : public plCreatable {
public:
    plReceiver();
    virtual ~plReceiver();

    DECLARE_CREATABLE(plReceiver)

    //virtual bool msgReceive(plMessage* msg);
};

#endif
