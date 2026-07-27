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

#include "pyAxisAnimModifier.h"

#include <PRP/Modifier/plAxisAnimModifier.h>
#include "pyModifier.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Message/pyNotifyMsg.h"

PY_PLASMA_NEW(AxisAnimModifier, plAxisAnimModifier)

PY_PROPERTY(plKey, AxisAnimModifier, XAnim, getXAnim, setXAnim)
PY_PROPERTY(plKey, AxisAnimModifier, YAnim, getYAnim, setYAnim)
PY_PROPERTY(plKey, AxisAnimModifier, notificationKey, getNotificationKey, setNotificationKey)
PY_PROPERTY_CREATABLE(plNotifyMsg, NotifyMsg, AxisAnimModifier, notify,
    getNotify, setNotify)
PY_PROPERTY(ST::string, AxisAnimModifier, animLabel, getAnimLabel, setAnimLabel)
PY_PROPERTY(bool, AxisAnimModifier, allOrNothing, getAllOrNothing, setAllOrNothing)

static PyGetSetDef pyAxisAnimModifier_GetSet[] = {
    pyAxisAnimModifier_XAnim_getset,
    pyAxisAnimModifier_YAnim_getset,
    pyAxisAnimModifier_notificationKey_getset,
    pyAxisAnimModifier_notify_getset,
    pyAxisAnimModifier_animLabel_getset,
    pyAxisAnimModifier_allOrNothing_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AxisAnimModifier, plAxisAnimModifier,
    "plAxisAnimModifier wrapper")

PY_PLASMA_TYPE_INIT(AxisAnimModifier)
{
    pyAxisAnimModifier_Type.tp_new = pyAxisAnimModifier_new;
    pyAxisAnimModifier_Type.tp_getset = pyAxisAnimModifier_GetSet;
    pyAxisAnimModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyAxisAnimModifier_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAxisAnimModifier_Type);
    return (PyObject*)&pyAxisAnimModifier_Type;
}

PY_PLASMA_IFC_METHODS(AxisAnimModifier, plAxisAnimModifier)
