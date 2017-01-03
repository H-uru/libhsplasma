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
#include "Stream/pyStream.h"

extern "C" {

PY_PLASMA_DEALLOC(GBufferGroup)

PY_PLASMA_INIT_DECL(GBufferGroup) {
    int fmt;
    if (!PyArg_ParseTuple(args, "i", &fmt))
        return -1;
    self->fThis->setFormat((unsigned int)fmt);
    return 0;
}

PY_PLASMA_NEW_VA(GBufferGroup, plGBufferGroup, 0)

PY_METHOD_VA(GBufferGroup, read,
    "Params: stream\n"
    "Read this BufferGroup from a stream")
{
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
    Py_RETURN_NONE;
}

PY_METHOD_VA(GBufferGroup, write,
    "Params: stream\n"
    "Write this BufferGroup to a stream")
{
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
    Py_RETURN_NONE;
}

PY_METHOD_VA(GBufferGroup, getVertices,
    "Params: idx\n"
    "Get the specified vertex group as a list of plGBufferVertex objects")
{
    int idx, start = 0, len = -1;
    if (!PyArg_ParseTuple(args, "i|ii", &idx, &start, &len)) {
        PyErr_SetString(PyExc_TypeError, "getVertices expects an int");
        return NULL;
    }

    std::vector<plGBufferVertex> verts;
    if (start == 0 && len == -1)
        verts = self->fThis->getVertices(idx);
    else
        verts = self->fThis->getVertices(start, len);
    PyObject* list = PyList_New(verts.size());
    for (size_t i=0; i<verts.size(); i++)
        PyList_SET_ITEM(list, i, pyGBufferVertex_FromGBufferVertex(verts[i]));
    return list;
}

PY_METHOD_VA(GBufferGroup, getIndices,
    "Params: idx\n"
    "Get the specified face index list as a list of indices")
{
    int idx, start = 0, len = -1;
    if (!PyArg_ParseTuple(args, "i|ii", &idx, &start, &len)) {
        PyErr_SetString(PyExc_TypeError, "getIndices expects an int");
        return NULL;
    }

    std::vector<unsigned short> indices;
    if (start == 0 && len == -1)
        indices = self->fThis->getIndices(idx);
    else
        indices = self->fThis->getIndices(idx, start, len);
    PyObject* list = PyList_New(indices.size());
    for (size_t i=0; i<indices.size(); i++)
        PyList_SET_ITEM(list, i, pyPlasma_convert(indices[i]));
    return list;
}

PY_METHOD_VA(GBufferGroup, getCells,
    "Params: idx\n"
    "Get the specified cell list as a list of plGBufferCell objects")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getCells expects an int");
        return NULL;
    }

    std::vector<plGBufferCell> cells = self->fThis->getCells(idx);
    PyObject* list = PyList_New(cells.size());
    for (size_t i=0; i<cells.size(); i++)
        PyList_SET_ITEM(list, i, pyGBufferCell_FromGBufferCell(cells[i]));
    return list;
}

PY_METHOD_VA(GBufferGroup, addVertices,
    "Params: list\n"
    "Add a Vertex Buffer with the contents of the supplied vertex list")
{
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addVertices expects a list of plGBufferVertex objects");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addVertices expects a list of plGBufferVertex objects");
        return NULL;
    }

    std::vector<plGBufferVertex> verts(PyList_Size(list));
    for (size_t i=0; i<verts.size(); i++) {
        if (!pyGBufferVertex_Check(PyList_GetItem(list, i))) {
            PyErr_SetString(PyExc_TypeError, "addVertices expects a list of plGBufferVertex objects");
            return NULL;
        }
        verts[i] = *((pyGBufferVertex*)PyList_GetItem(list, i))->fThis;
    }
    self->fThis->addVertices(verts);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GBufferGroup, addIndices,
    "Params: list\n"
    "Add a Face Index Buffer with the contents of the supplied index list")
{
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addIndices expects a list of ints");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addIndices expects a list of ints");
        return NULL;
    }

    std::vector<unsigned short> indices(PyList_Size(list));
    for (size_t i=0; i<indices.size(); i++) {
        if (!PyInt_Check(PyList_GetItem(list, i))) {
            PyErr_SetString(PyExc_TypeError, "addVertices expects a list of ints");
            return NULL;
        }
        indices[i] = PyInt_AsLong(PyList_GetItem(list, i));
    }
    self->fThis->addIndices(indices);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GBufferGroup, addCells,
    "Params: list\n"
    "Add a Cell Buffer with the contents of the specified cell list" )
{
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addCells expects a list of plGBufferCell objects");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addCells expects a list of plGBufferCell objects");
        return NULL;
    }

    std::vector<plGBufferCell> cells(PyList_Size(list));
    for (size_t i=0; i<cells.size(); i++) {
        if (!pyGBufferCell_Check(PyList_GetItem(list, i))) {
            PyErr_SetString(PyExc_TypeError, "addCells expects a list of plGBufferCell objects");
            return NULL;
        }
        cells[i] = *((pyGBufferCell*)PyList_GetItem(list, i))->fThis;
    }
    self->fThis->addCells(cells);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GBufferGroup, delVertices,
    "Params: idx\n"
    "Remove the specified Vertex buffer")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delVertices expects an int");
        return NULL;
    }
    self->fThis->delVertices(idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GBufferGroup, delIndices,
    "Params: idx\n"
    "Remove the specified Face Index buffer")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delIndices expects an int");
        return NULL;
    }
    self->fThis->delIndices(idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GBufferGroup, delCells,
    "Params: idx\n"
    "Remove the specified Cell buffer")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCells expects an int");
        return NULL;
    }
    self->fThis->delCells(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GBufferGroup, clearVertices, "Remove all Vertex buffers") {
    self->fThis->clearVertices();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GBufferGroup, clearIndices, "Remove all Face Index buffers") {
    self->fThis->clearIndices();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GBufferGroup, clearCells, "Remove all Cell buffers") {
    self->fThis->clearCells();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GBufferGroup, getNumVertBuffers,
    "Return the nubmer of stored Vertex buffers")
{
    return pyPlasma_convert(self->fThis->getNumVertBuffers());
}

PY_METHOD_NOARGS(GBufferGroup, getNumIdxBuffers,
    "Return the nubmer of stored Index buffers")
{
    return pyPlasma_convert(self->fThis->getNumIdxBuffers());
}

PY_METHOD_VA(GBufferGroup, getVertBufferStorage,
    "Params: idx\n"
    "Retrieve a raw Vertex buffer")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getVertBufferStorage expects an int");
        return NULL;
    }
    return PyBytes_FromStringAndSize((const char*)self->fThis->getVertBufferStorage(idx),
                                     self->fThis->getVertBufferSize(idx));
}

PY_METHOD_VA(GBufferGroup, getIdxBufferStorage,
    "Params: idx\n"
    "Retrieve a raw Vertex buffer")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getIdxBufferStorage expects an int");
        return NULL;
    }
    size_t count = self->fThis->getIdxBufferCount(idx);
    const unsigned short* indices = self->fThis->getIdxBufferStorage(idx);
    PyObject* idxList = PyList_New(count);
    for (size_t i=0; i<count; i++)
        PyList_SET_ITEM(idxList, i, pyPlasma_convert(indices[i]));
    return idxList;
}

PY_METHOD_VA(GBufferGroup, getVertBufferSize,
    "Params: idx\n"
    "Return the size of the specified Vertex buffer")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getVertBufferSize expects an int");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->getVertBufferSize(idx));
}

PY_METHOD_VA(GBufferGroup, getIdxBufferCount,
    "Params: idx\n"
    "Return the number of indices in the specified Index buffer")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getIdxBufferCount expects an int");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->getIdxBufferCount(idx));
}

static PyMethodDef pyGBufferGroup_Methods[] = {
    pyGBufferGroup_read_method,
    pyGBufferGroup_write_method,
    pyGBufferGroup_getVertices_method,
    pyGBufferGroup_getIndices_method,
    pyGBufferGroup_getCells_method,
    pyGBufferGroup_addVertices_method,
    pyGBufferGroup_addIndices_method,
    pyGBufferGroup_addCells_method,
    pyGBufferGroup_delVertices_method,
    pyGBufferGroup_delIndices_method,
    pyGBufferGroup_delCells_method,
    pyGBufferGroup_clearVertices_method,
    pyGBufferGroup_clearIndices_method,
    pyGBufferGroup_clearCells_method,
    pyGBufferGroup_getNumVertBuffers_method,
    pyGBufferGroup_getNumIdxBuffers_method,
    pyGBufferGroup_getVertBufferStorage_method,
    pyGBufferGroup_getIdxBufferStorage_method,
    pyGBufferGroup_getVertBufferSize_method,
    pyGBufferGroup_getIdxBufferCount_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(unsigned int, GBufferGroup, format, getFormat, setFormat)
PY_PROPERTY(size_t, GBufferGroup, skinWeights, getSkinWeights, setSkinWeights)
PY_PROPERTY(size_t, GBufferGroup, numUVs, getNumUVs, setNumUVs)
PY_PROPERTY(bool, GBufferGroup, hasSkinIndices, getHasSkinIndices, setHasSkinIndices)
PY_PROPERTY_RO(GBufferGroup, stride, getStride)

static PyGetSetDef pyGBufferGroup_GetSet[] = {
    pyGBufferGroup_format_getset,
    pyGBufferGroup_skinWeights_getset,
    pyGBufferGroup_numUVs_getset,
    pyGBufferGroup_hasSkinIndices_getset,
    pyGBufferGroup_stride_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyGBufferGroup_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plGBufferGroup",        /* tp_name */
    sizeof(pyGBufferGroup),             /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyGBufferGroup_dealloc,             /* tp_dealloc */
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

    pyGBufferGroup___init__,            /* tp_init */
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
    TP_FINALIZE_INIT                    /* tp_finalize */
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

PY_PLASMA_IFC_METHODS(GBufferGroup, plGBufferGroup)

}
