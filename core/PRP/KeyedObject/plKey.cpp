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
plKeyData::plKeyData() : fUoid(), fObjPtr(NULL), fFileOff(0), fObjSize(0),
                         fRefCnt(0) { }

bool plKeyData::operator==(plKeyData& other) const {
    return (fUoid == other.fUoid);
}

plString plKeyData::toString() const {
    if (this == NULL)
        return "NULL";
    return fUoid.toString();
}

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

void plKeyData::readUoid(hsStream* S) {
    fUoid.read(S);
}

void plKeyData::writeUoid(hsStream* S) {
    fUoid.write(S);
}

void plKeyData::prcWrite(pfPrcHelper* prc) {
    if (this == NULL || !getLocation().isValid()) {
        prc->startTag("plKey");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    } else {
        fUoid.prcWrite(prc);
    }
}

plKeyData* plKeyData::PrcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plKey")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    if (!tag->getParam("NULL", "false").toBool()) {
        plKeyData* key = new plKeyData();
        key->fUoid.prcParse(tag);
        return key;
    } else {
        return NULL;
    }
}

void plKeyData::UnRef() {
    if (--fRefCnt == 0) {
        //plDebug::Debug("Key %s no longer in use, deleting...", toString().cstr());
        delete this;
    }
}


/* plKey */
plKey::plKey() : fKeyData(NULL) { }

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

bool plKey::operator==(const plKey& other) const {
    return fKeyData == other.fKeyData;
}

bool plKey::operator==(const plKeyData* other) const {
    return fKeyData == other;
}

bool plKey::operator!=(const plKey& other) const {
    return fKeyData != other.fKeyData;
}

bool plKey::operator!=(const plKeyData* other) const {
    return fKeyData != other;
}

bool plKey::operator<(const plKey& other) const {
    return fKeyData->getUoid() < other->getUoid();
}

bool plKey::Exists() const {
    return (fKeyData != NULL);
}

bool plKey::isLoaded() const {
    if (!Exists())
        return true;
    return fKeyData->getObj() != NULL;
}
