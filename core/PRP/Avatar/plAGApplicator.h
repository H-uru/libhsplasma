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

#ifndef _PLAGAPPLICATOR_H
#define _PLAGAPPLICATOR_H

#include "plAGChannel.h"

class PLASMA_DLL plAGApplicator : public plCreatable
{
    CREATABLE(plAGApplicator, kAGApplicator, plCreatable)

protected:
    plAGChannel* fChannel;
    bool fEnabled;
    ST::string fChannelName;

public:
    plAGApplicator() : fChannel(), fEnabled(true) { }
    ~plAGApplicator();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plAGChannel* getChannel() const { return fChannel; }
    void setChannel(plAGChannel*);

    bool isEnabled() const { return fEnabled; }
    ST::string getChannelName() const { return fChannelName; }

    void setEnabled(bool enabled) { fEnabled = enabled; }
    void setChannelName(const ST::string& channelName) { fChannelName = channelName; }
};


class PLASMA_DLL plSoundVolumeApplicator : public plAGApplicator
{
    CREATABLE(plSoundVolumeApplicator, kSoundVolumeApplicator, plAGApplicator)

protected:
    unsigned int fIndex;

public:
    plSoundVolumeApplicator() : fIndex() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned int getIndex() const { return fIndex; }
    void setIndex(unsigned int index) { fIndex = index; }
};


class PLASMA_DLL plLightAmbientApplicator : public plAGApplicator
{
    CREATABLE(plLightAmbientApplicator, kLightAmbientApplicator, plAGApplicator)
};

class PLASMA_DLL plLightDiffuseApplicator : public plAGApplicator
{
    CREATABLE(plLightDiffuseApplicator, kLightDiffuseApplicator, plAGApplicator)
};

class PLASMA_DLL plLightSpecularApplicator : public plAGApplicator
{
    CREATABLE(plLightSpecularApplicator, kLightSpecularApplicator, plAGApplicator)
};

class PLASMA_DLL plOmniApplicator : public plAGApplicator
{
    CREATABLE(plOmniApplicator, kOmniApplicator, plAGApplicator)
};

class PLASMA_DLL plOmniCutoffApplicator : public plAGApplicator
{
    CREATABLE(plOmniCutoffApplicator, kOmniCutoffApplicator, plAGApplicator)
};

class PLASMA_DLL plOmniSqApplicator : public plAGApplicator
{
    CREATABLE(plOmniSqApplicator, kOmniSqApplicator, plAGApplicator)
};

class PLASMA_DLL plSpotInnerApplicator : public plAGApplicator
{
    CREATABLE(plSpotInnerApplicator, kSpotInnerApplicator, plAGApplicator)
};

class PLASMA_DLL plSpotOuterApplicator : public plAGApplicator
{
    CREATABLE(plSpotOuterApplicator, kSpotOuterApplicator, plAGApplicator)
};

#endif
