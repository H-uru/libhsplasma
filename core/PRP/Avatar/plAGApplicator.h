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

DllClass plAGApplicator : public plCreatable {
    CREATABLE(plAGApplicator, kAGApplicator, plCreatable)

protected:
    plAGChannel* fChannel;
    bool fEnabled;
    plString fChannelName;

public:
    plAGApplicator();
    virtual ~plAGApplicator();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plAGChannel* getChannel() const { return fChannel; }
    void setChannel(plAGChannel*);

    bool isEnabled() const { return fEnabled; }
    plString getChannelName() const { return fChannelName; }

    void setEnabled(bool enabled) { fEnabled = enabled; }
    void setChannelName(const plString& channelName) { fChannelName = channelName; }
};


DllClass plSoundVolumeApplicator : public plAGApplicator {
    CREATABLE(plSoundVolumeApplicator, kSoundVolumeApplicator, plAGApplicator)

protected:
    unsigned int fIndex;

public:
    plSoundVolumeApplicator();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getIndex() const { return fIndex; }
    void setIndex(unsigned int index) { fIndex = index; }
};


DllClass plLightAmbientApplicator : public plAGApplicator {
    CREATABLE(plLightAmbientApplicator, kLightAmbientApplicator, plAGApplicator)
};

DllClass plLightDiffuseApplicator : public plAGApplicator {
    CREATABLE(plLightDiffuseApplicator, kLightDiffuseApplicator, plAGApplicator)
};

DllClass plLightSpecularApplicator : public plAGApplicator {
    CREATABLE(plLightSpecularApplicator, kLightSpecularApplicator, plAGApplicator)
};

DllClass plOmniApplicator : public plAGApplicator {
    CREATABLE(plOmniApplicator, kOmniApplicator, plAGApplicator)
};

DllClass plOmniCutoffApplicator : public plAGApplicator {
    CREATABLE(plOmniCutoffApplicator, kOmniCutoffApplicator, plAGApplicator)
};

DllClass plOmniSqApplicator : public plAGApplicator {
    CREATABLE(plOmniSqApplicator, kOmniSqApplicator, plAGApplicator)
};

DllClass plSpotInnerApplicator : public plAGApplicator {
    CREATABLE(plSpotInnerApplicator, kSpotInnerApplicator, plAGApplicator)
};

DllClass plSpotOuterApplicator : public plAGApplicator {
    CREATABLE(plSpotOuterApplicator, kSpotOuterApplicator, plAGApplicator)
};

#endif
