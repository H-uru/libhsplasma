#include "plNetMsgSDLState.h"
#include "SDL/plStateDataRecord.h"

/* plNetMsgSDLState */
plNetMsgSDLState::plNetMsgSDLState()
                : fIsInitialState(false), fPersistOnServer(false),
                  fIsAvatarState(false), fDescriptor(NULL) { }

plNetMsgSDLState::~plNetMsgSDLState() { }

IMPLEMENT_CREATABLE(plNetMsgSDLState, kNetMsgSDLState, plNetMsgStreamedObject)

void plNetMsgSDLState::read(hsStream* S, plResManager* mgr) {
    plNetMsgStreamedObject::read(S, mgr);

    fIsInitialState = S->readBool();
    fPersistOnServer = S->readBool();
    fIsAvatarState = S->readBool();
}

void plNetMsgSDLState::write(hsStream* S, plResManager* mgr) {
    plNetMsgStreamedObject::write(S, mgr);

    S->writeBool(fIsInitialState);
    S->writeBool(fPersistOnServer);
    S->writeBool(fIsAvatarState);
}

void plNetMsgSDLState::IPrcWrite(pfPrcHelper* prc) {
    if (fDescriptor != NULL) {
        // We have a loaded descriptor, so we can output actual
        // PRC data, instead of just a hex stream
        plNetMsgObject::IPrcWrite(prc);
        
        hsStream* blob = getStream();
        plStateDataRecord rec;
        rec.setDescriptor(fDescriptor);
        rec.read(blob, NULL);
        prc->startTag("SDLStateDefinitions");
        prc->writeParam("DescName", fDescriptor->getName());
        prc->writeParam("DescVersion", fDescriptor->getVersion());
        prc->endTag();
        rec.prcWrite(prc);
        prc->closeTag();
    } else {
        // No loaded descriptor, so just output the hex stream
        plNetMsgStreamedObject::IPrcWrite(prc);
    }

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
        if (fDescriptor != NULL)
            //TODO: Parse SDL as PRC
            plNetMsgObject::IPrcParse(tag, mgr);
        else
            plNetMsgStreamedObject::IPrcParse(tag, mgr);
    }
}

void plNetMsgSDLState::findDescriptor(plSDLMgr* sdl) {
    hsStream* blob = getStream();
    plString descName;
    int descVersion = -1;
    plStateDataRecord::ReadStreamHeader(blob, descName, descVersion, NULL);
    fDescriptor = sdl->GetDescriptor(descName, descVersion);
}

/* plNetMsgSDLStateBCast */
IMPLEMENT_CREATABLE(plNetMsgSDLStateBCast, kNetMsgSDLStateBCast, plNetMsgSDLState)
