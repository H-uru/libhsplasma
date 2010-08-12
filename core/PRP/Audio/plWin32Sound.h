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

#ifndef _PLWIN32SOUND_H
#define _PLWIN32SOUND_H

#include "plSound.h"

DllClass plWin32Sound : public virtual plSound {
    CREATABLE(plWin32Sound, kWin32Sound, plSound)

public:
    enum ChannelSelect { kLeftChannel, kRightChannel };

protected:
    unsigned char fChannelSelect;

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);

public:
    unsigned char getChannel() const { return fChannelSelect; }
    void setChannel(unsigned char channel) { fChannelSelect = channel; }
};

DllClass plWin32StreamingSound : public plWin32Sound {
    CREATABLE(plWin32StreamingSound, kWin32StreamingSound, plWin32Sound)
};

#endif
