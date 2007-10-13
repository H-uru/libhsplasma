#include <string.h>
#include "plPageInfo.h"
#include "../../DynLib/pdUnifiedTypeMap.h"

plPageInfo::plPageInfo() { IInit(); }

plPageInfo::~plPageInfo() { }

void plPageInfo::IInit() {
    location.invalidate();
    releaseVersion = 0;
    checksum = 0;
    idxChecksum = 0;
    flags = 0;
    idxStart = 0;
    dataStart = 0;
}

bool plPageInfo::isValid() { return location.isValid(); }

void plPageInfo::read(hsStream* S) {
    IInit();

    short prpVer = S->readShort();
    if (prpVer == 6) {
        unsigned short nTypes = S->readShort();
        if (nTypes == 0) {
            S->setVer(pvLive);
        } else {
            S->setVer(pvEoa);
            for (int i=0; i<nTypes; i++) {
                short type = S->readShort();
                short ver = S->readShort();
                if (pdUnifiedTypeMap::ClassVersion(type, pvEoa) != ver) {
                    printf("Warning: Class %s expected version %d, got %d\n",
                           pdUnifiedTypeMap::ClassName(type, pvEoa),
                           pdUnifiedTypeMap::ClassVersion(type, pvEoa), ver);
                }
            }
        }
        location.read(S);
        age = S->readSafeStr();
        page = S->readSafeStr();
        if (S->getVer() == pvLive)
            S->readShort();  // majorVer
    } else if (prpVer == 5) {
        S->readShort(); // prpVer is DWORD on <= 5
        int pid = S->readInt();
        int pflags = S->readShort();
        S->setVer(pvPrime);
        age = S->readSafeStr();
        S->readSafeStr(); // "District"
        page = S->readSafeStr();
        short majorVer = S->readShort();
        short minorVer = S->readShort();
        if (majorVer > 63) // Old Live version (e.g. 69.x)
            throw hsBadVersionException(__FILE__, __LINE__);
        else if (minorVer >= 12) S->setVer(pvPots);
        location.set(pid, pflags, S->getVer());
        releaseVersion = S->readInt();
        flags = S->readInt();
    } else {
        throw hsBadVersionException(__FILE__, __LINE__);
    }
    checksum = S->readInt();
    dataStart = S->readInt();
    idxStart = S->readInt();
}

void plPageInfo::write(hsStream* S) {
    if (S->getVer() == pvEoa) {
        S->writeShort(6);
        S->writeShort(classList.size());
        for (size_t i=0; i<classList.size(); i++) {
            S->writeShort(pdUnifiedTypeMap::MappedToPlasma(classList[i], pvEoa));
            S->writeShort(pdUnifiedTypeMap::ClassVersion(classList[i], pvEoa));
        }
        location.write(S);
        S->writeSafeStr(getAge());
        S->writeSafeStr(getPage());
    } else if (S->getVer() == pvLive) {
        S->writeInt(6);
        location.write(S);
        S->writeSafeStr(getAge());
        S->writeSafeStr(getPage());
        S->writeShort(70);
    } else {
        S->writeInt(5);
        location.write(S);
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
        S->writeInt(releaseVersion);
        S->writeInt(flags);
    }
    S->writeInt(checksum);
    S->writeInt(dataStart);
    S->writeInt(idxStart);
}

void plPageInfo::writeSums(hsStream* S) {
    unsigned int pos = S->pos();
    S->seek(dataStart-12);
    S->writeInt(checksum);
    S->writeInt(dataStart);
    S->writeInt(idxStart);
    S->seek(pos);
}

void plPageInfo::prcWrite(pfPrcHelper* prc) {
    prc->startTag("Page");
    prc->writeParam("AgeName", age);
    prc->writeParam("PageName", page);
    location.prcWrite(prc);
    prc->endTag();
}

const char* plPageInfo::getAge() { return age; }
const char* plPageInfo::getChapter() { return "District"; }
const char* plPageInfo::getPage() { return page; }
unsigned int plPageInfo::getChecksum() { return checksum; }
unsigned int plPageInfo::getDataStart() { return dataStart; }
unsigned int plPageInfo::getIndexStart() { return idxStart; }
unsigned int plPageInfo::getFlags() { return flags; }
plLocation& plPageInfo::getLocation() { return location; }

void plPageInfo::setChecksum(unsigned int sum) { checksum = sum; }
void plPageInfo::setReleaseVersion(unsigned int relVer) { releaseVersion = relVer; }
void plPageInfo::setDataStart(unsigned int loc) { dataStart = loc; }
void plPageInfo::setIndexStart(unsigned int loc) { idxStart = loc; }
void plPageInfo::setFlags(unsigned int f) { flags = f; }
void plPageInfo::setLocation(plLocation& loc) { location = loc; }

void plPageInfo::setNames(const char* newAge, const char* newPage) {
    age = newAge;
    page = newPage;
}

void plPageInfo::clearClassList() { classList.clear(); }
void plPageInfo::addClass(short classIdx) { classList.push_back(classIdx); }
void plPageInfo::setClassList(std::vector<short>& list) { classList = list; }
