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

#include "plNetMsgRoomsList.h"

/* plNetMsgRoomsList */
void plNetMsgRoomsList::read(hsStream* S, plResManager* mgr)
{
    plNetMessage::read(S, mgr);

    size_t count = S->readInt();
    fRooms.resize(count);
    for (size_t i=0; i<count; i++) {
        fRooms[i].fLocation.read(S);
        unsigned short slen = S->readShort();
        fRooms[i].fName = S->readStr(slen);
    }
}

void plNetMsgRoomsList::write(hsStream* S, plResManager* mgr)
{
    plNetMessage::write(S, mgr);

    S->writeInt(fRooms.size());
    for (size_t i=0; i<fRooms.size(); i++) {
        fRooms[i].fLocation.write(S);
        S->writeShort(fRooms[i].fName.size());
        S->writeStr(fRooms[i].fName);
    }
}

void plNetMsgRoomsList::IPrcWrite(pfPrcHelper* prc)
{
    plNetMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Rooms");
    for (size_t i=0; i<fRooms.size(); i++) {
        prc->startTag("Room");
        prc->writeParam("Name", fRooms[i].fName);
        fRooms[i].fLocation.prcWrite(prc);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plNetMsgRoomsList::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Rooms") {
        fRooms.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fRooms.size(); i++) {
            if (child->getName() != "Room")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fRooms[i].fName = child->getParam("Name", "");
            if (child->hasChildren())
                fRooms[i].fLocation.prcParse(child->getFirstChild());
            child = child->getNextSibling();
        }
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}

void plNetMsgRoomsList::addRoom(const plLocation& loc, const ST::string& name)
{
    Room rm;
    rm.fLocation = loc;
    rm.fName = name;
    fRooms.push_back(rm);
}


/* plNetMsgPagingRoom */
void plNetMsgPagingRoom::read(hsStream* S, plResManager* mgr)
{
    plNetMsgRoomsList::read(S, mgr);
    fPageFlags = S->readByte();
}

void plNetMsgPagingRoom::write(hsStream* S, plResManager* mgr)
{
    plNetMsgRoomsList::write(S, mgr);
    S->writeByte(fPageFlags);
}

void plNetMsgPagingRoom::IPrcWrite(pfPrcHelper* prc)
{
    plNetMsgRoomsList::IPrcWrite(prc);

    prc->startTag("PageFlags");
    prc->writeParamHex("value", fPageFlags);
    prc->endTag(true);
}

void plNetMsgPagingRoom::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "PageFlags") {
        fPageFlags = tag->getParam("value", "0").to_uint();
    } else {
        plNetMsgRoomsList::IPrcParse(tag, mgr);
    }
}
