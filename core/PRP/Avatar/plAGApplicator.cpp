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

#include "plAGApplicator.h"

/* plAGApplicator */
plAGApplicator::~plAGApplicator()
{
    delete fChannel;
}

void plAGApplicator::read(hsStream* S, plResManager* mgr)
{
    fEnabled = S->readBool();
    fChannelName = S->readSafeStr();
}

void plAGApplicator::write(hsStream* S, plResManager* mgr)
{
    S->writeBool(fEnabled);
    S->writeSafeStr(fChannelName);
}

void plAGApplicator::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("AGApplicatorParams");
    prc->writeParam("Enabled", fEnabled);
    prc->writeParam("ChannelName", fChannelName);
    prc->endTag(true);
}

void plAGApplicator::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "AGApplicatorParams") {
        fEnabled = tag->getParam("Enabled", "false").to_bool();
        fChannelName = tag->getParam("ChannelName", "");
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plAGApplicator::setChannel(plAGChannel* chan)
{
    delete fChannel;
    fChannel = chan;
}


/* plSoundVolumeApplicator */
void plSoundVolumeApplicator::read(hsStream* S, plResManager* mgr)
{
    plAGApplicator::read(S, mgr);
    fIndex = S->readInt();
}

void plSoundVolumeApplicator::write(hsStream* S, plResManager* mgr)
{
    plAGApplicator::write(S, mgr);
    S->writeInt(fIndex);
}

void plSoundVolumeApplicator::IPrcWrite(pfPrcHelper* prc)
{
    plAGApplicator::IPrcWrite(prc);

    prc->startTag("SoundVolumeApplicatorParams");
    prc->writeParam("Index", fIndex);
    prc->endTag(true);
}

void plSoundVolumeApplicator::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SoundVolumeApplicatorParams") {
        fIndex = tag->getParam("Index", "0").to_uint();
    } else {
        plAGApplicator::IPrcParse(tag, mgr);
    }
}
