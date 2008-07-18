#include "plODEPhysical.h"
#include "plPXPhysical.h"
#include "plHKPhysical.h"

#include "Debug/plDebug.h"

plODEPhysical::plODEPhysical()
             : fBounds(plSimDefs::kBoxBounds), fCategory(0), fLOSDBs(0),
               fUnk1(0), fUnk2(0), fFlags(0), fMass(0.0f), fRadius(0.0f),
               fLength(0.0f), fNumVerts(0), fNumTris(0), fTMDSize(0),
               fVerts(NULL), fIndices(NULL), fTMDBuffer(NULL) { }

plODEPhysical::plODEPhysical(const plODEPhysical& init)
             : fBounds(init.fBounds), fCategory(init.fCategory),
               fLOSDBs(init.fLOSDBs), fObjectKey(init.fObjectKey),
               fSceneNode(init.fSceneNode), fUnk1(init.fUnk1), fUnk2(init.fUnk2),
               fFlags(init.fFlags), fBoxDimensions(init.fBoxDimensions),
               fMass(init.fMass), fRadius(init.fRadius), fLength(init.fLength),
               fNumVerts(init.fNumVerts), fNumTris(init.fNumTris),
               fTMDSize(init.fTMDSize) {
    fVerts = new hsVector3[fNumVerts];
    fIndices = new unsigned int[fNumTris * 3];
    fTMDBuffer = new unsigned char[fTMDSize];
    for (size_t i=0; i<fNumVerts; i++)
        fVerts[i] = init.fVerts[i];
    memcpy(fIndices, init.fIndices, fNumTris * 3 * sizeof(unsigned int));
    memcpy(fTMDBuffer, init.fTMDBuffer, fTMDSize);
}

plODEPhysical::~plODEPhysical() {
    if (fVerts != NULL)
        delete[] fVerts;
    if (fIndices != NULL)
        delete[] fIndices;
    if (fTMDBuffer != NULL)
        delete[] fTMDBuffer;
}

IMPLEMENT_CREATABLE(plODEPhysical, kODEPhysical, plPhysical)

plHKPhysical* plODEPhysical::ConvertToHavok() const {
    plHKPhysical* conv = new plHKPhysical();
    conv->fBounds = fBounds;
    conv->fCategory = fCategory;
    conv->fLOSDBs = fLOSDBs;
    conv->fObjectKey = fObjectKey;
    conv->fSceneNode = fSceneNode;
    conv->fUnk1 = fUnk1;
    conv->fUnk2 = fUnk2;
    // fProps
    // fBoxDimensions
    // fPos
    // fRot
    conv->fMass = fMass;
    conv->fFriction = 0.5f;
    conv->fRestitution = 0.0f;
    conv->fSphereRadius = fRadius;
    // fSphereOffset
    conv->fNumVerts = fNumVerts;
    conv->fNumTris = fNumTris;

    conv->fVerts = new hsVector3[fNumVerts];
    conv->fIndices = new unsigned short[fNumTris * 3];
    for (size_t i=0; i<fNumVerts; i++)
        conv->fVerts[i] = fVerts[i];
    for (size_t i=0; i<fNumTris; i += 3) {
        conv->fIndices[i+0] = fIndices[i+0];
        conv->fIndices[i+1] = fIndices[i+1];
        conv->fIndices[i+2] = fIndices[i+2];
    }
    
    plDebug::Warning("plODEPhysical::ConvertToHavok() incomplete");

    return conv;
}

plPXPhysical* plODEPhysical::ConvertToPhysX() const {
    plPXPhysical* conv = new plPXPhysical();
    conv->fMass = fMass;
    conv->fFriction = 0.5f;
    conv->fRestitution = 0.0f;
    conv->fBounds = fBounds;
    // fGroup
    // fReportsOn
    conv->fObjectKey = fObjectKey;
    conv->fSceneNode = fSceneNode;
    conv->fSphereRadius = fRadius;
    // fSphereOffset
    conv->fLOSDBs = fLOSDBs;
    // fPos
    // fRot
    // fProps
    
    // fBoxDimensions
    // fBoxOffset

    plDebug::Warning("plODEPhysical::ConvertToPhysX() incomplete");
    
    return conv;
}

plODEPhysical* plODEPhysical::ConvertToODE() const {
    return new plODEPhysical(*this);
}

void plODEPhysical::readData(hsStream* S, plResManager* mgr) {
    fBounds = (plSimDefs::Bounds)S->readInt();

    if (fBounds == plSimDefs::kExplicitBounds) {
        fNumVerts = S->readInt();
        fVerts = new hsVector3[fNumVerts];
        for (size_t i=0; i<fNumVerts; i++)
            fVerts[i].read(S);
        fNumTris = S->readInt();
        fIndices = new unsigned int[fNumTris * 3];
        S->read(fNumTris * 3 * sizeof(unsigned int), fIndices);
        fTMDSize = S->readInt();
        fTMDBuffer = new unsigned char[fTMDSize];
        S->read(fTMDSize, fTMDBuffer);
    } else if (fBounds == plSimDefs::kSphereBounds) {
        fRadius = S->readFloat();
    } else if (fBounds == plSimDefs::kBoxBounds) {
        fBoxDimensions.read(S);
    } else if (fBounds == plSimDefs::kCylinderBounds) {
        fLength = S->readFloat();
        fRadius = S->readFloat();
    }
    fMass = S->readFloat();

    fCategory = S->readInt();
    fUnk1 = S->readInt();
    fUnk2 = S->readInt();
    S->readInt();   // Le sigh
    fFlags = S->readInt();
    fLOSDBs = S->readShort();
    fObjectKey = mgr->readKey(S);
    fSceneNode = mgr->readKey(S);
}

void plODEPhysical::writeData(hsStream* S, plResManager* mgr) {
    S->writeInt(fBounds);
    
    if (fBounds == plSimDefs::kExplicitBounds) {
        S->writeInt(fNumVerts);
        for (size_t i=0; i<fNumVerts; i++)
            fVerts[i].write(S);
        S->writeInt(fNumTris);
        S->write(fNumTris * 3 * sizeof(unsigned int), fIndices);
        S->writeInt(fTMDSize);
        S->write(fTMDSize, fTMDBuffer);
    } else if (fBounds == plSimDefs::kSphereBounds) {
        S->writeFloat(fRadius);
    } else if (fBounds == plSimDefs::kBoxBounds) {
        fBoxDimensions.write(S);
    } else if (fBounds == plSimDefs::kCylinderBounds) {
        S->writeFloat(fLength);
        S->writeFloat(fRadius);
    }
    S->writeFloat(fMass);

    S->writeInt(fCategory);
    S->writeInt(fUnk1);
    S->writeInt(fUnk2);
    S->writeInt(1);
    S->writeInt(fFlags);
    S->writeShort(fLOSDBs);
    mgr->writeKey(S, fObjectKey);
    mgr->writeKey(S, fSceneNode);
}

void plODEPhysical::IPrcWrite(pfPrcHelper* prc) {
    plPhysical::IPrcWrite(prc);

    prc->startTag("PhysicalParams");
    prc->writeParam("Mass", fMass);
    prc->writeParamHex("Category", fCategory);
    prc->writeParamHex("LOSDBs", fLOSDBs);
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Unknown1", fUnk1);
    prc->writeParam("Unknown2", fUnk2);
    prc->endTag(true);

    prc->writeSimpleTag("Object");
    fObjectKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SceneNode");
    fSceneNode->prcWrite(prc);
    prc->closeTag();

    prc->startTag("Bounds");
    prc->writeParam("Type", plSimDefs::BoundsNames[fBounds]);
    prc->endTag();
    if (fBounds == plSimDefs::kExplicitBounds) {
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
        for (size_t i=0; i<fTMDSize; i++) {
            prc->startTag("Face");
            prc->writeParam("data", fTMDBuffer[i]);
            prc->endTag(true);
        }
        prc->closeTag();
    } else if (fBounds == plSimDefs::kSphereBounds) {
        prc->startTag("SphereBounds");
        prc->writeParam("Radius", fRadius);
        prc->endTag(true);
    } else if (fBounds == plSimDefs::kBoxBounds) {
        prc->writeSimpleTag("BoxBounds");
        fBoxDimensions.prcWrite(prc);
        prc->closeTag();
    } else if (fBounds == plSimDefs::kCylinderBounds) {
        prc->startTag("CylinderBounds");
        prc->writeParam("Radius", fRadius);
        prc->writeParam("Length", fLength);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plODEPhysical::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "PhysicalParams") {
        fMass = tag->getParam("Mass", "0").toFloat();
        fCategory = tag->getParam("Category", "0").toUint();
        fLOSDBs = tag->getParam("LOSDBs", "0").toUint();
        fFlags = tag->getParam("Flags", "0").toUint();
        fUnk1 = tag->getParam("Unknown1", "0").toUint();
        fUnk2 = tag->getParam("Unknown2", "0").toUint();
    } else if (tag->getName() == "Object") {
        if (tag->hasChildren())
            fObjectKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Bounds" ) {
        plString bounds = tag->getParam("Type", "kBoxBounds");
        for (size_t i=0; i<plSimDefs::kNumBounds; i++)
            if (bounds == plSimDefs::BoundsNames[i])
                fBounds = (plSimDefs::Bounds)i;
        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
            if (child->getName() == "SphereBounds") {
                fRadius = child->getParam("Radius", "0").toFloat();
            } else if (child->getName() == "BoxBounds") {
                if (child->hasChildren())
                    fBoxDimensions.prcParse(child->getFirstChild());
            } else if (child->getName() == "CylinderBounds") {
                fRadius = child->getParam("Radius", "0").toFloat();
                fLength = child->getParam("Length", "0").toFloat();
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
