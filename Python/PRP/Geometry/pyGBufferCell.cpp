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

#include "pyGBufferGroup.h"

#include <PRP/Geometry/plGBufferGroup.h>

PY_PLASMA_VALUE_DEALLOC(GBufferCell)
PY_PLASMA_EMPTY_INIT(GBufferCell)
PY_PLASMA_VALUE_NEW(GBufferCell, plGBufferCell)

PY_PROPERTY_MEMBER(unsigned int, GBufferCell, vtxStart, fVtxStart)
PY_PROPERTY_MEMBER(unsigned int, GBufferCell, colorStart, fColorStart)
PY_PROPERTY_MEMBER(unsigned int, GBufferCell, length, fLength)

static PyGetSetDef pyGBufferCell_GetSet[] = {
    pyGBufferCell_vtxStart_getset,
    pyGBufferCell_colorStart_getset,
    pyGBufferCell_length_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GBufferCell, plGBufferCell, "plGBufferCell wrapper")

PY_PLASMA_TYPE_INIT(GBufferCell)
{
    pyGBufferCell_Type.tp_dealloc = pyGBufferCell_dealloc;
    pyGBufferCell_Type.tp_init = pyGBufferCell___init__;
    pyGBufferCell_Type.tp_new = pyGBufferCell_new;
    pyGBufferCell_Type.tp_getset = pyGBufferCell_GetSet;
    if (PyType_CheckAndReady(&pyGBufferCell_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGBufferCell_Type);
    return (PyObject*)&pyGBufferCell_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(GBufferCell, plGBufferCell)
