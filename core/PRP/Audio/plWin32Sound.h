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

class PLASMA_DLL plWin32Sound : public plSound
{
    CREATABLE(plWin32Sound, kWin32Sound, plSound)

public:
    enum ChannelSelect { kLeftChannel, kRightChannel };

protected:
    unsigned char fChannelSelect;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
    void IRead(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void IWrite(hsStream* S, plResManager* mgr) HS_OVERRIDE;

public:
    plWin32Sound() : fChannelSelect(kLeftChannel) { }

    unsigned char getChannel() const { return fChannelSelect; }
    void setChannel(unsigned char channel) { fChannelSelect = channel; }
};

class PLASMA_DLL plWin32StreamingSound : public plWin32Sound
{
    CREATABLE(plWin32StreamingSound, kWin32StreamingSound, plWin32Sound)
};

#endif
