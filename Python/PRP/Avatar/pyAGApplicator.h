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

#ifndef _PYAGAPPLICATOR_H
#define _PYAGAPPLICATOR_H

#include "PyPlasma.h"

PY_WRAP_PLASMA(AGApplicator, class plAGApplicator);
PY_WRAP_PLASMA(SoundVolumeApplicator, class plSoundVolumeApplicator);
PY_WRAP_PLASMA(LightAmbientApplicator, class plLightAmbientApplicator);
PY_WRAP_PLASMA(LightDiffuseApplicator, class plLightDiffuseApplicator);
PY_WRAP_PLASMA(LightSpecularApplicator, class plLightSpecularApplicator);
PY_WRAP_PLASMA(OmniApplicator, class plOmniApplicator);
PY_WRAP_PLASMA(OmniCutoffApplicator, class plOmniCutoffApplicator);
PY_WRAP_PLASMA(OmniSqApplicator, class plOmniSqApplicator);
PY_WRAP_PLASMA(SpotInnerApplicator, class plSpotInnerApplicator);
PY_WRAP_PLASMA(SpotOuterApplicator, class plSpotOuterApplicator);
PY_WRAP_PLASMA(MatrixChannelApplicator, class plMatrixChannelApplicator);
PY_WRAP_PLASMA(MatrixDelayedCorrectionApplicator, class plMatrixDelayedCorrectionApplicator);
PY_WRAP_PLASMA(MatrixDifferenceApp, class plMatrixDifferenceApp);
PY_WRAP_PLASMA(RelativeMatrixChannelApplicator, class plRelativeMatrixChannelApplicator);
PY_WRAP_PLASMA(PointChannelApplicator, class plPointChannelApplicator);
PY_WRAP_PLASMA(QuatChannelApplicator, class plQuatChannelApplicator);
PY_WRAP_PLASMA(ScalarChannelApplicator, class plScalarChannelApplicator);

#endif
