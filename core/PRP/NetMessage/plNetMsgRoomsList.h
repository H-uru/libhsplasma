#ifndef _PLNETMSGROOMSLIST_H
#define _PLNETMSGROOMSLIST_H

#include "plNetMessage.h"

DllClass plNetMsgRoomsList : public plNetMessage {
    CREATABLE(plNetMsgRoomsList, kNetMsgRoomsList, plNetMessage)

public:
    DllStruct Room {
        plLocation fLocation;
        plString fName;
    };

private:
    hsTArray<Room> fRooms;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<Room>& getRooms() const { return fRooms; }
    hsTArray<Room>& getRooms() { return fRooms; }
    void addRoom(const plLocation& loc, const plString& name);
    void delRoom(size_t idx) { fRooms.remove(idx); }
    void clearRooms() { fRooms.clear(); }
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

public:
    unsigned char getPageFlags() const { return fPageFlags; }
    void setPageFlags(unsigned char flags) { fPageFlags = flags; }
};


DllClass plNetMsgGameStateRequest : public plNetMsgRoomsList {
    CREATABLE(plNetMsgGameStateRequest, kNetMsgGameStateRequest, plNetMsgRoomsList)
};

#endif
