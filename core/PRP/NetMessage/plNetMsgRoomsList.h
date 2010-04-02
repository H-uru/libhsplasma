#ifndef _PLNETMSGROOMSLIST_H
#define _PLNETMSGROOMSLIST_H

#include "plNetMessage.h"

DllClass plNetMsgRoomsList : public plNetMessage {
    CREATABLE(plNetMsgRoomsList, kNetMsgRoomsList, plNetMessage)

private:
    hsTArray<plLocation> fRooms;
    hsTArray<plString> fRoomNames;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plNetMsgPagingRoom : public plNetMsgRoomsList {
    CREATABLE(plNetMsgPagingRoom, kNetMsgPagingRoom, plNetMsgRoomsList)

public:
    enum PageFlags {
        kPagingOut = 0x1,
        kResetList = 0x2,
        kRequestState = 0x4,
        kFinalRoomInAge = 0x8,
    };

private:
    unsigned char fPageFlags;

public:
    plNetMsgPagingRoom();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plNetMsgGameStateRequest : public plNetMsgRoomsList {
    CREATABLE(plNetMsgGameStateRequest, kNetMsgGameStateRequest, plNetMsgRoomsList)
};

#endif
