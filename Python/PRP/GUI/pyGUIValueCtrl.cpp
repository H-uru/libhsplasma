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

#include <PRP/GUI/pfGUIValueCtrl.h>
#include "pyGUIValueCtrl.h"
#include "PRP/GUI/pyGUIControlMod.h"

PY_PLASMA_NEW(GUIValueCtrl, pfGUIValueCtrl)

PY_PROPERTY(float, GUIValueCtrl, min, getMin, setMin)
PY_PROPERTY(float, GUIValueCtrl, max, getMax, setMax)
PY_PROPERTY(float, GUIValueCtrl, step, getStep, setStep)

static PyGetSetDef pyGUIValueCtrl_GetSet[] = {
    pyGUIValueCtrl_min_getset,
    pyGUIValueCtrl_max_getset,
    pyGUIValueCtrl_step_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIValueCtrl, pfGUIValueCtrl, "pfGUIValueCtrl wrapper")

PY_PLASMA_TYPE_INIT(GUIValueCtrl)
{
    pyGUIValueCtrl_Type.tp_new = pyGUIValueCtrl_new;
    pyGUIValueCtrl_Type.tp_getset = pyGUIValueCtrl_GetSet;
    pyGUIValueCtrl_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_CheckAndReady(&pyGUIValueCtrl_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGUIValueCtrl_Type);
    return (PyObject*)&pyGUIValueCtrl_Type;
}

PY_PLASMA_IFC_METHODS(GUIValueCtrl, pfGUIValueCtrl)
