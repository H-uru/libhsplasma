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

plPageInfo::plPageInfo(const ST::string& age, const ST::string& page)
{
    IInit();
    setAge(age);
    setPage(page);
}

void plPageInfo::IInit()
{
    fLocation.invalidate();
    fReleaseVersion = 0;
    fChecksum = 0;
    fIdxChecksum = 0;
    fFlags = 0;
    fIdxStart = 0;
    fDataStart = 0;
    fNumObjects = 0;
}

void plPageInfo::read(hsStream* S)
{
    short prpVer = S->readShort();
    if (prpVer == -1)
        S->setVer(PlasmaVer::pvUniversal);
    else if (prpVer == 9)
        S->setVer(PlasmaVer::pvHex);
    else if (prpVer == 2)
        S->setVer(MAKE_VERSION(2, 0, 56, 0));
    else
        S->setVer(PlasmaVer::pvPrime);

    if (S->getVer().isValid() && !S->getVer().isUniversal()) {
        unsigned short numTypes = S->readShort();
        if (prpVer >= 6) {
            if (numTypes && prpVer == 6)
                S->setVer(PlasmaVer::pvEoa);
            if (numTypes == 0 && prpVer == 6)
                S->setVer(PlasmaVer::pvMoul);
            pdUnifiedTypeMap::SetCurrentVersionBase(S->getVer());
            for (unsigned short i = 0; i < numTypes; i++) {
                short type = S->readShort();
                short ver = S->readShort();
                pdUnifiedTypeMap::SetCurrentVersion(type, S->getVer(), ver);

                if (pdUnifiedTypeMap::ClassVersion(type, S->getVer()) != ver) {
                    plDebug::Warning("Warning: Class {} expected version {}, got {}",
                                     pdUnifiedTypeMap::ClassName(type, S->getVer()),
                                     pdUnifiedTypeMap::ClassVersion(type, S->getVer()), ver);
                }
            }
        }
    }

    if (prpVer >= 1) {
        int location = S->readInt();
        short locflags = (S->getVer().isNewPlasma() ?
                                S->readByte() :
                                S->readShort());

        fAge = S->readSafeStr();
        if (fAge.empty()) {
            locflags = 0;
            S->skip(-4);
            fAge = S->readSafeStr();
        }

        if (prpVer < 6)
            S->readSafeStr();

        fPage = S->readSafeStr();

        if (!S->getVer().isNewPlasma()) {
            S->setVer(MAKE_VERSION(S->getVer().plsMajor(), S->getVer().plsMinor(), S->readShort(), 0));
            if (prpVer < 6) {
                S->setVer(MAKE_VERSION(S->getVer().plsMajor(), S->getVer().plsMinor(), S->getVer().revMajor(), S->readShort()));
                if (prpVer < 5)
                    fIdxChecksum = S->readInt();
                if (prpVer >= 2)
                    fReleaseVersion = S->readInt();
                if (prpVer >= 3)
                    fFlags = S->readInt();
            }
        }
        if (S->getVer().isUniversal()) {
            fFlags = S->readInt();
        }

        fLocation.setVer(S->getVer());
        fLocation.parse(location);
        fLocation.setFlags(locflags);
    }
    if (prpVer >= 4 || S->getVer().isUniversal())
        fChecksum = S->readInt();
    if (prpVer >= 5 || S->getVer().isUniversal()) {
        fDataStart = S->readInt();
        fIdxStart = S->readInt();
    } else {
        fDataStart = 0;
        fIdxStart = S->pos();
    }

    if (S->getVer().isMoul()) {
        unsigned short numTypes = S->readShort();
        for (unsigned short i = 0; i < numTypes; i++) {
            short type = S->readShort();
            short ver = S->readShort();
            pdUnifiedTypeMap::SetCurrentVersion(type, S->getVer(), ver);

            if (pdUnifiedTypeMap::ClassVersion(type, S->getVer()) != ver) {
                plDebug::Warning("Warning: Class {} expected version {}, got {}",
                                 pdUnifiedTypeMap::ClassName(type, S->getVer()),
                                 pdUnifiedTypeMap::ClassVersion(type, S->getVer()), ver);
            }
        }
    }

    plDebug::Debug("* Loading: {} ({})\n"
                   "  Location: <{}|{}>\n"
                   "  Version: {}",
                   fPage, fAge,
                   fLocation.getSeqPrefix(), fLocation.getPageNum(),
                   PlasmaVer::GetVersionName(S->getVer()));
}

void plPageInfo::write(hsStream* S)
{
    if (S->getVer().isUniversal()) {
        S->writeShort(-1);
        fLocation.write(S);
        S->writeSafeStr(fAge);
        S->writeSafeStr(fPage);
        S->writeInt(fFlags);
    } else if (S->getVer().isEoa()) {
        S->writeShort(6);
        S->writeShort(fClassList.size());
        for (size_t i=0; i<fClassList.size(); i++) {
            short typeIdx = pdUnifiedTypeMap::MappedToPlasma(fClassList[i], S->getVer());
            S->writeShort(typeIdx);
            S->writeShort(pdUnifiedTypeMap::ClassVersion(typeIdx, S->getVer()));
        }
        fLocation.write(S);
        S->writeSafeStr(getAge());
        S->writeSafeStr(getPage());
    } else if (S->getVer().isHexIsle()) {
        S->writeShort(9);
        S->writeShort(fClassList.size());
        for (size_t i=0; i<fClassList.size(); i++) {
            short typeIdx = pdUnifiedTypeMap::MappedToPlasma(fClassList[i], S->getVer());
            S->writeShort(typeIdx);
            S->writeShort(pdUnifiedTypeMap::ClassVersion(typeIdx, S->getVer()));
        }
        fLocation.write(S);
        S->writeSafeStr(getAge());
        S->writeSafeStr(getPage());
    } else if (S->getVer().isMoul()) {
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
        S->writeShort(63);
        S->writeShort(S->getVer().revMinor());
        S->writeInt(fReleaseVersion);
        S->writeInt(fFlags);
    }
    S->writeInt(fChecksum);
    S->writeInt(fDataStart);
    S->writeInt(fIdxStart);

    if (S->getVer().isMoul()) {
        S->writeShort(fClassList.size());
        for (size_t i=0; i<fClassList.size(); i++) {
            short typeIdx = pdUnifiedTypeMap::MappedToPlasma(fClassList[i], S->getVer());
            S->writeShort(typeIdx);
            S->writeShort(pdUnifiedTypeMap::ClassVersion(typeIdx, S->getVer()));
        }
    }
}

void plPageInfo::writeSums(hsStream* S)
{
    unsigned int pos = S->pos();
    unsigned int offs = fDataStart - 12;
    if (S->getVer().isMoul()) {
        offs -= 2 + (4 * fClassList.size());
    }
    S->seek(offs);
    S->writeInt(fChecksum);
    S->writeInt(fDataStart);
    S->writeInt(fIdxStart);
    S->seek(pos);
}

void plPageInfo::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("Page");
    prc->writeParam("AgeName", fAge);
    prc->writeParam("PageName", fPage);
    fLocation.prcWrite(prc);
    prc->endTag();
}

void plPageInfo::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "Page")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fAge = tag->getParam("AgeName", "");
    fPage = tag->getParam("PageName", "");
    fLocation.prcParse(tag);
}

ST::string plPageInfo::getFilename(PlasmaVer ver) const
{
    if (ver.isNewPlasma())
        return ST::format("{}_{}.prp", fAge, fPage);
    else if (ver < MAKE_VERSION(2, 0, 60, 00))
        return ST::format("{}_District_{}.prx", fAge, fPage);
    else
        return ST::format("{}_District_{}.prp", fAge, fPage);
}
