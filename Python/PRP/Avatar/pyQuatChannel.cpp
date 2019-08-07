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

#include <PRP/Avatar/plQuatChannel.h>
#include "PRP/pyCreatable.h"
#include "Math/pyGeometry3.h"

PY_PLASMA_NEW(QuatChannel, plQuatChannel)

PY_PROPERTY(hsQuat, QuatChannel, result, getResult, setResult)

static PyGetSetDef pyQuatChannel_GetSet[] = {
    pyQuatChannel_result_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(QuatChannel, plQuatChannel, "plQuatChannel wrapper")

PY_PLASMA_TYPE_INIT(QuatChannel)
{
    pyQuatChannel_Type.tp_new = pyQuatChannel_new;
    pyQuatChannel_Type.tp_getset = pyQuatChannel_GetSet;
    pyQuatChannel_Type.tp_base = &pyAGChannel_Type;
    if (PyType_CheckAndReady(&pyQuatChannel_Type) < 0)
        return nullptr;

    Py_INCREF(&pyQuatChannel_Type);
    return (PyObject*)&pyQuatChannel_Type;
}

PY_PLASMA_IFC_METHODS(QuatChannel, plQuatChannel)
