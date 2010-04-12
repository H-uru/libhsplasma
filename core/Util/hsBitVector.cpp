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

#include "hsBitVector.h"
#include <cstring>

/* hsBitVector::Bit */
hsBitVector::Bit::Bit(hsBitVector* vec, unsigned int off)
           : fVector(vec), fOffset(off) { }

bool hsBitVector::Bit::operator==(bool value) const {
    return fVector->get(fOffset) == value;
}

hsBitVector::Bit& hsBitVector::Bit::operator=(bool value) {
    fVector->set(fOffset, value);
    return *this;
}


/* hsBiVector */
hsBitVector::hsBitVector() : fBits(NULL), fNumVectors(0) { }

hsBitVector::hsBitVector(const hsBitVector& init)
           : fNumVectors(init.fNumVectors) {
    fBits = new hsUint32[fNumVectors];
    memcpy(fBits, init.fBits, fNumVectors * sizeof(hsUint32));
}

hsBitVector::~hsBitVector() {
    delete[] fBits;

    std::map<unsigned int, char*>::iterator it;
    for (it = fBitNames.begin(); it != fBitNames.end(); it++)
        free(it->second);
}

bool hsBitVector::get(unsigned int idx) const {
    if ((idx / BVMULT) >= fNumVectors)
        return false;
    return (fBits[idx / BVMULT] & (1 << (idx & BVMASK))) != 0;
}

void hsBitVector::set(unsigned int idx, bool b) {
    if ((idx / BVMULT) >= fNumVectors) {
        size_t oldNumVectors = fNumVectors;
        fNumVectors = (idx / BVMULT) + 1;
        hsUint32* newBits = new hsUint32[fNumVectors];
        if (fBits != NULL) {
            for (size_t i=0; i<oldNumVectors; i++)
                newBits[i] = fBits[i];
            for (size_t i=oldNumVectors; i<fNumVectors; i++)
                newBits[i] = 0;
            delete[] fBits;
        } else {
            memset(newBits, 0, sizeof(hsUint32)*fNumVectors);
        }
        fBits = newBits;
    }
    if (b) fBits[idx / BVMULT] |=  (1 << (idx & BVMASK));
    else   fBits[idx / BVMULT] &= ~(1 << (idx & BVMASK));
}

hsBitVector& hsBitVector::operator=(const hsBitVector& cpy) {
    delete[] fBits;
    fNumVectors = cpy.fNumVectors;
    fBits = new hsUint32[fNumVectors];
    memcpy(fBits, cpy.fBits, fNumVectors * sizeof(hsUint32));
    return *this;
}

void hsBitVector::clear() {
    delete[] fBits;
    fBits = NULL;
    fNumVectors = 0;
}

void hsBitVector::compact() {
    size_t newNumVectors = fNumVectors;
    while (newNumVectors > 0 && fBits[newNumVectors-1] == 0)
        newNumVectors--;
    if (newNumVectors < fNumVectors) {
        if (newNumVectors == 0) {
            clear();
        } else {
            hsUint32* newBits = new hsUint32[newNumVectors];
            memcpy(newBits, fBits, sizeof(hsUint32)*newNumVectors);
            delete[] fBits;
            fBits = newBits;
            fNumVectors = newNumVectors;
        }
    }
}

const char* hsBitVector::getName(unsigned int idx) {
    static char tempName[11];
    if (fBitNames.count(idx) > 0) {
        return fBitNames[idx];
    } else {
        snprintf(tempName, 11, "%u", idx);
        return tempName;
    }
}

unsigned int hsBitVector::getValue(const char* name) {
    std::map<unsigned int, char*>::iterator i;
    for (i = fBitNames.begin(); i != fBitNames.end(); i++) {
        if (strcmp(i->second, name) == 0)
            return i->first;
    }
    return (unsigned int)plString(name).toUint();
}

void hsBitVector::setName(unsigned int idx, const char* name) {
    if (fBitNames.find(idx) != fBitNames.end())
        free(fBitNames[idx]);
    fBitNames[idx] = strdup(name);
}

void hsBitVector::read(hsStream* S) {
    fNumVectors = S->readInt();
    delete[] fBits;
    if (fNumVectors > 0)
        fBits = new hsUint32[fNumVectors];
    for (size_t i=0; i<fNumVectors; i++)
        fBits[i] = S->readInt();
}

void hsBitVector::write(hsStream* S) {
    compact();
    S->writeInt(fNumVectors);
    for (size_t i=0; i<fNumVectors; i++)
        S->writeInt(fBits[i]);
}

void hsBitVector::prcWrite(pfPrcHelper* prc) {
    prc->writeTagNoBreak("hsBitVector");
    for (size_t i=0; i<fNumVectors; i++) {
        for (unsigned int j=0; j<BVMULT; j++) {
            if (get((i*BVMULT) + j)) {
                prc->getStream()->writeStr(getName((i*BVMULT) + j));
                prc->getStream()->writeStr(" ");
            }
        }
    }
    prc->closeTagNoBreak();
}

void hsBitVector::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsBitVector")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    hsTList<plString> flags = tag->getContents();
    while (!flags.empty())
        setBit(getValue(flags.pop()));
}
