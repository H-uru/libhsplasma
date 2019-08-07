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

#include "pyFadeOpacityMod.h"

#include <PRP/Surface/plFadeOpacityMod.h>
#include "PRP/Modifier/pyModifier.h"

PY_PLASMA_NEW(FadeOpacityMod, plFadeOpacityMod)

PY_PROPERTY(float, FadeOpacityMod, fadeUp, getFadeUp, setFadeUp)
PY_PROPERTY(float, FadeOpacityMod, fadeDown, getFadeDown, setFadeDown)

/* Shortcut for self.{get,set}Flag(plFadeOpacityMod.kBoundsCenter) */
PY_GETSET_GETTER_DECL(FadeOpacityMod, boundsCenter)
{
    return pyPlasma_convert(self->fThis->getFlag(plFadeOpacityMod::kBoundsCenter));
}

PY_GETSET_SETTER_DECL(FadeOpacityMod, boundsCenter)
{
    PY_PROPERTY_CHECK_NULL(boundsCenter)
    if (!pyPlasma_check<bool>(value)) {
        PyErr_SetString(PyExc_TypeError, "boundsCenter should be a bool");
        return -1;
    }
    self->fThis->setFlag(plFadeOpacityMod::kBoundsCenter, pyPlasma_get<bool>(value));
    return 0;
}

PY_PROPERTY_GETSET_DECL(FadeOpacityMod, boundsCenter)

static PyGetSetDef pyFadeOpacityMod_GetSet [] = {
    pyFadeOpacityMod_fadeUp_getset,
    pyFadeOpacityMod_fadeDown_getset,
    pyFadeOpacityMod_boundsCenter_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(FadeOpacityMod, plFadeOpacityMod, "plFadeOpacityMod wrapper")

PY_PLASMA_TYPE_INIT(FadeOpacityMod)
{
    pyFadeOpacityMod_Type.tp_new = pyFadeOpacityMod_new;
    pyFadeOpacityMod_Type.tp_getset = pyFadeOpacityMod_GetSet;
    pyFadeOpacityMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyFadeOpacityMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyFadeOpacityMod_Type);
    return (PyObject*) &pyFadeOpacityMod_Type;
}

PY_PLASMA_IFC_METHODS(FadeOpacityMod, plFadeOpacityMod)
