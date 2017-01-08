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

extern "C" {

PY_PLASMA_NEW(DynamicTextMap, plDynamicTextMap)

static PyObject* pyDynamicTextMap_getInitBuffer(pyDynamicTextMap* self, void*) {
    PyObject* data = PyList_New(self->fThis->getInitBufferSize());
    for (size_t i=0; i<self->fThis->getInitBufferSize(); i++)
        PyList_SET_ITEM(data, i, pyPlasma_convert(self->fThis->getInitBuffer()[i]));
    return data;
}

static int pyDynamicTextMap_setInitBuffer(pyDynamicTextMap* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setInitBuffer(NULL, 0);
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "initBuffer should be a list of ints");
        return -1;
    }
    int len = PyList_Size(value);
    unsigned int* buf = new unsigned int[len];
    for (int i=0; i<len; i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!PyInt_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "initBuffer should be a list of ints");
            delete[] buf;
            return -1;
        }
        buf[i] = PyInt_AsLong(itm);
    }
    self->fThis->setInitBuffer(buf, (size_t)len);
    delete[] buf;
    return 0;
}

PY_PROPERTY(unsigned int, DynamicTextMap, visWidth, getVisWidth, setVisWidth)
PY_PROPERTY(unsigned int, DynamicTextMap, visHeight, getVisHeight, setVisHeight)
PY_PROPERTY(bool, DynamicTextMap, hasAlpha, hasAlpha, setHasAlpha)

static PyGetSetDef pyDynamicTextMap_GetSet[] = {
    pyDynamicTextMap_visWidth_getset,
    pyDynamicTextMap_visHeight_getset,
    pyDynamicTextMap_hasAlpha_getset,
    { _pycs("initBuffer"), (getter)pyDynamicTextMap_getInitBuffer,
        (setter)pyDynamicTextMap_setInitBuffer, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DynamicTextMap, plDynamicTextMap, "plDynamicTextMap wrapper")

PY_PLASMA_TYPE_INIT(DynamicTextMap) {
    pyDynamicTextMap_Type.tp_new = pyDynamicTextMap_new;
    pyDynamicTextMap_Type.tp_getset = pyDynamicTextMap_GetSet;
    pyDynamicTextMap_Type.tp_base = &pyMipmap_Type;
    if (PyType_CheckAndReady(&pyDynamicTextMap_Type) < 0)
        return NULL;

    Py_INCREF(&pyDynamicTextMap_Type);
    return (PyObject*)&pyDynamicTextMap_Type;
}

PY_PLASMA_IFC_METHODS(DynamicTextMap, plDynamicTextMap)

}
