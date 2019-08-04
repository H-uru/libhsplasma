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

#include <cstring>
#include <cstdlib>
#include "hsElfStream.h"

void hsElfStream::decipher(unsigned char* v, int size, unsigned char hint)
{
    unsigned char key = (v[0] ^ hint) >> 5;
    for (int i=size-1; i>=0; i--) {
        unsigned char a = (v[i] ^ hint);
        key = (a << 3) | key;
        v[i] = (key >> 6) | (key << 2);
        key = a >> 5;
    }
}

void hsElfStream::encipher(unsigned char* v, int size, unsigned char hint)
{
    unsigned char key = (v[size-1] & 0xFC) << 3;
    for (int i=0; i<size; i++) {
        unsigned char a = (v[i] << 6) | (v[i] >> 2);
        v[i] = ((a >> 3) | key) ^ hint;
        key = a << 5;
    }
}

ST::string hsElfStream::readLine()
{
    unsigned int p = pos();
    unsigned short segHead = readShort();
    unsigned short segSize = segHead ^ (p & 0xFFFF);

    ST::char_buffer line;
    line.allocate(segSize);
    read(segSize, line.data());
    decipher((unsigned char*)line.data(), segSize, (p & 0xFF));
    return line;
}

void hsElfStream::writeLine(const ST::string& ln, bool winEOL)
{
    // This may or may not work...
    unsigned int p = pos();
    unsigned short segSize = ln.size();

    // Note: winEOL is ignored here
    ST::char_buffer buffer = ln.to_utf8();
    encipher((unsigned char*)buffer.data(), segSize, (p & 0xFF));
    writeShort(segSize ^ (p & 0xFFFF));
    write(segSize, buffer.data());
}
