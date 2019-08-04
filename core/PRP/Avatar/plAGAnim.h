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

#ifndef _PLAGANIM_H
#define _PLAGANIM_H

#include "PRP/Object/plSynchedObject.h"
#include "plAGApplicator.h"

class PLASMA_DLL plAGAnim : public plSynchedObject
{
    CREATABLE(plAGAnim, kAGAnim, plSynchedObject)

public:
    enum BodyUsage
    {
        kBodyUnknown, kBodyUpper, kBodyFull, kBodyLower, kBodyMax
    };

protected:
    std::vector<plAGApplicator*> fApps;
    float fBlend, fStart, fEnd;
    ST::string fName;
    unsigned char fEoaFlag;

public:
    plAGAnim() : fBlend(), fStart(), fEnd(), fEoaFlag() { }
    ~plAGAnim();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plAGApplicator*>& getApplicators() const { return fApps; }
    std::vector<plAGApplicator*>& getApplicators() { return fApps; }
    void addApplicator(plAGApplicator* app) { fApps.push_back(app); }
    void delApplicator(size_t idx);
    void clearApplicators();

    float getBlend() const { return fBlend; }
    float getStart() const { return fStart; }
    float getEnd() const { return fEnd; }
    ST::string getName() const { return fName; }

    void setBlend(float blend) { fBlend = blend; }
    void setStart(float start) { fStart = start; }
    void setEnd(float end) { fEnd = end; }
    void setName(const ST::string& name) { fName = name; }
};

class PLASMA_DLL plAgeGlobalAnim : public plAGAnim
{
    CREATABLE(plAgeGlobalAnim, kAgeGlobalAnim, plAGAnim)

protected:
    ST::string fGlobalVarName;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    ST::string getGlobalVarName() const { return fGlobalVarName; }
    void setGlobalVarName(const ST::string& name) { fGlobalVarName = name; }
};

#endif
