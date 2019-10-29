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

#include "pyUnifiedTime.h"

PY_PLASMA_VALUE_DEALLOC(UnifiedTime)

PY_PLASMA_INIT_DECL(UnifiedTime)
{
    double time = 0;
    if (!PyArg_ParseTuple(args, "|d", &time)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects an optional float");
        return -1;
    }
    if (time)
        *self->fThis = plUnifiedTime(time);
    return 0;
}

PY_PLASMA_VALUE_NEW(UnifiedTime, plUnifiedTime)

PY_PROPERTY(double, UnifiedTime, secs, getSecsDouble, setSecsDouble)

static PyGetSetDef pyUnifiedTime_GetSet[] = {
    pyUnifiedTime_secs_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(UnifiedTime, hsUnifiedTime, "plUnifiedTime wrapper")

PY_PLASMA_TYPE_INIT(UnifiedTime)
{
    pyUnifiedTime_Type.tp_dealloc = pyUnifiedTime_dealloc;
    pyUnifiedTime_Type.tp_init = pyUnifiedTime___init__;
    pyUnifiedTime_Type.tp_new = pyUnifiedTime_new;
    pyUnifiedTime_Type.tp_getset = pyUnifiedTime_GetSet;
    if (PyType_CheckAndReady(&pyUnifiedTime_Type) < 0)
        return nullptr;

    Py_INCREF(&pyUnifiedTime_Type);
    return (PyObject*)&pyUnifiedTime_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(UnifiedTime, plUnifiedTime)
