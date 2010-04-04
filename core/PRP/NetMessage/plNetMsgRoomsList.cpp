#include "plNetMsgRoomsList.h"

/* plNetMsgRoomsList */
void plNetMsgRoomsList::read(hsStream* S, plResManager* mgr) {
    plNetMessage::read(S, mgr);

    size_t count = S->readInt();
    fRooms.setSize(count);
    for (size_t i=0; i<count; i++) {
        fRooms[i].fLocation.read(S);
        unsigned short slen = S->readShort();
        fRooms[i].fName = S->readStr(slen);
    }
}

void plNetMsgRoomsList::write(hsStream* S, plResManager* mgr) {
    plNetMessage::write(S, mgr);

    S->writeInt(fRooms.getSize());
    for (size_t i=0; i<fRooms.getSize(); i++) {
        fRooms[i].fLocation.write(S);
        S->writeShort(fRooms[i].fName.len());
        S->writeStr(fRooms[i].fName);
    }
}

void plNetMsgRoomsList::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Rooms");
    for (size_t i=0; i<fRooms.getSize(); i++) {
        prc->startTag("Room");
        prc->writeParam("Name", fRooms[i].fName);
        fRooms[i].fLocation.prcWrite(prc);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plNetMsgRoomsList::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Rooms") {
        fRooms.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fRooms.getSize(); i++) {
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

void plNetMsgRoomsList::addRoom(const plLocation& loc, const plString& name) {
    Room rm;
    rm.fLocation = loc;
    rm.fName = name;
    fRooms.append(rm);
}


/* plNetMsgPagingRoom */
plNetMsgPagingRoom::plNetMsgPagingRoom() : fPageFlags(0) { }

void plNetMsgPagingRoom::read(hsStream* S, plResManager* mgr) {
    plNetMsgRoomsList::read(S, mgr);
    fPageFlags = S->readByte();
}

void plNetMsgPagingRoom::write(hsStream* S, plResManager* mgr) {
    plNetMsgRoomsList::write(S, mgr);
    S->writeByte(fPageFlags);
}

void plNetMsgPagingRoom::IPrcWrite(pfPrcHelper* prc) {
    plNetMsgRoomsList::IPrcWrite(prc);

    prc->startTag("PageFlags");
    prc->writeParamHex("value", fPageFlags);
    prc->endTag(true);
}

void plNetMsgPagingRoom::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "PageFlags") {
        fPageFlags = tag->getParam("value", "0").toUint();
    } else {
        plNetMsgRoomsList::IPrcParse(tag, mgr);
    }
}
