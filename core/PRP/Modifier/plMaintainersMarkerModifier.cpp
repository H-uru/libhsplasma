#include "plMaintainersMarkerModifier.h"

static const char* CalibratedLevelNames[] = {
    "Broken", "Repaired", "Calibrated"
};

plMaintainersMarkerModifier::plMaintainersMarkerModifier()
                           : fCalibrated(kBroken) { }
plMaintainersMarkerModifier::~plMaintainersMarkerModifier() { }

IMPLEMENT_CREATABLE(plMaintainersMarkerModifier, kMaintainersMarkerModifier,
                    plMultiModifier)

void plMaintainersMarkerModifier::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);
    fCalibrated = S->readInt();
}

void plMaintainersMarkerModifier::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);
    S->writeInt(fCalibrated);
}

void plMaintainersMarkerModifier::IPrcWrite(pfPrcHelper* prc) {
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("Calibrated");
    prc->writeParam("Level", CalibratedLevelNames[fCalibrated]);
    prc->endTag(true);
}

void plMaintainersMarkerModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Calibrated") {
        plString level = tag->getParam("Level", "Broken");
        fCalibrated = kBroken;
        for (size_t i=0; i<kNumCalibratedLevels; i++) {
            if (level == CalibratedLevelNames[i])
                fCalibrated = i;
        }
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
