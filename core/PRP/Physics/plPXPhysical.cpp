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

#include "plPXPhysical.h"
#include "plGenericPhysical.h"
#include "Debug/plDebug.h"

PXCookedData::PXCookedData(plGenericPhysical* phys) : fPhysical(phys) { }

unsigned int PXCookedData::readOPC(hsStream* S) {
    char tag[4];
    S->read(4, tag);
    if (memcmp(tag, "OPC\x01", 4) != 0) {
        plDebug::Debug("StreamPos = %d", S->pos());
        throw hsBadParamException(__FILE__, __LINE__, "Invalid PhysX Opcode header");
    }
    S->readInt(); //0

    unsigned int opcFlags = S->readInt();
    //plDebug::Debug("OPC Flags = %08X", opcFlags);

    if (!(opcFlags & 0x2) || !(opcFlags & 0x4)) {
        return opcFlags;
    }

    if (opcFlags & 0x1) {
        unsigned int count = S->readInt();

        for (unsigned int i = 0; i < count; i++) {
            S->readShort();
            S->readShort();
            S->readShort();
            S->readShort();
            S->readShort();
            S->readShort();
            S->readInt();
            S->readInt();
        }

        S->readInt();
        S->readInt();
        S->readInt();
        S->readInt();
        S->readInt();
        S->readInt();
    } else {
        unsigned int count = S->readInt();
        S->readInt();

        for (unsigned int i = 0; i < count; i++) {
            unsigned char* buf = new unsigned char[32];
            S->read(32, buf);
            delete[] buf;
        }
    }

    return opcFlags;
}

void PXCookedData::readHBM(hsStream* S) {
    S->readInt(); // size : In theory, we could just skip over this many bytes
    unsigned int opcFlags = readOPC(S);

    if (!(opcFlags & 0x4)) {
        return;
    }

    char tag[4];
    S->read(4, tag);
    if (memcmp(tag, "HBM\x01", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid PhysX HBM header");
    S->readInt(); //0

    unsigned int count = S->readInt();
    unsigned char* buf;
    if (count > 1) {
        S->readInt();
        buf = new unsigned char[count];
        S->read(count, buf);
        delete[] buf;
    }

    count = S->readInt();
    buf = new unsigned char[count];
    S->read(count, buf);
    delete[] buf;
}

void PXCookedData::readTriangleMesh(hsStream* S) {
    char tag[4];
    S->read(4, tag);
    if (memcmp(tag, "NXS\x01", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid PhysX header");
    S->read(4, tag);
    if (memcmp(tag, "MESH", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid Mesh header");
    S->readInt();

    unsigned int nxFlags = S->readInt();
    S->readFloat();
    S->readInt();
    S->readFloat();
    unsigned int nxNumVerts = S->readInt();
    unsigned int nxNumTris = S->readInt();

    hsVector3* nxVerts = new hsVector3[nxNumVerts];
    for (size_t i = 0; i < nxNumVerts; i++) {
        nxVerts[i].read(S);
    }
    fPhysical->setVerts(nxNumVerts, nxVerts);
    delete[] nxVerts;

    unsigned int* nxTris = new unsigned int[nxNumTris * 3];
    for (size_t i = 0; i < nxNumTris * 3; i += 3) {
        if (nxFlags & 0x8) {
            nxTris[i+0] = S->readByte();
            nxTris[i+1] = S->readByte();
            nxTris[i+2] = S->readByte();
        } else if (nxFlags & 0x10) {
            nxTris[i+0] = S->readShort();
            nxTris[i+1] = S->readShort();
            nxTris[i+2] = S->readShort();
        } else {
            nxTris[i+0] = S->readInt();
            nxTris[i+1] = S->readInt();
            nxTris[i+2] = S->readInt();
        }
    }
    fPhysical->setIndices(nxNumTris * 3, nxTris);
    delete[] nxTris;

    if (nxFlags & 1) {
        for (unsigned int i = 0; i < nxNumTris; i++) {
            S->readShort();
        }
    }

    if (nxFlags & 2) {
        unsigned int max = S->readInt();
        for (unsigned int i = 0; i < nxNumTris; i++) {
            if (max > 0xFFFF) {
                S->readInt();
            } else if (max > 0xFF) {
                S->readShort();
            } else {
                S->readByte();
            }
        }
    }

    unsigned int nxNumConvexParts = S->readInt();
    unsigned int nxNumFlatParts = S->readInt();

    if (nxNumConvexParts) {
        for (unsigned int i = 0; i < nxNumTris; i++) {
            S->readShort();
        }
    }

    if (nxNumFlatParts) {
        unsigned char* nxFlatParts = new unsigned char[(nxNumFlatParts >= 0x100) ? 2*nxNumTris : nxNumTris];
        S->read((nxNumFlatParts >= 0x100) ? 2*nxNumTris : nxNumTris, nxFlatParts);
        delete[] nxFlatParts;
    }

    //readHBM(S);
    unsigned int size = S->readInt();
    unsigned char* dat = new unsigned char[size];
    S->read(size, dat);
    delete[] dat;

    S->readFloat();
    S->readFloat();
    S->readFloat();
    S->readFloat();
    S->readFloat();
    S->readFloat();
    S->readFloat();
    S->readFloat();
    S->readFloat();
    S->readFloat();
    S->readFloat();

    float nxVolume = S->readFloat();
    if (nxVolume > -1.0) {
        S->readFloat();
        S->readFloat();
        S->readFloat();
        S->readFloat();
        S->readFloat();
        S->readFloat();
        S->readFloat();
        S->readFloat();
        S->readFloat();
        S->readFloat();
        S->readFloat();
        S->readFloat();
    }

    if (S->readInt()) {
        unsigned char* nxConvexParts = new unsigned char[nxNumTris];
        S->read(nxNumTris, nxConvexParts);
        delete[] nxConvexParts;
    }
}
