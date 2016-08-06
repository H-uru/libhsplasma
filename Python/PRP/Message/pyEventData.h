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

#ifndef _PYEVENTDATA_H
#define _PYEVENTDATA_H

#include "PyPlasma.h"

PY_WRAP_PLASMA(EventData, class proEventData);
PY_WRAP_PLASMA(CollisionEventData, class proCollisionEventData);
PY_WRAP_PLASMA(PickedEventData, class proPickedEventData);
PY_WRAP_PLASMA(ControlKeyEventData, class proControlKeyEventData);
PY_WRAP_PLASMA(VariableEventData, class proVariableEventData);
PY_WRAP_PLASMA(FacingEventData, class proFacingEventData);
PY_WRAP_PLASMA(ContainedEventData, class proContainedEventData);
PY_WRAP_PLASMA(ActivateEventData, class proActivateEventData);
PY_WRAP_PLASMA(CallbackEventData, class proCallbackEventData);
PY_WRAP_PLASMA(ResponderStateEventData, class proResponderStateEventData);
PY_WRAP_PLASMA(MultiStageEventData, class proMultiStageEventData);
PY_WRAP_PLASMA(SpawnedEventData, class proSpawnedEventData);
PY_WRAP_PLASMA(ClickDragEventData, class proClickDragEventData);
PY_WRAP_PLASMA(CoopEventData, class proCoopEventData);
PY_WRAP_PLASMA(OfferLinkBookEventData, class proOfferLinkBookEventData);
PY_WRAP_PLASMA(BookEventData, class proBookEventData);
PY_WRAP_PLASMA(ClimbingBlockerHitEventData, class proClimbingBlockerHitEventData);

#endif
