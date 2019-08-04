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
#include <cstring>

unsigned int PXCookedData::readOPC(hsStream* S)
{
    char tag[4];
    S->read(4, tag);
    if (memcmp(tag, "OPC\x01", 4) != 0) {
        plDebug::Debug("StreamPos = {}", S->pos());
        throw hsBadParamException(__FILE__, __LINE__, "Invalid PhysX Opcode header");
    }
    if (S->readInt() != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid PhysX Opcode version");

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
        S->skip(32*count);
    }

    return opcFlags;
}

void PXCookedData::readHBM(hsStream* S)
{
    unsigned int size = S->readInt(); // size : In theory, we could just skip over this many bytes
    const unsigned int endpos = S->pos()+size;
    unsigned int opcFlags = readOPC(S);

    if (opcFlags & 0x4) {
        char tag[4];
        S->read(4, tag);
        if (memcmp(tag, "HBM\x01", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid PhysX HBM header");
        if (S->readInt() != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid PhysX HBM version");

        unsigned int count = S->readInt();
        if (count > 1) {
            S->readInt();
            S->skip(count);
        }

        count = S->readInt();
        S->skip(count);
    }
    else {
        // there is still some stuff missing... skip to endpos
        if (S->pos() < endpos)
            S->skip(endpos - S->pos());
    }

    // verify size
    if (S->pos() != endpos)
        throw hsBadParamException(__FILE__, __LINE__, ST::format("Invalid HBM size: Expected pos {}, but reached pos {}", endpos, S->pos()));
}

void PXCookedData::skipMaxDependantList(hsStream*S, unsigned int size)
{
    const unsigned int max = S->readInt();
    if (max > 0xFFFF)
        S->skip(4*size);
    else if (max > 0xFF)
        S->skip(2*size);
    else
        S->skip(size);
}

void PXCookedData::readSuffix(hsStream* S)
{
    readHBM(S);

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
}


void PXCookedData::readConvexMesh(hsStream* S, plGenericPhysical* physical)
{
    char tag[4];
    unsigned int unk1, unk2, unk3, unk4, unk5;
    // NOTE: PhysX Cooked data always begins with "NXS\x01". This is read in plGenericPhysical
    // to determine if the buffer is cooked or hax'd
    S->read(4, tag);
    if (memcmp(tag, "CVXM", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid CVXM header");
    if (S->readInt() != 2)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid CVXM: Only version 2 supported");
    S->readInt();

    S->read(4, tag);
    if (memcmp(tag, "ICE\x01", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid ICE header");
    S->read(4, tag);
    if (memcmp(tag, "CLHL", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid CLHL header");
    if (S->readInt() != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid CLHL: Only version 0 supported");

    S->read(4, tag);
    if (memcmp(tag, "ICE\x01", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid ICE header");
    S->read(4, tag);
    if (memcmp(tag, "CVHL", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid CVHL header");
    if (S->readInt() != 5)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid CVHL: Only version 5 supported");

    const unsigned int nxNumVerts = S->readInt();
    const unsigned int nxNumTris = S->readInt();
    unk2 = S->readInt();
    unk3 = S->readInt();
    unk4 = S->readInt();
    if (unk4 != 2*unk2)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid u4");
    unk5 = S->readInt();
    if (unk4 != unk5)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid u5");

    hsVector3* nxVerts = new hsVector3[nxNumVerts];
    for (size_t i=0; i<nxNumVerts; i++)
        nxVerts[i].read(S);
    physical->setVerts(nxNumVerts, nxVerts);
    delete[] nxVerts;

    const unsigned int maxVertIndex = S->readInt();
    if (maxVertIndex+1 != nxNumVerts)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid maxVertIndex");

    unsigned int* nxTris = new unsigned int[nxNumTris * 3];
    for (size_t i=0; i<nxNumTris*3; i += 3) {
        if (maxVertIndex > 0xFFFF) {
            nxTris[i+0] = S->readInt();
            nxTris[i+1] = S->readInt();
            nxTris[i+2] = S->readInt();
        } else if (maxVertIndex > 0xFF) {
            nxTris[i+0] = S->readShort();
            nxTris[i+1] = S->readShort();
            nxTris[i+2] = S->readShort();
        } else {
            nxTris[i+0] = S->readByte();
            nxTris[i+1] = S->readByte();
            nxTris[i+2] = S->readByte();
        }
    }
    physical->setIndices(nxNumTris * 3, nxTris);
    delete[] nxTris;

    if (S->readShort() != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid u7: only 0 supported");

    S->skip(nxNumVerts*2); // nxNumVerts words

    S->readFloat();
    S->readFloat();
    S->readFloat();

    S->skip(36*unk3);
    S->skip(unk4);

    // a list of size unk4, with the maximum first to determine the size of the elements
    skipMaxDependantList(S, unk4);

    S->readInt();
    S->readInt();
    S->skip(2*unk2);
    S->skip(2*unk2);

    // three lists of size u2 in the format: first the maximum, then the elements are only large enough to hold values <= max
    skipMaxDependantList(S, unk2);
    skipMaxDependantList(S, unk2);
    skipMaxDependantList(S, unk2);
    // and another fixed-size list
    S->skip(2*unk2);


    S->read(4, tag);
    if (memcmp(tag, "ICE\x01", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid ICE header");
    S->read(4, tag);
    if (memcmp(tag, "VALE", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid VALE header");
    if (S->readInt() != 2)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid VALE: Only version 2 supported");

    unk1 = S->readInt();
    unk2 = S->readInt();

    skipMaxDependantList(S, unk1);
    S->skip(unk2);


    readSuffix(S);

    if (nxNumVerts > 0x20) {
        S->read(4, tag);
        if (memcmp(tag, "ICE\x01", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid ICE header");
        S->read(4, tag);
        if (memcmp(tag, "SUPM", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid SUPM header");
        if (S->readInt() != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid SUPM: Only version 0 supported");

        S->read(4, tag);
        if (memcmp(tag, "ICE\x01", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid ICE header");
        S->read(4, tag);
        if (memcmp(tag, "GAUS", 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid GAUS header");
        if (S->readInt() != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid GAUS: Only version 0 supported");

        S->readInt();
        unk2 = S->readInt();
        S->skip(2*unk2);
    }
}

void PXCookedData::readTriangleMesh(hsStream* S, plGenericPhysical* physical)
{
    char tag[4];
    // NOTE: PhysX Cooked data always begins with "NXS\x01". This is read in plGenericPhysical
    // to determine if the buffer is cooked or hax'd
    S->read(4, tag);
    if (memcmp(tag, "MESH", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid Mesh header");
    if (S->readInt() != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid MESH: Only version 0 supported");

    const unsigned int nxFlags = S->readInt();
    S->readFloat();
    S->readInt();
    S->readFloat();
    const unsigned int nxNumVerts = S->readInt();
    const unsigned int nxNumTris = S->readInt();

    hsVector3* nxVerts = new hsVector3[nxNumVerts];
    for (size_t i = 0; i < nxNumVerts; i++) {
        nxVerts[i].read(S);
    }
    physical->setVerts(nxNumVerts, nxVerts);
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
    physical->setIndices(nxNumTris * 3, nxTris);
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
        S->skip((nxNumFlatParts >= 0x100) ? 2*nxNumTris : nxNumTris);
    }

    readSuffix(S);

    if (S->readInt()) {
        S->skip(nxNumTris);
    }
}
