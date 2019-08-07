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

#include "pyController.h"

#include <PRP/Animation/plTMController.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_EMPTY_INIT(CompoundController)
PY_PLASMA_NEW(CompoundController, plCompoundController)

PY_METHOD_NOARGS(CompoundController, convertToTMController,
    "Converts this controller to a plTMController")
{
    return ICreate(self->fThis->convertToTMController());
}

static PyMethodDef pyCompoundController_Methods[] = {
    pyCompoundController_convertToTMController_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_CREATABLE(plController, Controller, CompoundController, X,
                      getXController, setXController)
PY_PROPERTY_CREATABLE(plController, Controller, CompoundController, Y,
                      getYController, setYController)
PY_PROPERTY_CREATABLE(plController, Controller, CompoundController, Z,
                      getZController, setZController)

static PyGetSetDef pyCompoundController_GetSet[] = {
    pyCompoundController_X_getset,
    pyCompoundController_Y_getset,
    pyCompoundController_Z_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CompoundController, plCompoundController, "plCompoundController wrapper")

PY_PLASMA_TYPE_INIT(CompoundController)
{
    pyCompoundController_Type.tp_init = pyCompoundController___init__;
    pyCompoundController_Type.tp_new = pyCompoundController_new;
    pyCompoundController_Type.tp_methods = pyCompoundController_Methods;
    pyCompoundController_Type.tp_getset = pyCompoundController_GetSet;
    pyCompoundController_Type.tp_base = &pyController_Type;
    if (PyType_CheckAndReady(&pyCompoundController_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCompoundController_Type);
    return (PyObject*)&pyCompoundController_Type;
}

PY_PLASMA_IFC_METHODS(CompoundController, plCompoundController)
