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

#include "pyKeys.h"

#include <PRP/Animation/hsKeys.h>

PY_PLASMA_EMPTY_INIT(ScalarKey)
PY_PLASMA_NEW(ScalarKey, hsScalarKey)

PY_PROPERTY_MEMBER(float, ScalarKey, inTan, fInTan)
PY_PROPERTY_MEMBER(float, ScalarKey, outTan, fOutTan)
PY_PROPERTY_MEMBER(float, ScalarKey, value, fValue)

static PyGetSetDef pyScalarKey_GetSet[] = {
    pyScalarKey_inTan_getset,
    pyScalarKey_outTan_getset,
    pyScalarKey_value_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ScalarKey, hsScalarKey, "hsScalarKey wrapper")

PY_PLASMA_TYPE_INIT(ScalarKey)
{
    pyScalarKey_Type.tp_init = pyScalarKey___init__;
    pyScalarKey_Type.tp_new = pyScalarKey_new;
    pyScalarKey_Type.tp_getset = pyScalarKey_GetSet;
    pyScalarKey_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_CheckAndReady(&pyScalarKey_Type) < 0)
        return nullptr;

    Py_INCREF(&pyScalarKey_Type);
    return (PyObject*)&pyScalarKey_Type;
}

PY_PLASMA_IFC_METHODS(ScalarKey, hsScalarKey)
