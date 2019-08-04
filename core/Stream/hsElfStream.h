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

#ifndef _HSELFSTREAM_H
#define _HSELFSTREAM_H

#include "hsStream.h"

class PLASMA_DLL hsElfStream : public hsFileStream
{
private:
    void decipher(unsigned char* v, int size, unsigned char hint);
    void encipher(unsigned char* v, int size, unsigned char hint);

protected:
    unsigned char hint;

public:
    hsElfStream() : hsFileStream(PlasmaVer::pvUnknown) { }

    ST::string readLine() HS_OVERRIDE;
    void writeLine(const ST::string& ln, bool winEOL = false) HS_OVERRIDE;
};

#endif

