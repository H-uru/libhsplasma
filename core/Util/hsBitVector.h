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

#ifndef _HSBITVECTOR_H
#define _HSBITVECTOR_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"
#include <map>

#define BIT_VEC_MASK 0x1F
#define BIT_VEC_WORD 0x20

/**
 * \brief Stores an array (vector) of bits.
 *
 * This can be used as a normal vector, but it allows direct access to
 * numbered (or named) bits, e.g. for flags or a logical bitmap.
 *
 * NOTE: In PyPlasma, this class has overloaded [] operators both for indexed
 * and for named bits.  For example:
 * \code
 * bv = hsBitVector()
 * bv.setName(3, 'Three')
 * bv['Three'] = True
 * \endcode
 */

class PLASMA_DLL hsBitVector
{
public:
    /**
     * \brief References an individual bit within an hsBitVector.
     *
     * This class is used internally by hsBitVector to enable easier access
     * to individual bits.  It allows you to assign bool values to subscripts
     * of the Bit Vector directly, instead of needing the set() method.
     */

    class PLASMA_DLL Bit
    {
    private:
        hsBitVector& fVector;
        size_t fOffset;

    public:
        /** Constructs the Bit class */
        Bit(hsBitVector& vec, size_t off) : fVector(vec), fOffset(off) { }

        /** Behave like a bool rvalue */
        operator bool() const { return fVector.get(fOffset); }

        /** Negation operator */
        bool operator!() const { return !fVector.get(fOffset); }

        /** Comparison operator */
        bool operator==(bool value) const;

        /** Assignment operator -- modifies the hsBitVector */
        Bit& operator=(bool value);
    };

private:
    std::vector<uint32_t> fBits;
    std::map<size_t, ST::string> fBitNames;

public:
    /** Constructs an empty bit vector */
    hsBitVector() { }

    /** Copy constructor */
    hsBitVector(const hsBitVector& init) : fBits(init.fBits) { }

    /** Returns the value of bit \a idx */
    bool get(size_t idx) const;

    /** Set the value of bit \a idx to \a b */
    void set(size_t idx, bool b);

    /** Return the number of available bits. */
    size_t size() const { return fBits.size() * BIT_VEC_WORD; }

    /** Return the value of bit \a idx, for const hsBitVectors */
    bool operator[](size_t idx) const { return get(idx); }

    /** Return a mutable reference to bit \a idx */
    Bit operator[](size_t idx) { return Bit(*this, idx); }

    /** Assignment operator, copies the value of \a cpy */
    hsBitVector& operator=(const hsBitVector& cpy);

    /** Returns true if the bit vector is empty (all zeroes) */
    bool isEmpty() const { return fBits.empty(); }

    /** Clears the bit vector (set to all zeroes) */
    void clear() { fBits.clear(); }

    /** Sets the bit at \a idx to true */
    void setBit(size_t idx) { set(idx, true); }

    /** Sets the bit at \a idx to false */
    void clearBit(size_t idx) { set(idx, false); }

    /**
     * Clean up extra space in the bit vector.  This is called automatically
     * by write().
     */
    void compact();

    /**
     * Returns the name of bit \a idx.  If no name has been assigned with
     * setName(), this function returns a string of \a idx.
     */
    ST::string getName(size_t idx);

    /**
     * Returns the bit index corresponding to bit name \a name.  \a name can
     * be either a name assigned with setName() or an integer, like getName()
     * returns.
     */
    size_t getValue(const ST::string& name);

    /**
     * Sets the name of bit \a idx to \a name, for use in getName() and
     * PyPlasma's overloaded [] operator.
     */
    void setName(size_t idx, const ST::string& name) { fBitNames[idx] = name; }

    /** Read this bit vector from a stream */
    void read(hsStream* S);

    /** Write this bit vector to a stream */
    void write(hsStream* S);

    /** Write PRC source for the bit vector */
    void prcWrite(pfPrcHelper* prc);

    /** Parse a Bit Vector from PRC source */
    void prcParse(const pfPrcTag* tag);
};

#endif
