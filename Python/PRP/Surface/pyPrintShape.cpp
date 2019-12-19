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

#include "pyPrintShape.h"

#include <PRP/Surface/plPrintShape.h>
#include "PRP/Object/pyObjInterface.h"

PY_PLASMA_NEW(PrintShape, plPrintShape)

PY_PROPERTY(float, PrintShape, width, getWidth, setWidth)
PY_PROPERTY(float, PrintShape, length, getLength, setLength)
PY_PROPERTY(float, PrintShape, height, getHeight, setHeight)

static PyGetSetDef pyPrintShape_GetSet[] = {
    pyPrintShape_width_getset,
    pyPrintShape_length_getset,
    pyPrintShape_height_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(PrintShape, plPrintShape, "plPrintShape wrapper")

PY_PLASMA_TYPE_INIT(PrintShape)
{
    pyPrintShape_Type.tp_new = pyPrintShape_new;
    pyPrintShape_Type.tp_getset = pyPrintShape_GetSet;
    pyPrintShape_Type.tp_base = &pyObjInterface_Type;
    if (PyType_CheckAndReady(&pyPrintShape_Type) < 0)
        return nullptr;

    Py_INCREF(&pyPrintShape_Type);
    return (PyObject*)&pyPrintShape_Type;
}

PY_PLASMA_IFC_METHODS(PrintShape, plPrintShape)
