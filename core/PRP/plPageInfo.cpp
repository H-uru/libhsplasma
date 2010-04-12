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

#include <cstring>
#include "plPageInfo.h"
#include "ResManager/pdUnifiedTypeMap.h"
#include "Debug/plDebug.h"

plPageInfo::plPageInfo() {
    IInit();
}

plPageInfo::plPageInfo(const plString& age, const plString& page) {
    IInit();
    setAge(age);
    setPage(page);
}

void plPageInfo::IInit() {
    fLocation.invalidate();
    fReleaseVersion = 0;
    fChecksum = 0;
    fIdxChecksum = 0;
    fFlags = 0;
    fIdxStart = 0;
    fDataStart = 0;
    fNumObjects = 0;
}

void plPageInfo::read(hsStream* S) {
    short prpVer = S->readShort();
    if (prpVer == -1) {
        S->setVer(pvUniversal);
        fLocation.read(S);
        fAge = S->readSafeStr();
        fPage = S->readSafeStr();
        fFlags = S->readInt();
    } else if (prpVer == 6) {
        unsigned short numTypes = S->readShort();
        if (numTypes == 0) {
            S->setVer(pvLive);
        } else {
            S->setVer(pvEoa);
            for (unsigned short i=0; i<numTypes; i++) {
                short type = S->readShort();
                short ver = S->readShort();
                if (pdUnifiedTypeMap::ClassVersion(type, pvEoa) != ver) {
                    plDebug::Warning("Warning: Class %s expected version %d, got %d",
                                     pdUnifiedTypeMap::ClassName(type, pvEoa),
                                     pdUnifiedTypeMap::ClassVersion(type, pvEoa), ver);
                }
            }
        }
        fLocation.read(S);
        fAge = S->readSafeStr();
        fPage = S->readSafeStr();
        if (S->getVer() == pvLive)
            S->readShort();  // majorVer
    } else if (prpVer == 9) {
        S->setVer(pvHex);
        unsigned short numTypes = S->readShort();
        for (unsigned short i=0; i<numTypes; i++) {
            short type = S->readShort();
            short ver = S->readShort();
            if (pdUnifiedTypeMap::ClassVersion(type, pvHex) != ver) {
                plDebug::Warning("Warning: Class %s expected version %d, got %d",
                                 pdUnifiedTypeMap::ClassName(type, pvHex),
                                 pdUnifiedTypeMap::ClassVersion(type, pvHex), ver);
            }
        }
        fLocation.read(S);
        fAge = S->readSafeStr();
        fPage = S->readSafeStr();
    } else if (prpVer == 5) {
        S->readShort(); // prpVer is DWORD on <= 5
        int pid = S->readInt();
        int pflags = S->readShort();
        S->setVer(pvPrime);
        fAge = S->readSafeStr();
        S->readSafeStr(); // "District"
        fPage = S->readSafeStr();
        short majorVer = S->readShort();
        short minorVer = S->readShort();
        if (majorVer > 63) // Old Live version (e.g. 69.x)
            throw hsBadVersionException(__FILE__, __LINE__);
        else if (minorVer >= 12)
            S->setVer(pvPots);
        fLocation.set(pid, pflags, S->getVer());
        fReleaseVersion = S->readInt();
        fFlags = S->readInt();
    } else {
        throw hsBadVersionException(__FILE__, __LINE__);
    }
    fChecksum = S->readInt();
    fDataStart = S->readInt();
    fIdxStart = S->readInt();

    plDebug::Debug("* Loading: %s (%s)\n"
                   "  Location: <%d|%d>\n"
                   "  Version: %s",
                   fPage.cstr(), fAge.cstr(),
                   fLocation.getSeqPrefix(), fLocation.getPageNum(),
                   GetVersionName(S->getVer()));
}

void plPageInfo::write(hsStream* S) {
    if (S->getVer() == pvUniversal) {
        S->writeShort(-1);
        fLocation.write(S);
        S->writeSafeStr(fAge);
        S->writeSafeStr(fPage);
        S->writeInt(fFlags);
    } else if (S->getVer() == pvEoa) {
        S->writeShort(6);
        S->writeShort(fClassList.size());
        for (size_t i=0; i<fClassList.size(); i++) {
            S->writeShort(pdUnifiedTypeMap::MappedToPlasma(fClassList[i], pvEoa));
            S->writeShort(pdUnifiedTypeMap::ClassVersion(fClassList[i], pvEoa));
        }
        fLocation.write(S);
        S->writeSafeStr(getAge());
        S->writeSafeStr(getPage());
    } else if (S->getVer() == pvHex) {
        S->writeShort(9);
        S->writeShort(fClassList.size());
        for (size_t i=0; i<fClassList.size(); i++) {
            S->writeShort(pdUnifiedTypeMap::MappedToPlasma(fClassList[i], pvHex));
            S->writeShort(pdUnifiedTypeMap::ClassVersion(fClassList[i], pvHex));
        }
        fLocation.write(S);
        S->writeSafeStr(getAge());
        S->writeSafeStr(getPage());
    } else if (S->getVer() == pvLive) {
        S->writeInt(6);
        fLocation.write(S);
        S->writeSafeStr(getAge());
        S->writeSafeStr(getPage());
        S->writeShort(70);
    } else {
        S->writeInt(5);
        fLocation.write(S);
        S->writeSafeStr(getAge());
        S->writeSafeStr(getChapter());
        S->writeSafeStr(getPage());
        short majorVer = 63;
        short minorVer = 11;
        if (S->getVer() == pvPots)
            minorVer = 12;
        if (S->getVer() == pvLive) {
            majorVer = 70;
            minorVer = 0;
        }
        S->writeShort(majorVer);
        S->writeShort(minorVer);
        S->writeInt(fReleaseVersion);
        S->writeInt(fFlags);
    }
    S->writeInt(fChecksum);
    S->writeInt(fDataStart);
    S->writeInt(fIdxStart);
}

void plPageInfo::writeSums(hsStream* S) {
    unsigned int pos = S->pos();
    S->seek(fDataStart-12);
    S->writeInt(fChecksum);
    S->writeInt(fDataStart);
    S->writeInt(fIdxStart);
    S->seek(pos);
}

void plPageInfo::prcWrite(pfPrcHelper* prc) {
    prc->startTag("Page");
    prc->writeParam("AgeName", fAge);
    prc->writeParam("PageName", fPage);
    fLocation.prcWrite(prc);
    prc->endTag();
}

void plPageInfo::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "Page")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fAge = tag->getParam("AgeName", "");
    fPage = tag->getParam("PageName", "");
    fLocation.prcParse(tag);
}

plString plPageInfo::getFilename(PlasmaVer ver) const {
    if (ver >= pvEoa)
        return plString::Format("%s_%s.prp", fAge.cstr(), fPage.cstr());
    else
        return plString::Format("%s_District_%s.prp", fAge.cstr(), fPage.cstr());
}
