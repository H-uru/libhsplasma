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

#include "plAgeInfo.h"
#include <string_theory/format>

const ST::string plAgeInfo::kCommonPages[] = { "Textures", "BuiltIn" };

/* plAgeInfo */
void plAgeInfo::readFromFile(const ST::string& filename)
{
    fName = filename.after_last(PATHSEP);
    ST_ssize_t dot = fName.find_last('.');
    if (dot >= 0)
        fName = fName.left(dot);

    if (plEncryptedStream::IsFileEncrypted(filename)) {
        plEncryptedStream S;
        S.open(filename, fmRead, plEncryptedStream::kEncAuto);
        readFromStream(&S);
        S.close();
    } else {
        hsFileStream S;
        S.open(filename, fmRead);
        readFromStream(&S);
        S.close();
    }
}

void plAgeInfo::readFromStream(hsStream* S)
{
    while (!S->eof()) {
        ST::string ln = S->readLine();
        if (ln.trim().empty())
            continue;

        std::vector<ST::string> parts = ln.split('=', 1);
        ST::string field = parts.at(0).to_lower();
        ST::string value = parts.at(1);

        if (field == "startdatetime") {
            fStartDateTime = value.to_uint();
        } else if (field == "daylength") {
            fDayLength = value.to_float();
        } else if (field == "maxcapacity") {
            fMaxCapacity = (short)value.to_int();
        } else if (field == "lingertime") {
            fLingerTime = (short)value.to_int();
        } else if (field == "sequenceprefix") {
            fSeqPrefix = value.to_int();
        } else if (field == "releaseversion") {
            fReleaseVersion = value.to_uint();
        } else if (field == "page") {
            std::vector<ST::string> parts = value.split(',');
            ST::string name = parts.at(0);
            int seqSuffix = (parts.size() > 1) ? parts.at(1).to_int() : 0;
            unsigned int loadFlags = (parts.size() > 2) ? parts.at(2).to_uint() : 0;
            PageEntry page(name, seqSuffix, loadFlags);
            addPage(page);
        }
    }
}

void plAgeInfo::writeToFile(const ST::string& filename, PlasmaVer ver) const
{
    if (ver.isUniversal()) {
        hsFileStream S;
        S.open(filename, fmCreate);
        writeToStream(&S);
        S.close();
    } else {
        plEncryptedStream S;
        plEncryptedStream::EncryptionType eType = plEncryptedStream::kEncAuto;
        if (ver.isNewPlasma())
            eType = plEncryptedStream::kEncAES;
        else
            eType = plEncryptedStream::kEncXtea;
        S.open(filename, fmCreate, eType);
        writeToStream(&S);
        S.close();
    }
}

void plAgeInfo::writeToStream(hsStream* S) const
{
    S->writeLine(ST::format("StartDateTime={_010}", fStartDateTime), true);
    S->writeLine(ST::format("DayLength={f}", fDayLength), true);
    S->writeLine(ST::format("MaxCapacity={}", fMaxCapacity), true);
    S->writeLine(ST::format("LingerTime={}", fLingerTime), true);
    S->writeLine(ST::format("SequencePrefix={}", fSeqPrefix), true);
    S->writeLine(ST::format("ReleaseVersion={}", fReleaseVersion), true);

    for (size_t i=0; i<fPages.size(); i++) {
        if (fPages[i].fLoadFlags != 0)
            S->writeLine(ST::format("Page={},{},{}",
                         fPages[i].fName,
                         fPages[i].fSeqSuffix,
                         fPages[i].fLoadFlags), true);
        else
            S->writeLine(ST::format("Page={},{}",
                         fPages[i].fName,
                         fPages[i].fSeqSuffix), true);
    }
}

void plAgeInfo::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("Age");
    prc->writeParam("Name", fName);
    prc->endTag();

    prc->startTag("AgeParams");
    prc->writeParam("StartDateTime", fStartDateTime);
    prc->writeParam("DayLength", fDayLength);
    prc->writeParam("MaxCapacity", fMaxCapacity);
    prc->writeParam("LingerTime", fLingerTime);
    prc->writeParam("SeqPrefix", fSeqPrefix);
    prc->writeParam("ReleaseVersion", fReleaseVersion);
    prc->endTag(true);

    prc->writeSimpleTag("Pages");
    for (size_t i=0; i<fPages.size(); i++) {
        prc->startTag("Page");
        prc->writeParam("AgeName", fName);
        prc->writeParam("PageName", fPages[i].fName);
        plLocation loc;
        loc.setSeqPrefix(fSeqPrefix);
        loc.setPageNum(fPages[i].fSeqSuffix);
        loc.setFlags(fPages[i].fLoadFlags);
        loc.prcWrite(prc);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->closeTag();
}

void plAgeInfo::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "Age")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fName = tag->getParam("Name", "");

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        if (child->getName() == "AgeParams") {
            fStartDateTime = child->getParam("StartDateTime", "0").to_uint();
            fDayLength = child->getParam("DayLength", "0").to_float();
            fMaxCapacity = child->getParam("MaxCapacity", "0").to_int();
            fLingerTime = child->getParam("LingerTime", "0").to_int();
            fSeqPrefix = child->getParam("SeqPrefix", "0").to_int();
            fReleaseVersion = child->getParam("ReleaseVersion", "0").to_uint();
        } else if (child->getName() == "Pages") {
            fPages.resize(child->countChildren());
            const pfPrcTag* page = child->getFirstChild();
            for (size_t i=0; i<fPages.size(); i++) {
                plLocation loc;
                loc.prcParse(page);
                fPages[i].fName = page->getParam("PageName", "");
                fPages[i].fSeqSuffix = loc.getPageNum();
                fPages[i].fLoadFlags = loc.getFlags();
                page = page->getNextSibling();
            }
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

size_t plAgeInfo::getNumCommonPages(PlasmaVer pv) const
{
    if (fSeqPrefix < 0)
        return 0;
    return (!pv.isNewPlasma() || pv.isUniversal()) ? 2 : 1;
}

plAgeInfo::PageEntry plAgeInfo::getCommonPage(size_t idx, PlasmaVer pv) const
{
    return PageEntry(kCommonPages[idx], (-1) - idx, 0);
}

ST::string plAgeInfo::getPageFilename(size_t idx, PlasmaVer pv) const
{
    if (!pv.isValid())
        throw hsBadVersionException(__FILE__, __LINE__);
    if (pv.isNewPlasma() || pv.isUniversal())    // Includes pvUniversal
        return ST::format("{}_{}.prp", fName, fPages[idx].fName);
    else if (pv < MAKE_VERSION(2, 0, 60, 00))
        return ST::format("{}_District_{}.prx", fName, fPages[idx].fName);
    else
        return ST::format("{}_District_{}.prp", fName, fPages[idx].fName);
}

ST::string plAgeInfo::getCommonPageFilename(size_t idx, PlasmaVer pv) const
{
    if (!pv.isValid())
        throw hsBadVersionException(__FILE__, __LINE__);
    if (pv.isNewPlasma() || pv.isUniversal())    // Includes pvUniversal
        return ST::format("{}_{}.prp", fName, kCommonPages[idx]);
    else if (pv < MAKE_VERSION(2, 0, 60, 00))
        return ST::format("{}_District_{}.prx", fName, kCommonPages[idx]);
    else
        return ST::format("{}_District_{}.prp", fName, kCommonPages[idx]);
}

plLocation plAgeInfo::getPageLoc(size_t idx, PlasmaVer pv) const
{
    plLocation loc(pv);
    loc.setSeqPrefix(fSeqPrefix);
    loc.setPageNum(fPages[idx].fSeqSuffix);
    loc.parse(loc.unparse());   // Fix misbehaving ages
    return loc;
}

plLocation plAgeInfo::getCommonPageLoc(size_t idx, PlasmaVer pv) const
{
    plLocation loc(pv);
    loc.setSeqPrefix(fSeqPrefix);
    loc.setPageNum((-1) - idx);
    loc.parse(loc.unparse());   // Fix misbehaving ages
    return loc;
}

std::vector<plLocation> plAgeInfo::getPageLocs(PlasmaVer pv, bool all) const
{
    std::vector<plLocation> locs;

    for (size_t i=0; i < fPages.size(); i++) {
        if (all || !(fPages[i].fLoadFlags & kDontLoadMask))
            locs.push_back(getPageLoc(i, pv));
    }

    return locs;
}
