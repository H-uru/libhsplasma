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

#ifndef _PLGENERICPHYSICAL_H
#define _PLGENERICPHYSICAL_H

#include "plPhysical.h"
#include "Math/hsGeometry3.h"
#include "Math/hsQuat.h"
#include "Util/hsBitVector.h"

/**************
 * plGenericPhysical attempts to be a generic interface for plHKPhysical,
 * plODEPhysical and plPXPhysical.  When setting properties, try to set as
 * many as possible, as the three engines may have different ways of storing
 * the same physical data.  Obviously, more work still needs to be done here,
 * but hopefully this generic interface will cover most cases and eventually
 * provide fully working physical objects for all 3 engines.
 **************/

class PLASMA_DLL plGenericPhysical : public plPhysical
{
    CREATABLE(plGenericPhysical, kGenericPhysical, plPhysical)

public:
    enum PhysType
    {
        kPhysNone, kPhysHavok, kPhysODE, kPhysX, kNumPhysTypes
    };

protected:
    // Generic properties
    PhysType fInternalType;
    unsigned char* fInternalBuffer;
    size_t fInternalSize;

    // Shared Properties
    float fMass, fFriction, fRestitution;
    plSimDefs::Bounds fBounds;
    unsigned int fMemberGroup;
    unsigned int fCollideGroup;
    unsigned int fReportGroup;
    bool fDisableReport, fDisableCollide;
    unsigned short fLOSDBs;
    plKey fObjectKey, fSceneNode, fSubWorld, fSoundGroup;
    hsVector3 fPos;
    hsQuat fRot;
    hsVector3 fDimensions, fOffset;
    float fRadius, fLength;

    hsBitVector fProps;
    std::vector<hsVector3> fVerts;
    std::vector<unsigned int> fIndices;

    // ODE Properties
    size_t fTMDSize;
    unsigned char* fTMDBuffer;

    void IReadHKPhysical(hsStream* S, plResManager* mgr);
    void IReadODEPhysical(hsStream* S, plResManager* mgr);
    void IReadPXPhysical(hsStream* S, plResManager* mgr);
    void IWriteHKPhysical(hsStream* S, plResManager* mgr);
    void IWriteODEPhysical(hsStream* S, plResManager* mgr);
    void IWritePXPhysical(hsStream* S, plResManager* mgr);

#ifdef HAVE_PX_SDK
    static bool sPhysxWasInit;
#endif

public:
    plGenericPhysical();
    ~plGenericPhysical();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getMass() const { return fMass; }
    float getFriction() const { return fFriction; }
    float getRestitution() const { return fRestitution; }
    plSimDefs::Bounds getBoundsType() const { return fBounds; }
    unsigned int getMemberGroup() const { return fMemberGroup; }
    unsigned int getReportGroup() const { return fReportGroup; }
    unsigned int getCollideGroup() const { return fCollideGroup; }
    bool isReportEnabled() const { return !fDisableReport; }
    bool isCollideEnabled() const { return !fDisableCollide; }
    unsigned short getLOSDBs() const { return fLOSDBs; }

    plKey getObject() const { return fObjectKey; }
    plKey getSceneNode() const { return fSceneNode; }
    plKey getSubWorld() const { return fSubWorld; }
    plKey getSoundGroup() const { return fSoundGroup; }
    hsVector3 getPos() const { return fPos; }
    hsQuat getRot() const { return fRot; }

    bool getProperty(size_t prop) const { return fProps.get(prop); }
    void setProperty(size_t prop, bool value) { fProps.set(prop, value); }

    hsVector3 getDimensions() const { return fDimensions; }
    hsVector3 getOffset() const { return fOffset; }
    float getRadius() const { return fRadius; }
    float getLength() const { return fLength; }

    const std::vector<hsVector3>& getVerts() const { return fVerts; }
    std::vector<hsVector3>& getVerts() { return fVerts; }
    const std::vector<unsigned int>& getIndices() const { return fIndices; }
    std::vector<unsigned int>& getIndices() { return fIndices; }
    size_t getTMDSize() const { return fTMDSize; }
    const unsigned char* getTMDBuffer() const { return fTMDBuffer; }

    void setMass(float mass) { fMass = mass; }
    void setFriction(float friction) { fFriction = friction; }
    void setRestitution(float restitution) { fRestitution = restitution; }
    void setBoundsType(plSimDefs::Bounds bounds) { fBounds = bounds; }
    void setMemberGroup(unsigned int group) { fMemberGroup = group; }
    void setReportGroup(unsigned int report) { fReportGroup = report; }
    void setCollideGroup(unsigned int collide) { fCollideGroup = collide; }
    void setReportEnabled(bool enable) { fDisableReport = !enable; }
    void setCollideEnabled(bool enable) { fDisableCollide = !enable; }
    void setLOSDBs(unsigned short los) { fLOSDBs = los; }

    void setObject(plKey object) { fObjectKey = std::move(object); }
    void setSceneNode(plKey node) { fSceneNode = std::move(node); }
    void setSubWorld(plKey world) { fSubWorld = std::move(world); }
    void setSoundGroup(plKey group) { fSoundGroup = std::move(group); }
    void setPos(const hsVector3& pos) { fPos = pos; }
    void setRot(const hsQuat& rot) { fRot = rot; }

    void setDimensions(const hsVector3& box) { fDimensions = box; }
    void setOffset(const hsVector3& offset) { fOffset = offset; }
    void setRadius(float radius) { fRadius = radius; }
    void setLength(float length) { fLength = length; }
    void setVerts(size_t numVerts, const hsVector3* verts);
    void setIndices(size_t numIndices, const unsigned int* indices);
    void setTMDBuffer(size_t tmdSize, const unsigned char* tmdBuffer);

    // Direct baked data buffer access (Currently only for PhysX with baked data)
    PhysType getBufferType() const;
    size_t getBufferSize() const;
    const unsigned char* getBufferData() const;
    void setBuffer(PhysType type, size_t size, const unsigned char* data);

    /** Calculates SphereBounds from a given point cloud */
    void calcSphereBounds(size_t numPoints, const hsVector3* points);

    /** Calculates BoxBounds from a given point cloud */
    void calcBoxBounds(size_t numPoints, const hsVector3* points);
};

#endif
