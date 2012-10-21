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

plResManager::~plResManager() {
    if (ages.size() > 0 || pages.size() > 0)
        plDebug::Debug("~plResManager: cleaning up %d ages and %d pages",
                       ages.size(), pages.size());
    while (ages.size() > 0)
        UnloadAge(ages[0]->getAgeName());
    while (pages.size() > 0)
        UnloadPage(pages[0]->getLocation());
}

void plResManager::setVer(PlasmaVer pv, bool force) {
    if (fPlasmaVer == PlasmaVer::pvUnknown || force)
        fPlasmaVer = pv;
}

plKey plResManager::readKey(hsStream* S) {
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

plKey plResManager::readKeyNotify(hsStream* S,  const plKeyData::AfterLoadCallback& callback) {
    plKey key = readKey(S);
    key->addCallback(callback);
    return key;
}

plKey plResManager::readUoid(hsStream* S) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    plKey k = new plKeyData();
    k->readUoid(S);
    if (!k->getLocation().isValid())
        return plKey();
    return AddKey(k);
}

void plResManager::writeKey(hsStream* S, plKey key) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    //key->exists = (strcmp(key->objName, "") != 0);
    if (S->getVer().isUru() || S->getVer().isUniversal())
        S->writeBool(key.Exists());
    if (key.Exists() || (S->getVer().isNewPlasma()))
        writeUoid(S, key);
}

void plResManager::writeKey(hsStream* S, hsKeyedObject* ko) {
    writeKey(S, ko->getKey());
}

void plResManager::writeUoid(hsStream* S, plKey key) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    if (!key.Exists()) {
        plKey empty = new plKeyData();
        empty->writeUoid(S);
    } else {
        key->writeUoid(S);
    }
}

void plResManager::writeUoid(hsStream* S, hsKeyedObject* ko) {
    writeUoid(S, ko->getKey());
}

plKey plResManager::prcParseKey(const pfPrcTag* tag) {
    plKey k = plKeyData::PrcParse(tag);
    if (k.Exists())
        return AddKey(k);
    return k;
}

plKey plResManager::prcParseKeyNotify(const pfPrcTag* tag, const plKeyData::AfterLoadCallback& callback) {
    plKey key = prcParseKey(tag);
    key->addCallback(callback);
    return key;
}

hsKeyedObject* plResManager::getObject(plKey key) {
    plKey fk = keys.findKey(key);
    if (!fk.Exists())
        return NULL;
    return fk->getObj();
}

plPageInfo* plResManager::ReadPage(const char* filename, bool stub) {
    bool packed = true;
    plString file = plString(filename);

    if (!file.endsWith(".prp", true)) {
        if (file.endsWith(".prx", true) || file.endsWith(".prm", true)) {
            packed = false;
            file = file.beforeLast('.');
            if (!hsFileStream::FileExists(file + ".prx"))
                throw hsFileReadException(__FILE__, __LINE__,
                        (file+".prx").cstr());
            if (!hsFileStream::FileExists(file + ".prm"))
                throw hsFileReadException(__FILE__, __LINE__,
                        (file+".prm").cstr());

            file += ".prx";
        } else {
            throw hsBadParamException(__FILE__, __LINE__,
                plString::Format("%s is not a valid Page file", file.cstr()).cstr());
        }
    }

    hsFileStream* S = new hsFileStream();
    if (!S->open(file, fmRead))
        throw hsFileReadException(__FILE__, __LINE__, file.cstr());
    plPageInfo* page = new plPageInfo();
    page->read(S);

    const plLocation& loc = page->getLocation();
    UnloadPage(loc);

    pages.push_back(page);
    setVer(S->getVer(), true);
    S->seek(page->getIndexStart());
    totalKeys = ReadKeyring(S, loc);
    if (!packed) {
        S->close();
        delete S;
        file = file.beforeLast('.') + ".prm";
        S = new hsFileStream();
        S->setVer(getVer());
        if (!S->open(file, fmRead))
            throw hsFileReadException(__FILE__, __LINE__, file.cstr());
    }
    readKeys = 0;
    mustStub = stub;
    page->setNumObjects(ReadObjects(S, loc));
    mustStub = false;
    S->close();
    delete S;
    return page;
}

plPageInfo* plResManager::ReadPagePrc(const pfPrcTag* root) {
    plPageInfo* page = new plPageInfo();
    page->prcParse(root);

    const pfPrcTag* tag = root->getFirstChild();
    while (tag != NULL) {
        hsKeyedObject* ko = hsKeyedObject::Convert(prcParseCreatable(tag));
        if (ko != NULL)
            ko->getKey()->setObj(ko);
        tag = tag->getNextSibling();
    }

    UnloadPage(page->getLocation());
    pages.push_back(page);
    return page;
}

void plResManager::WritePage(const char* filename, plPageInfo* page) {
    hsFileStream* S = new hsFileStream();
    S->open(filename, fmWrite);
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
    S->close();
    delete S;
}

void plResManager::WritePagePrc(pfPrcHelper* prc, plPageInfo* page) {
    page->prcWrite(prc); // starts <Page>

    // Objects:
    std::vector<short> types = keys.getTypes(page->getLocation());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(page->getLocation(), types[i]);
        for (unsigned int j=0; j<kList.size(); j++) {
            if (kList[j]->getObj() != NULL)
                kList[j]->getObj()->prcWrite(prc);
        }
    }

    prc->closeTag();
}

plPageInfo* plResManager::FindPage(const plLocation& loc) {
    std::vector<plPageInfo*>::iterator pi = pages.begin();
    while (pi != pages.end()) {
        if ((*pi)->getLocation() == loc)
            return *pi;
        pi++;
    }
    return NULL;
}

void plResManager::UnloadPage(const plLocation& loc) {
    for (auto it = pages.begin(); it != pages.end(); it++) {
        if ((*it)->getLocation() == loc) {
            if (pageUnloadFunc !=  NULL)
                pageUnloadFunc(loc);
            delete *it;
            pages.erase(it);
            keys.delAll(loc);
            break;
        }
    }
}

unsigned int plResManager::ReadPage(hsStream* S, std::vector<plPageInfo*>& agepages) {
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

plAgeInfo* plResManager::ReadAge(const char* filename, bool readPages) {
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
        plString path = plString(filename).beforeLast(PATHSEP);
        if (path.len() > 0)
            path = path + PATHSEPSTR;

        PlasmaVer ageVer = PlasmaVer::pvUnknown;
        bool packed = true;
        if (age->getNumPages() > 0) {
            plString file = plString::Format("%s_District_%s",
                    age->getAgeName().cstr(),
                    age->getPage(0).fName.cstr());
            if (hsFileStream::FileExists(path + file + ".prp")) {
                ageVer = MAKE_VERSION(2, 0, 63, 12);
            } else if (hsFileStream::FileExists(path + file + ".prx")) {
                ageVer = MAKE_VERSION(2, 0, 63, 12);
                packed = false;
            } else {
                ageVer = MAKE_VERSION(2, 1, 6, 10);
            }
        }

        hsFileStream* S = NULL;
        std::vector<plPageInfo*> agepages;
        totalKeys = 0;
        readKeys = 0;

        for (size_t i=0; i<age->getNumPages(); i++) {
            if (hsFileStream::FileExists(path + age->getPageFilename(i, ageVer))) {
                S = new hsFileStream();
                if (!S->open(path + age->getPageFilename(i, ageVer), fmRead)) {
                    throw hsFileReadException(__FILE__, __LINE__, filename);
                }
                totalKeys += ReadPage(S, agepages);
                S->close();
                delete S;
            }
        }

        for (size_t i=0; i<age->getNumCommonPages(ageVer); i++) {
            if (hsFileStream::FileExists(path + age->getCommonPageFilename(i, ageVer))) {
                S = new hsFileStream();
                if (!S->open(path + age->getCommonPageFilename(i, ageVer), fmRead)) {
                    throw hsFileReadException(__FILE__, __LINE__, filename);
                }
                totalKeys += ReadPage(S, agepages);
                S->close();
                delete S;
            }
        }

        for (size_t i=0; i < agepages.size(); i++) {
            S = new hsFileStream();
            S->setVer(getVer());
            plString file = path + agepages[i]->getFilename(ageVer);
            if (!packed) {
                file = file.beforeLast('.') + ".prm";
            }

            if (!S->open(file, fmRead)) {
                throw hsFileReadException(__FILE__, __LINE__, filename);
            }

            agepages[i]->setNumObjects(
                    ReadObjects(S, agepages[i]->getLocation()));

            S->close();
            delete S;
        }

#ifdef DEBUG
        if (totalKeys != readKeys) {
            plDebug::Error("* Keyring count %d but we could only read %d",
                           totalKeys, readKeys);
        }
#endif
    }

    ages.push_back(age);
    return age;
}

plAgeInfo* plResManager::ReadAgePrc(const pfPrcTag* root) {
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

void plResManager::WriteAge(const char* filename, plAgeInfo* age) {
    plString path = filename;
    plString ageName = path.afterLast(PATHSEP);
    if (!ageName.beforeLast('.').empty())
        ageName = ageName.beforeLast('.');
    age->setAgeName(ageName);
    age->writeToFile(path, getVer());
}

void plResManager::WriteAgePrc(pfPrcHelper* prc, plAgeInfo* age) {
    age->prcWrite(prc);
}

plAgeInfo* plResManager::FindAge(const plString& name) {
    std::vector<plAgeInfo*>::iterator ai = ages.begin();
    while (ai != ages.end()) {
        if ((*ai)->getAgeName() == name)
            return *ai;
        ai++;
    }
    return NULL;
}

void plResManager::UnloadAge(const plString& name) {
    std::vector<plPageInfo*>::iterator pi = pages.begin();
    while (pi != pages.end()) {
        if ((*pi)->getAge() == name) {
            const plLocation& loc = (*pi)->getLocation();
            if (pageUnloadFunc != NULL)
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

unsigned int plResManager::ReadKeyring(hsStream* S, const plLocation& loc) {
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
        plDebug::Debug("  * Indexing %d objects of type [%04hX]%s", oCount, type,
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

void plResManager::WriteKeyring(hsStream* S, const plLocation& loc) {
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

unsigned int plResManager::ReadObjects(hsStream* S, const plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc);
    unsigned int nRead = 0;

    if (progressFunc != NULL)
        progressFunc(0.0f);

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc, types[i]);
#ifdef RMTRACE
        plDebug::Debug("* Reading %d objects of type [%04hX]%s", kList.size(),
                       types[i], pdUnifiedTypeMap::ClassName(types[i]));
#endif
        for (unsigned int j=0; j<kList.size(); j++) {
            if (kList[j]->getFileOff() <= 0)
                continue;
#ifdef RMTRACE
            plDebug::Debug("  * (%d) Reading %s @ 0x%08X", j, kList[j]->getName().cstr(),
                           kList[j]->getFileOff());
#endif
            S->seek(kList[j]->getFileOff());
            uint32_t len = kList[j]->getObjSize();
            pfSizedStream *subStream = new pfSizedStream(S, len);
            try {
                plCreatable* pCre = ReadCreatable(subStream, true, len);
                if (pCre != NULL && pCre->isStub()) {
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
                if (kList[j]->getObj() != NULL) {
                    nRead++;
                    readKeys++;
                    if (!subStream->eof()) {
                        plDebug::Warning("[%04hX:%s] Size-Read difference: %d bytes left after reading",
                            kList[j]->getType(), kList[j]->getName().cstr(),
                            (int)(subStream->size() - (subStream->pos())));
                        plDebug::Debug("At: 0x%08X (%d bytes)",
                            kList[j]->getFileOff(),
                            kList[j]->getObjSize());
                    }
                }
            } catch (const hsException& e) {
                plDebug::Error("Failed reading %s: %s",
                               kList[j]->toString().cstr(), e.what());
                plDebug::Error("Failure on line %s:%d", e.File(), e.Line());
                kList[j]->deleteObj();
            } catch (const std::exception& e) {
                plDebug::Error("Failed reading %s: %s",
                               kList[j]->toString().cstr(), e.what());
                kList[j]->deleteObj();
            } catch (...) {
                plDebug::Error("Undefined error reading %s",
                               kList[j]->toString().cstr());
                kList[j]->deleteObj();
            }
            delete subStream;
        }

        if (progressFunc != NULL)
            progressFunc((float)(readKeys)/(totalKeys));
    }

    return nRead;
}

unsigned int plResManager::WriteObjects(hsStream* S, const plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc);
    unsigned int nWritten = 0;

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc, types[i]);
#ifdef RMTRACE
        plDebug::Debug("* Writing %d objects of type [%04hX]", kList.size(), types[i]);
#endif
        for (unsigned int j=0; j<kList.size(); j++) {
            kList[j]->setFileOff(S->pos());
            kList[j]->setID(j + 1);
            if (kList[j]->getObj() != NULL) {
                try {
#ifdef RMTRACE
                    plDebug::Debug("  * (%d) Writing %s @ 0x%08X", j, kList[j]->getName().cstr(),
                                   kList[j]->getFileOff());
#endif
                    WriteCreatable(S, kList[j]->getObj());
                    nWritten++;
                } catch (const hsException &e) {
                    plDebug::Error("Failed writing %s: %s",
                                   kList[j]->toString().cstr(), e.what());
                    plDebug::Error("Failure on line %s:%d", e.File(), e.Line());
                } catch (const std::exception &e) {
                    plDebug::Error("Failed writing %s: %s",
                                   kList[j]->toString().cstr(), e.what());
                } catch (...) {
                    plDebug::Error("Undefined error writing %s",
                                   kList[j]->toString().cstr());
                }
            } else {
                WriteCreatable(S, NULL);
                plDebug::Warning("Object for %s does not exist", kList[j]->toString().cstr());
            }
            kList[j]->setObjSize(S->pos() - kList[j]->getFileOff());
        }
    }

    return nWritten;
}

plCreatable* plResManager::ReadCreatable(hsStream* S, bool canStub, int stubLen) {
    unsigned short type = S->readShort();
    plCreatable* pCre;
    if (mustStub) {
        pCre = new plCreatableStub(pdUnifiedTypeMap::PlasmaToMapped(type, S->getVer()), stubLen - 2);
        pCre->read(S, this);
    } else {
        pCre = plFactory::Create(type, S->getVer());
        if (pCre != NULL) {
            pCre->read(S, this);
        } else if (type != 0x8000) {
            if (canStub) {
                plDebug::Warning("Warning: Type [%04hX]%s is a STUB",
                                 pdUnifiedTypeMap::PlasmaToMapped(type, S->getVer()),
                                 pdUnifiedTypeMap::ClassName(type, S->getVer()));
                pCre = new plCreatableStub(pdUnifiedTypeMap::PlasmaToMapped(type, S->getVer()), stubLen - 2);
                pCre->read(S, this);
            } else {
                throw hsNotImplementedException(__FILE__, __LINE__,
                            plString::Format("Cannot read unimplemented type [%04hX]%s",
                                             pdUnifiedTypeMap::PlasmaToMapped(type, S->getVer()),
                                             pdUnifiedTypeMap::ClassName(type, S->getVer())));
            }
        }
    }
    return pCre;
}

void plResManager::WriteCreatable(hsStream* S, plCreatable* pCre) {
    if (pCre == NULL) {
        S->writeShort(0x8000);
    } else {
        short classIdx = pCre->ClassIndex(S->getVer());
        if (classIdx == -1) {
            plDebug::Warning("Class [%04hX]%s not available in the requested Plasma version",
                             pCre->ClassIndex(), pCre->ClassName());
            S->writeShort(0x8000);
        } else {
            S->writeShort(classIdx);
            pCre->write(S, this);
        }
    }
}

plCreatable* plResManager::prcParseCreatable(const pfPrcTag* tag) {
    plCreatable* pCre = plFactory::Create(tag->getName());
    if (pCre != NULL)
        pCre->prcParse(tag, this);
    return pCre;
}

plSceneNode* plResManager::getSceneNode(const plLocation& loc) {
    std::vector<plKey> kList = keys.getKeys(loc, kSceneNode);
    if (kList.size() < 1)
        return NULL;
    return plSceneNode::Convert(kList[0]->getObj());
}

std::vector<plLocation> plResManager::getLocations() {
    std::vector<plLocation> locArr;
    for (size_t i=0; i<pages.size(); i++)
        locArr.push_back(pages[i]->getLocation());
    return locArr;
}

std::vector<short> plResManager::getTypes(const plLocation& loc, bool checkKeys) {
    return keys.getTypes(loc, checkKeys);
}

std::vector<plKey> plResManager::getKeys(const plLocation& loc, short type,
                                         bool checkKeys) {
    return keys.getKeys(loc, type, checkKeys);
}

std::vector<plKey> plResManager::getKeys(short type, bool checkKeys) {
    std::vector<plKey> kList;
    for (size_t i=0; i<pages.size(); i++) {
        std::vector<plKey> kPageKeys = keys.getKeys(pages[i]->getLocation(), type, checkKeys);
        kList.insert(kList.end(), kPageKeys.begin(), kPageKeys.end());
    }
    return kList;
}

plKey plResManager::AddKey(plKey key) {
    plKey xkey = keys.findKey(key);
    if (xkey.Exists()) {
        return xkey;
    } else {
        keys.add(key);
        return key;
    }
}

void plResManager::AddObject(const plLocation& loc, hsKeyedObject* obj) {
    obj->getKey()->setLocation(loc);
    AddKey(obj->getKey());
}

void plResManager::DelPage(const plLocation& loc) {
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

void plResManager::DelAge(const plString& name) {
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

void plResManager::ChangeLocation(plLocation from, plLocation to) {
    to.setVer(from.getVer());
    std::vector<plPageInfo*>::iterator pi;
    for (pi = pages.begin(); pi != pages.end(); pi++) {
        if ((*pi)->getLocation() == from)
            (*pi)->setLocation(to);
    }
    keys.ChangeLocation(from, to);
}

ProgressCallback plResManager::SetProgressFunc(ProgressCallback newFunc) {
    ProgressCallback old = progressFunc;
    progressFunc = newFunc;
    return old;
}

PageUnloadCallback plResManager::SetPageUnloadFunc(PageUnloadCallback newFunc) {
    PageUnloadCallback old = pageUnloadFunc;
    pageUnloadFunc = newFunc;
    return old;
}
