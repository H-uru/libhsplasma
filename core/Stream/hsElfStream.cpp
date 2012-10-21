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

void hsElfStream::decipher(unsigned char* v, int size, unsigned char hint) {
    unsigned char key = (v[0] ^ hint) >> 5;
    for (int i=size-1; i>=0; i--) {
        unsigned char a = (v[i] ^ hint);
        key = (a << 3) | key;
        v[i] = (key >> 6) | (key << 2);
        key = a >> 5;
    }
}

void hsElfStream::encipher(unsigned char* v, int size, unsigned char hint) {
    unsigned char key = (v[size-1] & 0xFC) << 3;
    for (int i=0; i<size; i++) {
        unsigned char a = (v[i] << 6) | (v[i] >> 2);
        v[i] = ((a >> 3) | key) ^ hint;
        key = a << 5;
    }
}

plString hsElfStream::readLine() {
    unsigned int p = pos();
    unsigned short segHead = readShort();
    unsigned short segSize = segHead ^ (p & 0xFFFF);

    char* ln = new char[segSize+1];
    read(segSize, ln);
    ln[segSize] = 0;
    decipher((unsigned char*)ln, segSize, (p & 0xFF));
    plString line(ln);
    delete[] ln;
    return line;
}

void hsElfStream::writeLine(const plString& ln, bool winEOL) {
    // This may or may not work...
    unsigned int p = pos();
    unsigned short segSize = ln.len();

    // Note: winEOL is ignored here
    char* lnWrite = new char[ln.len() + 1];
    memcpy(lnWrite, ln.cstr(), ln.len() + 1);
    encipher((unsigned char*)lnWrite, segSize, (p & 0xFF));
    writeShort(segSize ^ (p & 0xFFFF));
    write(segSize, lnWrite);
    delete[] lnWrite;
}
