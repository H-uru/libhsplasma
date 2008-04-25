#include "plActivatorConditionalObject.h"

/* plActivatorConditionalObject */
plActivatorConditionalObject::plActivatorConditionalObject() { }
plActivatorConditionalObject::~plActivatorConditionalObject() { }

IMPLEMENT_CREATABLE(plActivatorConditionalObject, kActivatorConditionalObject,
                    plConditionalObject)

void plActivatorConditionalObject::read(hsStream* S, plResManager* mgr) {
    plConditionalObject::read(S, mgr);
    fActivators.clear();
    size_t count = S->readInt();
    for (size_t i=0; i<count; i++)
        fActivators.append(mgr->readKey(S));
}

void plActivatorConditionalObject::write(hsStream* S, plResManager* mgr) {
    plConditionalObject::write(S, mgr);
    S->writeInt(fActivators.getSize());
    for (size_t i=0; i<fActivators.getSize(); i++)
        mgr->writeKey(S, fActivators[i]);
}

void plActivatorConditionalObject::IPrcWrite(pfPrcHelper* prc) {
    plConditionalObject::IPrcWrite(prc);
    prc->writeSimpleTag("Activators");
    for (size_t i=0; i<fActivators.getSize(); i++)
        fActivators[i]->prcWrite(prc);
    prc->closeTag();
}


/* plActivatorActivatorConditionalObject */
IMPLEMENT_CREATABLE(plActivatorActivatorConditionalObject,
                    kActivatorActivatorConditionalObject,
                    plActivatorConditionalObject)


/* plVolActivatorConditionalObject */
IMPLEMENT_CREATABLE(plVolActivatorConditionalObject,
                    kVolActivatorConditionalObject,
                    plActivatorConditionalObject)
