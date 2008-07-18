#include "plPXPhysical.h"
#include "plHKPhysical.h"
#include "plODEPhysical.h"

#include "Debug/plDebug.h"
#include "PRP/Object/plSimulationInterface.h"

plPXPhysical::plPXPhysical()
            : fMass(0.0f), fFriction(0.0f), fRestitution(0.0f),
              fBounds(plSimDefs::kBoxBounds), fGroup(plSimDefs::kGroupStatic),
              fReportsOn(0), fSphereRadius(0.0f), fLOSDBs(0), fNumVerts(0),
              fNumTris(0), fVerts(NULL), fIndices(NULL), fTMDBuffer(NULL) {
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
              fProps(init.fProps), fSndGroup(init.fSndGroup),
              fNumVerts(init.fNumVerts), fNumTris(init.fNumTris) {
    fVerts = new hsVector3[fNumVerts];
    fIndices = new unsigned int[fNumTris * 3];
    fTMDBuffer = new unsigned int[fNumTris];
    for (size_t i=0; i<fNumVerts; i++)
        fVerts[i] = init.fVerts[i];
    memcpy(fIndices, init.fIndices, fNumTris * 3 * sizeof(unsigned int));
    memcpy(fTMDBuffer, init.fTMDBuffer, fNumTris * sizeof(unsigned int));
    
    SetFlagNames();
}

plPXPhysical::~plPXPhysical() {
    if (fVerts != NULL)
        delete[] fVerts;
    if (fIndices != NULL)
        delete[] fIndices;
    if (fTMDBuffer != NULL)
        delete[] fTMDBuffer;
}

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
        fNumVerts = S->readInt();
        fNumTris = S->readInt();
        S->readInt();
        S->readInt();
        S->readInt();
        S->readInt();

        fVerts = new hsVector3[fNumVerts];
        for (size_t i=0; i<fNumVerts; i++)
            fVerts[i].read(S);
        S->readInt();
        
        fIndices = new unsigned int[fNumTris * 3];
        for (size_t i=0; i<fNumTris; i++) {
            if (fNumVerts < 256) {
                fIndices[(i*3)+0] = S->readByte();
                fIndices[(i*3)+1] = S->readByte();
                fIndices[(i*3)+2] = S->readByte();
            } else if (fNumVerts < 65536) {
                fIndices[(i*3)+0] = S->readShort();
                fIndices[(i*3)+1] = S->readShort();
                fIndices[(i*3)+2] = S->readShort();
            } else {
                fIndices[(i*3)+0] = S->readInt();
                fIndices[(i*3)+1] = S->readInt();
                fIndices[(i*3)+2] = S->readInt();
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
        fNumVerts = S->readInt();
        fNumTris = S->readInt();

        fVerts = new hsVector3[fNumVerts];
        for (size_t i=0; i<fNumVerts; i++)
            fVerts[i].read(S);
        
        fIndices = new unsigned int[fNumTris * 3];
        for (size_t i=0; i<fNumTris; i++) {
            if (fNumVerts < 256) {
                fIndices[(i*3)+0] = S->readByte();
                fIndices[(i*3)+1] = S->readByte();
                fIndices[(i*3)+2] = S->readByte();
            } else if (fNumVerts < 65536) {
                fIndices[(i*3)+0] = S->readShort();
                fIndices[(i*3)+1] = S->readShort();
                fIndices[(i*3)+2] = S->readShort();
            } else {
                fIndices[(i*3)+0] = S->readInt();
                fIndices[(i*3)+1] = S->readInt();
                fIndices[(i*3)+2] = S->readInt();
            }
        }
        S->readInt();

        fTMDBuffer = new unsigned int[fNumTris];
        for (size_t i=0; i<fNumTris; i++) {
            if (fNumVerts < 256)
                fTMDBuffer[i] = S->readByte();
            else if (fNumVerts < 65536)
                fTMDBuffer[i] = S->readShort();
            else
                fTMDBuffer[i] = S->readInt();
        }
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
    } else {    // Proxy or Explicit
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

        prc->writeSimpleTag("TriMeshDataBuffer");
        for (size_t i=0; i<fNumTris; i++) {
            prc->startTag("Face");
            prc->writeParam("data", fTMDBuffer[i]);
            prc->endTag(true);
        }
        prc->closeTag();
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
                fIndices = new unsigned int[fNumTris * 3];
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
            } else if (child->getName() == "TriMeshDataBuffer") {
                if (fNumTris != child->countChildren())
                    throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of Data Faces");
                fTMDBuffer = new unsigned int[fNumTris];
                const pfPrcTag* face = child->getFirstChild();
                for (size_t i=0; i<fNumTris; i++) {
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
