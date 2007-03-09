#include "plPageInfo.h"
#include <string.h>

plPageInfo::plPageInfo() { IInit(); }

plPageInfo::~plPageInfo() {
    if (age) delete[] age;
    if (page) delete[] page;
}

void plPageInfo::IInit() {
    age = NULL;
    page = NULL;
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
    if (age) delete[] age;
    if (page) delete[] page;
    IInit();

    short prpVer = S->readShort();
    if (prpVer > 6) return;
    if (prpVer == 6) {
        S->setVer(pvEoa);
        unsigned short nTypes = S->readShort();
        S->skip(nTypes * 4); // Type info table...
        location.read(S);
        age = S->readSafeStr();
        page = S->readSafeStr();
    } else {
        S->readShort(); // prpVer is DWORD on <= 5
        if (prpVer >= 1) {
            int pid = S->readInt();
            int pflags = S->readShort();
            S->setVer(pvPrime);
            age = S->readSafeStr();
            delete[] S->readSafeStr(); // "District"
            page = S->readSafeStr();
            short majorVer = S->readShort();
            short minorVer = S->readShort();
            if (majorVer >= 69) S->setVer(pvLive);
            else if (minorVer >= 12) S->setVer(pvPots);
            location.set(pid, pflags, S->getVer());
            if (prpVer < 5)
                idxChecksum = S->readInt();
        }
        if (prpVer >= 2)
            releaseVersion = S->readInt();
        if (prpVer >= 3)
            flags = S->readInt();
    }
    if (prpVer >= 4)
        checksum = S->readInt();
    if (prpVer >= 5) {
        dataStart = S->readInt();
        idxStart = S->readInt();
    } else {
        dataStart = 0;
        idxStart = S->readByte();
    }
}

void plPageInfo::write(hsStream* S) {
    if (S->getVer() == pvEoa) {
        S->writeShort(6);
        throw "Incomplete"; // Needs the type info thingy
        location.write(S);
        S->writeSafeStr(age);
        S->writeSafeStr(page);
    } else {
        S->writeInt(5);
        location.write(S);
        S->writeSafeStr(age);
        S->writeSafeStr(getChapter());
        S->writeSafeStr(page);
        short majorVer = 63;
        short minorVer = 11;
        if (S->getVer() == pvPots)
            minorVer = 12;
        if (S->getVer() == pvLive) {
            majorVer = 69;
            minorVer = 4;
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

void plPageInfo::setNames(char* newAge, char* newPage) {
    if (age) delete[] age;
    if (page) delete[] page;
    age = newAge;
    page = newPage;
}

