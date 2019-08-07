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

#include "pyAnimationEventConditionalObject.h"

#include <PRP/ConditionalObject/plAnimationEventConditionalObject.h>
#include "pyConditionalObject.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(AnimationEventConditionalObject, plAnimationEventConditionalObject)

PY_PROPERTY(CallbackEvent, AnimationEventConditionalObject, action, getAction, setAction)
PY_PROPERTY(plKey, AnimationEventConditionalObject, target, getTarget, setTarget)

static PyGetSetDef pyAnimationEventConditionalObject_GetSet[] = {
    pyAnimationEventConditionalObject_action_getset,
    pyAnimationEventConditionalObject_target_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AnimationEventConditionalObject, plAnimationEventConditionalObject,
               "plAnimationEventConditionalObject wrapper")

PY_PLASMA_TYPE_INIT(AnimationEventConditionalObject)
{
    pyAnimationEventConditionalObject_Type.tp_new = pyAnimationEventConditionalObject_new;
    pyAnimationEventConditionalObject_Type.tp_getset = pyAnimationEventConditionalObject_GetSet;
    pyAnimationEventConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_CheckAndReady(&pyAnimationEventConditionalObject_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAnimationEventConditionalObject_Type);
    return (PyObject*)&pyAnimationEventConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(AnimationEventConditionalObject, plAnimationEventConditionalObject)
