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

#ifndef _PLNETSERVERSESSIONINFO_H
#define _PLNETSERVERSESSIONINFO_H

#include "PRP/plCreatable.h"
#include "Sys/plUuid.h"
#include "plSpawnPointInfo.h"

class PLASMA_DLL plAgeInfoStruct : public plCreatable {
    CREATABLE(plAgeInfoStruct, kAgeInfoStruct, plCreatable)

public:
    enum {
        kHasAgeFilename = 0x1,
        kHasAgeInstanceName = 0x2,
        kHasAgeInstanceGuid = 0x4,
        kHasAgeUserDefinedName = 0x8,
        kHasAgeSequenceNumber = 0x10,
        kHasAgeDescription = 0x20,
        kHasAgeLanguage = 0x40
    };

protected:
    unsigned char fFlags;
    plString fAgeFilename, fAgeInstanceName;
    plUuid fAgeInstanceGuid;
    plString fAgeUserDefinedName, fAgeDescription;
    int fAgeSequenceNumber, fAgeLanguage;

public:
    plAgeInfoStruct();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool isEmpty() { return (fFlags == 0); }
    void clear() { fFlags = 0; }

    plString getAgeFilename() const { return fAgeFilename; }
    plString getAgeInstanceName() const { return fAgeInstanceName; }
    const plUuid& getAgeInstanceGuid() const { return fAgeInstanceGuid; }
    plString getAgeUserDefinedName() const { return fAgeUserDefinedName; }
    plString getAgeDescription() const { return fAgeDescription; }
    int getAgeSequenceNumber() const { return fAgeSequenceNumber; }
    int getAgeLanguage() const { return fAgeLanguage; }

    void setAgeFilename(plString name);
    void setAgeInstanceName(plString name);
    void setAgeInstanceGuid(const plUuid& guid);
    void setAgeUserDefinedName(plString name);
    void setAgeDescription(plString desc);
    void setAgeSequenceNumber(int seq);
    void setAgeLanguage(int lang);

    void clearAgeFilename();
    void clearAgeInstanceName();
    void clearAgeInstanceGuid();
    void clearAgeUserDefinedName();
    void clearAgeDescription();
    void clearAgeSequenceNumber();
    void clearAgeLanguage();

    bool hasAgeFilename() const { return (fFlags & kHasAgeFilename) != 0; }
    bool hasAgeInstanceName() const { return (fFlags & kHasAgeInstanceName) != 0; }
    bool hasAgeInstanceGuid() const { return (fFlags & kHasAgeInstanceGuid) != 0; }
    bool hasAgeUserDefiniedName() const { return (fFlags & kHasAgeUserDefinedName) != 0; }
    bool hasAgeDescription() const { return (fFlags & kHasAgeDescription) != 0; }
    bool hasAgeSequenceNumber() const { return (fFlags & kHasAgeSequenceNumber) != 0; }
    bool hasAgeLanguage() const { return (fFlags & kHasAgeLanguage) != 0; }
};


class PLASMA_DLL plAgeLinkStruct : public plCreatable {
    CREATABLE(plAgeLinkStruct, kAgeLinkStruct, plCreatable)

public:
    enum {
        kHasAgeInfo = 0x1,
        kHasLinkingRules = 0x2,
        kHasSpawnPt_DEAD = 0x4,
        kHasSpawnPt_DEAD2 = 0x8,
        kHasAmCCR = 0x10,
        kHasSpawnPt = 0x20,
        kHasParentAgeFilename = 0x40
    };

    enum LinkingRules {
        /** Link to public age; Don't remember this link in KI/Vault */
        kBasicLink,

        /** Link and create a book in the AgesIOwn folder */
        kOriginalBook,

        /** Link to a sub age of current age */
        kSubAgeBook,

        /** Link using info from my AgesIOwn folder */
        kOwnedBook,

        /** Link using info from my AgesICanVisit folder */
        kVisitBook,

        /** Link to a child age of current age */
        kChildAgeBook
    };

    /** Textual name lookup for linking rule types */
    static const char* kLinkingRuleNames[];

protected:
    unsigned short fFlags;
    signed char fLinkingRules;
    unsigned char fAmCCR;
    plAgeInfoStruct fAgeInfo;
    plSpawnPointInfo fSpawnPoint;
    plString fParentAgeFilename;

public:
    plAgeLinkStruct();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool isEmpty() { return (fFlags == 0); }
    void clear() { fFlags = 0; }

    const plAgeInfoStruct& getAgeInfo() const { return fAgeInfo; }
    plAgeInfoStruct& getAgeInfo() { return fAgeInfo; }

    const plSpawnPointInfo& getSpawnPoint() const { return fSpawnPoint; }
    plSpawnPointInfo& getSpawnPoint() { return fSpawnPoint; }

    signed char getLinkingRules() const { return fLinkingRules; }
    unsigned char getAmCCR() const { return fAmCCR; }
    plString getParentAgeFilename() const { return fParentAgeFilename; }

    void setLinkingRules(signed char rules);
    void setAmCCR(unsigned char ccr);
    void setParentAgeFilename(plString filename);

    void setHasAgeInfo(bool has);
    void setHasSpawnPoint(bool has);
    void clearLinkingRules();
    void clearAmCCR();
    void clearParentAgeFilename();

    bool hasAgeInfo() const { return (fFlags & kHasAgeInfo) != 0; }
    bool hasLinkingRules() const { return (fFlags & kHasLinkingRules) != 0; }
    bool hasAmCCR() const { return (fFlags & kHasAmCCR) != 0; }
    bool hasSpawnPoint() const { return (fFlags & kHasSpawnPt) != 0; }
    bool hasParentAgeFilename() const { return (fFlags & kHasParentAgeFilename) != 0; }
};


class PLASMA_DLL plAgeLinkEffects {
protected:
    plString fLinkInAnimName;
    bool fBool1, fBool2, fBool3, fBool4;

public:
    plAgeLinkEffects();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    plString getLinkInAnimName() const { return fLinkInAnimName; }
    bool getBool1() const { return fBool1; }
    bool getBool2() const { return fBool2; }
    bool getBool3() const { return fBool3; }
    bool getBool4() const { return fBool4; }

    void setLinkInAnimName(plString name) { fLinkInAnimName = name; }
    void setBool1(bool value) { fBool1 = value; }
    void setBool2(bool value) { fBool2 = value; }
    void setBool3(bool value) { fBool3 = value; }
    void setBool4(bool value) { fBool4 = value; }
};

#endif
