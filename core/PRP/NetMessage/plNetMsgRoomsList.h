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

#ifndef _PLNETMSGROOMSLIST_H
#define _PLNETMSGROOMSLIST_H

#include "plNetMessage.h"

class PLASMA_DLL plNetMsgRoomsList : public plNetMessage {
    CREATABLE(plNetMsgRoomsList, kNetMsgRoomsList, plNetMessage)

public:
    struct PLASMA_DLL Room {
        plLocation fLocation;
        plString fName;
    };

private:
    std::vector<Room> fRooms;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const std::vector<Room>& getRooms() const { return fRooms; }
    std::vector<Room>& getRooms() { return fRooms; }
    void addRoom(const plLocation& loc, const plString& name);
    void delRoom(size_t idx) { fRooms.erase(fRooms.begin() + idx); }
    void clearRooms() { fRooms.clear(); }
};


class PLASMA_DLL plNetMsgPagingRoom : public plNetMsgRoomsList {
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
    plNetMsgPagingRoom() : fPageFlags(0) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned char getPageFlags() const { return fPageFlags; }
    void setPageFlags(unsigned char flags) { fPageFlags = flags; }
};


class PLASMA_DLL plNetMsgGameStateRequest : public plNetMsgRoomsList {
    CREATABLE(plNetMsgGameStateRequest, kNetMsgGameStateRequest, plNetMsgRoomsList)
};

#endif
