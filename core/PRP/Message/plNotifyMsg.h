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

#ifndef _PLNOTIFYMSG_H
#define _PLNOTIFYMSG_H

#include "plMessage.h"
#include "proEventData.h"

class PLASMA_DLL plNotifyMsg : public plMessage {
    CREATABLE(plNotifyMsg, kNotifyMsg, plMessage)

public:
    enum notificationType {
        kActivator, kVarNotification, kNotifySelf, kResponderFF,
        kResponderChangeState
    };

protected:
    int fType, fID;
    float fState;
    hsTArray<proEventData*> fEvents;

public:
    plNotifyMsg();
    virtual ~plNotifyMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    int getType() const { return fType; }
    float getState() const { return fState; }
    int getID() const { return fID; }

    void setType(int type) { fType = type; }
    void setState(float state) { fState = state; }
    void setID(int id) { fID = id; }

    const hsTArray<proEventData*>& getEvents() const { return fEvents; }
    hsTArray<proEventData*>& getEvents() { return fEvents; }
    void addEvent(proEventData* evt) { fEvents.append(evt); }
    void delEvent(size_t idx);
    void clearEvents();
};

#endif
