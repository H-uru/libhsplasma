#include "plHKPhysical.h"
#include "plPXPhysical.h"
#include "plODEPhysical.h"

#include "Debug/plDebug.h"
#include "PRP/Object/plSimulationInterface.h"

plHKPhysical::plHKPhysical()
            : fMass(0.0f), fFriction(0.0f), fRestitution(0.0f),
              fBounds(plSimDefs::kBoxBounds), fCategory(0),
              fUnk1(0), fUnk2(0), fBool1(false), fBool2(false), fLOSDBs(0),
              fSphereRadius(0.0f), fNumVerts(0), fNumTris(0), fVerts(NULL),
              fIndices(NULL) {
    SetFlagNames();
}

plHKPhysical::plHKPhysical(const plHKPhysical& init)
            : fPos(init.fPos), fRot(init.fRot), fMass(init.fMass),
              fFriction(init.fFriction), fRestitution(init.fRestitution),
              fBounds(init.fBounds), fCategory(init.fCategory),
              fProps(init.fProps), fObjectKey(init.fObjectKey),
              fSceneNode(init.fSceneNode), fWorldKey(init.fWorldKey),
              fSndGroup(init.fSndGroup), fUnk1(init.fUnk1), fUnk2(init.fUnk2),
              fBool1(init.fBool1), fBool2(init.fBool2), fLOSDBs(init.fLOSDBs),
              fSphereOffset(init.fSphereOffset), fSphereRadius(init.fSphereRadius),
              fNumVerts(init.fNumVerts), fNumTris(init.fNumTris) {
    fVerts = new hsVector3[fNumVerts];
    fIndices = new unsigned short[fNumTris * 3];
    for (size_t i=0; i<fNumVerts; i++)
        fVerts[i] = init.fVerts[i];
    memcpy(fIndices, init.fIndices, fNumTris * 3 * sizeof(unsigned short));

    SetFlagNames();
}

plHKPhysical::~plHKPhysical() {
    if (fVerts != NULL)
        delete[] fVerts;
    if (fIndices != NULL)
        delete[] fIndices;
}

IMPLEMENT_CREATABLE(plHKPhysical, kHKPhysical, plPhysical)

void plHKPhysical::SetFlagNames() {
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

plHKPhysical* plHKPhysical::ConvertToHavok() const {
    return new plHKPhysical(*this);
}

plPXPhysical* plHKPhysical::ConvertToPhysX() const {
    plPXPhysical* conv = new plPXPhysical();
    conv->fMass = fMass;
    conv->fFriction = fFriction;
    conv->fRestitution = fRestitution;
    conv->fBounds = fBounds;
    // fGroup
    // fReportsOn
    conv->fObjectKey = fObjectKey;
    conv->fSceneNode = fSceneNode;
    conv->fWorldKey = fWorldKey;
    conv->fSndGroup = fSndGroup;
    conv->fSphereRadius = fSphereRadius;
    conv->fSphereOffset = fSphereOffset;
    conv->fLOSDBs = fLOSDBs;
    conv->fPos = fPos;
    conv->fRot = fRot;
    conv->fProps = fProps;

    // fBoxDimensions
    // fBoxOffset

    plDebug::Warning("plHKPhysical::ConvertToPhysX() incomplete");

    return conv;
}

plODEPhysical* plHKPhysical::ConvertToODE() const {
    plODEPhysical* conv = new plODEPhysical();
    conv->fBounds = fBounds;
    conv->fCategory = fCategory;
    conv->fLOSDBs = fLOSDBs;
    conv->fObjectKey = fObjectKey;
    conv->fSceneNode = fSceneNode;
    conv->fUnk1 = fUnk1;
    conv->fUnk2 = fUnk2;
    // fFlags
    // fBoxDimensions
    conv->fMass = fMass;
    conv->fRadius = fSphereRadius;
    conv->fLength = 0.0f;
    conv->fNumVerts = fNumVerts;
    conv->fNumTris = fNumTris;
    conv->fTMDSize = 0;

    conv->fVerts = new hsVector3[fNumVerts];
    conv->fIndices = new unsigned int[fNumTris * 3];
    for (size_t i=0; i<fNumVerts; i++)
        conv->fVerts[i] = fVerts[i];
    for (size_t i=0; i<fNumTris; i += 3) {
        conv->fIndices[i+0] = fIndices[i+0];
        conv->fIndices[i+1] = fIndices[i+1];
        conv->fIndices[i+2] = fIndices[i+2];
    }
    // fTMDBuffer

    plDebug::Warning("plHKPhysical::ConvertToODE() incomplete");

    return conv;
}

void plHKPhysical::readData(hsStream* S, plResManager* mgr) {
    fPos.read(S);
    float rad = S->readFloat();
    hsVector3 axis;
    axis.read(S);
    fRot = hsQuat(rad, axis);
    
    fMass = S->readFloat();
    fFriction = S->readFloat();
    fRestitution = S->readFloat();
    fBounds = (plSimDefs::Bounds)S->readInt();
    fCategory = S->readInt();
    fUnk1 = S->readInt();
    fUnk2 = S->readInt();
    fBool1 = S->readBool();
    fBool2 = S->readBool();

    if (fBounds == plSimDefs::kHullBounds) {
        fNumVerts = S->readInt();
        fVerts = new hsVector3[fNumVerts];
        for (size_t i=0; i<fNumVerts; i++)
            fVerts[i].read(S);
    } else if (fBounds == plSimDefs::kSphereBounds) {
        fSphereOffset.read(S);
        fSphereRadius = S->readFloat();
    } else {    // Box, Proxy, Explicit
        fNumVerts = S->readInt();
        fVerts = new hsVector3[fNumVerts];
        for (size_t i=0; i<fNumVerts; i++)
            fVerts[i].read(S);
        fNumTris = S->readInt();
        fIndices = new unsigned short[fNumTris * 3];
        S->read(fNumTris * 3 * sizeof(unsigned short), fIndices);
    }

    fObjectKey = mgr->readKey(S);
    fProps.read(S);
    fSceneNode = mgr->readKey(S);
    fLOSDBs = S->readInt();
    fWorldKey = mgr->readKey(S);
    fSndGroup = mgr->readKey(S);
}

void plHKPhysical::writeData(hsStream* S, plResManager* mgr) {
    fPos.write(S);
    S->writeFloat(fRot.W);
    S->writeFloat(fRot.X);
    S->writeFloat(fRot.Y);
    S->writeFloat(fRot.Z);
    
    S->writeFloat(fMass);
    S->writeFloat(fFriction);
    S->writeFloat(fRestitution);
    S->writeInt(fBounds);
    S->writeInt(fCategory);
    S->writeInt(fUnk1);
    S->writeInt(fUnk2);
    S->writeBool(fBool1);
    S->writeBool(fBool2);

    if (fBounds == plSimDefs::kHullBounds) {
        S->writeInt(fNumVerts);
        for (size_t i=0; i<fNumVerts; i++)
            fVerts[i].write(S);
    } else if (fBounds == plSimDefs::kSphereBounds) {
        fSphereOffset.write(S);
        S->writeFloat(fSphereRadius);
    } else {    // Box, Proxy, Explicit
        S->writeInt(fNumVerts);
        for (size_t i=0; i<fNumVerts; i++)
            fVerts[i].write(S);
        S->writeInt(fNumTris);
        S->write(fNumTris * 3 * sizeof(unsigned short), fIndices);
    }

    mgr->writeKey(S, fObjectKey);
    fProps.write(S);
    mgr->writeKey(S, fSceneNode);
    S->writeInt(fLOSDBs);
    mgr->writeKey(S, fWorldKey);
    mgr->writeKey(S, fSndGroup);
}

void plHKPhysical::IPrcWrite(pfPrcHelper* prc) {
    plPhysical::IPrcWrite(prc);

    prc->startTag("PhysicalParams");
    prc->writeParam("Mass", fMass);
    prc->writeParam("Friction", fFriction);
    prc->writeParam("Restitution", fRestitution);
    prc->writeParamHex("Category", fCategory);
    prc->writeParamHex("Unk1", fUnk1);
    prc->writeParamHex("Unk2", fUnk2);
    prc->writeParamHex("LOSDBs", fLOSDBs);
    prc->writeParam("Bool1", fBool1);
    prc->writeParam("Bool2", fBool2);
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
    if (fBounds == plSimDefs::kHullBounds) {
        prc->writeSimpleTag("Verts");
        for (size_t i=0; i<fNumVerts; i++)
            fVerts[i].prcWrite(prc);
        prc->closeTag();
    } else if (fBounds == plSimDefs::kSphereBounds) {
        prc->startTag("SphereBounds");
        prc->writeParam("Radius", fSphereRadius);
        prc->endTag();
        fSphereOffset.prcWrite(prc);
        prc->closeTag();
    } else {    // Box, Proxy, Explicit
        prc->writeSimpleTag("Verts");
        for (size_t i=0; i<fNumVerts; i++)
            fVerts[i].prcWrite(prc);
        prc->closeTag();

        prc->writeSimpleTag("Triangles");
        for (size_t i=0; i<fNumTris; i++) {
            prc->writeTagNoBreak("Triangle");
            prc->getStream()->writeStr(plString::Format("%d %d %d",
                                        fIndices[(i*3)+0],
                                        fIndices[(i*3)+1],
                                        fIndices[(i*3)+2]));
            prc->closeTagNoBreak();
        }
        prc->closeTag();
    }
    prc->closeTag();
}

void plHKPhysical::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "PhysicalParams") {
        fMass = tag->getParam("Mass", "0").toFloat();
        fFriction = tag->getParam("Friction", "0").toFloat();
        fRestitution = tag->getParam("Restitution", "0").toFloat();
        fCategory = tag->getParam("Category", "0").toUint();
        fUnk1 = tag->getParam("Unk1", "0").toUint();
        fUnk2 = tag->getParam("Unk2", "0").toUint();
        fLOSDBs = tag->getParam("LOSDBs", "0").toUint();
        fBool1 = tag->getParam("Bool1", "false").toBool();
        fBool2 = tag->getParam("Bool2", "false").toBool();
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
            } else if (child->getName() == "Verts") {
                fNumVerts = child->countChildren();
                fVerts = new hsVector3[fNumVerts];
                const pfPrcTag* vert = child->getFirstChild();
                for (size_t i=0; i<fNumVerts; i++) {
                    fVerts[i].prcParse(vert);
                    vert = vert->getNextSibling();
                }
            } else if (child->getName() == "Triangles") {
                fNumTris = child->countChildren();
                fIndices = new unsigned short[fNumTris * 3];
                const pfPrcTag* tri = child->getFirstChild();
                for (size_t i=0; i<fNumTris; i++) {
                    if (tri->getName() != "Triangle")
                        throw pfPrcTagException(__FILE__, __LINE__, tri->getName());
                    hsTList<plString> idxList = tri->getContents();
                    if (idxList.getSize() != 3)
                        throw pfPrcParseException(__FILE__, __LINE__, "Triangles should have exactly 3 indices");
                    fIndices[(i*3)+0] = idxList.pop().toUint();
                    fIndices[(i*3)+1] = idxList.pop().toUint();
                    fIndices[(i*3)+2] = idxList.pop().toUint();
                    tri = tri->getNextSibling();
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
