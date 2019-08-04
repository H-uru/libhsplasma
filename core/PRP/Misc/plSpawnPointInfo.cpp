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

#include "plSpawnPointInfo.h"
#include "Util/hsBitVector.h"

void plSpawnPointInfo::read(hsStream* S)
{
    hsBitVector flags;
    flags.read(S);
    if (flags[kHasTitle]) {
        size_t len = S->readShort();
        fTitle = S->readStr(len);
    }
    if (flags[kHasSpawnPt]) {
        size_t len = S->readShort();
        fSpawnPt = S->readStr(len);
    }
    if (flags[kHasCameraStack]) {
        size_t len = S->readShort();
        fCameraStack = S->readStr(len);
    }
}

void plSpawnPointInfo::write(hsStream* S)
{
    hsBitVector flags;
    flags[kHasTitle] = true;
    flags[kHasSpawnPt] = true;
    flags[kHasCameraStack] = true;
    flags.write(S);

    S->writeShort(fTitle.size());
    S->writeStr(fTitle);
    S->writeShort(fSpawnPt.size());
    S->writeStr(fSpawnPt);
    S->writeShort(fCameraStack.size());
    S->writeStr(fCameraStack);
}

void plSpawnPointInfo::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plSpawnPointInfo");
    prc->writeParam("Title", fTitle);
    prc->writeParam("SpawnPoint", fSpawnPt);
    prc->writeParam("CameraStack", fCameraStack);
    prc->endTag(true);
}

void plSpawnPointInfo::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plSpawnPointInfo")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fTitle = tag->getParam("Title", "");
    fSpawnPt = tag->getParam("SpawnPoint", "");
    fCameraStack = tag->getParam("CameraStack", "");
}

void plSpawnPointInfo::clear()
{
    fTitle = "";
    fSpawnPt = "";
    fCameraStack = "";
}
