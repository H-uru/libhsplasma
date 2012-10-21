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

#include <PyPlasma.h>
#include <PRP/Geometry/plGBufferGroup.h>
#include "pyGBufferGroup.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyGBufferGroup_dealloc(pyGBufferGroup* self) {
    if (self->fPyOwned)
        delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyGBufferGroup___init__(pyGBufferGroup* self, PyObject* args, PyObject* kwds) {
    int fmt;
    if (!PyArg_ParseTuple(args, "i", &fmt))
        return -1;
    self->fThis->setFormat(fmt);
    return 0;
}

static PyObject* pyGBufferGroup_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyGBufferGroup* self = (pyGBufferGroup*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plGBufferGroup(0);
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyGBufferGroup_read(pyGBufferGroup* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferGroup_write(pyGBufferGroup* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferGroup_getVerts(pyGBufferGroup* self, PyObject* args) {
    int idx, start = 0, len = -1;
    if (!PyArg_ParseTuple(args, "i|ii", &idx, &start, &len)) {
        PyErr_SetString(PyExc_TypeError, "getVertices expects an int");
        return NULL;
    }

    hsTArray<plGBufferVertex> verts;
    if (start == 0 && len == -1)
        verts = self->fThis->getVertices(idx);
    else
        verts = self->fThis->getVertices(start, len);
    PyObject* list = PyList_New(verts.getSize());
    for (size_t i=0; i<verts.getSize(); i++)
        PyList_SET_ITEM(list, i, pyGBufferVertex_FromGBufferVertex(verts[i]));
    return list;
}

static PyObject* pyGBufferGroup_getIndices(pyGBufferGroup* self, PyObject* args) {
    int idx, start = 0, len = -1;
    if (!PyArg_ParseTuple(args, "i|ii", &idx, &start, &len)) {
        PyErr_SetString(PyExc_TypeError, "getIndices expects an int");
        return NULL;
    }

    hsTArray<unsigned short> indices;
    if (start == 0 && len == -1)
        indices = self->fThis->getIndices(idx);
    else
        indices = self->fThis->getIndices(idx, start, len);
    PyObject* list = PyList_New(indices.getSize());
    for (size_t i=0; i<indices.getSize(); i++)
        PyList_SET_ITEM(list, i, PyInt_FromLong(indices[i]));
    return list;
}

static PyObject* pyGBufferGroup_getCells(pyGBufferGroup* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getCells expects an int");
        return NULL;
    }

    hsTArray<plGBufferCell> cells = self->fThis->getCells(idx);
    PyObject* list = PyList_New(cells.getSize());
    for (size_t i=0; i<cells.getSize(); i++)
        PyList_SET_ITEM(list, i, pyGBufferCell_FromGBufferCell(cells[i]));
    return list;
}

static PyObject* pyGBufferGroup_addVerts(pyGBufferGroup* self, PyObject* args) {
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addVertices expects a list of plGBufferVertex objects");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addVertices expects a list of plGBufferVertex objects");
        return NULL;
    }

    hsTArray<plGBufferVertex> verts;
    verts.setSize(PyList_Size(list));
    for (size_t i=0; i<verts.getSize(); i++) {
        if (!pyGBufferVertex_Check(PyList_GetItem(list, i))) {
            PyErr_SetString(PyExc_TypeError, "addVertices expects a list of plGBufferVertex objects");
            return NULL;
        }
        verts[i] = *((pyGBufferVertex*)PyList_GetItem(list, i))->fThis;
    }
    self->fThis->addVertices(verts);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferGroup_addIndices(pyGBufferGroup* self, PyObject* args) {
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addIndices expects a list of ints");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addIndices expects a list of ints");
        return NULL;
    }

    hsTArray<unsigned short> indices;
    indices.setSize(PyList_Size(list));
    for (size_t i=0; i<indices.getSize(); i++) {
        if (!PyInt_Check(PyList_GetItem(list, i))) {
            PyErr_SetString(PyExc_TypeError, "addVertices expects a list of ints");
            return NULL;
        }
        indices[i] = PyInt_AsLong(PyList_GetItem(list, i));
    }
    self->fThis->addIndices(indices);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferGroup_addCells(pyGBufferGroup* self, PyObject* args) {
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addCells expects a list of plGBufferCell objects");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addCells expects a list of plGBufferCell objects");
        return NULL;
    }

    hsTArray<plGBufferCell> cells;
    cells.setSize(PyList_Size(list));
    for (size_t i=0; i<cells.getSize(); i++) {
        if (!pyGBufferCell_Check(PyList_GetItem(list, i))) {
            PyErr_SetString(PyExc_TypeError, "addCells expects a list of plGBufferCell objects");
            return NULL;
        }
        cells[i] = *((pyGBufferCell*)PyList_GetItem(list, i))->fThis;
    }
    self->fThis->addCells(cells);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferGroup_delVerts(pyGBufferGroup* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delVertices expects an int");
        return NULL;
    }
    self->fThis->delVertices(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferGroup_delIndices(pyGBufferGroup* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delIndices expects an int");
        return NULL;
    }
    self->fThis->delIndices(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferGroup_delCells(pyGBufferGroup* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCells expects an int");
        return NULL;
    }
    self->fThis->delCells(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferGroup_clearVerts(pyGBufferGroup* self) {
    self->fThis->clearVertices();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferGroup_clearIndices(pyGBufferGroup* self) {
    self->fThis->clearIndices();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferGroup_clearCells(pyGBufferGroup* self) {
    self->fThis->clearCells();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferGroup_getNumVertBuffers(pyGBufferGroup* self) {
    return PyInt_FromLong(self->fThis->getNumVertBuffers());
}

static PyObject* pyGBufferGroup_getNumIdxBuffers(pyGBufferGroup* self) {
    return PyInt_FromLong(self->fThis->getNumIdxBuffers());
}

static PyObject* pyGBufferGroup_getVertBufferStorage(pyGBufferGroup* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getVertBufferStorage expects an int");
        return NULL;
    }
    return PyBytes_FromStringAndSize((const char*)self->fThis->getVertBufferStorage(idx),
                                     self->fThis->getVertBufferSize(idx));
}

static PyObject* pyGBufferGroup_getIdxBufferStorage(pyGBufferGroup* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getIdxBufferStorage expects an int");
        return NULL;
    }
    size_t count = self->fThis->getIdxBufferCount(idx);
    const unsigned short* indices = self->fThis->getIdxBufferStorage(idx);
    PyObject* idxList = PyList_New(count);
    for (size_t i=0; i<count; i++)
        PyList_SET_ITEM(idxList, i, PyInt_FromLong(indices[i]));
    return idxList;
}

static PyObject* pyGBufferGroup_getVertBufferSize(pyGBufferGroup* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getVertBufferSize expects an int");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->getVertBufferSize(idx));
}

static PyObject* pyGBufferGroup_getIdxBufferCount(pyGBufferGroup* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getIdxBufferCount expects an int");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->getIdxBufferCount(idx));
}

static PyObject* pyGBufferGroup_getFormat(pyGBufferGroup* self, void*) {
    return PyInt_FromLong(self->fThis->getFormat());
}

static PyObject* pyGBufferGroup_getSkinWeights(pyGBufferGroup* self, void*) {
    return PyInt_FromLong(self->fThis->getSkinWeights());
}

static PyObject* pyGBufferGroup_getNumUVs(pyGBufferGroup* self, void*) {
    return PyInt_FromLong(self->fThis->getNumUVs());
}

static PyObject* pyGBufferGroup_getHasSIs(pyGBufferGroup* self, void*) {
    return PyBool_FromLong(self->fThis->getHasSkinIndices());
}

static PyObject* pyGBufferGroup_getStride(pyGBufferGroup* self, void*) {
    return PyInt_FromLong(self->fThis->getStride());
}

static int pyGBufferGroup_setFormat(pyGBufferGroup* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "format should be an int");
        return -1;
    }
    self->fThis->setFormat(PyInt_AsLong(value));
    return 0;
}

static int pyGBufferGroup_setSkinWeights(pyGBufferGroup* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "skinWeights should be an int");
        return -1;
    }
    self->fThis->setSkinWeights(PyInt_AsLong(value));
    return 0;
}

static int pyGBufferGroup_setNumUVs(pyGBufferGroup* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "numUVs should be an int");
        return -1;
    }
    self->fThis->setNumUVs(PyInt_AsLong(value));
    return 0;
}

static int pyGBufferGroup_setHasSIs(pyGBufferGroup* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "hasSkinIndices should be a bool");
        return -1;
    }
    self->fThis->setHasSkinIndices(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyGBufferGroup_setStride(pyGBufferGroup* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "stride is read-only");
    return -1;
}

static PyMethodDef pyGBufferGroup_Methods[] = {
    { "read", (PyCFunction)pyGBufferGroup_read, METH_VARARGS,
      "Params: stream\n"
      "Read this BufferGroup from a stream" },
    { "write", (PyCFunction)pyGBufferGroup_write, METH_VARARGS,
      "Params: stream\n"
      "Write this BufferGroup to a stream" },
    { "getVertices", (PyCFunction)pyGBufferGroup_getVerts, METH_VARARGS,
      "Params: idx\n"
      "Get the specified vertex group as a list of plGBufferVertex objects" },
    { "getIndices", (PyCFunction)pyGBufferGroup_getIndices, METH_VARARGS,
      "Params: idx\n"
      "Get the specified face index list as a list of indices" },
    { "getCells", (PyCFunction)pyGBufferGroup_getCells, METH_VARARGS,
      "Params: idx\n"
      "Get the specified cell list as a list of plGBufferCell objects" },
    { "addVertices", (PyCFunction)pyGBufferGroup_addVerts, METH_VARARGS,
      "Params: list\n"
      "Add a Vertex Buffer with the contents of the supplied vertex list" },
    { "addIndices", (PyCFunction)pyGBufferGroup_addIndices, METH_VARARGS,
      "Params: list\n"
      "Add a Face Index Buffer with the contents of the supplied index list" },
    { "addCells", (PyCFunction)pyGBufferGroup_addCells, METH_VARARGS,
      "Params: list\n"
      "Add a Cell Buffer with the contents of the specified cell list" },
    { "delVertices", (PyCFunction)pyGBufferGroup_delVerts, METH_VARARGS,
      "Params: idx\n"
      "Remove the specified Vertex buffer" },
    { "delIndices", (PyCFunction)pyGBufferGroup_delIndices, METH_VARARGS,
      "Params: idx\n"
      "Remove the specified Face Index buffer" },
    { "delCells", (PyCFunction)pyGBufferGroup_delCells, METH_VARARGS,
      "Params: idx\n"
      "Remove the specified Cell buffer" },
    { "clearVertices", (PyCFunction)pyGBufferGroup_clearVerts, METH_NOARGS,
      "Remove all Vertex buffers" },
    { "clearIndices", (PyCFunction)pyGBufferGroup_clearIndices, METH_NOARGS,
      "Remove all Face Index buffers" },
    { "clearCells", (PyCFunction)pyGBufferGroup_clearCells, METH_NOARGS,
      "Remove all Cell buffers" },
    { "getNumVertBuffers", (PyCFunction)pyGBufferGroup_getNumVertBuffers, METH_NOARGS,
      "Return the nubmer of stored Vertex buffers" },
    { "getNumIdxBuffers", (PyCFunction)pyGBufferGroup_getNumIdxBuffers, METH_NOARGS,
      "Return the nubmer of stored Index buffers" },
    { "getVertBufferStorage", (PyCFunction)pyGBufferGroup_getVertBufferStorage, METH_VARARGS,
      "Params: idx\n"
      "Retrieve a raw Vertex buffer" },
    { "getIdxBufferStorage", (PyCFunction)pyGBufferGroup_getIdxBufferStorage, METH_VARARGS,
      "Params: idx\n"
      "Retrieve a raw Vertex buffer" },
    { "getVertBufferSize", (PyCFunction)pyGBufferGroup_getVertBufferSize, METH_VARARGS,
      "Params: idx\n"
      "Return the size of the specified Vertex buffer" },
    { "getIdxBufferCount", (PyCFunction)pyGBufferGroup_getIdxBufferCount, METH_VARARGS,
      "Params: idx\n"
      "Return the number of indices in the specified Index buffer" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyGBufferGroup_GetSet[] = {
    { _pycs("format"), (getter)pyGBufferGroup_getFormat,
        (setter)pyGBufferGroup_setFormat, NULL, NULL },
    { _pycs("skinWeights"), (getter)pyGBufferGroup_getSkinWeights,
        (setter)pyGBufferGroup_setSkinWeights, NULL, NULL },
    { _pycs("numUVs"), (getter)pyGBufferGroup_getNumUVs,
        (setter)pyGBufferGroup_setNumUVs, NULL, NULL },
    { _pycs("hasSkinIndices"), (getter)pyGBufferGroup_getHasSIs,
        (setter)pyGBufferGroup_setHasSIs, NULL, NULL },
    { _pycs("stride"), (getter)pyGBufferGroup_getStride,
        (setter)pyGBufferGroup_setStride, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyGBufferGroup_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plGBufferGroup",          /* tp_name */
    sizeof(pyGBufferGroup),             /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyGBufferGroup_dealloc, /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plGBufferGroup wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyGBufferGroup_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyGBufferGroup_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyGBufferGroup___init__,  /* tp_init */
    NULL,                               /* tp_alloc */
    pyGBufferGroup_new,                 /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pyGBufferGroup_Type() {
    if (PyType_Ready(&pyGBufferGroup_Type) < 0)
        return NULL;

    // Formats
    PyDict_SetItemString(pyGBufferGroup_Type.tp_dict, "kUVCountMask",
                         PyInt_FromLong(plGBufferGroup::kUVCountMask));
    PyDict_SetItemString(pyGBufferGroup_Type.tp_dict, "kSkinNoWeights",
                         PyInt_FromLong(plGBufferGroup::kSkinNoWeights));
    PyDict_SetItemString(pyGBufferGroup_Type.tp_dict, "kSkin1Weight",
                         PyInt_FromLong(plGBufferGroup::kSkin1Weight));
    PyDict_SetItemString(pyGBufferGroup_Type.tp_dict, "kSkin2Weights",
                         PyInt_FromLong(plGBufferGroup::kSkin2Weights));
    PyDict_SetItemString(pyGBufferGroup_Type.tp_dict, "kSkin3Weights",
                         PyInt_FromLong(plGBufferGroup::kSkin3Weights));
    PyDict_SetItemString(pyGBufferGroup_Type.tp_dict, "kSkinWeightMask",
                         PyInt_FromLong(plGBufferGroup::kSkinWeightMask));
    PyDict_SetItemString(pyGBufferGroup_Type.tp_dict, "kSkinIndices",
                         PyInt_FromLong(plGBufferGroup::kSkinIndices));
    PyDict_SetItemString(pyGBufferGroup_Type.tp_dict, "kEncoded",
                         PyInt_FromLong(plGBufferGroup::kEncoded));

    Py_INCREF(&pyGBufferGroup_Type);
    return (PyObject*)&pyGBufferGroup_Type;
}

int pyGBufferGroup_Check(PyObject* obj) {
    if (obj->ob_type == &pyGBufferGroup_Type
        || PyType_IsSubtype(obj->ob_type, &pyGBufferGroup_Type))
        return 1;
    return 0;
}

PyObject* pyGBufferGroup_FromGBufferGroup(plGBufferGroup* bg) {
    if (bg == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyGBufferGroup* pybg = PyObject_New(pyGBufferGroup, &pyGBufferGroup_Type);
    pybg->fThis = bg;
    pybg->fPyOwned = false;
    return (PyObject*)pybg;
}

}
