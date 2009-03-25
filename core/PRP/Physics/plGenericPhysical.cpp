#include "plGenericPhysical.h"
#include "Debug/plDebug.h"
#include "PRP/Object/plSimulationInterface.h"

plGenericPhysical::plGenericPhysical()
                 : fMass(0.0f), fFriction(0.0f), fRestitution(0.0f),
                   fBounds(plSimDefs::kBoxBounds), fGroup(plSimDefs::kGroupStatic),
                   fCategory(0), fLOSDBs(0), fRadius(0.0f), fLength(0.0f),
                   fUnk1(0), fUnk2(0), fHKBool1(false), fHKBool2(false),
                   fTMDSize(0), fTMDBuffer(NULL), fReportsOn(0) {
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

plGenericPhysical::~plGenericPhysical() {
    if (fTMDBuffer != NULL)
        delete[] fTMDBuffer;
}

IMPLEMENT_CREATABLE(plGenericPhysical, kGenericPhysical, plPhysical)

void plGenericPhysical::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    if (S->getVer() >= pvEoa)
        IReadODEPhysical(S, mgr);
    else if (S->getVer() == pvLive)
        IReadPXPhysical(S, mgr);
    else
        IReadHKPhysical(S, mgr);
}

void plGenericPhysical::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);

    if (S->getVer() >= pvEoa)
        IWriteODEPhysical(S, mgr);
    else if (S->getVer() == pvLive)
        IWritePXPhysical(S, mgr);
    else
        IWriteHKPhysical(S, mgr);
}

void plGenericPhysical::IPrcWrite(pfPrcHelper* prc) {
    plPhysical::IPrcWrite(prc);

    prc->startTag("PhysicalParams");
    prc->writeParam("Mass", fMass);
    prc->writeParam("Friction", fFriction);
    prc->writeParam("Restitution", fRestitution);
    prc->writeParam("Group", plSimDefs::GroupNames[fGroup]);
    prc->writeParamHex("Category", fCategory);
    prc->writeParamHex("ReportsOn", fReportsOn);
    prc->writeParamHex("LOSDBs", fLOSDBs);
    prc->writeParamHex("Unknown1", fUnk1);
    prc->writeParamHex("Unknown2", fUnk2);
    prc->writeParam("HKBool1", fHKBool1);
    prc->writeParam("HKBool2", fHKBool2);
    prc->endTag(true);

    prc->writeSimpleTag("Object");
    fObjectKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SceneNode");
    fSceneNode->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SubWorld");
    fSubWorld->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SoundGroup");
    fSoundGroup->prcWrite(prc);
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
        prc->writeParam("Radius", fRadius);
        prc->endTag();
        fOffset.prcWrite(prc);
        prc->closeTag();
    } else if (fBounds == plSimDefs::kBoxBounds) {
        // ODE/PhysX format
        prc->writeSimpleTag("BoxBounds");
        prc->writeSimpleTag("Dimensions");
        fDimensions.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("Offset");
        fOffset.prcWrite(prc);
        prc->closeTag();
        prc->closeTag();

        // Havok format
        prc->writeSimpleTag("Verts");
        for (size_t i=0; i<fVerts.getSize(); i++)
            fVerts[i].prcWrite(prc);
        prc->closeTag();

        prc->writeSimpleTag("Faces");
        for (size_t i=0; i<fIndices.getSize(); i += 3) {
            prc->writeTagNoBreak("Triangle");
            prc->getStream()->writeStr(plString::Format("%d %d %d",
                                    fIndices[i+0],
                                    fIndices[i+1],
                                    fIndices[i+2]));
            prc->closeTagNoBreak();
        }
        prc->closeTag();
    } else if (fBounds == plSimDefs::kCylinderBounds) {
        prc->startTag("CylinderBounds");
        prc->writeParam("Radius", fRadius);
        prc->writeParam("Length", fLength);
        prc->endTag(true);
    } else {
        prc->writeSimpleTag("Verts");
        for (size_t i=0; i<fVerts.getSize(); i++)
            fVerts[i].prcWrite(prc);
        prc->closeTag();

        prc->writeSimpleTag("Faces");
        for (size_t i=0; i<fIndices.getSize(); i += 3) {
            prc->writeTagNoBreak("Triangle");
            prc->getStream()->writeStr(plString::Format("%d %d %d",
                                       fIndices[i+0],
                                       fIndices[i+1],
                                       fIndices[i+2]));
            prc->closeTagNoBreak();
        }
        prc->closeTag();

        if (fTMDBuffer != NULL) {
            prc->writeSimpleTag("TriMeshDataBuffer");
            for (size_t i=0; i<fTMDSize; i++) {
                prc->startTag("Face");
                prc->writeParam("data", fTMDBuffer[i]);
                prc->endTag(true);
            }
            prc->closeTag();
        }
    }
    prc->closeTag();
}

void plGenericPhysical::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "PhysicalParams") {
        fMass = tag->getParam("Mass", "0").toFloat();
        fFriction = tag->getParam("Friction", "0").toFloat();
        fRestitution = tag->getParam("Restitution", "0").toFloat();
        fCategory = tag->getParam("Category", "0").toUint();
        fReportsOn = tag->getParam("ReportsOn", "0").toUint();
        fLOSDBs = tag->getParam("LOSDBs", "0").toUint();
        fUnk1 = tag->getParam("Unknown1", "0").toUint();
        fUnk2 = tag->getParam("Unknown2", "0").toUint();
        fHKBool1 = tag->getParam("HKBool1", "false").toBool();
        fHKBool2 = tag->getParam("HKBool2", "false").toBool();

        plString group = tag->getParam("Group", "kGroupStatic");
        for (size_t i=0; i<plSimDefs::kGroupMax; i++) {
            if (group == plSimDefs::GroupNames[i])
                fGroup = (plSimDefs::Group)i;
        }
    } else if (tag->getName() == "Object") {
        if (tag->hasChildren())
            fObjectKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SubWorld") {
        if (tag->hasChildren())
            fSubWorld = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SoundGroup") {
        if (tag->hasChildren())
            fSoundGroup = mgr->prcParseKey(tag->getFirstChild());
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
                fRadius = child->getParam("Radius", "0").toFloat();
                if (child->hasChildren())
                    fOffset.prcParse(child->getFirstChild());
            } else if (child->getName() == "BoxBounds") {
                const pfPrcTag* subchild = child->getFirstChild();
                while (subchild != NULL) {
                    if (subchild->getName() == "Dimensions") {
                        if (subchild->hasChildren())
                            fDimensions.prcParse(subchild->getFirstChild());
                    } else if (subchild->getName() == "Offset") {
                        if (subchild->hasChildren())
                            fOffset.prcParse(subchild->getFirstChild());
                    } else {
                        throw pfPrcTagException(__FILE__, __LINE__, subchild->getName());
                    }
                    subchild = subchild->getNextSibling();
                }
            } else if (child->getName() == "CylinderBounds") {
                fRadius = child->getParam("Radius", "0").toFloat();
                fLength = child->getParam("Length", "0").toFloat();
            } else if (child->getName() == "Verts") {
                fVerts.setSize(child->countChildren());
                const pfPrcTag* vert = child->getFirstChild();
                for (size_t i=0; i<fVerts.getSize(); i++) {
                    fVerts[i].prcParse(vert);
                    vert = vert->getNextSibling();
                }
            } else if (child->getName() == "Faces") {
                fIndices.setSize(child->countChildren() * 3);
                const pfPrcTag* tri = child->getFirstChild();
                for (size_t i=0; i<fIndices.getSize(); i += 3) {
                    if (tri->getName() != "Triangle")
                        throw pfPrcTagException(__FILE__, __LINE__, tri->getName());
                    hsTList<plString> idxList = tri->getContents();
                    if (idxList.getSize() != 3)
                        throw pfPrcParseException(__FILE__, __LINE__, "Triangles should have exactly 3 indices");
                    fIndices[i+0] = idxList.pop().toUint();
                    fIndices[i+1] = idxList.pop().toUint();
                    fIndices[i+2] = idxList.pop().toUint();
                    tri = tri->getNextSibling();
                }
            } else if (child->getName() == "TriMeshDataBuffer") {
                fTMDSize = child->countChildren();
                fTMDBuffer = new unsigned char[fTMDSize];
                const pfPrcTag* face = child->getFirstChild();
                for (size_t i=0; i<fTMDSize; i++) {
                    if (face->getName() != "Face")
                        throw pfPrcTagException(__FILE__, __LINE__, face->getName());
                    fTMDBuffer[i] = face->getParam("data", "0").toUint();
                    face = face->getNextSibling();
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

void plGenericPhysical::IReadHKPhysical(hsStream* S, plResManager* mgr) {
    fPos.read(S);
    float rad = S->readFloat();
    hsVector3 axis;
    axis.read(S);
    fRot = hsQuat(axis.X, axis.Y, axis.Z, rad);

    fMass = S->readFloat();
    fFriction = S->readFloat();
    fRestitution = S->readFloat();
    fBounds = (plSimDefs::Bounds)S->readInt();
    fCategory = S->readInt();
    fUnk1 = S->readInt();
    fUnk2 = S->readInt();
    fHKBool1 = S->readBool();
    fHKBool2 = S->readBool();

    if (fBounds == plSimDefs::kHullBounds) {
        fVerts.setSize(S->readInt());
        for (size_t i=0; i<fVerts.getSize(); i++)
            fVerts[i].read(S);
    } else if (fBounds == plSimDefs::kSphereBounds) {
        fOffset.read(S);
        fRadius = S->readFloat();
    } else {    // Box, Proxy, Explicit
        fVerts.setSize(S->readInt());
        for (size_t i=0; i<fVerts.getSize(); i++)
            fVerts[i].read(S);
        fIndices.setSize(S->readInt() * 3);
        for (size_t i=0; i<fIndices.getSize(); i++)
            fIndices[i] = S->readShort();
    }

    fObjectKey = mgr->readKey(S);
    fProps.read(S);
    fSceneNode = mgr->readKey(S);
    fLOSDBs = S->readInt();
    fSubWorld = mgr->readKey(S);
    fSoundGroup = mgr->readKey(S);
}

void plGenericPhysical::IReadODEPhysical(hsStream* S, plResManager* mgr) {
    fBounds = (plSimDefs::Bounds)S->readInt();

    if (fTMDBuffer != NULL)
        delete[] fTMDBuffer;
    fTMDBuffer = NULL;

    if (fBounds == plSimDefs::kExplicitBounds) {
        fVerts.setSize(S->readInt());
        for (size_t i=0; i<fVerts.getSize(); i++)
            fVerts[i].read(S);
        fIndices.setSize(S->readInt() * 3);
        for (size_t i=0; i<fIndices.getSize(); i++)
            fIndices[i] = S->readInt();
        fTMDSize = S->readInt();
        fTMDBuffer = new unsigned char[fTMDSize];
        S->read(fTMDSize, fTMDBuffer);
    } else if (fBounds == plSimDefs::kSphereBounds) {
        fRadius = S->readFloat();
    } else if (fBounds == plSimDefs::kBoxBounds) {
        fDimensions.read(S);
    } else if (fBounds == plSimDefs::kCylinderBounds) {
        fLength = S->readFloat();
        fRadius = S->readFloat();
    }
    fMass = S->readFloat();

    fCategory = S->readInt();
    fUnk1 = S->readInt();
    fUnk2 = S->readInt();
    fProps.read(S);
    fLOSDBs = S->readShort();
    fObjectKey = mgr->readKey(S);
    fSceneNode = mgr->readKey(S);
}

void plGenericPhysical::IReadPXPhysical(hsStream* S, plResManager* mgr) {
    fMass = S->readFloat();
    fFriction = S->readFloat();
    fRestitution = S->readFloat();
    fBounds = (plSimDefs::Bounds)S->readByte();
    fGroup = (plSimDefs::Group)S->readByte();
    fReportsOn = S->readInt();
    fLOSDBs = S->readShort();
    fObjectKey = mgr->readKey(S);
    fSceneNode = mgr->readKey(S);
    fSubWorld = mgr->readKey(S);

    fSoundGroup = mgr->readKey(S);
    fPos.read(S);
    fRot.read(S);
    fProps.read(S);

    if (fTMDBuffer != NULL)
        delete[] fTMDBuffer;
    fTMDBuffer = NULL;

    if (fBounds == plSimDefs::kSphereBounds) {
        fRadius = S->readFloat();
        fOffset.read(S);
    } else if (fBounds == plSimDefs::kBoxBounds) {
        fDimensions.read(S);
        fOffset.read(S);
    } else if (fBounds == plSimDefs::kHullBounds) {
        //TODO: This is messy and incomplete
        char tag[4];
        S->read(4, tag);
        if (memcmp(tag, "NXS\x01", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid PhysX header");
        S->read(4, tag);
        if (memcmp(tag, "CVXM", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid header");
        S->readInt();
        S->readInt();

        S->read(4, tag);
        if (memcmp(tag, "ICE\x01", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid header");
        S->read(4, tag);
        if (memcmp(tag, "CLHL", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid header");
        S->readInt();

        S->read(4, tag);
        if (memcmp(tag, "ICE\x01", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid header");
        S->read(4, tag);
        if (memcmp(tag, "CVHL", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid header");

        S->readInt();
        fVerts.setSize(S->readInt());
        fIndices.setSize(S->readInt() * 3);
        S->readInt();
        S->readInt();
        S->readInt();
        S->readInt();

        for (size_t i=0; i<fVerts.getSize(); i++)
            fVerts[i].read(S);
        S->readInt();

        for (size_t i=0; i<fIndices.getSize(); i += 3) {
            if (fVerts.getSize() < 256) {
                fIndices[i+0] = S->readByte();
                fIndices[i+1] = S->readByte();
                fIndices[i+2] = S->readByte();
            } else if (fVerts.getSize() < 65536) {
                fIndices[i+0] = S->readShort();
                fIndices[i+1] = S->readShort();
                fIndices[i+2] = S->readShort();
            } else {
                fIndices[i+0] = S->readInt();
                fIndices[i+1] = S->readInt();
                fIndices[i+2] = S->readInt();
            }
        }
    } else {    // Proxy or Explicit
        //TODO: This is messy and incomplete
        char tag[4];
        S->read(4, tag);
        if (memcmp(tag, "NXS\x01", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid PhysX header");
        S->read(4, tag);
        if (memcmp(tag, "MESH", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid Mesh header");
        S->readInt();
        S->readInt();
        S->readFloat();
        S->readInt();
        S->readInt();
        fVerts.setSize(S->readInt());
        fIndices.setSize(S->readInt() * 3);

        for (size_t i=0; i<fVerts.getSize(); i++)
            fVerts[i].read(S);

        for (size_t i=0; i<fIndices.getSize(); i += 3) {
            if (fVerts.getSize() < 256) {
                fIndices[i+0] = S->readByte();
                fIndices[i+1] = S->readByte();
                fIndices[i+2] = S->readByte();
            } else if (fVerts.getSize() < 65536) {
                fIndices[i+0] = S->readShort();
                fIndices[i+1] = S->readShort();
                fIndices[i+2] = S->readShort();
            } else {
                fIndices[i+0] = S->readInt();
                fIndices[i+1] = S->readInt();
                fIndices[i+2] = S->readInt();
            }
        }
        S->readInt();

        /*
        fTMDBuffer = new unsigned int[fNumTris];
        for (size_t i=0; i<fNumTris; i++) {
            if (fNumVerts < 256)
                fTMDBuffer[i] = S->readByte();
            else if (fNumVerts < 65536)
                fTMDBuffer[i] = S->readShort();
            else
                fTMDBuffer[i] = S->readInt();
        }
        */
    }
}

void plGenericPhysical::IWriteHKPhysical(hsStream* S, plResManager* mgr) {
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
    S->writeBool(fHKBool1);
    S->writeBool(fHKBool2);

    if (fBounds == plSimDefs::kHullBounds) {
        S->writeInt(fVerts.getSize());
        for (size_t i=0; i<fVerts.getSize(); i++)
            fVerts[i].write(S);
    } else if (fBounds == plSimDefs::kSphereBounds) {
        fOffset.write(S);
        S->writeFloat(fRadius);
    } else {    // Box, Proxy, Explicit
        S->writeInt(fVerts.getSize());
        for (size_t i=0; i<fVerts.getSize(); i++)
            fVerts[i].write(S);
        S->writeInt(fIndices.getSize() / 3);
        for (size_t i=0; i<fIndices.getSize(); i++)
            S->writeShort(fIndices[i]);
    }

    mgr->writeKey(S, fObjectKey);
    fProps.write(S);
    mgr->writeKey(S, fSceneNode);
    S->writeInt(fLOSDBs);
    mgr->writeKey(S, fSubWorld);
    mgr->writeKey(S, fSoundGroup);
}

void plGenericPhysical::IWriteODEPhysical(hsStream* S, plResManager* mgr) {
    S->writeInt(fBounds);

    if (fBounds == plSimDefs::kExplicitBounds) {
        S->writeInt(fVerts.getSize());
        for (size_t i=0; i<fVerts.getSize(); i++)
            fVerts[i].write(S);
        S->writeInt(fIndices.getSize() / 3);
        for (size_t i=0; i<fIndices.getSize(); i++)
            S->writeInt(fIndices[i]);
        S->writeInt(fTMDSize);
        S->write(fTMDSize, fTMDBuffer);
    } else if (fBounds == plSimDefs::kSphereBounds) {
        S->writeFloat(fRadius);
    } else if (fBounds == plSimDefs::kBoxBounds) {
        fDimensions.write(S);
    } else if (fBounds == plSimDefs::kCylinderBounds) {
        S->writeFloat(fLength);
        S->writeFloat(fRadius);
    }
    S->writeFloat(fMass);

    S->writeInt(fCategory);
    S->writeInt(fUnk1);
    S->writeInt(fUnk2);
    fProps.write(S);
    S->writeShort(fLOSDBs);
    mgr->writeKey(S, fObjectKey);
    mgr->writeKey(S, fSceneNode);
}

void plGenericPhysical::IWritePXPhysical(hsStream* S, plResManager* mgr) {
    S->writeFloat(fMass);
    S->writeFloat(fFriction);
    S->writeFloat(fRestitution);
    S->writeByte((hsUbyte)fBounds);
    S->writeByte((hsUbyte)fGroup);
    S->writeInt(fReportsOn);
    S->writeShort(fLOSDBs);
    mgr->writeKey(S, fObjectKey);
    mgr->writeKey(S, fSceneNode);
    mgr->writeKey(S, fSubWorld);

    mgr->writeKey(S, fSoundGroup);
    fPos.write(S);
    fRot.write(S);
    fProps.write(S);

    if (fBounds == plSimDefs::kSphereBounds) {
        S->writeFloat(fRadius);
        fOffset.write(S);
    } else if (fBounds == plSimDefs::kBoxBounds) {
        fDimensions.write(S);
        fOffset.write(S);
    } else if (fBounds == plSimDefs::kHullBounds) {
        plDebug::Warning("plPXPhysical: HullBounds not implemented");
    } else {    // Proxy or Explicit
        plDebug::Warning("plPXPhysical: TriangleMesh not implemented");
    }
}

float plGenericPhysical::getMass() const { return fMass; }
float plGenericPhysical::getFriction() const { return fFriction; }
float plGenericPhysical::getRestitution() const { return fRestitution; }
plSimDefs::Bounds plGenericPhysical::getBoundsType() const { return fBounds; }
plSimDefs::Group plGenericPhysical::getGroup() const { return fGroup; }
unsigned int plGenericPhysical::getCategory() const { return fCategory; }
unsigned short plGenericPhysical::getLOSDBs() const { return fLOSDBs; }
unsigned int plGenericPhysical::getReportsOn() const { return fReportsOn; }

plKey plGenericPhysical::getObject() const { return fObjectKey; }
plKey plGenericPhysical::getSceneNode() const { return fSceneNode; }
plKey plGenericPhysical::getSubWorld() const { return fSubWorld; }
plKey plGenericPhysical::getSoundGroup() const { return fSoundGroup; }
hsVector3 plGenericPhysical::getPos() const { return fPos; }
hsQuat plGenericPhysical::getRot() const { return fRot; }
hsBitVector& plGenericPhysical::getProps() { return fProps; }

hsVector3 plGenericPhysical::getDimensions() const { return fDimensions; }
hsVector3 plGenericPhysical::getOffset() const { return fOffset; }
float plGenericPhysical::getRadius() const { return fRadius; }
float plGenericPhysical::getLength() const { return fLength; }
size_t plGenericPhysical::getNumVerts() const { return fVerts.getSize(); }
size_t plGenericPhysical::getNumIndices() const { return fIndices.getSize(); }
hsVector3 plGenericPhysical::getVert(size_t idx) const { return fVerts[idx]; }
unsigned int plGenericPhysical::getIndex(size_t idx) const { return fIndices[idx]; }
size_t plGenericPhysical::getTMDSize() const { return fTMDSize; }
const unsigned char* plGenericPhysical::getTMDBuffer() const { return fTMDBuffer; }

void plGenericPhysical::setMass(float mass) { fMass = mass; }
void plGenericPhysical::setFriction(float friction) { fFriction = friction; }
void plGenericPhysical::setRestitution(float restitution) { fRestitution = restitution; }
void plGenericPhysical::setBoundsType(plSimDefs::Bounds bounds) { fBounds = bounds; }
void plGenericPhysical::setGroup(plSimDefs::Group group) { fGroup = group; }
void plGenericPhysical::setCategory(unsigned int category) { fCategory = category; }
void plGenericPhysical::setLOSDBs(unsigned short los) { fLOSDBs = los; }
void plGenericPhysical::setReportsOn(unsigned int reports) { fReportsOn = reports; }

void plGenericPhysical::setObject(plKey object) { fObjectKey = object; }
void plGenericPhysical::setSceneNode(plKey node) { fSceneNode = node; }
void plGenericPhysical::setSubWorld(plKey world) { fSubWorld = world; }
void plGenericPhysical::setSoundGroup(plKey group) { fSoundGroup = group; }
void plGenericPhysical::setPos(const hsVector3& pos) { fPos = pos; }
void plGenericPhysical::setRot(const hsQuat& rot) { fRot = rot; }

void plGenericPhysical::setDimensions(const hsVector3& box) { fDimensions = box; }
void plGenericPhysical::setOffset(const hsVector3& offset) { fOffset = offset; }
void plGenericPhysical::setRadius(float radius) { fRadius = radius; }
void plGenericPhysical::setLength(float length) { fLength = length; }

void plGenericPhysical::setVerts(size_t numVerts, const hsVector3* verts) {
    fVerts.setSize(numVerts);
    for (size_t i=0; i<numVerts; i++)
        fVerts[i] = verts[i];
}

void plGenericPhysical::setIndices(size_t numIndices, const unsigned int* indices) {
    fIndices.setSize(numIndices);
    for (size_t i=0; i<numIndices; i++)
        fIndices[i] = indices[i];
}

void plGenericPhysical::setTMDBuffer(size_t tmdSize, const unsigned char* tmdBuffer) {
    if (fTMDBuffer != NULL)
        delete[] fTMDBuffer;
    if (tmdSize == 0 || tmdBuffer == NULL) {
        fTMDSize = 0;
        fTMDBuffer = NULL;
    }
    fTMDSize = tmdSize;
    fTMDBuffer = new unsigned char[fTMDSize];
    memcpy(fTMDBuffer, tmdBuffer, fTMDSize);
}
