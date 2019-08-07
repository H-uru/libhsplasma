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

#include "pyPosController.h"

#include <PRP/Animation/plPosController.h>
#include "pyLeafController.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_EMPTY_INIT(SimplePosController)
PY_PLASMA_NEW(SimplePosController, plSimplePosController)

PY_PROPERTY_CREATABLE(plPoint3Controller, Point3Controller, SimplePosController,
                      position, getPosition, setPosition)

static PyGetSetDef pySimplePosController_GetSet[] = {
    pySimplePosController_position_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SimplePosController, plSimplePosController,
               "plSimplePosController wrapper")

PY_PLASMA_TYPE_INIT(SimplePosController)
{
    pySimplePosController_Type.tp_init = pySimplePosController___init__;
    pySimplePosController_Type.tp_new = pySimplePosController_new;
    pySimplePosController_Type.tp_getset = pySimplePosController_GetSet;
    pySimplePosController_Type.tp_base = &pyPosController_Type;
    if (PyType_CheckAndReady(&pySimplePosController_Type) < 0)
        return nullptr;

    Py_INCREF(&pySimplePosController_Type);
    return (PyObject*)&pySimplePosController_Type;
}

PY_PLASMA_IFC_METHODS(SimplePosController, plSimplePosController)
