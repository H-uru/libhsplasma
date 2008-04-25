#include "plAGApplicator.h"

// plAGApplicator //
plAGApplicator::plAGApplicator() : fChannel(NULL), fEnabled(true) { }

plAGApplicator::~plAGApplicator() {
    if (fChannel != NULL)
        delete fChannel;
}

IMPLEMENT_CREATABLE(plAGApplicator, kAGApplicator, plCreatable)

void plAGApplicator::read(hsStream* S, plResManager* mgr) {
    fEnabled = S->readBool();
    fChannelName = S->readSafeStr();
}

void plAGApplicator::write(hsStream* S, plResManager* mgr) {
    S->writeBool(fEnabled);
    S->writeSafeStr(fChannelName);
}

void plAGApplicator::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("AGApplicatorParams");
    prc->writeParam("Enabled", fEnabled);
    prc->writeParam("ChannelName", fChannelName);
    prc->endTag(true);
}

plAGChannel* plAGApplicator::getChannel() const { return fChannel; }
void plAGApplicator::setChannel(plAGChannel* chan) { fChannel = chan; }


// plSoundVolumeApplicator //
plSoundVolumeApplicator::plSoundVolumeApplicator() : fIndex(0) { }
plSoundVolumeApplicator::~plSoundVolumeApplicator() { }

IMPLEMENT_CREATABLE(plSoundVolumeApplicator, kSoundVolumeApplicator,
                    plAGApplicator)

void plSoundVolumeApplicator::read(hsStream* S, plResManager* mgr) {
    plAGApplicator::read(S, mgr);
    fIndex = S->readInt();
}

void plSoundVolumeApplicator::write(hsStream* S, plResManager* mgr) {
    plAGApplicator::write(S, mgr);
    S->writeInt(fIndex);
}

void plSoundVolumeApplicator::IPrcWrite(pfPrcHelper* prc) {
    plAGApplicator::IPrcWrite(prc);

    prc->startTag("SoundVolumeApplicatorParams");
    prc->writeParam("Index", fIndex);
    prc->endTag(true);
}


// plLightAmbientApplicator //
plLightAmbientApplicator::plLightAmbientApplicator() { }
plLightAmbientApplicator::~plLightAmbientApplicator() { }

IMPLEMENT_CREATABLE(plLightAmbientApplicator, kLightAmbientApplicator,
                    plAGApplicator)


// plLightDiffuseApplicator //
plLightDiffuseApplicator::plLightDiffuseApplicator() { }
plLightDiffuseApplicator::~plLightDiffuseApplicator() { }

IMPLEMENT_CREATABLE(plLightDiffuseApplicator, kLightDiffuseApplicator,
                    plAGApplicator)


// plLightSpecularApplicator //
plLightSpecularApplicator::plLightSpecularApplicator() { }
plLightSpecularApplicator::~plLightSpecularApplicator() { }

IMPLEMENT_CREATABLE(plLightSpecularApplicator, kLightSpecularApplicator,
                    plAGApplicator)


// plOmniApplicator //
plOmniApplicator::plOmniApplicator() { }
plOmniApplicator::~plOmniApplicator() { }

IMPLEMENT_CREATABLE(plOmniApplicator, kOmniApplicator, plAGApplicator)


// plOmniCutoffApplicator //
plOmniCutoffApplicator::plOmniCutoffApplicator() { }
plOmniCutoffApplicator::~plOmniCutoffApplicator() { }

IMPLEMENT_CREATABLE(plOmniCutoffApplicator, kOmniCutoffApplicator, plAGApplicator)


// plOmniSqApplicator //
plOmniSqApplicator::plOmniSqApplicator() { }
plOmniSqApplicator::~plOmniSqApplicator() { }

IMPLEMENT_CREATABLE(plOmniSqApplicator, kOmniSqApplicator, plAGApplicator)


// plSpotInnerApplicator //
plSpotInnerApplicator::plSpotInnerApplicator() { }
plSpotInnerApplicator::~plSpotInnerApplicator() { }

IMPLEMENT_CREATABLE(plSpotInnerApplicator, kSpotInnerApplicator, plAGApplicator)


// plSpotOuterApplicator //
plSpotOuterApplicator::plSpotOuterApplicator() { }
plSpotOuterApplicator::~plSpotOuterApplicator() { }

IMPLEMENT_CREATABLE(plSpotOuterApplicator, kSpotOuterApplicator, plAGApplicator)
