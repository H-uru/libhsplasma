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

#include "pySpan.h"

#include <PRP/Geometry/plIcicle.h>
#include "pyGBufferGroup.h"

extern "C" {

PY_PLASMA_NEW(Icicle, plIcicle)

static PyObject* pyIcicle_getSortData(pyIcicle* self, void*) {
    int size = self->fThis->getILength() / 3;
    const plGBufferTriangle* sortData = self->fThis->getSortData();
    if (sortData == NULL) {
        PyObject* list = PyList_New(0);
        return list;
    } else {
        PyObject* list = PyList_New(size);
        for (int i=0; i<size; i++)
            PyList_SET_ITEM(list, i, pyGBufferTriangle_FromGBufferTriangle(sortData[i]));
        return list;
    }
}

static int pyIcicle_setSortData(pyIcicle* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setSortData(NULL);
        return 0;
    } else if (PyList_Check(value)) {
        int size = PyList_Size(value);
        plGBufferTriangle* sortData = new plGBufferTriangle[size];
        for (int i=0; i<size; i++) {
            if (!pyGBufferTriangle_Check(PyList_GetItem(value, i))) {
                PyErr_SetString(PyExc_TypeError, "sortData should be a list of plGBufferTriangles");
                delete[] sortData;
                return -1;
            }
            sortData[i] = *((pyGBufferTriangle*)PyList_GetItem(value, i))->fThis;
        }
        self->fThis->setSortData(sortData);
        delete[] sortData;
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "sortData should be a list of plGBufferTriangles");
        return -1;
    }
}

PY_PROPERTY(unsigned int, Icicle, IBufferIdx, getIBufferIdx, setIBufferIdx)
PY_PROPERTY(unsigned int, Icicle, IStartIdx, getIStartIdx, setIStartIdx)
PY_PROPERTY(unsigned int, Icicle, ILength, getILength, setILength)

static PyGetSetDef pyIcicle_GetSet[] = {
    pyIcicle_IBufferIdx_getset,
    pyIcicle_IStartIdx_getset,
    pyIcicle_ILength_getset,
    { _pycs("sortData"), (getter)pyIcicle_getSortData, (setter)pyIcicle_setSortData,
      _pycs("Optional face sort data"), NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Icicle, plIcicle, "plIcicle wrapper")

PY_PLASMA_TYPE_INIT(Icicle) {
    pyIcicle_Type.tp_new = pyIcicle_new;
    pyIcicle_Type.tp_getset = pyIcicle_GetSet;
    pyIcicle_Type.tp_base = &pyVertexSpan_Type;
    if (PyType_Ready(&pyIcicle_Type) < 0)
        return NULL;

    Py_INCREF(&pyIcicle_Type);
    return (PyObject*)&pyIcicle_Type;
}

PY_PLASMA_IFC_METHODS(Icicle, plIcicle)

}
