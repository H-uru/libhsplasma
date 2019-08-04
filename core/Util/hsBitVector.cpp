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
bool hsBitVector::Bit::operator==(bool value) const
{
    return fVector.get(fOffset) == value;
}

hsBitVector::Bit& hsBitVector::Bit::operator=(bool value)
{
    fVector.set(fOffset, value);
    return *this;
}


/* hsBiVector */
bool hsBitVector::get(size_t idx) const
{
    if ((idx / BIT_VEC_WORD) >= fBits.size())
        return false;
    return (fBits[idx / BIT_VEC_WORD] & (1 << (idx & BIT_VEC_MASK))) != 0;
}

void hsBitVector::set(size_t idx, bool b)
{
    if ((idx / BIT_VEC_WORD) >= fBits.size())
        fBits.resize((idx / BIT_VEC_WORD) + 1, 0);

    if (b)
        fBits[idx / BIT_VEC_WORD] |=  (1 << (idx & BIT_VEC_MASK));
    else
        fBits[idx / BIT_VEC_WORD] &= ~(1 << (idx & BIT_VEC_MASK));
}

hsBitVector& hsBitVector::operator=(const hsBitVector& cpy)
{
    fBits = cpy.fBits;
    return *this;
}

void hsBitVector::compact()
{
    size_t newSize = fBits.size();
    while (newSize > 0 && fBits[newSize-1] == 0)
        newSize--;
    if (newSize < fBits.size())
        fBits.resize(newSize);
}

ST::string hsBitVector::getName(size_t idx)
{
    if (fBitNames.count(idx) > 0)
        return fBitNames[idx];
    else
        return ST::string::from_uint(idx);
}

size_t hsBitVector::getValue(const ST::string& name)
{
    for (const auto& bit : fBitNames) {
        if (bit.second == name)
            return bit.first;
    }
    return name.to_uint();
}

void hsBitVector::read(hsStream* S)
{
    size_t count = S->readInt();
    fBits.resize(count);
    for (size_t i = 0; i < count; ++i)
        fBits[i] = S->readInt();
}

void hsBitVector::write(hsStream* S)
{
#ifdef DEBUG
    /* Don't modify the written objects.  We might want to compare them
     * to test round-tripping files through libhsplasma. */
#else
    compact();
#endif

    S->writeInt(fBits.size());
    for (uint32_t bit : fBits)
        S->writeInt(bit);
}

void hsBitVector::prcWrite(pfPrcHelper* prc)
{
    prc->writeTagNoBreak("hsBitVector");
    for (size_t i = 0; i < size(); ++i) {
        if (get(i)) {
            prc->directWrite(getName(i));
            prc->directWrite(" ");
        }
    }
    prc->closeTagNoBreak();
}

void hsBitVector::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "hsBitVector")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    std::list<ST::string> flags = tag->getContents();
    for (const auto& flag : flags)
        setBit(getValue(flag.c_str()));
}
