#include "plNetMsgRoomsList.h"

/* plNetMsgRoomsList */
void plNetMsgRoomsList::read(hsStream* S, plResManager* mgr) {
    plNetMessage::read(S, mgr);

    size_t count = S->readInt();
    fRooms.setSize(count);
    fRoomNames.setSize(count);
    for (size_t i=0; i<count; i++) {
        fRooms[i].read(S);
        unsigned short slen = S->readShort();
        fRoomNames[i] = S->readStr(slen);
    }
}

void plNetMsgRoomsList::write(hsStream* S, plResManager* mgr) {
    plNetMessage::write(S, mgr);

    S->writeInt(fRooms.getSize());
    for (size_t i=0; i<fRooms.getSize(); i++) {
        fRooms[i].write(S);
        S->writeShort(fRoomNames[i].len());
        S->writeStr(fRoomNames[i]);
    }
}

void plNetMsgRoomsList::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Rooms");
    for (size_t i=0; i<fRooms.getSize(); i++) {
        prc->startTag("Room");
        prc->writeParam("Name", fRoomNames[i]);
        fRooms[i].prcWrite(prc);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plNetMsgRoomsList::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Rooms") {
        fRooms.setSize(tag->countChildren());
        fRoomNames.setSize(fRooms.getSize());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fRooms.getSize(); i++) {
            if (child->getName() != "Room")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fRoomNames[i] = child->getParam("Name", "");
            if (child->hasChildren())
                fRooms[i].prcParse(child->getFirstChild());
            child = child->getNextSibling();
        }
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
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
