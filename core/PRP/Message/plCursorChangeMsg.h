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

#ifndef _PLCURSORCHANGEMSG_H
#define _PLCURSORCHANGEMSG_H

#include "plMessage.h"

class PLASMA_DLL plCursorChangeMsg : public plMessage {
    CREATABLE(plCursorChangeMsg, kCursorChangeMsg, plMessage)

public:
    enum {
        kNoChange, kCursorUp, kCursorLeft, kCursorRight,
        kCursorDown, kCursorPoised, kCursorClicked, kCursorUnClicked,
        kCursorHidden, kCursorOpen, kCursorGrab, kCursorArrow,
        kNullCursor
    };

protected:
    int fType, fPriority;

public:
    plCursorChangeMsg() : fType(kNoChange), fPriority(0) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    int getType() const { return fType; }
    int getPriority() const { return fPriority; }

    void setType(int value) { fType = value; }
    void setPriority(int value) { fPriority = value; }
};

#endif
