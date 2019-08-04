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

#include "plMaintainersMarkerModifier.h"

static const char* CalibratedLevelNames[] = {
    "Broken", "Repaired", "Calibrated"
};

void plMaintainersMarkerModifier::read(hsStream* S, plResManager* mgr)
{
    plMultiModifier::read(S, mgr);
    fCalibrated = S->readInt();
}

void plMaintainersMarkerModifier::write(hsStream* S, plResManager* mgr)
{
    plMultiModifier::write(S, mgr);
    S->writeInt(fCalibrated);
}

void plMaintainersMarkerModifier::IPrcWrite(pfPrcHelper* prc)
{
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("Calibration");
    prc->writeParam("Level", CalibratedLevelNames[fCalibrated]);
    prc->endTag(true);
}

void plMaintainersMarkerModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Calibration") {
        ST::string level = tag->getParam("Level", "Broken");
        fCalibrated = kBroken;
        for (size_t i=0; i<kNumCalibratedLevels; i++) {
            if (level == CalibratedLevelNames[i])
                fCalibrated = i;
        }
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
