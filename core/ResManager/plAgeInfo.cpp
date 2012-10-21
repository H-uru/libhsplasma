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

const plString plAgeInfo::kCommonPages[] = { "Textures", "BuiltIn" };

/* plAgeInfo */
void plAgeInfo::readFromFile(const plString& filename) {
    fName = filename.afterLast(PATHSEP);
    if (!fName.beforeLast('.').empty())
        fName = fName.beforeLast('.');

    hsStream* S;
    if (plEncryptedStream::IsFileEncrypted(filename)) {
        S = new plEncryptedStream();
        ((plEncryptedStream*)S)->open(filename, fmRead, plEncryptedStream::kEncAuto);
    } else {
        S = new hsFileStream();
        ((hsFileStream*)S)->open(filename, fmRead);
    }

    while (!S->eof()) {
        plString ln = S->readLine();
        plString field = ln.beforeFirst('=').toLower();
        plString value = ln.afterFirst('=');

        if (field == "startdatetime") {
            fStartDateTime = value.toUint();
        } else if (field == "daylength") {
            fDayLength = value.toFloat();
        } else if (field == "maxcapacity") {
            fMaxCapacity = (short)value.toInt();
        } else if (field == "lingertime") {
            fLingerTime = (short)value.toInt();
        } else if (field == "sequenceprefix") {
            fSeqPrefix = value.toInt();
        } else if (field == "releaseversion") {
            fReleaseVersion = value.toUint();
        } else if (field == "page") {
            plString name = value.beforeFirst(',');
            value = value.afterFirst(',');
            int seqSuffix = value.beforeFirst(',').toInt();
            value = value.afterFirst(',');
            unsigned int loadFlags = value.toUint();
            PageEntry page(name, seqSuffix, loadFlags);
            addPage(page);
        }
    }

    delete S;
}

void plAgeInfo::writeToFile(const plString& filename, PlasmaVer ver) {
    hsStream* S;
    if (ver.isUniversal()) {
        S = new hsFileStream();
        ((hsFileStream*)S)->open(filename, fmCreate);
    } else {
        S = new plEncryptedStream();
        plEncryptedStream::EncryptionType eType = plEncryptedStream::kEncAuto;
        if (ver.isNewPlasma())
            eType = plEncryptedStream::kEncAES;
        else
            eType = plEncryptedStream::kEncXtea;
        ((plEncryptedStream*)S)->open(filename, fmCreate, eType);
    }

    S->writeLine(plString::Format("StartDateTime=%010u", fStartDateTime), true);
    S->writeLine(plString::Format("DayLength=%f", fDayLength), true);
    S->writeLine(plString::Format("MaxCapacity=%hd", fMaxCapacity), true);
    S->writeLine(plString::Format("LingerTime=%hd", fLingerTime), true);
    S->writeLine(plString::Format("SequencePrefix=%d", fSeqPrefix), true);
    S->writeLine(plString::Format("ReleaseVersion=%u", fReleaseVersion), true);

    for (size_t i=0; i<fPages.getSize(); i++) {
        if (fPages[i].fLoadFlags != 0)
            S->writeLine(plString::Format("Page=%s,%d,%d",
                         fPages[i].fName.cstr(),
                         fPages[i].fSeqSuffix,
                         fPages[i].fLoadFlags), true);
        else
            S->writeLine(plString::Format("Page=%s,%d",
                         fPages[i].fName.cstr(),
                         fPages[i].fSeqSuffix), true);
    }

    delete S;
}

void plAgeInfo::prcWrite(pfPrcHelper* prc) {
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
    for (size_t i=0; i<fPages.getSize(); i++) {
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

void plAgeInfo::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "Age")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fName = tag->getParam("Name", "");

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "AgeParams") {
            fStartDateTime = child->getParam("StartDateTime", "0").toUint();
            fDayLength = child->getParam("DayLength", "0").toFloat();
            fMaxCapacity = child->getParam("MaxCapacity", "0").toInt();
            fLingerTime = child->getParam("LingerTime", "0").toInt();
            fSeqPrefix = child->getParam("SeqPrefix", "0").toInt();
            fReleaseVersion = child->getParam("ReleaseVersion", "0").toUint();
        } else if (child->getName() == "Pages") {
            fPages.setSize(child->countChildren());
            const pfPrcTag* page = child->getFirstChild();
            for (size_t i=0; i<fPages.getSize(); i++) {
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

size_t plAgeInfo::getNumCommonPages(PlasmaVer pv) const {
    if (fSeqPrefix < 0)
        return 0;
    return (!pv.isNewPlasma() || pv.isUniversal()) ? 2 : 1;
}

plAgeInfo::PageEntry plAgeInfo::getCommonPage(size_t idx, PlasmaVer pv) const {
    return PageEntry(kCommonPages[idx], (-1) - idx, 0);
}

plString plAgeInfo::getPageFilename(size_t idx, PlasmaVer pv) const {
    if (!pv.isValid())
        throw hsBadVersionException(__FILE__, __LINE__);
    if (pv.isNewPlasma() || pv.isUniversal())    // Includes pvUniversal
        return plString::Format("%s_%s.prp", fName.cstr(), fPages[idx].fName.cstr());
    else if (pv < MAKE_VERSION(2, 0, 60, 00))
        return plString::Format("%s_District_%s.prx", fName.cstr(), fPages[idx].fName.cstr());
    else
        return plString::Format("%s_District_%s.prp", fName.cstr(), fPages[idx].fName.cstr());
}

plString plAgeInfo::getCommonPageFilename(size_t idx, PlasmaVer pv) const {
    if (!pv.isValid())
        throw hsBadVersionException(__FILE__, __LINE__);
    if (pv.isNewPlasma() || pv.isUniversal())    // Includes pvUniversal
        return plString::Format("%s_%s.prp", fName.cstr(), kCommonPages[idx].cstr());
    else if (pv < MAKE_VERSION(2, 0, 60, 00))
        return plString::Format("%s_District_%s.prx", fName.cstr(), kCommonPages[idx].cstr());
    else
        return plString::Format("%s_District_%s.prp", fName.cstr(), kCommonPages[idx].cstr());
}

plLocation plAgeInfo::getPageLoc(size_t idx, PlasmaVer pv) const {
    plLocation loc(pv);
    loc.setSeqPrefix(fSeqPrefix);
    loc.setPageNum(fPages[idx].fSeqSuffix);
    loc.parse(loc.unparse());   // Fix misbehaving ages
    return loc;
}

plLocation plAgeInfo::getCommonPageLoc(size_t idx, PlasmaVer pv) const {
    plLocation loc(pv);
    loc.setSeqPrefix(fSeqPrefix);
    loc.setPageNum((-1) - idx);
    loc.parse(loc.unparse());   // Fix misbehaving ages
    return loc;
}

std::vector<plLocation> plAgeInfo::getPageLocs(PlasmaVer pv, bool all) const {
    std::vector<plLocation> locs;

    for (size_t i=0; i < fPages.getSize(); i++) {
        if (all || !(fPages[i].fLoadFlags & kDontLoadMask))
            locs.push_back(getPageLoc(i, pv));
    }

    return locs;
}
