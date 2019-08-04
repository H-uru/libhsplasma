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

#ifndef _PLUUID_H
#define _PLUUID_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

/**
 * \brief Stores a UUID (Universally Unique Identifier).
 */

struct PLASMA_DLL plUuid {
private:
    unsigned int fData1;
    unsigned short fData2, fData3;
    unsigned char fData4[8];

public:
    static const plUuid Null;

    /** Constructs a null UUID, i.e. 00000000-0000-0000-0000-000000000000. */
    plUuid() : fData1(), fData2(), fData3(), fData4() { }

    /**
     * Constructs a UUID from the four arguments. The argument \a data4 should
     * be a pointer to an unsigned char array with 8 elements.
     */
    plUuid(unsigned int data1, unsigned short data2, unsigned short data3,
           const unsigned char* data4);

    /**
     * Constructs a UUID from a string in the form of
     * "00000000-0000-0000-0000-000000000000".
     */
    plUuid(const ST::string& str) { fromString(str); }

    /** Returns true if the two UUIDs are identical. */
    bool operator==(const plUuid& other) const;

    /** Returns true if the two UUIDs are non-identical. */
    bool operator!=(const plUuid& other) const;

    /** Read the UUID from a stream */
    void read(hsStream* S);

    /** Reads the UUID from a buffer. */
    void read(const unsigned char* buffer);

    /** Writes the UUID to a stream */
    void write(hsStream* S) const;

    /** Writes the UUID to a buffer. */
    void write(unsigned char* buffer) const;

    /** Writes the UUID to PRC source. */
    void prcWrite(pfPrcHelper* prc);

    /** Parses the UUID from PRC source. */
    void prcParse(const pfPrcTag* tag);

    /** Sets the UUID to 00000000-0000-0000-0000-000000000000. */
    void clear();

    /** Returns true if the UUID is 00000000-0000-0000-0000-000000000000. */
    bool isNull() const { return operator==(Null); }

    /**
     * Returns a string representation of this UUID in the form of
     * "00000000-0000-0000-0000-000000000000" as a string.
     */
    ST::string toString() const;

    /**
     * Parses the UUID from a string representation in the form of
     * "00000000-0000-0000-0000-000000000000".
     *
     * \exception hsBadParamException given string doesn't appear to be a
     *            valid UUID string representation
     */
    void fromString(const ST::string& str);
};

#endif
