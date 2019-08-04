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

#include "pyEventData.h"

#include <PRP/Message/proEventData.h>
#include <typeinfo>

PyObject* ICreateEventData(proEventData* edata)
{
    if (typeid(edata) == typeid(proCollisionEventData))
        return pyCollisionEventData_FromCollisionEventData((proCollisionEventData*)edata);
    else if (typeid(edata) == typeid(proPickedEventData))
        return pyPickedEventData_FromPickedEventData((proPickedEventData*)edata);
    else if (typeid(edata) == typeid(proControlKeyEventData))
        return pyControlKeyEventData_FromControlKeyEventData((proControlKeyEventData*)edata);
    else if (typeid(edata) == typeid(proVariableEventData))
        return pyVariableEventData_FromVariableEventData((proVariableEventData*)edata);
    else if (typeid(edata) == typeid(proFacingEventData))
        return pyFacingEventData_FromFacingEventData((proFacingEventData*)edata);
    else if (typeid(edata) == typeid(proContainedEventData))
        return pyContainedEventData_FromContainedEventData((proContainedEventData*)edata);
    else if (typeid(edata) == typeid(proActivateEventData))
        return pyActivateEventData_FromActivateEventData((proActivateEventData*)edata);
    else if (typeid(edata) == typeid(proCallbackEventData))
        return pyCallbackEventData_FromCallbackEventData((proCallbackEventData*)edata);
    else if (typeid(edata) == typeid(proResponderStateEventData))
        return pyResponderStateEventData_FromResponderStateEventData((proResponderStateEventData*)edata);
    else if (typeid(edata) == typeid(proMultiStageEventData))
        return pyMultiStageEventData_FromMultiStageEventData((proMultiStageEventData*)edata);
    else if (typeid(edata) == typeid(proSpawnedEventData))
        return pySpawnedEventData_FromSpawnedEventData((proSpawnedEventData*)edata);
    else if (typeid(edata) == typeid(proClickDragEventData))
        return pyClickDragEventData_FromClickDragEventData((proClickDragEventData*)edata);
    else if (typeid(edata) == typeid(proCoopEventData))
        return pyCoopEventData_FromCoopEventData((proCoopEventData*)edata);
    else if (typeid(edata) == typeid(proOfferLinkBookEventData))
        return pyOfferLinkBookEventData_FromOfferLinkBookEventData((proOfferLinkBookEventData*)edata);
    else if (typeid(edata) == typeid(proBookEventData))
        return pyBookEventData_FromBookEventData((proBookEventData*)edata);
    else if (typeid(edata) == typeid(proClimbingBlockerHitEventData))
        return pyClimbingBlockerHitEventData_FromClimbingBlockerHitEventData((proClimbingBlockerHitEventData*)edata);
    return pyEventData_FromEventData(edata);
}
