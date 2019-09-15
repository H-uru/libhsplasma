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

#ifndef _PROEVENTDATA_H
#define _PROEVENTDATA_H

#include "PlasmaDefs.h"
#include "Math/hsGeometry3.h"
#include "PRP/KeyedObject/plKey.h"
#include "ResManager/plResManager.h"

#define EVTDATA(classname, evtType) \
public:\
    static classname* Convert(proEventData* evt) \
    { \
        if (evt && evt->EventType() == evtType) \
            return (classname*)evt; \
        return nullptr; \
    }


class PLASMA_DLL proEventData
{
public:
    enum eventType
    {
        kCollision = 1, kPicked, kControlKey, kVariable, kFacing, kContained,
        kActivate, kCallback, kResponderState, kMultiStage, kSpawned,
        kClickDrag, kCoop, kOfferLinkBook, kBook, kClimbingBlockerHit,
        kNone
    };

    enum dataType { kNumber, kKey, kNotta };

    enum multiStageEventType
    {
        kEnterStage = 1, kBeginningOfLoop, kAdvanceNextStage,
        kRegressPrevStage, kNothing
    };

private:
    static const char* const fEventNames[];

protected:
    int fEventType;

public:
    proEventData() : fEventType() { }
    virtual ~proEventData() { }

    int EventType() const { return fEventType; }

    static proEventData* Read(hsStream* S, plResManager* mgr);
    void write(hsStream* S, plResManager* mgr);
    void prcWrite(pfPrcHelper* prc);
    static proEventData* PrcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    static proEventData* ICreateEventDataType(int type);
    static proEventData* ICreateEventDataType(const char* typeName);
    virtual void IRead(hsStream* S, plResManager* mgr)=0;
    virtual void IWrite(hsStream* S, plResManager* mgr)=0;
    virtual void IPrcWrite(pfPrcHelper* prc)=0;
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL proCollisionEventData : public proEventData
{
    EVTDATA(proCollisionEventData, kCollision)

protected:
    bool fEnter;
    plKey fHitter;
    plKey fHittee;

public:
    proCollisionEventData() : fEnter()
    {
        fEventType = kCollision;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    bool isEnter() const { return fEnter; }
    plKey getHitter() const { return fHitter; }
    plKey getHittee() const { return fHittee; }

    void setEnter(bool enter) { fEnter = enter; }
    void setHitter(plKey hitter) { fHitter = std::move(hitter); }
    void setHittee(plKey hittee) { fHittee = std::move(hittee); }
};


class PLASMA_DLL proPickedEventData : public proEventData
{
    EVTDATA(proPickedEventData, kPicked)

protected:
    plKey fPicker;
    plKey fPicked;
    bool fEnabled;
    hsVector3 fHitPoint;

public:
    proPickedEventData() : fEnabled()
    {
        fEventType = kPicked;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getPicker() const { return fPicker; }
    plKey getPicked() const { return fPicked; }
    bool isEnabled() const { return fEnabled; }
    hsVector3 getHitPoint() const { return fHitPoint; }

    void setPicker(plKey picker) { fPicker = std::move(picker); }
    void setPicked(plKey picked) { fPicked = std::move(picked); }
    void setEnabled(bool enabled) { fEnabled = enabled; }
    void setHitPoint(const hsVector3& point) { fHitPoint = point; }
};


class PLASMA_DLL proControlKeyEventData : public proEventData
{
    EVTDATA(proControlKeyEventData, kControlKey)

protected:
    int fControlKey;
    bool fDown;

public:
    proControlKeyEventData() : fControlKey(), fDown()
    {
        fEventType = kControlKey;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    int getControlKey() const { return fControlKey; }
    bool isDown() const { return fDown; }

    void setControlKey(int key) { fControlKey = key; }
    void setDown(bool down) { fDown = down; }
};


class PLASMA_DLL proVariableEventData : public proEventData
{
    EVTDATA(proVariableEventData, kVariable)

protected:
    ST::string fName;
    int fDataType;
    float fNumber;
    plKey fKey;

public:
    proVariableEventData() : fNumber()
    {
        fEventType = kVariable;
        fDataType = kNotta;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    ST::string getName() const { return fName; }
    int getDataType() const { return fDataType; }
    float getNumber() const { return fNumber; }
    plKey getKey() const { return fKey; }

    void setName(const ST::string& name) { fName = name; }
    void setDataType(int type) { fDataType = type; }
    void setNumber(float number) { fNumber = number; }
    void setKey(plKey key) { fKey = std::move(key); }
};


class PLASMA_DLL proFacingEventData : public proEventData
{
    EVTDATA(proFacingEventData, kFacing)

protected:
    plKey fFacer;
    plKey fFacee;
    float fDot;
    bool fEnabled;

public:
    proFacingEventData() : fDot(), fEnabled()
    {
        fEventType = kFacing;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getFacer() const { return fFacer; }
    plKey getFacee() const { return fFacee; }
    float getDot() const { return fDot; }
    bool isEnabled() const { return fEnabled; }

    void setFacer(plKey facer) { fFacer = std::move(facer); }
    void setFacee(plKey facee) { fFacee = std::move(facee); }
    void setDot(float dot) { fDot = dot; }
    void setEnabled(bool enabled) { fEnabled = enabled; }
};


class PLASMA_DLL proContainedEventData : public proEventData
{
    EVTDATA(proContainedEventData, kContained)

protected:
    plKey fContained;
    plKey fContainer;
    bool fEntering;

public:
    proContainedEventData() : fEntering()
    {
        fEventType = kContained;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getContained() const { return fContained; }
    plKey getContainer() const { return fContainer; }
    bool isEntering() const { return fEntering; }

    void setContained(plKey contained) { fContained = std::move(contained); }
    void setContainer(plKey container) { fContainer = std::move(container); }
    void setEntering(bool entering) { fEntering = entering; }
};


class PLASMA_DLL proActivateEventData : public proEventData
{
    EVTDATA(proActivateEventData, kActivate)

protected:
    bool fActive, fActivate;

public:
    proActivateEventData() : fActive(), fActivate()
    {
        fEventType = kActivate;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    bool isActive() const { return fActive; }
    bool isActivate() const { return fActivate; }

    void setActive(bool active) { fActive = active; }
    void setActivate(bool activate) { fActivate = activate; }
};


class PLASMA_DLL proCallbackEventData : public proEventData
{
    EVTDATA(proCallbackEventData, kCallback)

protected:
    int fCallbackEventType;

public:
    proCallbackEventData() : fCallbackEventType()
    {
        fEventType = kCallback;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    int getCallbackEventType() const { return fCallbackEventType; }
    void setCallbackEventType(int type) { fCallbackEventType = type; }
};


class PLASMA_DLL proResponderStateEventData : public proEventData
{
    EVTDATA(proResponderStateEventData, kResponderState)

protected:
    int fState;

public:
    proResponderStateEventData() : fState()
    {
        fEventType = kResponderState;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    int getState() const { return fState; }
    void setState(int state) { fState = state; }
};


class PLASMA_DLL proMultiStageEventData : public proEventData
{
    EVTDATA(proMultiStageEventData, kMultiStage)

protected:
    int fStage, fEvent;
    plKey fAvatar;

public:
    proMultiStageEventData() : fStage(), fEvent(kNothing)
    {
        fEventType = kMultiStage;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    int getStage() const { return fStage; }
    int getEvent() const { return fEvent; }
    plKey getAvatar() const { return fAvatar; }

    void setStage(int stage) { fStage = stage; }
    void setEvent(int event) { fEvent = event; }
    void setAvatar(plKey avatar) { fAvatar = std::move(avatar); }
};


class PLASMA_DLL proSpawnedEventData : public proEventData
{
    EVTDATA(proSpawnedEventData, kSpawned)

protected:
    plKey fSpawner;
    plKey fSpawnee;

public:
    proSpawnedEventData() { fEventType = kSpawned; }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getSpawner() const { return fSpawner; }
    plKey getSpawnee() const { return fSpawnee; }

    void setSpawner(plKey spawner) { fSpawner = std::move(spawner); }
    void setSpawnee(plKey spawnee) { fSpawnee = std::move(spawnee); }
};


class PLASMA_DLL proClickDragEventData : public proEventData
{
    EVTDATA(proClickDragEventData, kClickDrag)

public:
    proClickDragEventData() { fEventType = kClickDrag; }

protected:
    void IRead(hsStream*, plResManager*) HS_OVERRIDE { }
    void IWrite(hsStream*, plResManager*) HS_OVERRIDE { }
    void IPrcWrite(pfPrcHelper*) HS_OVERRIDE { }
};


class PLASMA_DLL proCoopEventData : public proEventData
{
    EVTDATA(proCoopEventData, kCoop)

protected:
    unsigned int fID;
    unsigned short fSerial;

public:
    proCoopEventData() : fID(), fSerial()
    {
        fEventType = kCoop;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned int getID() const { return fID; }
    unsigned short getSerial() const { return fSerial; }

    void setID(unsigned int id) { fID = id; }
    void setSerial(unsigned short serial) { fSerial = serial; }
};


class PLASMA_DLL proOfferLinkBookEventData : public proEventData
{
    EVTDATA(proOfferLinkBookEventData, kOfferLinkBook)

protected:
    plKey fOfferer;
    int fTargetAge, fOfferee;

public:
    proOfferLinkBookEventData() : fTargetAge(), fOfferee()
    {
        fEventType = kOfferLinkBook;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getOfferer() const { return fOfferer; }
    int getTargetAge() const { return fTargetAge; }
    int getOfferee() const { return fOfferee; }

    void setOfferer(plKey offerer) { fOfferer = std::move(offerer); }
    void setTargetAge(int age) { fTargetAge = age; }
    void setOfferee(int offeree) { fOfferee = offeree; }
};


class PLASMA_DLL proBookEventData : public proEventData
{
    EVTDATA(proBookEventData, kBook)

protected:
    unsigned int fEvent, fLinkID;

public:
    proBookEventData() : fEvent(), fLinkID()
    {
        fEventType = kBook;
    }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned int getEvent() const { return fEvent; }
    unsigned int getLinkID() const { return fLinkID; }

    void setEvent(unsigned int event) { fEvent = event; }
    void setLinkID(unsigned int id) { fLinkID = id; }
};


class PLASMA_DLL proClimbingBlockerHitEventData : public proEventData
{
    EVTDATA(proClimbingBlockerHitEventData, kClimbingBlockerHit)

protected:
    plKey fBlockerKey;

public:
    proClimbingBlockerHitEventData() { fEventType = kClimbingBlockerHit; }

protected:
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getBlocker() const { return fBlockerKey; }
    void setBlocker(plKey blocker) { fBlockerKey = std::move(blocker); }
};

#endif
