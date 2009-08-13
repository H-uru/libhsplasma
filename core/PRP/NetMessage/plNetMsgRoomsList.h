#ifndef _PLNETMSGROOMSLIST_H
#define _PLNETMSGROOMSLIST_H

#include "plNetMessage.h"

DllClass plNetMsgRoomsList : public plNetMessage {
private:
    hsTArray<plLocation> fRooms;
    hsTArray<plString> fRoomNames;

public:
    plNetMsgRoomsList();
    ~plNetMsgRoomsList();

    DECLARE_CREATABLE(plNetMsgRoomsList)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plNetMsgPagingRoom : public plNetMsgRoomsList {
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
    ~plNetMsgPagingRoom();

    DECLARE_CREATABLE(plNetMsgPagingRoom)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plNetMsgGameStateRequest : public plNetMsgRoomsList {
public:
    DECLARE_CREATABLE(plNetMsgGameStateRequest)
};

#endif
