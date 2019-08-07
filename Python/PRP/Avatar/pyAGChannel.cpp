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

#include <PRP/Avatar/plAGChannel.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(AGChannel, "plAGChannel is abstract")

PY_PROPERTY(ST::string, AGChannel, name, getName, setName)

static PyGetSetDef pyAGChannel_GetSet[] = {
    pyAGChannel_name_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AGChannel, plAGChannel, "plAGChannel wrapper")

PY_PLASMA_TYPE_INIT(AGChannel)
{
    pyAGChannel_Type.tp_new = pyAGChannel_new;
    pyAGChannel_Type.tp_getset = pyAGChannel_GetSet;
    pyAGChannel_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyAGChannel_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAGChannel_Type);
    return (PyObject*)&pyAGChannel_Type;
}

PY_PLASMA_IFC_METHODS(AGChannel, plAGChannel)
