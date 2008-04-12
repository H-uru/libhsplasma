#include "plAgeInfo.h"

const plString plAgeInfo::kCommonPages[] = { "Textures", "BuiltIn" };

/* PageEntry */
plAgeInfo::PageEntry::PageEntry(const plString& name, int seqSuffix,
                                unsigned int loadFlags)
         : fName(name), fSeqSuffix(seqSuffix), fLoadFlags(loadFlags) { }

plAgeInfo::PageEntry::PageEntry()
         : fSeqSuffix(0), fLoadFlags(0) { }


/* plAgeInfo */
plAgeInfo::plAgeInfo() : fStartDateTime(0), fDayLength(24.0f), fMaxCapacity(-1),
                         fLingerTime(180), fSeqPrefix(0), fReleaseVersion(0) { }

plAgeInfo::~plAgeInfo() { }

void plAgeInfo::readFromFile(const plString& filename) {
    fName = filename.afterLast(PATHSEP);
    if (!fName.beforeLast('.').empty())
        fName = fName.beforeLast('.');
    for (size_t i=0; i<kNumCommonPages; i++)
        addPage(PageEntry(kCommonPages[i], (-1) - i, 0));

    plEncryptedStream* S = new plEncryptedStream();
    S->open(filename, fmRead, plEncryptedStream::kEncAuto);

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

void plAgeInfo::writeToPath(const plString& path, PlasmaVer ver) {
    plString filename = path;
    if (filename[filename.len()-1] != PATHSEP)
        filename += PATHSEP;
    filename += fName + ".age";
    
    plEncryptedStream* S = new plEncryptedStream();
    plEncryptedStream::EncryptionType eType = plEncryptedStream::kEncAuto;
    if (ver >= pvEoa)
        eType = plEncryptedStream::kEncAES;
    else
        eType = plEncryptedStream::kEncXtea;
    S->open(filename, fmCreate, eType);

    S->writeLine(plString::Format("StartDateTime=%010u", fStartDateTime));
    S->writeLine(plString::Format("DayLength=%f", fDayLength));
    S->writeLine(plString::Format("MaxCapacity=%hd", fMaxCapacity));
    S->writeLine(plString::Format("LingerTime=%hd", fLingerTime));
    S->writeLine(plString::Format("SequencePrefix=%d", fSeqPrefix));
    S->writeLine(plString::Format("ReleaseVersion=%u", fReleaseVersion));

    for (size_t i=0; i<fPages.getSize(); i++) {
        if (fPages[i].fLoadFlags != 0)
            S->writeLine(plString::Format("Page=%s,%d,%d",
                         fPages[i].fName.cstr(),
                         fPages[i].fSeqSuffix,
                         fPages[i].fLoadFlags));
        else
            S->writeLine(plString::Format("Page=%s,%d",
                         fPages[i].fName.cstr(),
                         fPages[i].fSeqSuffix));
    }

    delete S;
}

const plString& plAgeInfo::getAgeName() const { return fName; }
unsigned int plAgeInfo::getStartDateTime() const { return fStartDateTime; }
float plAgeInfo::getDayLength() const { return fDayLength; }
short plAgeInfo::getMaxCapacity() const { return fMaxCapacity; }
short plAgeInfo::getLingerTime() const { return fLingerTime; }
int plAgeInfo::getSeqPrefix() const { return fSeqPrefix; }
unsigned int plAgeInfo::getReleaseVersion() const { return fReleaseVersion; }

void plAgeInfo::setAgeName(const plString& name) {
    if (name != fName)
        fName = name;
}

void plAgeInfo::setStartDateTime(unsigned int time) { fStartDateTime = time; }
void plAgeInfo::setDayLength(float length) { fDayLength = length; }
void plAgeInfo::setMaxCapacity(short maxCap) { fMaxCapacity = maxCap; }
void plAgeInfo::setLingerTime(short time) { fLingerTime = time; }
void plAgeInfo::setSeqPrefix(int prefix) { fSeqPrefix = prefix; }
void plAgeInfo::setReleaseVersion(unsigned int ver) { fReleaseVersion = ver; }

size_t plAgeInfo::getNumPages() const { return fPages.getSize(); }
plAgeInfo::PageEntry plAgeInfo::getPage(size_t idx) const { return fPages[idx]; }
void plAgeInfo::setPage(size_t idx, const PageEntry& page) { fPages[idx] = page; }
void plAgeInfo::addPage(const PageEntry& page) { fPages.append(page); }

plString plAgeInfo::getPageFileName(size_t idx, PlasmaVer pv) const {
    if (pv >= pvEoa)
        return plString::Format("%s_%s.prp", fName.cstr(), fPages[idx].fName.cstr());
    else
        return plString::Format("%s_District_%s.prp", fName.cstr(), fPages[idx].fName.cstr());
}
