#include "plNetMsgSDLState.h"

/* plNetMsgSDLState */
plNetMsgSDLState::plNetMsgSDLState()
                : fIsInitialState(false), fPersistOnServer(false),
                  fIsAvatarState(false) { }

plNetMsgSDLState::~plNetMsgSDLState() { }

IMPLEMENT_CREATABLE(plNetMsgSDLState, kNetMsgSDLState, plNetMsgStreamedObject)

void plNetMsgSDLState::read(hsStream* S, plResManager* mgr) {
    plNetMsgStreamedObject::read(S, mgr);

    fIsInitialState = S->readBool();
    fPersistOnServer = S->readBool();
    fIsAvatarState = S->readBool();
    
    hsStream* blob;
    blob = getStream();
    fDescVersion = -1;
    plStateDataRecord::ReadStreamHeader(blob, fDescName, fDescVersion, NULL);
    plStateDescriptor* desc = plSDLMgr::GetManager()->GetDescriptor(fDescName, fDescVersion);
    fRecord.setDescriptor(desc);
    fRecord.read(blob, mgr);
}

void plNetMsgSDLState::write(hsStream* S, plResManager* mgr) {
    plNetMsgStreamedObject::write(S, mgr);

    S->writeBool(fIsInitialState);
    S->writeBool(fPersistOnServer);
    S->writeBool(fIsAvatarState);
}

void plNetMsgSDLState::IPrcWrite(pfPrcHelper* prc) {
    /* plNetMsgStreamedObject::IPrcWrite(prc);*/
    /* Okay, the NetMsgStreamedObject just uses a StremHelper
       to dump the stream as hex output. We want to parse it
       and display the SDL data. So we'll handle PRC output
       of the stream ourselves. */
    plNetMsgObject::IPrcWrite(prc);
    
    prc->startTag("SDLStateDefinitions");
    prc->writeParam("DescName", fDescName);
    prc->writeParam("DescVersion", fDescVersion);
    prc->endTag();
    fRecord.prcWrite(prc);
    prc->closeTag();

    prc->startTag("SDLStateParams");
    prc->writeParam("IsInitialState", fIsInitialState);
    prc->writeParam("PersistOnServer", fPersistOnServer);
    prc->writeParam("IsAvatarState", fIsAvatarState);
    prc->endTag(true);
}

void plNetMsgSDLState::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SDLStateParams") {
        fIsInitialState = tag->getParam("IsInitialState", "false").toBool();
        fPersistOnServer = tag->getParam("PersistOnServer", "false").toBool();
        fIsAvatarState = tag->getParam("IsAvatarState", "false").toBool();
    } else {
        /*plNetMsgStreamedObject::IPrcParse(tag, mgr);*/
        plNetMsgObject::IPrcParse(tag, mgr);
    }
}


/* plNetMsgSDLStateBCast */
IMPLEMENT_CREATABLE(plNetMsgSDLStateBCast, kNetMsgSDLStateBCast, plNetMsgSDLState)
