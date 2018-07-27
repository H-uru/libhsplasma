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

#include <stdlib.h>
#include <string.h>
#include "plKey.h"
#include "hsKeyedObject.h"
#include "Debug/plDebug.h"

/* plKeyData */
void plKeyData::read(hsStream* S) {
    fUoid.read(S);
    fFileOff = S->readInt();
    fObjSize = S->readInt();
}

void plKeyData::write(hsStream* S) {
    fUoid.write(S);
    S->writeInt(fFileOff);
    S->writeInt(fObjSize);
}

void plKeyData::prcWriteUoid(pfPrcHelper* prc) {
    fUoid.prcWrite(prc);
}

plKeyData* plKeyData::PrcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plKey")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    if (!tag->getParam("NULL", "false").to_bool()) {
        plKeyData* key = new plKeyData();
        key->fUoid.prcParse(tag);
        return key;
    } else {
        return NULL;
    }
}

void plKeyData::UnRef() {
    if (--fRefCnt == 0) {
        //plDebug::Debug("Key %s no longer in use, deleting...", toString());
        delete this;
    }
}

void plKeyData::setObj(class hsKeyedObject* obj) {
    if (obj == fObjPtr)
        return;

    if (fObjPtr != NULL && !fObjPtr->isStub())
        throw hsBadParamException(__FILE__, __LINE__, "Trying to change already loaded object");

    fObjPtr = obj;

    if (obj && !obj->isStub()) {
        for (auto it = fCallbacks.begin(); it != fCallbacks.end(); it++)
            (*it)(obj);

        fCallbacks.clear();
    }
}

void plKeyData::deleteObj() {
    delete fObjPtr;
    fObjPtr = 0;
}

void plKeyData::addCallback(AfterLoadCallback callback) {
    if (fObjPtr != NULL)
        callback(fObjPtr);
    else
        fCallbacks.push_back(callback);
}

/* plKey */
plKey::plKey(const plKey& init) : fKeyData(init.fKeyData) {
    if (fKeyData != NULL)
        fKeyData->Ref();
}

plKey::plKey(plKeyData* init) : fKeyData(init) {
    if (fKeyData != NULL)
        fKeyData->Ref();
}

plKey::~plKey() {
    if (fKeyData != NULL)
        fKeyData->UnRef();
}

plKey& plKey::operator=(const plKey& other) {
    if (fKeyData != other.fKeyData) {
        if (other.fKeyData != NULL)
            other->Ref();
        if (fKeyData != NULL)
            fKeyData->UnRef();
        fKeyData = other.fKeyData;
    }
    return *this;
}

plKey& plKey::operator=(plKeyData* other) {
    if (fKeyData != other) {
        if (other != NULL)
            other->Ref();
        if (fKeyData != NULL)
            fKeyData->UnRef();
        fKeyData = other;
    }
    return *this;
}

bool plKey::isLoaded() const {
    if (!Exists())
        return true;
    return fKeyData->getObj() != NULL;
}

ST::string plKey::toString() const {
    if (!Exists())
        return "NULL";
    return fKeyData->getUoid().toString();
}

bool plKey::orderAfter(const plKey& other) const {
    if (!Exists() || !other.Exists())
        return false;
    if (!isLoaded() || !other.isLoaded())
        return false;

    return fKeyData->getObj()->orderAfter(other.fKeyData->getObj());
}

std::vector<plKey> hsOrderKeys(const std::vector<plKey>& keys) {
    // std::sort cannot be used here, since hsKeyedObject::orderAfter does
    // not provide strict weak ordering, which is required for std::sort
    // to work correctly.  Instead, we perform a stable topological sort.
    // TODO: This algorithm could probably be more efficient.
    std::vector<plKey> result;
    result.reserve(keys.size());
    std::list<plKey> input = std::list<plKey>(keys.begin(), keys.end());

    while (!input.empty()) {
        auto lowest = input.begin();
        auto iter = lowest;
        while (iter != input.end()) {
            if (lowest->orderAfter(*iter)) {
                lowest = iter;
                iter = input.begin();
            } else {
                ++iter;
            }
        }
        result.push_back(*lowest);
        input.erase(lowest);
    }

    return result;
}
