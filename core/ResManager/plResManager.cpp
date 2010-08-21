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

plResManager::plResManager(PlasmaVer pv) :
    fPlasmaVer(pvUnknown), totalKeys(0), readKeys(0) {
    setVer(pv);
    progressFunc = NULL;
}

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
    if (fPlasmaVer == pvUnknown || force)
        fPlasmaVer = pv;
}

plKey plResManager::readKey(hsStream* S) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    if (S->getVer() < pvEoa || S->getVer() == pvUniversal) {
        if (S->readBool())
            return readUoid(S);
        else
            return plKey();
    } else {
        return readUoid(S);
    }
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
    if (S->getVer() < pvEoa || S->getVer() == pvUniversal)
        S->writeBool(key.Exists());
    if (key.Exists() || (S->getVer() >= pvEoa && S->getVer() != pvUniversal))
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

hsKeyedObject* plResManager::getObject(plKey key) {
    plKey fk = keys.findKey(key);
    if (!fk.Exists())
        return NULL;
    return fk->getObj();
}

plPageInfo* plResManager::ReadPage(const char* filename) {
    hsFileStream* S = new hsFileStream();
    if (!S->open(filename, fmRead))
        throw hsFileReadException(__FILE__, __LINE__, filename);
    plPageInfo* page = new plPageInfo();
    page->read(S);

    for (size_t i=0; i<pages.size(); i++) {
        if (pages[i]->getLocation() == page->getLocation()) {
            delete page;
            return pages[i];
        }
    }

    pages.push_back(page);
    setVer(S->getVer(), true);
    S->seek(page->getIndexStart());
    totalKeys = ReadKeyring(S, page->getLocation());
    readKeys = 0;
    page->setNumObjects(ReadObjects(S, page->getLocation()));
    S->close();
    delete S;
    return page;
}

plPageInfo* plResManager::ReadPageRaw(const char* filename) {
    hsFileStream* S = new hsFileStream();
    if (!S->open(filename, fmRead))
        throw hsFileReadException(__FILE__, __LINE__, filename);
    plPageInfo* page = new plPageInfo();
    page->read(S);

    for (size_t i=0; i<pages.size(); i++) {
        if (pages[i]->getLocation() == page->getLocation()) {
            delete page;
            return pages[i];
        }
    }

    pages.push_back(page);
    setVer(S->getVer(), true);
    S->seek(page->getIndexStart());
    ReadKeyring(S, page->getLocation());
    //page->setNumObjects(ReadObjects(S, page->getLocation()));
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

    for (size_t i=0; i<pages.size(); i++) {
        if (pages[i]->getLocation() == page->getLocation()) {
            delete page;
            return pages[i];
        }
    }

    pages.push_back(page);
    return page;
}

void plResManager::WritePage(const char* filename, plPageInfo* page) {
    hsFileStream* S = new hsFileStream();
    S->open(filename, fmWrite);
    S->setVer(getVer());
    if (getVer() >= pvLive && getVer() != pvUniversal) {
        std::vector<short> types = keys.getTypes(page->getLocation());
        page->setClassList(types);
    }
    //keys.sortKeys(page->getLocation());
    page->write(S);
    page->setDataStart(S->pos());
    page->setNumObjects(WriteObjects(S, page->getLocation()));
    page->setIndexStart(S->pos());
    WriteKeyring(S, page->getLocation());
    if (getVer() >= pvEoa)
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
    keys.delAll(loc);
    DelPage(loc);
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

        PlasmaVer ageVer = pvUnknown;
        if (age->getNumPages() > 0) {
            plString file = plString::Format("%s_District_%s.prp",
                    age->getAgeName().cstr(),
                    age->getPage(0).fName.cstr());
            if (hsFileStream::FileExists(path + file))
                ageVer = pvPots;
            else
                ageVer = pvEoa;
        }

        size_t numpages = age->getNumPages() + age->getNumCommonPages(ageVer);
        plPageStream* pageStreams = new plPageStream[numpages];
        hsFileStream* S = NULL;
        totalKeys = 0;
        readKeys = 0;

        for (size_t i=0; i<age->getNumPages(); i++) {
            if (hsFileStream::FileExists(path + age->getPageFilename(i, ageVer))) {
                //ReadPage(path + age->getPageFilename(i, ageVer));
                S = new hsFileStream();
                if (!S->open(path + age->getPageFilename(i, ageVer), fmRead))
                    throw hsFileReadException(__FILE__, __LINE__, filename);
                plPageInfo* page = new plPageInfo();
                page->read(S);

                pageStreams[i] = plPageStream();
                pageStreams[i].stream = S;

                for (size_t j=0; j<pages.size(); j++) {
                    if (pages[j]->getLocation() == page->getLocation()) {
                        delete page;
                        pageStreams[i].page = pages[j];
                        continue;
                    }
                }
                pageStreams[i].page = page;

                pages.push_back(page);
                setVer(S->getVer(), true);
                S->seek(page->getIndexStart());
                totalKeys += ReadKeyring(S, page->getLocation());
            }
        }

        for (size_t i=0; i<age->getNumCommonPages(ageVer); i++) {
            if (hsFileStream::FileExists(path + age->getCommonPageFilename(i, ageVer)))
                //ReadPage(path + age->getCommonPageFilename(i, ageVer));
                S = new hsFileStream();
                if (!S->open(path + age->getCommonPageFilename(i, ageVer), fmRead))
                    throw hsFileReadException(__FILE__, __LINE__, filename);
                plPageInfo* page = new plPageInfo();
                page->read(S);

                pageStreams[numpages - 1 - i] = plPageStream();
                pageStreams[numpages - 1 - i].stream = S;

                for (size_t j=0; j<pages.size(); j++) {
                    if (pages[j]->getLocation() == page->getLocation()) {
                        delete page;
                        pageStreams[numpages - 1 - i].page = pages[j];
                        continue;
                    }
                }
                pageStreams[numpages - 1 - i].page = page;

                pages.push_back(page);
                setVer(S->getVer(), true);
                S->seek(page->getIndexStart());
                totalKeys += ReadKeyring(S, page->getLocation());
        }

        for (size_t i=0; i < numpages; i++) {
            pageStreams[i].page->setNumObjects(
                    ReadObjects(pageStreams[i].stream,
                        pageStreams[i].page->getLocation()));
            pageStreams[i].stream->close();
            delete pageStreams[i].stream;
        }
        delete pageStreams;

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
            keys.delAll((*pi)->getLocation());
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
        if (S->getVer() >= pvLive && S->getVer() != pvUniversal) {
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
        if (S->getVer() >= pvLive && S->getVer() != pvUniversal) {
            S->writeInt(0);
            S->writeByte(0);
        }
        S->writeInt(kList.size());
        for (unsigned int j=0; j<kList.size(); j++)
            kList[j]->write(S);
        if (S->getVer() >= pvLive && S->getVer() != pvUniversal) {
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
            try {
                plCreatable* pCre = ReadCreatable(S, true, kList[j]->getObjSize());
                if (pCre != NULL && pCre->isStub()) {
                    plCreatableStub* stub = (plCreatableStub*)pCre;
                    hsKeyedObjectStub* ko = new hsKeyedObjectStub();
                    hsRAMStream RS(S->getVer());
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
                    if (kList[j]->getObjSize() != S->pos() - kList[j]->getFileOff()) {
                        plDebug::Warning("[%04hX:%s] Size-Read difference: %d bytes",
                            kList[j]->getType(), kList[j]->getName().cstr(),
                            (int)(kList[j]->getObjSize() -
                                  (S->pos() - kList[j]->getFileOff())));
                        plDebug::Debug("At: 0x%08X (%d bytes)",
                            kList[j]->getFileOff(),
                            kList[j]->getObjSize());
                    }
                }
            } catch (const hsException& e) {
                plDebug::Error("Failed reading %s: %s",
                               kList[j]->toString().cstr(), e.what());
                plDebug::Debug("Failure on line %s:%d", e.File(), e.Line());
                delete kList[j]->getObj();
                kList[j]->setObj(NULL);
            } catch (const std::exception& e) {
                plDebug::Error("Failed reading %s: %s",
                               kList[j]->toString().cstr(), e.what());
                delete kList[j]->getObj();
                kList[j]->setObj(NULL);
            } catch (...) {
                plDebug::Error("Undefined error reading %s",
                               kList[j]->toString().cstr());
                delete kList[j]->getObj();
                kList[j]->setObj(NULL);
            }
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
                } catch (const char* e) {
                    plDebug::Error("Failed writing %s: %s",
                                   kList[j]->toString().cstr(), e);
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
    plCreatable* pCre = plFactory::Create(type, S->getVer());
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

void plResManager::MoveKey(plKey key, const plLocation& to) {
    keys.MoveKey(key, to);
}

void plResManager::AddObject(const plLocation& loc, hsKeyedObject* obj) {
    obj->getKey()->setLocation(loc);
    keys.add(obj->getKey());
}

void plResManager::AddPage(plPageInfo* page) {
    pages.push_back(page);
}

void plResManager::AddAge(plAgeInfo* age) {
    ages.push_back(age);
}

void plResManager::DelObject(plKey obj) {
    keys.del(obj);
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
