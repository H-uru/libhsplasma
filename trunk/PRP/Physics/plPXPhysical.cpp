#include "plPXPhysical.h"
#include "plHKPhysical.h"
#include "plODEPhysical.h"

#include "Debug/plDebug.h"
#include "PRP/Object/plSimulationInterface.h"

plPXPhysical::plPXPhysical()
            : fMass(0.0f), fFriction(0.0f), fRestitution(0.0f),
              fBounds(plSimDefs::kBoxBounds), fGroup(plSimDefs::kGroupStatic),
              fReportsOn(0), fSphereRadius(0.0f), fLOSDBs(0) {
    SetFlagNames();
}

plPXPhysical::plPXPhysical(const plPXPhysical& init)
            : fMass(init.fMass), fFriction(init.fFriction),
              fRestitution(init.fRestitution), fBounds(init.fBounds),
              fGroup(init.fGroup), fReportsOn(init.fReportsOn),
              fObjectKey(init.fObjectKey), fSceneNode(init.fSceneNode),
              fWorldKey(init.fWorldKey), fSphereRadius(init.fSphereRadius),
              fSphereOffset(init.fSphereOffset),
              fBoxDimensions(init.fBoxDimensions), fBoxOffset(init.fBoxOffset),
              fLOSDBs(init.fLOSDBs), fPos(init.fPos), fRot(init.fRot),
              fProps(init.fProps), fSndGroup(init.fSndGroup) {
    SetFlagNames();
}

plPXPhysical::~plPXPhysical() { }

IMPLEMENT_CREATABLE(plPXPhysical, kPXPhysical, plPhysical)

void plPXPhysical::SetFlagNames() {
    fProps.setName(plSimulationInterface::kDisable, "kDisable");
    fProps.setName(plSimulationInterface::kWeightless, "kWeightless");
    fProps.setName(plSimulationInterface::kPinned, "kPinned");
    fProps.setName(plSimulationInterface::kWarp, "kWarp");
    fProps.setName(plSimulationInterface::kUpright, "kUpright");
    fProps.setName(plSimulationInterface::kPassive, "kPassive");
    fProps.setName(plSimulationInterface::kRotationForces, "kRotationForces");
    fProps.setName(plSimulationInterface::kCameraAvoidObject, "kCameraAvoidObject");
    fProps.setName(plSimulationInterface::kPhysAnim, "kPhysAnim");
    fProps.setName(plSimulationInterface::kStartInactive, "kStartInactive");
    fProps.setName(plSimulationInterface::kNoSynchronize, "kNoSynchronize");
    fProps.setName(plSimulationInterface::kSuppressed, "kSuppressed");
    fProps.setName(plSimulationInterface::kNoOwnershipChange, "kNoOwnershipChange");
    fProps.setName(plSimulationInterface::kAvAnimPushable, "kAvAnimPushable");
}

plHKPhysical* plPXPhysical::ConvertToHavok() const {
    plHKPhysical* conv = new plHKPhysical();
    conv->fPos = fPos;
    conv->fRot = fRot;
    conv->fMass = fMass;
    conv->fFriction = fFriction;
    conv->fRestitution = fRestitution;
    conv->fBounds = fBounds;
    // fCategory
    conv->fProps = fProps;
    conv->fObjectKey = fObjectKey;
    conv->fSceneNode = fSceneNode;
    conv->fWorldKey = fWorldKey;
    conv->fSndGroup = fSndGroup;
    // fUnk1
    // fUnk2
    conv->fLOSDBs = fLOSDBs;
    
    conv->fSphereOffset = fSphereOffset;
    conv->fSphereRadius = fSphereRadius;
    // fVerts
    // fIndices
    
    plDebug::Warning("plPXPhysical::ConvertToHavok() incomplete");

    return conv;
}

plPXPhysical* plPXPhysical::ConvertToPhysX() const {
    return new plPXPhysical(*this);
}

plODEPhysical* plPXPhysical::ConvertToODE() const {
    plODEPhysical* conv = new plODEPhysical();
    conv->fBounds = fBounds;
    // fCategory
    conv->fLOSDBs = fLOSDBs;
    conv->fObjectKey = fObjectKey;
    conv->fSceneNode = fSceneNode;
    // fUnk1
    // fUnk2
    // fFlags

    conv->fBoxDimensions = fBoxDimensions;
    conv->fMass = fMass;
    conv->fRadius = fSphereRadius;
    conv->fLength = 0.0f;
    // fVerts
    // fIndices
    // fTMDBuffer

    plDebug::Warning("plPXPhysical::ConvertToODE() incomplete");

    return conv;
}

void plPXPhysical::readData(hsStream* S, plResManager* mgr) {
    fMass = S->readFloat();
    fFriction = S->readFloat();
    fRestitution = S->readFloat();
    fBounds = (plSimDefs::Bounds)S->readByte();
    fGroup = (plSimDefs::Group)S->readByte();
    fReportsOn = S->readInt();
    fLOSDBs = S->readShort();
    fObjectKey = mgr->readKey(S);
    fSceneNode = mgr->readKey(S);
    fWorldKey = mgr->readKey(S);

    fSndGroup = mgr->readKey(S);
    fPos.read(S);
    fRot.read(S);
    fProps.read(S);

    if (fBounds == plSimDefs::kSphereBounds) {
        fSphereRadius = S->readFloat();
        fSphereOffset.read(S);
    } else if (fBounds == plSimDefs::kBoxBounds) {
        fBoxDimensions.read(S);
        fBoxOffset.read(S);
    } else if (fBounds == plSimDefs::kHullBounds) {
        plDebug::Warning("plPXPhysical: HullBounds not implemented");
    } else {    // Proxy or Explicit
        plDebug::Warning("plPXPhysical: TriangleMesh not implemented");
    }
}

void plPXPhysical::writeData(hsStream* S, plResManager* mgr) {
    S->writeFloat(fMass);
    S->writeFloat(fFriction);
    S->writeFloat(fRestitution);
    S->writeByte((hsUbyte)fBounds);
    S->writeByte((hsUbyte)fGroup);
    S->writeInt(fReportsOn);
    S->writeShort(fLOSDBs);
    mgr->writeKey(S, fObjectKey);
    mgr->writeKey(S, fSceneNode);
    mgr->writeKey(S, fWorldKey);

    mgr->writeKey(S, fSndGroup);
    fPos.write(S);
    fRot.write(S);
    fProps.write(S);

    if (fBounds == plSimDefs::kSphereBounds) {
        S->writeFloat(fSphereRadius);
        fSphereOffset.write(S);
    } else if (fBounds == plSimDefs::kBoxBounds) {
        fBoxDimensions.write(S);
        fBoxOffset.write(S);
    } else if (fBounds == plSimDefs::kHullBounds) {
        plDebug::Warning("plPXPhysical: HullBounds not implemented");
    } else {    // Proxy or Explicit
        plDebug::Warning("plPXPhysical: TriangleMesh not implemented");
    }
}

void plPXPhysical::IPrcWrite(pfPrcHelper* prc) {
    plPhysical::IPrcWrite(prc);

    prc->startTag("PhysicalParams");
    prc->writeParam("Mass", fMass);
    prc->writeParam("Friction", fFriction);
    prc->writeParam("Restitution", fRestitution);
    prc->writeParam("Group", plSimDefs::GroupNames[fGroup]);
    prc->writeParamHex("ReportsOn", fReportsOn);
    prc->writeParamHex("LOSDBs", fLOSDBs);
    prc->endTag(true);

    prc->writeSimpleTag("Object");
    fObjectKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SceneNode");
    fSceneNode->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SubWorld");
    fWorldKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SoundGroup");
    fSndGroup->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Transform");
    fPos.prcWrite(prc);
    fRot.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Props");
    fProps.prcWrite(prc);
    prc->closeTag();

    prc->startTag("Bounds");
    prc->writeParam("Type", plSimDefs::BoundsNames[fBounds]);
    prc->endTag();
    if (fBounds == plSimDefs::kSphereBounds) {
        prc->startTag("SphereBounds");
        prc->writeParam("Radius", fSphereRadius);
        prc->endTag();
        fSphereOffset.prcWrite(prc);
        prc->closeTag();
    } else if (fBounds == plSimDefs::kBoxBounds) {
        prc->writeSimpleTag("BoxBounds");
        prc->writeSimpleTag("Dimensions");
        fBoxDimensions.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("Offset");
        fBoxOffset.prcWrite(prc);
        prc->closeTag();
        prc->closeTag();
    } else if (fBounds == plSimDefs::kHullBounds) {
        prc->writeComment("HullBounds not implemented");
    } else {    // Proxy or Explicit
        prc->writeComment("TriangleMesh not implemented");
    }
    prc->closeTag();
}

void plPXPhysical::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "PhysicalParams") {
        fMass = tag->getParam("Mass", "0").toFloat();
        fFriction = tag->getParam("Friction", "0").toFloat();
        fRestitution = tag->getParam("Restitution", "0").toFloat();
        fReportsOn = tag->getParam("ReportsOn", "0").toUint();
        fLOSDBs = tag->getParam("LOSDBs", "0").toUint();
        plString group = tag->getParam("Group", "kGroupStatic");
        for (size_t i=0; i<plSimDefs::kGroupMax; i++)
            if (group == plSimDefs::GroupNames[i])
                fGroup = (plSimDefs::Group)i;
    } else if (tag->getName() == "Object") {
        if (tag->hasChildren())
            fObjectKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SubWorld") {
        if (tag->hasChildren())
            fWorldKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SoundGroup") {
        if (tag->hasChildren())
            fSndGroup = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Transform") {
        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
            if (child->getName() == "hsVector3") {
                fPos.prcParse(child);
            } else if (child->getName() == "hsQuat") {
                fRot.prcParse(child);
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Props") {
        if (tag->hasChildren())
            fProps.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Bounds" ) {
        plString bounds = tag->getParam("Type", "kBoxBounds");
        for (size_t i=0; i<plSimDefs::kNumBounds; i++)
            if (bounds == plSimDefs::BoundsNames[i])
                fBounds = (plSimDefs::Bounds)i;
        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
            if (child->getName() == "SphereBounds") {
                fSphereRadius = child->getParam("Radius", "0").toFloat();
                if (child->hasChildren())
                    fSphereOffset.prcParse(child->getFirstChild());
            } else if (child->getName() == "BoxBounds") {
                const pfPrcTag* subchild = child->getFirstChild();
                while (subchild != NULL) {
                    if (subchild->getName() == "Dimensions") {
                        if (subchild->hasChildren())
                            fBoxDimensions.prcParse(subchild->getFirstChild());
                    } else if (subchild->getName() == "Offset") {
                        if (subchild->hasChildren())
                            fBoxOffset.prcParse(subchild->getFirstChild());
                    } else {
                        throw pfPrcTagException(__FILE__, __LINE__, subchild->getName());
                    }
                    subchild = subchild->getNextSibling();
                }
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else {
        plPhysical::IPrcParse(tag, mgr);
    }
}
