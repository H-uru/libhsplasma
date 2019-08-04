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

#include "plUoid.h"
#include "ResManager/plFactory.h"
#include "ResManager/pdUnifiedTypeMap.h"
#include <string.h>
#include <stdlib.h>
#include <string_theory/format>

bool plUoid::operator==(const plUoid& other) const
{
    return (location == other.location) && (classType == other.classType) &&
           (objName == other.objName) && (clonePlayerID == other.clonePlayerID) &&
           (cloneID == other.cloneID);
}

bool plUoid::operator<(const plUoid& other) const
{
    if (location == other.location) {
        if (classType == other.classType) {
            if (objName == other.objName) {
                if (clonePlayerID == other.clonePlayerID)
                    return cloneID < other.cloneID;
                return clonePlayerID < other.clonePlayerID;
            }
            return objName < other.objName;
        }
        return classType < other.classType;
    }
    return location < other.location;
}

void plUoid::read(hsStream* S)
{
    unsigned char contents = 0;
    if (S->getVer() < MAKE_VERSION(2, 0, 63, 0) && S->getVer().isValid()) {
        contents = kHasCloneIDs;
    } else {
        contents = S->readByte();
    }
    location.read(S);
    if ((contents & kHasLoadMask) && (!S->getVer().isNewPlasma() || S->getVer().isUniversal()))
        loadMask.read(S);
    else
        loadMask.setAlways();
    classType = pdUnifiedTypeMap::PlasmaToMapped(S->readShort(), S->getVer());
    if (!S->getVer().isUruSP() && !S->getVer().isUniversal())
        objID = S->readInt();
    objName = S->readSafeStr();
    if ((contents & kHasCloneIDs) && (S->getVer().isUru() || S->getVer().isUniversal())) {
        cloneID = S->readInt();
        if (S->getVer() < MAKE_VERSION(2, 0, 57, 0))
            clonePlayerID = 0;
        else
            clonePlayerID = S->readInt();
    } else {
        cloneID = clonePlayerID = 0;
    }
    if ((contents & (kHasLoadMask | kHasLoadMask2)) && S->getVer().isNewPlasma()) {
        loadMask.read(S);
    }
}

void plUoid::write(hsStream* S)
{
    unsigned char contents = 0;
    if (!S->getVer().isSafeVer())
        S->setVer(PlasmaVer::GetSafestVersion(S->getVer()));

    if (cloneID != 0)
        contents |= kHasCloneIDs;
    if (loadMask.isUsed()) {
        if (S->getVer().isNewPlasma())
            contents |= kHasLoadMask2;
        else
            contents |= kHasLoadMask;
    }
    S->writeByte(contents);

    location.write(S);
    if ((contents & kHasLoadMask) && (S->getVer().isUru() || S->getVer().isUniversal()))
        loadMask.write(S);
    S->writeShort(pdUnifiedTypeMap::MappedToPlasma(classType, S->getVer()));
    if (!S->getVer().isUruSP() && !S->getVer().isUniversal())
        S->writeInt(objID);

    S->writeSafeStr(objName);

    if ((contents & kHasCloneIDs) && (S->getVer().isUru() || S->getVer().isUniversal())) {
        S->writeInt(cloneID);
        S->writeInt(clonePlayerID);
    }
    if ((contents & kHasLoadMask) && S->getVer().isNewPlasma())
        loadMask.write(S);
}

void plUoid::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plKey");
    prc->writeParam("Name", objName);
    prc->writeParam("Type", plFactory::ClassName(classType));
    location.prcWrite(prc);
    if (loadMask.isUsed())
        loadMask.prcWrite(prc);
    if (cloneID != 0) {
        prc->writeParam("CloneID", cloneID);
        prc->writeParam("ClonePlayerID", clonePlayerID);
    }
    if (objID != 0)
        prc->writeParam("ObjID", objID);
    prc->endTag(true);
}

void plUoid::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plKey")
        throw hsBadParamException(__FILE__, __LINE__, "Tag name mismatch");

    objName = tag->getParam("Name", "");
    classType = plFactory::ClassIndex(tag->getParam("Type", "").c_str());
    location.prcParse(tag);
    loadMask.prcParse(tag);
    cloneID = tag->getParam("CloneID", "0").to_uint();
    clonePlayerID = tag->getParam("ClonePlayerID", "0").to_uint();
}

ST::string plUoid::toString() const
{
    return ST::format("{}[{_04X}]{}", location.toString(),
                      classType, objName);
}
