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
#include "pyPosController.h"
#include "pyRotController.h"
#include "pyScaleController.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_EMPTY_INIT(TMController)
PY_PLASMA_NEW(TMController, plTMController)

PY_METHOD_NOARGS(TMController, convertToCompoundController,
    "Converts this controller to a plCompoundController")
{
    return ICreate(self->fThis->convertToCompoundController());
}

static PyMethodDef pyTMController_Methods[] = {
    pyTMController_convertToCompoundController_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_CREATABLE(plPosController, PosController, TMController, pos,
                      getPosController, setPosController)
PY_PROPERTY_CREATABLE(plRotController, RotController, TMController, rot,
                      getRotController, setRotController)
PY_PROPERTY_CREATABLE(plScaleController, ScaleController, TMController, scale,
                      getScaleController, setScaleController)

static PyGetSetDef pyTMController_GetSet[] = {
    pyTMController_pos_getset,
    pyTMController_rot_getset,
    pyTMController_scale_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(TMController, plTMController, "plTMController wrapper")

PY_PLASMA_TYPE_INIT(TMController)
{
    pyTMController_Type.tp_init = pyTMController___init__;
    pyTMController_Type.tp_new = pyTMController_new;
    pyTMController_Type.tp_methods = pyTMController_Methods;
    pyTMController_Type.tp_getset = pyTMController_GetSet;
    pyTMController_Type.tp_base = &pyController_Type;
    if (PyType_CheckAndReady(&pyTMController_Type) < 0)
        return nullptr;

    Py_INCREF(&pyTMController_Type);
    return (PyObject*)&pyTMController_Type;
}

PY_PLASMA_IFC_METHODS(TMController, plTMController)
