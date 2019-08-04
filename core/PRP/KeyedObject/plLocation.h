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

#ifndef _PLLOCATION_H
#define _PLLOCATION_H

#include "PlasmaDefs.h"
#include "Util/PlasmaVersions.h"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

class PLASMA_DLL plLocation
{
public:
    enum LocFlags
    {
        kLocalOnly = 0x1,
        kVolatile = 0x2,
        kReserved = 0x4,
        kBuiltIn = 0x8,
        kItinerant = 0x10
    };

    enum LocState
    {
        kStateInvalid, kStateNormal, kStateVirtual
    };

protected:
    PlasmaVer fVer;
    int fState;
    int fSeqPrefix, fPageNum;
    unsigned short fFlags;

public:
    plLocation(int pv = PlasmaVer::pvUnknown)
        : fVer(pv), fState(kStateInvalid), fSeqPrefix(), fPageNum(), fFlags() { }

    PlasmaVer getVer() const { return fVer; }
    void setVer(PlasmaVer pv) { fVer = pv; }

    bool operator==(const plLocation& other) const;
    bool operator!=(const plLocation& other) const;
    bool operator<(const plLocation& other) const;

    void parse(unsigned int id);
    unsigned int unparse() const;

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    void invalidate();
    bool isValid() const { return (fState != kStateInvalid); }

    bool isReserved() const { return (fFlags & kReserved) != 0; }
    bool isItinerant() const { return (fFlags & kItinerant) != 0; }
    bool isVirtual() const { return (fState == kStateVirtual); }
    bool isGlobal() const { return (fSeqPrefix < 0); }
    void setVirtual();

    int getPageNum() const { return fPageNum; }
    int getSeqPrefix() const { return fSeqPrefix; }
    unsigned short getFlags() const { return fFlags; }
    void setPageNum(int pn);
    void setSeqPrefix(int sp);
    void setFlags(unsigned short flags) { fFlags = flags; }
    void set(int pid, unsigned short flags, PlasmaVer pv);

    ST::string toString() const;
};

#endif
