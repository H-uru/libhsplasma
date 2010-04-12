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

#include "Util/hsTArray.hpp"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"
#include <map>

#define BVMASK 0x1F
#define BVMULT 0x20

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

DllClass hsBitVector {
public:
    /**
     * \brief References an individual bit within an hsBitVector.
     *
     * This class is used internally by hsBitVector to enable easier access
     * to individual bits.  It allows you to assign bool values to subscripts
     * of the Bit Vector directly, instead of needing the set() method.
     */

    DllClass Bit {
    private:
        hsBitVector* fVector;
        unsigned int fOffset;

    public:
        /** Constructs the Bit class */
        Bit(hsBitVector* vec, unsigned int off);

        /** Behave like a bool rvalue */
        operator bool() const { return fVector->get(fOffset); }

        /** Negation operator */
        bool operator!() const { return !fVector->get(fOffset); }

        /** Comparison operator */
        bool operator==(bool value) const;

        /** Assignment operator -- modifies the hsBitVector */
        Bit& operator=(bool value);
    };

private:
    hsUint32* fBits;
    size_t fNumVectors;
    std::map<unsigned int, char*> fBitNames;

public:
    /** Constructs an empty bit vector */
    hsBitVector();

    /** Copy constructor */
    hsBitVector(const hsBitVector& init);

    /** Destructor */
    ~hsBitVector();

    /** Returns the value of bit \a idx */
    bool get(unsigned int idx) const;

    /** Set the value of bit \a idx to \a b */
    void set(unsigned int idx, bool b);

    /** Return the value of bit \a idx, for const hsBitVectors */
    bool operator[](unsigned int idx) const { return get(idx); }

    /** Return a Bit class referencing bit \a idx */
    Bit operator[](unsigned int idx) { return hsBitVector::Bit(this, idx); }

    /** Assignment operator, copies the value of \a cpy */
    hsBitVector& operator=(const hsBitVector& cpy);

    /** Returns true if the bit vector is empty (all zeroes) */
    bool isEmpty() const { return (fNumVectors == 0); }

    /** Clears the bit vector (set to all zeroes) */
    void clear();

    /** Sets the bit at \a idx to true */
    void setBit(unsigned int idx) { set(idx, true); }

    /** Sets the bit at \a idx to false */
    void clearBit(unsigned int idx) { set(idx, false); }

    /**
     * Clean up extra space in the bit vector.  This is called automatically
     * by write().
     */
    void compact();

    /**
     * Returns the name of bit \a idx.  If no name has been assigned with
     * setName(), this function returns a string of \a idx.
     */
    const char* getName(unsigned int idx);

    /**
     * Returns the bit index corresponding to bit name \a name.  \a name can
     * be either a name assigned with setName() or an integer, like getName()
     * returns.
     */
    unsigned int getValue(const char* name);

    /**
     * Sets the name of bit \a idx to \a name, for use in getName() and
     * PyPlasma's overloaded [] operator.
     */
    void setName(unsigned int idx, const char* name);

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
