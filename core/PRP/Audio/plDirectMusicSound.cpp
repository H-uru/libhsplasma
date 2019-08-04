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

#include "plDirectMusicSound.h"

void plDirectMusicSound::read(hsStream* S, plResManager* mgr)
{
    plSound::read(S, mgr);

    fUnknown1 = S->readInt();
    fFileName = S->readSafeStr();
}

void plDirectMusicSound::write(hsStream* S, plResManager* mgr)
{
    plSound::write(S, mgr);

    S->writeInt(fUnknown1);
    S->writeSafeStr(fFileName);
}

void plDirectMusicSound::IPrcWrite(pfPrcHelper* prc)
{
    plSound::IPrcWrite(prc);

    prc->startTag("DirectMusicParams");
    prc->writeParam("FileName", fFileName);
    prc->writeParamHex("Unknown", fUnknown1);
    prc->endTag(true);
}

void plDirectMusicSound::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "DirectMusicParams") {
        fFileName = tag->getParam("FileName", "");
        fUnknown1 = tag->getParam("Unknown", "0").to_uint();
    } else {
        plSound::IPrcParse(tag, mgr);
    }
}
