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

#ifndef _PLKEY_HPP
#define _PLKEY_HPP

#include "plUoid.h"

template <class kobj_type = hsKeyedObject>
DllClass plKey {
private:
    struct _ref {
        plUoid fUoid;
        kobj_type* fObjPtr;

        hsUint32 fFileOff, fObjSize;
        hsUint32 fRefCnt;

        void ref() { ++fRefCnt; }
        void unref() {
            if (--fRefCnt == 0)
                delete this;
        }
    };
    _ref* fKeyData;

public:
    plKey() : fKeyData(NULL) { }

    ~plKey<kobj_type>() {
        if (fKeyData != NULL)
            fKeyData->unref();
    }

    static plKey<kobj_type> Create() {
        plKey<kobj_type> key;
        key.fKeyData = new _ref();
        key.fKeyData->fObjPtr = NULL;
        key.fKeyData->fFileOff = 0;
        key.fKeyData->fObjSize = 0;
        key.fKeyData->fRefCnt = 1;
        return key;
    }
};

#endif
