#include "plEnableMsg.h"

plEnableMsg::plEnableMsg() {
    fCmd.setName(kDisable, "kDisable");
    fCmd.setName(kEnable, "kEnable");
    fCmd.setName(kDrawable, "kDrawable");
    fCmd.setName(kPhysical, "kPhysical");
    fCmd.setName(kAudible, "kAudible");
    fCmd.setName(kAll, "kAll");
    fCmd.setName(kByType, "kByType");
}

plEnableMsg::~plEnableMsg() { }

IMPLEMENT_CREATABLE(plEnableMsg, kEnableMsg, plMessage)

void plEnableMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fCmd.read(S);
    fTypes.read(S);
}

void plEnableMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    fCmd.write(S);
    fTypes.write(S);
}

void plEnableMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Command");
    fCmd.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Types");
    fTypes.prcWrite(prc);
    prc->closeTag();
}
