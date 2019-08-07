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
#include "Math/pyMatrix.h"

PY_PLASMA_EMPTY_INIT(Matrix33Key)
PY_PLASMA_NEW(Matrix33Key, hsMatrix33Key)

PY_PROPERTY_MEMBER(hsMatrix33, Matrix33Key, value, fValue)

static PyGetSetDef pyMatrix33Key_GetSet[] = {
    pyMatrix33Key_value_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Matrix33Key, hsMatrix33Key, "hsMatrix33Key wrapper")

PY_PLASMA_TYPE_INIT(Matrix33Key)
{
    pyMatrix33Key_Type.tp_init = pyMatrix33Key___init__;
    pyMatrix33Key_Type.tp_new = pyMatrix33Key_new;
    pyMatrix33Key_Type.tp_getset = pyMatrix33Key_GetSet;
    pyMatrix33Key_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_CheckAndReady(&pyMatrix33Key_Type) < 0)
        return nullptr;

    Py_INCREF(&pyMatrix33Key_Type);
    return (PyObject*)&pyMatrix33Key_Type;
}

PY_PLASMA_IFC_METHODS(Matrix33Key, hsMatrix33Key)
