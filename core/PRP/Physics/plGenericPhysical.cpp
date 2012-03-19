/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plGenericPhysical.h"
#include "Debug/plDebug.h"
#include "PRP/Object/plSceneObject.h"
#include "PRP/Object/plSimulationInterface.h"
/* Engine specific headers */
#include "plHKPhysical.h"
#include "plODEPhysical.h"
#include "plPXPhysical.h"

#ifdef HAVE_PX_SDK
// for PhysX, these can't be defined
#undef min
#undef max
#include <NxCooking.h>
#include <NxConvexMeshDesc.h>
#include <NxTriangleMeshDesc.h>
#include <NxStream.h>

class plPXStream : public NxStream
{
    hsStream* fStream;
public:
    plPXStream(hsStream* s) : fStream(s) {}

    virtual NxU8        readByte() const { return fStream->readByte(); }
    virtual NxU16       readWord() const { return fStream->readShort(); }
    virtual NxU32       readDword() const { return fStream->readInt(); }
    virtual float       readFloat() const { return fStream->readFloat(); }
    virtual double      readDouble() const { return fStream->readDouble(); }
    virtual void        readBuffer(void* buffer, NxU32 size) const { fStream->read(size, buffer); }

    virtual NxStream&   storeByte(NxU8 b) { fStream->writeByte(b); return *this; }
    virtual NxStream&   storeWord(NxU16 w) { fStream->writeShort(w); return *this; }
    virtual NxStream&   storeDword(NxU32 d) { fStream->writeInt(d); return *this; }
    virtual NxStream&   storeFloat(NxReal f) { fStream->writeFloat(f); return *this; }
    virtual NxStream&   storeDouble(NxF64 f) { fStream->writeDouble(f); return *this; }
    virtual NxStream&   storeBuffer(const void* buffer, NxU32 size) { fStream->write(size, buffer); return *this; }

};

bool plGenericPhysical::sPhysxWasInit = false;

#endif

plGenericPhysical::plGenericPhysical()
                 : fInternalType(kPhysNone), fInternalBuffer(NULL), fInternalSize(0),
                   fMass(0.0f), fFriction(0.0f), fRestitution(0.0f),
                   fBounds(plSimDefs::kBoxBounds),
                   fMemberGroup(plSimDefs::kGroupStatic),
                   fCollideGroup(0), fReportGroup(0),
                   fDisableReport(false), fDisableCollide(false), fLOSDBs(0),
                   fRadius(0.0f), fLength(0.0f), fTMDSize(0), fTMDBuffer(NULL) {
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
    delete[] fInternalBuffer;
    delete[] fTMDBuffer;
}

void plGenericPhysical::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    if (S->getVer().isUniversal())
        fInternalType = (PhysType)S->readInt();
    else if (S->getVer().isNewPlasma())
        fInternalType = kPhysODE;
    else if (S->getVer().isLive())
        fInternalType = kPhysX;
    else
        fInternalType = kPhysHavok;

    switch (fInternalType) {
    case kPhysODE:
        IReadODEPhysical(S, mgr);
        break;
    case kPhysX:
        IReadPXPhysical(S, mgr);
        break;
    case kPhysHavok:
        IReadHKPhysical(S, mgr);
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__, "Physics type");
    }
}

void plGenericPhysical::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);

    PhysType wtype;
    if (S->getVer().isUniversal()) {
        wtype = fInternalType;
        S->writeInt(wtype);
    } else if (S->getVer().isNewPlasma()) {
        wtype = kPhysODE;
    } else if (S->getVer().isLive()) {
        wtype = kPhysX;
    } else {
        wtype = kPhysHavok;
    }

    switch (wtype) {
    case kPhysODE:
        IWriteODEPhysical(S, mgr);
        break;
    case kPhysX:
        IWritePXPhysical(S, mgr);
        break;
    case kPhysHavok:
        IWriteHKPhysical(S, mgr);
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__, "Physics type");
    }
}

void plGenericPhysical::IPrcWrite(pfPrcHelper* prc) {
    plPhysical::IPrcWrite(prc);

    plString groups = "";
    plString reports = fDisableReport ? "kDisable " : "";
    plString collides = fDisableCollide ? "kDisable " : "";
    for (size_t i=0; i<plSimDefs::kGroupMax; i++) {
        if (fMemberGroup == i) {
           groups += plSimDefs::GroupNames[i];
           groups += " ";
        }
        if ((fReportGroup & (1u << i)) == (1u << i)) {
           reports += plSimDefs::GroupNames[i];
           reports += " ";
        }
        if ((fCollideGroup & (1u << i)) == (1u << i)) {
           collides += plSimDefs::GroupNames[i];
           collides += " ";
        }
    }

    prc->startTag("PhysicalParams");
    prc->writeParam("Mass", fMass);
    prc->writeParam("Friction", fFriction);
    prc->writeParam("Restitution", fRestitution);
    prc->writeParam("MemberGroup", groups);
    prc->writeParam("ReportGroup", reports);
    prc->writeParam("CollideGroup", collides);
    /*prc->writeParamHex("MemberGroupHEX", fMemberGroup);
    prc->writeParamHex("ReportGroupHEX", fReportGroup);
    prc->writeParamHex("CollideGroupHEX", fCollideGroup);*/
    prc->writeParamHex("LOSDBs", fLOSDBs);
    /*prc->writeParam("HKBool1", fDisableReport);
    prc->writeParam("HKBool2", fDisableCollide);*/
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
        fLOSDBs = tag->getParam("LOSDBs", "0").toUint();
        fCollideGroup = tag->getParam("CollideGroup", "0").toUint();

        plString group = tag->getParam("MemberGroup", "kGroupStatic");
        plString reports = tag->getParam("ReportGroup", "");
        plString collides = tag->getParam("CollideGroup", "");
        fMemberGroup = fReportGroup = fCollideGroup = 0;
        fDisableReport = (reports.find("kDisable") != -1);
        fDisableCollide = (collides.find("kDisable") != -1);
        for (size_t i=0; i<plSimDefs::kGroupMax; i++) {
            if (group.find(plSimDefs::GroupNames[i]) != -1) {
                fMemberGroup |= i;
            }
            if (reports.find(plSimDefs::GroupNames[i]) != -1) {
                fReportGroup |= (1 << i);
            }
            if (collides.find(plSimDefs::GroupNames[i]) != -1) {
                fCollideGroup |= (1 << i);
            }
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

    unsigned int hMemberGroup, hReportGroup, hCollideGroup;
    fMass = S->readFloat();
    fFriction = S->readFloat();
    fRestitution = S->readFloat();
    fBounds = (plSimDefs::Bounds)S->readInt();
    fMemberGroup = plHKSimDefs::fromGroup(hMemberGroup = S->readInt());
    fReportGroup = plHKSimDefs::getBitshiftGroup(hReportGroup = S->readInt());
    fCollideGroup = plHKSimDefs::getBitshiftGroup(hCollideGroup = S->readInt());
    fDisableReport = S->readBool();
    fDisableCollide = S->readBool();

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

#ifdef DEBUG
    unsigned int memGroup = plHKSimDefs::toGroup(fMemberGroup);
    unsigned int repGroup = plHKSimDefs::setBitshiftGroup(fReportGroup);
    unsigned int colGroup = plHKSimDefs::setBitshiftGroup(fCollideGroup);
    bool showLOSDB = false;
    plHKSimDefs::fixGroups(this, &memGroup, &repGroup, &colGroup);
    // now compare
    if (memGroup != hMemberGroup) {
        showLOSDB = true;
        plDebug::Warning("%s memGroup changed: 0x%08X => 0x%08X",
                getKey()->toString().cstr(), hMemberGroup, memGroup);
    }
    if (repGroup != hReportGroup) {
        showLOSDB = true;
        plDebug::Warning("%s repGroup changed: 0x%08X => 0x%08X",
                getKey()->toString().cstr(), hReportGroup, repGroup);
    }
    if (colGroup != hCollideGroup) {
        showLOSDB = true;
        plDebug::Warning("%s colGroup changed: 0x%08X => 0x%08X",
                getKey()->toString().cstr(), hCollideGroup, colGroup);
    }
    if (showLOSDB) {
        plDebug::Debug("%s LOSDBs = 0x%08X", getKey()->toString().cstr(),
                fLOSDBs);
    }
#endif
}

void plGenericPhysical::IReadODEPhysical(hsStream* S, plResManager* mgr) {
    fBounds = (plSimDefs::Bounds)S->readInt();

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

    fMemberGroup = S->readInt();
    fCollideGroup = S->readInt();
    fReportGroup = S->readInt();
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

    uint8_t group = S->readByte();
    fMemberGroup = plPXSimDefs::fromGroup(group); //fGroup
    fCollideGroup = plPXSimDefs::getCollideGroup(group);
    fReportGroup = plPXSimDefs::getReportsOn(S->readInt()); //fReportsOn
    fLOSDBs = S->readShort();
    fObjectKey = mgr->readKey(S);
    fSceneNode = mgr->readKey(S);
    fSubWorld = mgr->readKey(S);

    fSoundGroup = mgr->readKey(S);
    fPos.read(S);
    fRot.read(S);
    fProps.read(S);

    delete[] fTMDBuffer;
    fTMDBuffer = NULL;

    if (fBounds == plSimDefs::kSphereBounds) {
        fRadius = S->readFloat();
        fOffset.read(S);
    } else if (fBounds == plSimDefs::kBoxBounds) {
        fDimensions.read(S);
        fOffset.read(S);
    } else if (fBounds == plSimDefs::kHullBounds) {
        PXCookedData::readConvexMesh(S, this);
    } else {    // Proxy or Explicit
        PXCookedData::readTriangleMesh(S, this);
    }
}

void plGenericPhysical::IWriteHKPhysical(hsStream* S, plResManager* mgr) {

    unsigned int memGroup = plHKSimDefs::toGroup(fMemberGroup);
    unsigned int repGroup = plHKSimDefs::setBitshiftGroup(fReportGroup);
    unsigned int colGroup = plHKSimDefs::setBitshiftGroup(fCollideGroup);
    plHKSimDefs::fixGroups(this, &memGroup, &repGroup, &colGroup);


    fPos.write(S);
    S->writeFloat(fRot.W);
    S->writeFloat(fRot.X);
    S->writeFloat(fRot.Y);
    S->writeFloat(fRot.Z);

    S->writeFloat(fMass);
    S->writeFloat(fFriction);
    S->writeFloat(fRestitution);

    if (fBounds == plSimDefs::kCylinderBounds) {
        throw hsBadParamException(__FILE__, __LINE__,
                "Invalid Bounds type");
    }
    S->writeInt(fBounds);

    S->writeInt(memGroup);
    S->writeInt(repGroup);
    S->writeInt(colGroup);

    S->writeBool(fDisableReport);
    S->writeBool(fDisableCollide);

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

    S->writeInt(fMemberGroup);
    S->writeInt(fCollideGroup);
    S->writeInt(fReportGroup);
    fProps.write(S);
    S->writeShort(fLOSDBs);
    mgr->writeKey(S, fObjectKey);
    mgr->writeKey(S, fSceneNode);
}

void plGenericPhysical::IWritePXPhysical(hsStream* S, plResManager* mgr) {
    S->writeFloat(fMass);
    S->writeFloat(fFriction);
    S->writeFloat(fRestitution);
    S->writeByte(fBounds);
    S->writeByte(plPXSimDefs::toGroup(fMemberGroup, fCollideGroup));
    S->writeInt(plPXSimDefs::setReportsOn(fReportGroup));
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
#ifdef HAVE_PX_SDK
        if (!sPhysxWasInit) {
            NxInitCooking();
            sPhysxWasInit = true;
        }
        NxConvexMeshDesc convexDesc;
        convexDesc.numVertices = fVerts.getSize();
        convexDesc.pointStrideBytes = sizeof(hsVector3);
        convexDesc.points = fVerts.getData();
        convexDesc.flags = NX_CF_COMPUTE_CONVEX;

        plPXStream buf(S);
        if (!NxCookConvexMesh(convexDesc, buf))
            throw hsBadParamException(__FILE__, __LINE__, "Incorrect data for PhysX Hull Bake");
#else
        throw hsNotImplementedException(__FILE__, __LINE__, "PhysX HullBounds");
#endif
    } else {    // Proxy or Explicit
#ifdef HAVE_PX_SDK
        if (!sPhysxWasInit) {
            NxInitCooking();
            sPhysxWasInit = true;
        }
        NxTriangleMeshDesc triDesc;
        triDesc.numVertices = fVerts.getSize();
        triDesc.pointStrideBytes = sizeof(hsVector3);
        triDesc.points = fVerts.getData();
        triDesc.numTriangles = fIndices.getSize() / 3;
        triDesc.triangleStrideBytes = sizeof(unsigned int) * 3;
        triDesc.triangles = fIndices.getData();
        triDesc.flags = 0; // 32-bit appears to be the default for index size

        plPXStream buf(S);
        if (!NxCookTriangleMesh(triDesc, buf))
            throw hsBadParamException(__FILE__, __LINE__, "Incorrect data for a PhysX Trimesh Bake");
#else
        throw hsNotImplementedException(__FILE__, __LINE__, "PhysX TriangleMesh");
#endif
    }
}

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
    delete[] fTMDBuffer;
    if (tmdSize == 0 || tmdBuffer == NULL) {
        fTMDSize = 0;
        fTMDBuffer = NULL;
    }
    fTMDSize = tmdSize;
    fTMDBuffer = new unsigned char[fTMDSize];
    memcpy(fTMDBuffer, tmdBuffer, fTMDSize);
}
