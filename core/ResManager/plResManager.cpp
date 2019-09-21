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

#include "plResManager.h"
#include "plFactory.h"
#include "PRP/plSceneNode.h"
#include "Debug/plDebug.h"
#include "Stream/hsRAMStream.h"
#include "Stream/pfSizedStream.h"
#include "Stream/pfPrcParser.h"
#include "Stream/plEncryptedStream.h"

plResManager::~plResManager()
{
    if (ages.size() > 0 || pages.size() > 0)
        plDebug::Debug("~plResManager: cleaning up {} ages and {} pages",
                       ages.size(), pages.size());
    while (ages.size() > 0)
        UnloadAge(ages[0]->getAgeName());
    while (pages.size() > 0)
        UnloadPage(pages[0]->getLocation());
}

void plResManager::setVer(PlasmaVer pv, bool force)
{
    if (fPlasmaVer == PlasmaVer::pvUnknown || force)
        fPlasmaVer = pv;
}

plKey plResManager::readKey(hsStream* S)
{
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    if (S->getVer().isUru() || S->getVer().isUniversal()) {
        if (S->readBool())
            return readUoid(S);
        else
            return plKey();
    } else {
        return readUoid(S);
    }
}

plKey plResManager::readKeyNotify(hsStream* S, plKeyData::AfterLoadCallback callback)
{
    plKey key = readKey(S);
    key->addCallback(std::move(callback));
    return key;
}

plKey plResManager::readUoid(hsStream* S)
{
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    plKey k = new plKeyData();
    k->readUoid(S);
    if (!k->getLocation().isValid())
        return plKey();
    return AddKey(k);
}

void plResManager::writeKey(hsStream* S, const plKey& key)
{
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    //key->exists = (strcmp(key->objName, "") != 0);
    if (S->getVer().isUru() || S->getVer().isUniversal())
        S->writeBool(key.Exists());
    if (key.Exists() || (S->getVer().isNewPlasma()))
        writeUoid(S, key);
}

void plResManager::writeKey(hsStream* S, hsKeyedObject* ko)
{
    writeKey(S, ko->getKey());
}

void plResManager::writeUoid(hsStream* S, const plKey& key)
{
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    if (!key.Exists()) {
        plKey empty = new plKeyData();
        empty->writeUoid(S);
    } else {
        key->writeUoid(S);
    }
}

void plResManager::writeUoid(hsStream* S, hsKeyedObject* ko)
{
    writeUoid(S, ko->getKey());
}

plKey plResManager::prcParseKey(const pfPrcTag* tag)
{
    plKey k = plKeyData::PrcParse(tag);
    if (k.Exists())
        return AddKey(k);
    return k;
}

plKey plResManager::prcParseKeyNotify(const pfPrcTag* tag,
                                      plKeyData::AfterLoadCallback callback)
{
    plKey key = prcParseKey(tag);
    key->addCallback(std::move(callback));
    return key;
}

void plResManager::PrcWriteKey(pfPrcHelper* prc, const plKey& key)
{
    if (!key.Exists() || !key->getLocation().isValid()) {
        prc->startTag("plKey");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    } else {
        key->prcWriteUoid(prc);
    }
}

void plResManager::PrcWriteKey(pfPrcHelper* prc, hsKeyedObject* ko)
{
    PrcWriteKey(prc, ko->getKey());
}

hsKeyedObject* plResManager::getObject(const plKey& key)
{
    plKey fk = keys.findKey(key);
    if (!fk.Exists())
        return nullptr;
    return fk->getObj();
}

plPageInfo* plResManager::ReadPage(const ST::string& filename, bool stub)
{
    bool packed = true;
    ST::string file(filename);

    if (!file.ends_with(".prp", ST::case_insensitive)) {
        if (file.ends_with(".prx", ST::case_insensitive) || file.ends_with(".prm", ST::case_insensitive)) {
            packed = false;
            file = file.before_last('.');
            if (!hsFileStream::FileExists(file + ".prx"))
                throw hsFileReadException(__FILE__, __LINE__,
                        (file+".prx").c_str());
            if (!hsFileStream::FileExists(file + ".prm"))
                throw hsFileReadException(__FILE__, __LINE__,
                        (file+".prm").c_str());

            file += ".prx";
        } else {
            throw hsBadParamException(__FILE__, __LINE__,
                ST::format("{} is not a valid Page file", file));
        }
    }

    if (packed) {
        hsFileStream prpS;
        if (!prpS.open(file, fmRead))
            throw hsFileReadException(__FILE__, __LINE__, file.c_str());
        // hsFileStream destructor closes the file
        return ReadPage(&prpS, &prpS, stub);
    } else {
        hsFileStream prxS;
        if (!prxS.open(file, fmRead))
            throw hsFileReadException(__FILE__, __LINE__, file.c_str());
        file = file.before_last('.') + ".prm";
        hsFileStream prmS;
        if (!prmS.open(file, fmRead))
            throw hsFileReadException(__FILE__, __LINE__, file.c_str());
        // hsFileStream destructor closes the file
        return ReadPage(&prxS, &prmS, stub);
    }
}

plPageInfo* plResManager::ReadPage(hsStream* prxS, hsStream* prmS, bool stub)
{
    plPageInfo* page = new plPageInfo();
    page->read(prxS);

    const plLocation& loc = page->getLocation();
    UnloadPage(loc);

    pages.push_back(page);
    setVer(prxS->getVer(), true);
    prxS->seek(page->getIndexStart());
    ReadKeyring(prxS, loc);

    if (!prmS)
        prmS = prxS;
    mustStub = stub;
    page->setNumObjects(ReadObjects(prmS, loc));
    mustStub = false;
    return page;
}

plPageInfo* plResManager::ReadPagePrc(const pfPrcTag* root)
{
    plPageInfo* page = new plPageInfo();
    page->prcParse(root);

    const pfPrcTag* tag = root->getFirstChild();
    while (tag) {
        hsKeyedObject* ko = prcParseCreatableC<hsKeyedObject>(tag);
        if (ko)
            ko->getKey()->setObj(ko);
        tag = tag->getNextSibling();
    }

    UnloadPage(page->getLocation());
    pages.push_back(page);
    return page;
}

void plResManager::WritePage(const ST::string& filename, plPageInfo* page)
{
    hsFileStream S;
    S.open(filename, fmWrite);
    WritePage(&S, page);
    S.close();
}

void plResManager::WritePage(hsStream* S, plPageInfo* page)
{
    S->setVer(getVer());
    std::vector<short> types = keys.getTypes(page->getLocation());
    page->setClassList(types);
    //keys.sortKeys(page->getLocation());
    page->write(S);
    page->setDataStart(S->pos());
    page->setNumObjects(WriteObjects(S, page->getLocation()));
    page->setIndexStart(S->pos());
    WriteKeyring(S, page->getLocation());
    if (getVer().isNewPlasma())
        page->setChecksum(S->pos());
    else
        page->setChecksum(S->pos() - page->getDataStart());
    page->writeSums(S);
}

void plResManager::WritePagePrc(pfPrcHelper* prc, plPageInfo* page)
{
    page->prcWrite(prc); // starts <Page>

    // Objects:
    std::vector<short> types = keys.getTypes(page->getLocation());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(page->getLocation(), types[i]);
        for (unsigned int j=0; j<kList.size(); j++) {
            if (kList[j]->getObj())
                kList[j]->getObj()->prcWrite(prc);
        }
    }

    prc->closeTag();
}

plPageInfo* plResManager::FindPage(const plLocation& loc)
{
    std::vector<plPageInfo*>::iterator pi = pages.begin();
    while (pi != pages.end()) {
        if ((*pi)->getLocation() == loc)
            return *pi;
        pi++;
    }
    return nullptr;
}

void plResManager::UnloadPage(const plLocation& loc)
{
    // Make a copy, in case someone passed us the page's getLocation() reference
    plLocation pageLoc = loc;

    for (auto it = pages.begin(); it != pages.end(); it++) {
        if ((*it)->getLocation() == loc) {
            if (pageUnloadFunc)
                pageUnloadFunc(loc);
            delete *it;
            pages.erase(it);
            keys.delAll(pageLoc);
            break;
        }
    }
}

unsigned int plResManager::ReadPage(hsStream* S, std::vector<plPageInfo*>& agepages)
{
    plPageInfo* page = new plPageInfo();
    page->read(S);
    plLocation loc = page->getLocation();
    UnloadPage(loc);
    pages.push_back(page);
    agepages.push_back(page);
    setVer(S->getVer(), true);
    S->seek(page->getIndexStart());
    return ReadKeyring(S, loc);
}

plAgeInfo* plResManager::ReadAge(const ST::string& filename, bool readPages)
{
    plAgeInfo* age = new plAgeInfo();
    age->readFromFile(filename);

    for (std::vector<plAgeInfo*>::iterator it=ages.begin(); it!=ages.end(); ) {
        if ((*it)->getAgeName() == age->getAgeName()) {
            delete *it;
            it = ages.erase(it);
        } else {
            it++;
        }
    }

    if (readPages) {
        ST::string path = filename.before_last(PATHSEP);
        if (path.size() > 0)
            path = path + PATHSEPSTR;

        PlasmaVer ageVer = PlasmaVer::pvUnknown;
        bool packed = true;
        if (age->getNumPages() > 0) {
            ST::string file = ST::format("{}_District_{}",
                    age->getAgeName(),
                    age->getPage(0).fName);
            if (hsFileStream::FileExists(path + file + ".prp")) {
                ageVer = MAKE_VERSION(2, 0, 63, 12);
            } else if (hsFileStream::FileExists(path + file + ".prx")) {
                ageVer = MAKE_VERSION(2, 0, 63, 12);
                packed = false;
            } else {
                ageVer = MAKE_VERSION(2, 1, 6, 10);
            }
        }

        hsFileStream* S = nullptr;
        std::vector<plPageInfo*> agepages;

        for (size_t i=0; i<age->getNumCommonPages(ageVer); i++) {
            if (hsFileStream::FileExists(path + age->getCommonPageFilename(i, ageVer))) {
                S = new hsFileStream();
                if (!S->open(path + age->getCommonPageFilename(i, ageVer), fmRead)) {
                    throw hsFileReadException(__FILE__, __LINE__, filename.c_str());
                }
                ReadPage(S, agepages);
                S->close();
                delete S;
            }
        }

        for (size_t i=0; i<age->getNumPages(); i++) {
            if (hsFileStream::FileExists(path + age->getPageFilename(i, ageVer))) {
                S = new hsFileStream();
                if (!S->open(path + age->getPageFilename(i, ageVer), fmRead)) {
                    throw hsFileReadException(__FILE__, __LINE__, filename.c_str());
                }
                ReadPage(S, agepages);
                S->close();
                delete S;
            }
        }

        for (size_t i=0; i < agepages.size(); i++) {
            S = new hsFileStream();
            S->setVer(getVer());
            ST::string file = path + agepages[i]->getFilename(ageVer);
            if (!packed) {
                file = file.before_last('.') + ".prm";
            }

            if (!S->open(file, fmRead)) {
                throw hsFileReadException(__FILE__, __LINE__, filename.c_str());
            }

            agepages[i]->setNumObjects(
                    ReadObjects(S, agepages[i]->getLocation()));

            S->close();
            delete S;
        }
    }

    ages.push_back(age);
    return age;
}

plAgeInfo* plResManager::ReadAgePrc(const pfPrcTag* root)
{
    plAgeInfo* age = new plAgeInfo();
    age->prcParse(root);

    for (std::vector<plAgeInfo*>::iterator it=ages.begin(); it!=ages.end(); ) {
        if ((*it)->getAgeName() == age->getAgeName()) {
            delete *it;
            it = ages.erase(it);
        } else {
            it++;
        }
    }

    ages.push_back(age);
    return age;
}

void plResManager::WriteAge(const ST::string& filename, plAgeInfo* age)
{
    ST::string ageName = filename.after_last(PATHSEP);
    ST_ssize_t dot = ageName.find_last('.');
    if (dot >= 0)
        ageName = ageName.left(dot);
    age->setAgeName(ageName);
    age->writeToFile(filename, getVer());
}

void plResManager::WriteAgePrc(pfPrcHelper* prc, plAgeInfo* age)
{
    age->prcWrite(prc);
}

plAgeInfo* plResManager::FindAge(const ST::string& name)
{
    std::vector<plAgeInfo*>::iterator ai = ages.begin();
    while (ai != ages.end()) {
        if ((*ai)->getAgeName() == name)
            return *ai;
        ai++;
    }
    return nullptr;
}

void plResManager::UnloadAge(const ST::string& name)
{
    std::vector<plPageInfo*>::iterator pi = pages.begin();
    while (pi != pages.end()) {
        if ((*pi)->getAge() == name) {
            const plLocation& loc = (*pi)->getLocation();
            if (pageUnloadFunc)
                pageUnloadFunc(loc);
            keys.delAll(loc);
            delete *pi;
            pi = pages.erase(pi);
        } else {
            pi++;
        }
    }

    std::vector<plAgeInfo*>::iterator ai = ages.begin();
    while (ai != ages.end()) {
        if ((*ai)->getAgeName() == name) {
            delete *ai;
            ai = ages.erase(ai);
        } else {
            ai++;
        }
    }
}

unsigned int plResManager::ReadKeyring(hsStream* S, const plLocation& loc)
{
#ifdef RMTRACE
    plDebug::Debug("* Reading Keyring");
#endif

    unsigned int pageKeys = 0;
    unsigned int tCount = S->readInt();
    for (unsigned int i=0; i<tCount; i++) {
        short type = pdUnifiedTypeMap::PlasmaToMapped(S->readShort(), S->getVer()); // objType
        if (S->getVer() >= MAKE_VERSION(2, 0, 70, 0) && !S->getVer().isUniversal()) {
            S->readInt();   // # of bytes after this int to next key list
            S->readByte();  // flag?
        }
        unsigned int oCount = S->readInt();
        keys.reserveKeySpace(loc, type, oCount);
#ifdef RMTRACE
        plDebug::Debug("  * Indexing {} objects of type [{_04X}]{}", oCount, type,
                       pdUnifiedTypeMap::ClassName(type));
#endif
        for (unsigned int j=0; j<oCount; j++) {
            plKey key = new plKeyData();
            key->read(S);
            pageKeys++;

            plKey xkey = keys.findKey(key);
            if (xkey.Exists()) {
                xkey->setFileOff(key->getFileOff());
                xkey->setObjSize(key->getObjSize());
            } else {
                keys.add(key);
            }
        }
    }

    return pageKeys;
}

void plResManager::WriteKeyring(hsStream* S, const plLocation& loc)
{
    std::vector<short> types = keys.getTypes(loc, true);
    S->writeInt(types.size());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc, types[i], true);
        S->writeShort(pdUnifiedTypeMap::MappedToPlasma(kList[0]->getType(), S->getVer()));
        unsigned int lenPos = S->pos();
        if (S->getVer() >= MAKE_VERSION(2, 0, 70, 0) && !S->getVer().isUniversal()) {
            S->writeInt(0);
            S->writeByte(0);
        }
        S->writeInt(kList.size());
        for (unsigned int j=0; j<kList.size(); j++)
            kList[j]->write(S);
        if (S->getVer() >= MAKE_VERSION(2, 0, 70, 0) && !S->getVer().isUniversal()) {
            unsigned int nextPos = S->pos();
            S->seek(lenPos);
            S->writeInt(nextPos - lenPos - 4);
            S->seek(nextPos);
        }
    }
}

unsigned int plResManager::ReadObjects(hsStream* S, const plLocation& loc)
{
    std::vector<short> types = keys.getTypes(loc);
    unsigned int nRead = 0;

    size_t totalKeys = 0, processedKeys = 0;

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc, types[i]);
        totalKeys += kList.size();
    }

    plPageInfo *page = nullptr;
    if (progressFunc) {
        for (size_t i = 0; i < pages.size(); ++i) {
            if (pages[i]->getLocation() == loc)
                page = pages[i];
        }
        progressFunc(page, 0, totalKeys);
    }

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc, types[i]);
#ifdef RMTRACE
        plDebug::Debug("* Reading {} objects of type [{_04X}]{}", kList.size(),
                       types[i], pdUnifiedTypeMap::ClassName(types[i]));
#endif
        for (unsigned int j=0; j<kList.size(); j++) {
            ++processedKeys;

            if (kList[j]->getFileOff() <= 0)
                continue;
#ifdef RMTRACE
            plDebug::Debug("  * ({}) Reading {} @ 0x{_08X}", j, kList[j]->getName(),
                           kList[j]->getFileOff());
#endif
            S->seek(kList[j]->getFileOff());
            uint32_t len = kList[j]->getObjSize();
            pfSizedStream *subStream = new pfSizedStream(S, len);
            try {
                plCreatable* pCre = ReadCreatable(subStream, true, len);
                if (pCre && pCre->isStub()) {
                    plCreatableStub* stub = (plCreatableStub*)pCre;
                    hsKeyedObjectStub* ko = new hsKeyedObjectStub();
                    hsRAMStream RS(subStream->getVer());
                    RS.copyFrom(stub->getData(), stub->getLength());
                    ko->read(&RS, this);
                    ko->setStub(stub);
                    kList[j]->setObj(ko);
                } else {
                    kList[j]->setObj(hsKeyedObject::Convert(pCre));
                }
                if (kList[j]->getObj()) {
                    nRead++;
                    if (!subStream->eof()) {
                        plDebug::Warning("[{_04X}:{}] Size-Read difference: {} bytes left after reading",
                            kList[j]->getType(), kList[j]->getName(),
                            (int)(subStream->size() - (subStream->pos())));
                        plDebug::Debug("At: 0x{_08X} ({} bytes)",
                            kList[j]->getFileOff(),
                            kList[j]->getObjSize());
                    }
                }
            } catch (const hsException& e) {
                plDebug::Error("Failed reading {}: {}",
                               kList[j].toString(), e.what());
                plDebug::Error("Failure on line {}:{}", e.File(), e.Line());
                kList[j]->deleteObj();
            } catch (const std::exception& e) {
                plDebug::Error("Failed reading {}: {}",
                               kList[j].toString(), e.what());
                kList[j]->deleteObj();
            } catch (...) {
                plDebug::Error("Undefined error reading {}",
                               kList[j].toString());
                kList[j]->deleteObj();
            }
            delete subStream;
        }

        if (progressFunc)
            progressFunc(page, processedKeys, totalKeys);
    }

    return nRead;
}

unsigned int plResManager::WriteObjects(hsStream* S, const plLocation& loc)
{
    std::vector<short> types = keys.getTypes(loc);
    unsigned int nWritten = 0;

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc, types[i]);
#ifdef RMTRACE
        plDebug::Debug("* Writing {} objects of type [{_04X}]", kList.size(), types[i]);
#endif
        for (unsigned int j=0; j<kList.size(); j++) {
            kList[j]->setFileOff(S->pos());
            kList[j]->setID(j + 1);
            if (kList[j]->getObj()) {
                try {
#ifdef RMTRACE
                    plDebug::Debug("  * ({}) Writing {} @ 0x{_08X}", j, kList[j]->getName(),
                                   kList[j]->getFileOff());
#endif
                    WriteCreatable(S, kList[j]->getObj());
                    nWritten++;
                } catch (const hsException &e) {
                    plDebug::Error("Failed writing {}: {}",
                                   kList[j].toString(), e.what());
                    plDebug::Error("Failure on line {}:{}", e.File(), e.Line());
                } catch (const std::exception &e) {
                    plDebug::Error("Failed writing {}: {}",
                                   kList[j].toString(), e.what());
                } catch (...) {
                    plDebug::Error("Undefined error writing {}",
                                   kList[j].toString());
                }
            } else {
                WriteCreatable(S, nullptr);
                plDebug::Warning("Object for {} does not exist", kList[j].toString());
            }
            kList[j]->setObjSize(S->pos() - kList[j]->getFileOff());
        }
    }

    return nWritten;
}

plCreatable* plResManager::ReadCreatable(hsStream* S, bool canStub, int stubLen)
{
    unsigned short type = S->readShort();
    plCreatable* pCre;
    if (mustStub) {
        pCre = new plCreatableStub(pdUnifiedTypeMap::PlasmaToMapped(type, S->getVer()), stubLen - 2);
        pCre->read(S, this);
    } else {
        pCre = plFactory::Create(type, S->getVer());
        if (pCre) {
            pCre->read(S, this);
        } else if (type != 0x8000) {
            if (canStub) {
                plDebug::Warning("Warning: Type [{_04X}]{} is a STUB",
                                 pdUnifiedTypeMap::PlasmaToMapped(type, S->getVer()),
                                 pdUnifiedTypeMap::ClassName(type, S->getVer()));
                pCre = new plCreatableStub(pdUnifiedTypeMap::PlasmaToMapped(type, S->getVer()), stubLen - 2);
                pCre->read(S, this);
            } else {
                throw hsNotImplementedException(__FILE__, __LINE__,
                            ST::format("Cannot read unimplemented type [{04X}]{}",
                                       pdUnifiedTypeMap::PlasmaToMapped(type, S->getVer()),
                                       pdUnifiedTypeMap::ClassName(type, S->getVer())));
            }
        }
    }
    return pCre;
}

void plResManager::WriteCreatable(hsStream* S, plCreatable* pCre)
{
    if (pCre == nullptr) {
        S->writeShort(0x8000);
    } else {
        short classIdx = pCre->ClassIndex(S->getVer());
        if (classIdx == -1) {
            plDebug::Warning("Class [{_04X}]{} not available in the requested Plasma version",
                             pCre->ClassIndex(), pCre->ClassName());
            S->writeShort(0x8000);
        } else {
            S->writeShort(classIdx);
            pCre->write(S, this);
        }
    }
}

plCreatable* plResManager::prcParseCreatable(const pfPrcTag* tag)
{
    plCreatable* pCre = plFactory::Create(tag->getName().c_str());
    if (pCre)
        pCre->prcParse(tag, this);
    else
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    return pCre;
}

plSceneNode* plResManager::getSceneNode(const plLocation& loc)
{
    std::vector<plKey> kList = keys.getKeys(loc, kSceneNode);
    if (kList.empty())
        return nullptr;
    return plSceneNode::Convert(kList[0]->getObj());
}

std::vector<plLocation> plResManager::getLocations()
{
    std::vector<plLocation> locArr;
    for (size_t i=0; i<pages.size(); i++)
        locArr.push_back(pages[i]->getLocation());
    return locArr;
}

std::vector<short> plResManager::getTypes(const plLocation& loc, bool checkKeys)
{
    return keys.getTypes(loc, checkKeys);
}

std::vector<plKey> plResManager::getKeys(const plLocation& loc, short type,
                                         bool checkKeys)
{
    return keys.getKeys(loc, type, checkKeys);
}

std::vector<plKey> plResManager::getKeys(short type, bool checkKeys)
{
    std::vector<plKey> kList;
    for (size_t i=0; i<pages.size(); i++) {
        std::vector<plKey> kPageKeys = keys.getKeys(pages[i]->getLocation(), type, checkKeys);
        kList.insert(kList.end(), kPageKeys.begin(), kPageKeys.end());
    }
    return kList;
}

plKey plResManager::AddKey(const plKey& key)
{
    plKey xkey = keys.findKey(key);
    if (xkey.Exists()) {
        return xkey;
    } else {
        keys.add(key);
        return key;
    }
}

void plResManager::AddObject(const plLocation& loc, hsKeyedObject* obj)
{
    obj->getKey()->setLocation(loc);
    AddKey(obj->getKey());
}

void plResManager::DelPage(const plLocation& loc)
{
    std::vector<plPageInfo*>::iterator pi = pages.begin();
    while (pi != pages.end()) {
        if ((*pi)->getLocation() == loc) {
            plPageInfo* page = *pi;
            delete page;
            pi = pages.erase(pi);
        } else {
            pi++;
        }
    }
}

void plResManager::DelAge(const ST::string& name)
{
    std::vector<plAgeInfo*>::iterator ai = ages.begin();
    while (ai != ages.end()) {
        if ((*ai)->getAgeName() == name) {
            plAgeInfo* age = *ai;
            delete age;
            ai = ages.erase(ai);
        } else {
            ai++;
        }
    }
}

void plResManager::ChangeLocation(plLocation from, plLocation to)
{
    to.setVer(from.getVer());
    std::vector<plPageInfo*>::iterator pi;
    for (pi = pages.begin(); pi != pages.end(); pi++) {
        if ((*pi)->getLocation() == from)
            (*pi)->setLocation(to);
    }
    keys.ChangeLocation(from, to);
}

LoadProgressCallback plResManager::SetProgressFunc(LoadProgressCallback newFunc)
{
    LoadProgressCallback old = progressFunc;
    progressFunc = std::move(newFunc);
    return old;
}

PageUnloadCallback plResManager::SetPageUnloadFunc(PageUnloadCallback newFunc)
{
    PageUnloadCallback old = pageUnloadFunc;
    pageUnloadFunc = std::move(newFunc);
    return old;
}
