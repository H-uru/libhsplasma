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

#include "pyDynamicTextMap.h"

#include <PRP/Surface/plDynamicTextMap.h>
#include "pyBitmap.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(DynamicTextMap, plDynamicTextMap)

PY_GETSET_GETTER_DECL(DynamicTextMap, initBuffer)
{
    PyObject* data = PyTuple_New(self->fThis->getInitBufferSize());
    for (size_t i=0; i<self->fThis->getInitBufferSize(); i++)
        PyTuple_SET_ITEM(data, i, pyPlasma_convert(self->fThis->getInitBuffer()[i]));
    return data;
}

PY_GETSET_SETTER_DECL(DynamicTextMap, initBuffer)
{
    PY_PROPERTY_CHECK_NULL(initBuffer)
    if (value == Py_None) {
        self->fThis->setInitBuffer(nullptr, 0);
        return 0;
    }
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "initBuffer should be a sequence of ints");
        return -1;
    }
    Py_ssize_t len = seq.size();
    std::vector<unsigned int> buf(len);
    for (Py_ssize_t i=0; i<len; i++) {
        PyObject* itm = seq.get(i);
        if (!pyPlasma_check<unsigned int>(itm)) {
            PyErr_SetString(PyExc_TypeError, "initBuffer should be a sequence of ints");
            return -1;
        }
        buf[i] = pyPlasma_get<unsigned int>(itm);
    }
    self->fThis->setInitBuffer(&buf[0], buf.size());
    return 0;
}

PY_PROPERTY_GETSET_DECL(DynamicTextMap, initBuffer)

PY_PROPERTY(unsigned int, DynamicTextMap, visWidth, getVisWidth, setVisWidth)
PY_PROPERTY(unsigned int, DynamicTextMap, visHeight, getVisHeight, setVisHeight)
PY_PROPERTY(bool, DynamicTextMap, hasAlpha, hasAlpha, setHasAlpha)

static PyGetSetDef pyDynamicTextMap_GetSet[] = {
    pyDynamicTextMap_visWidth_getset,
    pyDynamicTextMap_visHeight_getset,
    pyDynamicTextMap_hasAlpha_getset,
    pyDynamicTextMap_initBuffer_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DynamicTextMap, plDynamicTextMap, "plDynamicTextMap wrapper")

PY_PLASMA_TYPE_INIT(DynamicTextMap)
{
    pyDynamicTextMap_Type.tp_new = pyDynamicTextMap_new;
    pyDynamicTextMap_Type.tp_getset = pyDynamicTextMap_GetSet;
    pyDynamicTextMap_Type.tp_base = &pyMipmap_Type;
    if (PyType_CheckAndReady(&pyDynamicTextMap_Type) < 0)
        return nullptr;

    Py_INCREF(&pyDynamicTextMap_Type);
    return (PyObject*)&pyDynamicTextMap_Type;
}

PY_PLASMA_IFC_METHODS(DynamicTextMap, plDynamicTextMap)
