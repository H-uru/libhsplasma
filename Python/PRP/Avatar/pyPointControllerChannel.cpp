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

#include "pyAGChannel.h"

#include <PRP/Avatar/plPointChannel.h>
#include "PRP/pyCreatable.h"
#include "PRP/Animation/pyController.h"

PY_PLASMA_NEW(PointControllerChannel, plPointControllerChannel)

PY_PROPERTY_CREATABLE(plController, Controller, PointControllerChannel,
                      controller, getController, setController)

static PyGetSetDef pyPointControllerChannel_GetSet[] = {
    pyPointControllerChannel_controller_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(PointControllerChannel, plPointControllerChannel,
               "plPointControllerChannel wrapper")

PY_PLASMA_TYPE_INIT(PointControllerChannel)
{
    pyPointControllerChannel_Type.tp_new = pyPointControllerChannel_new;
    pyPointControllerChannel_Type.tp_getset = pyPointControllerChannel_GetSet;
    pyPointControllerChannel_Type.tp_base = &pyPointChannel_Type;
    if (PyType_CheckAndReady(&pyPointControllerChannel_Type) < 0)
        return nullptr;

    Py_INCREF(&pyPointControllerChannel_Type);
    return (PyObject*)&pyPointControllerChannel_Type;
}

PY_PLASMA_IFC_METHODS(PointControllerChannel, plPointControllerChannel)
