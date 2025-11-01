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
#include "Debug/plDebug.h"
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
    if (fVer.isLive()) {
        if (id >= 0xFF01'0000) {
            id -= 0xFF00'0001;
            fSeqPrefix = -(int)(id >> 16);
        } else {
            id -= 33;
            fSeqPrefix = id >> 16;
        }
        fPageNum = (int16_t)(id & 0xFFFF);
    } else {
        if (id >= 0xFFFF'0100) {
            id -= 0xFFFF'0001;
            fSeqPrefix = -(int)(id >> 8);
        } else {
            id -= 33;
            fSeqPrefix = id >> 8;
        }
        fPageNum = (int8_t)(id & 0xFF);
    }

    // Plasma does not actually use negative page numbers.  However, for
    // correctly mapping and converting the "reserved" pages at the end of the
    // max-uint8/max-uint16 range, we pretend they are signed and negative.
    // In order to leave more room for non-reserved pages, we only apply this
    // special logic up to -32
    if (fPageNum < -32) {
        if (fVer.isLive())
            fPageNum += 0x10000;
        else
            fPageNum += 0x100;
    }
}

unsigned int plLocation::unparse() const
{
    if (fState == kStateInvalid)
        return 0xFFFFFFFF;
    else if (fState == kStateVirtual)
        return 0;
    if (fVer.isUniversal())
        throw hsBadParamException(__FILE__, __LINE__, "Universal PRPs don't use encoded locations");

    if (fVer.isLive()) {
        if (fSeqPrefix < -254 || fSeqPrefix > 0xFEFF)
            plDebug::Warning("Sequence prefix {} cannot be uniquely encoded.", fSeqPrefix);
        if (fPageNum < -32 || fPageNum > 0xFFDF)
            plDebug::Warning("Page number {} cannot be uniquely encoded.", fPageNum);

        if (fSeqPrefix < 0)
            return (-fSeqPrefix << 16) + (fPageNum & 0xFFFF) + 0xFF00'0001;
        else
            return (fSeqPrefix << 16) + (fPageNum & 0xFFFF) + 33;
    } else {
        if (fSeqPrefix < -254 || fSeqPrefix > 0xFF'FEFF)
            plDebug::Warning("Sequence prefix {} cannot be uniquely encoded.", fSeqPrefix);
        if (fPageNum < -32 || fPageNum > 0xDF)
            plDebug::Warning("Page number {} cannot be uniquely encoded.", fPageNum);

        if (fSeqPrefix < 0)
            return (-fSeqPrefix << 8) + (fPageNum & 0xFF) + 0xFFFF'0001;
        else
            return (fSeqPrefix << 8) + (fPageNum & 0xFF) + 33;
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
