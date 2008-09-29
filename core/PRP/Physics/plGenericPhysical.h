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

DllClass plGenericPhysical : public plPhysical {
protected:
    // Shared Properties
    float fMass, fFriction, fRestitution;
    plSimDefs::Bounds fBounds;
    plSimDefs::Group fGroup;
    unsigned int fCategory;
    unsigned short fLOSDBs;
    plKey fObjectKey, fSceneNode, fSubWorld, fSoundGroup;
    hsVector3 fPos;
    hsQuat fRot;
    hsVector3 fDimensions, fOffset;
    float fRadius, fLength;

    hsBitVector fProps;
    hsTArray<hsVector3> fVerts;
    hsTArray<unsigned int> fIndices;

    // Havok Properties
    unsigned int fUnk1, fUnk2;
    bool fHKBool1, fHKBool2;
    
    // ODE Properties
    //unsigned int fUnk1, fUnk2;
    size_t fTMDSize;
    unsigned char* fTMDBuffer;

    // PhysX Properties
    unsigned int fReportsOn;

    void IReadHKPhysical(hsStream* S, plResManager* mgr);
    void IReadODEPhysical(hsStream* S, plResManager* mgr);
    void IReadPXPhysical(hsStream* S, plResManager* mgr);
    void IWriteHKPhysical(hsStream* S, plResManager* mgr);
    void IWriteODEPhysical(hsStream* S, plResManager* mgr);
    void IWritePXPhysical(hsStream* S, plResManager* mgr);

public:
    plGenericPhysical();
    virtual ~plGenericPhysical();

    DECLARE_CREATABLE(plGenericPhysical)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getMass() const;
    float getFriction() const;
    float getRestitution() const;
    plSimDefs::Bounds getBoundsType() const;
    plSimDefs::Group getGroup() const;
    unsigned int getCategory() const;
    unsigned short getLOSDBs() const;
    unsigned int getReportsOn() const;

    plKey getObject() const;
    plKey getSceneNode() const;
    plKey getSubWorld() const;
    plKey getSoundGroup() const;
    hsVector3 getPos() const;
    hsQuat getRot() const;
    hsBitVector& getProps();

    hsVector3 getDimensions() const;
    hsVector3 getOffset() const;
    float getRadius() const;
    float getLength() const;
    size_t getNumVerts() const;
    size_t getNumIndices() const;
    hsVector3 getVert(size_t idx) const;
    unsigned int getIndex(size_t idx) const;
    size_t getTMDSize() const;
    const unsigned char* getTMDBuffer() const;

    void setMass(float mass);
    void setFriction(float friction);
    void setRestitution(float restitution);
    void setBoundsType(plSimDefs::Bounds bounds);
    void setGroup(plSimDefs::Group group);
    void setCategory(unsigned int category);
    void setLOSDBs(unsigned short los);
    void setReportsOn(unsigned int reports);

    void setObject(plKey object);
    void setSceneNode(plKey node);
    void setSubWorld(plKey world);
    void setSoundGroup(plKey group);
    void setPos(const hsVector3& pos);
    void setRot(const hsQuat& rot);

    void setDimensions(const hsVector3& box);
    void setOffset(const hsVector3& offset);
    void setRadius(float radius);
    void setLength(float length);
    void setVerts(size_t numVerts, const hsVector3* verts);
    void setIndices(size_t numIndices, const unsigned int* indices);
    void setTMDBuffer(size_t tmdSize, const unsigned char* tmdBuffer);
};

#endif
