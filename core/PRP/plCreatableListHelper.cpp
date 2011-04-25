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

#include "plCreatableListHelper.h"
#include "Util/plZlib.h"
#include "Stream/hsRAMStream.h"

void plCreatableListHelper::read(hsStream* S, plResManager* mgr) {
    fFlags = S->readByte();
    fFlags &= ~kWritten;

    uint32_t size = S->readInt();
    uint8_t* buffer = new uint8_t[size];

    if ((fFlags & kCompressed) != 0) {
        uint32_t compressedSize = S->readInt();
        uint8_t* zbuffer = new uint8_t[compressedSize];
        S->read(compressedSize, zbuffer);
        plZlib::Uncompress(buffer, size, zbuffer, compressedSize);
        delete[] zbuffer;
    } else {
        S->read(size, buffer);
    }

    hsRAMStream ram;
    ram.stealFrom(buffer, size);

    uint16_t count = ram.readShort();
    clearCreatables();
    for (uint16_t i=0; i<count; ++i) {
        uint16_t id = ram.readShort();
        fCreatables[id] = mgr->ReadCreatable(&ram);
    }
}

void plCreatableListHelper::write(hsStream* S, plResManager* mgr) {
    hsRAMStream ram;

    ram.writeShort(fCreatables.size());
    std::map<uint16_t, plCreatable*>::iterator it;
    for (it = fCreatables.begin(); it != fCreatables.end(); ++it) {
        ram.writeShort(it->first);
        mgr->WriteCreatable(&ram, it->second);
    }
    uint32_t size = ram.size();
    uint8_t* buffer = new uint8_t[size];
    ram.copyTo(buffer, size);

    if ((fFlags & kWantCompression) != 0) {
        fFlags |= kCompressed;
        uint32_t compressedSize;
        uint8_t* zbuffer;
        plZlib::Compress(zbuffer, compressedSize, buffer, size);

        delete[] buffer;
        buffer = zbuffer;
        size = compressedSize;
    }

    S->writeByte(fFlags);
    S->writeInt(ram.size());
    if ((fFlags & kCompressed) != 0)
        S->writeInt(size);
    S->write(size, buffer);

    delete[] buffer;
}

void plCreatableListHelper::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("CreatableList");
    prc->writeParamHex("Flags", fFlags);
    prc->endTag(false);

    std::map<uint16_t, plCreatable*>::iterator it;
    for (it = fCreatables.begin(); it != fCreatables.end(); ++it) {
        prc->startTag("Creatable");
        prc->writeParam("id", it->first);
        prc->endTag(false);
        it->second->prcWrite(prc);
        prc->closeTag();
    }

    prc->closeTag();
}

void plCreatableListHelper::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "CreatableList") {
        fFlags = tag->getParam("Flags", "0").toUint();

        clearCreatables();
        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
            if (child->getName() != "Creatable")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            uint16_t id = child->getParam("id", "0").toUint();
            if (child->hasChildren())
                fCreatables[id] = mgr->prcParseCreatable(child->getFirstChild());
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plCreatableListHelper::clearCreatables() {
    std::map<uint16_t, plCreatable*>::iterator it;
    for (it = fCreatables.begin(); it != fCreatables.end(); ++it)
        delete it->second;
}
