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

#include "plLocation.h"
#include <string_theory/format>

bool plLocation::operator==(const plLocation& other) const
{
    return (fState == other.fState && fPageNum == other.fPageNum
            && fSeqPrefix == other.fSeqPrefix);
}

bool plLocation::operator!=(const plLocation& other) const
{
    return (fState != other.fState || fPageNum != other.fPageNum
            || fSeqPrefix != other.fSeqPrefix || fFlags != other.fFlags);
}

bool plLocation::operator<(const plLocation& other) const
{
    if (fSeqPrefix == other.fSeqPrefix)
        return fPageNum < other.fPageNum;
    return fSeqPrefix < other.fSeqPrefix;
}

void plLocation::parse(unsigned int id)
{
    if (id == 0xFFFFFFFF) {
        fState = kStateInvalid;
        fSeqPrefix = 0;
        fPageNum = 0;
        return;
    } else if (id == 0) {
        fState = kStateVirtual;
        fSeqPrefix = 0;
        fPageNum = 0;
        return;
    }
    if (fVer.isUniversal())
        throw hsBadParamException(__FILE__, __LINE__, "Universal PRPs don't use encoded locations");

    fState = kStateNormal;
    if ((id & 0x80000000) != 0) {
        id -= (fVer.isLive() ? 0xFF000001 : 0xFFFF0001);
        fSeqPrefix = id >> (fVer.isLive() ? 16 : 8);
        fPageNum = id - (fSeqPrefix << (fVer.isLive() ? 16 : 8));
        fSeqPrefix = -fSeqPrefix;
    } else {
        id -= 33;
        fSeqPrefix = id >> (fVer.isLive() ? 16 : 8);
        fPageNum = id - (fSeqPrefix << (fVer.isLive() ? 16 : 8));
    }
    if (fVer.isLive())
        fPageNum = (signed short)(unsigned short)fPageNum;
    else
        fPageNum = (signed char)(unsigned char)fPageNum;
}

unsigned int plLocation::unparse() const
{
    if (fState == kStateInvalid)
        return 0xFFFFFFFF;
    else if (fState == kStateVirtual)
        return 0;
    if (fVer.isUniversal())
        throw hsBadParamException(__FILE__, __LINE__, "Universal PRPs don't use encoded locations");

    int pgNum;
    if (fVer.isLive())
        pgNum = (unsigned short)(signed short)fPageNum;
    else
        pgNum = (unsigned char)(signed char)fPageNum;
    if (fSeqPrefix < 0) {
        return pgNum - (fSeqPrefix << (fVer.isLive() ? 16 : 8))
                     + (fVer.isLive() ? 0xFF000001 : 0xFFFF0001);
    } else {
        return pgNum + (fSeqPrefix << (fVer.isLive() ? 16 : 8)) + 33;
    }
}

void plLocation::read(hsStream* S)
{
    setVer(S->getVer());
    if (S->getVer().isUniversal()) {
        fState = S->readByte();
        fSeqPrefix = S->readInt();
        fPageNum = S->readInt();
        fFlags = S->readShort();
    } else {
        parse(S->readInt());
        if (S->getVer() < MAKE_VERSION(2, 0, 62, 0) && S->getVer().isValid())
            fFlags = 0;
        else if (S->getVer().isNewPlasma())
            fFlags = S->readByte();
        else
            fFlags = S->readShort();
    }
}

void plLocation::write(hsStream* S)
{
    if (S->getVer().isValid())
        setVer(S->getVer());

    if (!getVer().isSafeVer())
        setVer(PlasmaVer::GetSafestVersion(getVer()));

    if (S->getVer().isUniversal()) {
        S->writeByte(fState);
        S->writeInt(fSeqPrefix);
        S->writeInt(fPageNum);
        S->writeShort(fFlags);
    } else {
        S->writeInt(unparse());
        if (S->getVer().isNewPlasma())
            S->writeByte(fFlags);
        else
            S->writeShort(fFlags);
    }
}

void plLocation::prcWrite(pfPrcHelper* prc)
{
    if (fState == kStateInvalid) {
        prc->writeParam("Location", "INVALID");
    } else if (fState == kStateVirtual) {
        prc->writeParam("Location", "VIRTUAL");
        prc->writeParamHex("LocFlag", fFlags);
    } else {
        ST::string buf = ST::format("{};{}", fSeqPrefix, fPageNum);
        prc->writeParam("Location", buf);
        prc->writeParamHex("LocFlag", fFlags);
    }
}

void plLocation::prcParse(const pfPrcTag* tag)
{
    ST::string buf = tag->getParam("Location", "INVALID");
    if (buf == "INVALID") {
        fState = kStateInvalid;
        fSeqPrefix = 0;
        fPageNum = 0;
    } else if (buf == "VIRTUAL") {
        fState = kStateVirtual;
        fSeqPrefix = 0;
        fPageNum = 0;
    } else {
        fState = kStateNormal;
        std::vector<ST::string> parts = buf.split(';');
        fSeqPrefix = parts.at(0).to_int();
        fPageNum = parts.at(1).to_int();
    }
    fFlags = tag->getParam("LocFlag", "0").to_uint();
}

void plLocation::invalidate()
{
    fState = kStateInvalid;
    fPageNum = 0;
    fSeqPrefix = 0;
    fFlags = 0;
}

void plLocation::setVirtual()
{
    fState = kStateVirtual;
    fPageNum = 0;
    fSeqPrefix = 0;
}

void plLocation::setPageNum(int pn)
{
    fPageNum = pn;
    fState = kStateNormal;
}

void plLocation::setSeqPrefix(int sp)
{
    fSeqPrefix = sp;
    fState = kStateNormal;
}

void plLocation::set(int pid, unsigned short flags, PlasmaVer pv)
{
    if (pv.isUniversal())
        throw hsBadParamException(__FILE__, __LINE__, "Universal PRPs don't use encoded locations");
    setVer(pv);
    parse(pid);
    fFlags = flags;
}

ST::string plLocation::toString() const
{
    if (fState == kStateInvalid)
        return "<INVALID>";
    else if (fState == kStateVirtual)
        return "<VIRTUAL>";
    return ST::format("<{}|{}>", fSeqPrefix, fPageNum);
}
