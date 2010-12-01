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
#include <PRP/Geometry/plDrawableSpans.h>
#include "pyDrawableSpans.h"
#include "pySpan.h"
#include "pyGBufferGroup.h"
#include "pySpaceTree.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Region/pyBounds.h"
#include "Math/pyMatrix.h"

extern "C" {

static PyObject* pyDrawableSpans_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyDrawableSpans* self = (pyDrawableSpans*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plDrawableSpans();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyDrawableSpans_clearSpans(pyDrawableSpans* self) {
    self->fThis->clearSpans();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_addIcicle(pyDrawableSpans* self, PyObject* args) {
    pyIcicle* ice;
    if (!PyArg_ParseTuple(args, "O", &ice)) {
        PyErr_SetString(PyExc_TypeError, "addIcicle expects a plIcicle");
        return NULL;
    }
    if (!pyIcicle_Check((PyObject*)ice)) {
        PyErr_SetString(PyExc_TypeError, "addIcicle expects a plIcicle");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->addIcicle(*ice->fThis));
}

static PyObject* pyDrawableSpans_createBGroup(pyDrawableSpans* self, PyObject* args) {
    int fmt;
    if (!PyArg_ParseTuple(args, "i", &fmt)) {
        PyErr_SetString(PyExc_TypeError, "createBufferGroup expects an int");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->createBufferGroup(fmt));
}

static PyObject* pyDrawableSpans_deleteBGroup(pyDrawableSpans* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "deleteBufferGroup expects an int");
        return NULL;
    }
    self->fThis->deleteBufferGroup(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_getVerts(pyDrawableSpans* self, PyObject* args) {
    pyIcicle* ice;
    if (!PyArg_ParseTuple(args, "O", &ice)) {
        PyErr_SetString(PyExc_TypeError, "getVerts expects a plIcicle");
        return NULL;
    }
    if (!pyIcicle_Check((PyObject*)ice)) {
        PyErr_SetString(PyExc_TypeError, "getVerts expects a plIcicle");
        return NULL;
    }
    hsTArray<plGBufferVertex> verts = self->fThis->getVerts(ice->fThis);
    PyObject* list = PyList_New(verts.getSize());
    for (size_t i=0; i<verts.getSize(); i++)
        PyList_SET_ITEM(list, i, pyGBufferVertex_FromGBufferVertex(verts[i]));
    return list;
}

static PyObject* pyDrawableSpans_getIndices(pyDrawableSpans* self, PyObject* args) {
    pyIcicle* ice;
    if (!PyArg_ParseTuple(args, "O", &ice)) {
        PyErr_SetString(PyExc_TypeError, "getIndices expects a plIcicle");
        return NULL;
    }
    if (!pyIcicle_Check((PyObject*)ice)) {
        PyErr_SetString(PyExc_TypeError, "getIndices expects a plIcicle");
        return NULL;
    }
    hsTArray<unsigned short> indices = self->fThis->getIndices(ice->fThis);
    PyObject* list = PyList_New(indices.getSize());
    for (size_t i=0; i<indices.getSize(); i++)
        PyList_SET_ITEM(list, i, PyInt_FromLong(indices[i]));
    return list;
}

static PyObject* pyDrawableSpans_getCells(pyDrawableSpans* self, PyObject* args) {
    int buf, idx;
    if (!PyArg_ParseTuple(args, "ii", &buf, &idx)) {
        PyErr_SetString(PyExc_TypeError, "getCells expects int, int");
        return NULL;
    }
    hsTArray<plGBufferCell> cells = self->fThis->getCells(buf, idx);
    PyObject* list = PyList_New(cells.getSize());
    for (size_t i=0; i<cells.getSize(); i++)
        PyList_SET_ITEM(list, i, pyGBufferCell_FromGBufferCell(cells[i]));
    return list;
}

static PyObject* pyDrawableSpans_addVerts(pyDrawableSpans* self, PyObject* args) {
    int buf;
    PyObject* vlist;
    if (!PyArg_ParseTuple(args,  "iO", &buf, &vlist)) {
        PyErr_SetString(PyExc_TypeError, "addVerts expects int, list");
        return NULL;
    }
    if (!PyList_Check(vlist)) {
        PyErr_SetString(PyExc_TypeError, "addVerts expects int, list");
        return NULL;
    }
    hsTArray<plGBufferVertex> verts;
    verts.setSize(PyList_Size(vlist));
    for (size_t i=0; i<verts.getSize(); i++) {
        PyObject* vert = PyList_GetItem(vlist, i);
        if (!pyGBufferVertex_Check(vert)) {
            PyErr_SetString(PyExc_TypeError, "addVerts expects a list of plGBufferVertexes");
            return NULL;
        }
        verts[i] = *((pyGBufferVertex*)vert)->fThis;
    }
    self->fThis->addVerts(buf, verts);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_addIndices(pyDrawableSpans* self, PyObject* args) {
    int buf;
    PyObject* ilist;
    if (!PyArg_ParseTuple(args,  "iO", &buf, &ilist)) {
        PyErr_SetString(PyExc_TypeError, "addIndices expects int, list");
        return NULL;
    }
    if (!PyList_Check(ilist)) {
        PyErr_SetString(PyExc_TypeError, "addIndices expects int, list");
        return NULL;
    }
    hsTArray<unsigned short> indices;
    indices.setSize(PyList_Size(ilist));
    for (size_t i=0; i<indices.getSize(); i++) {
        PyObject* index = PyList_GetItem(ilist, i);
        if (!PyInt_Check(index)) {
            PyErr_SetString(PyExc_TypeError, "addIndices expects a list of ints");
            return NULL;
        }
        indices[i] = PyInt_AsLong(index);
    }
    self->fThis->addIndices(buf, indices);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_addCells(pyDrawableSpans* self, PyObject* args) {
    int buf;
    PyObject* clist;
    if (!PyArg_ParseTuple(args,  "iO", &buf, &clist)) {
        PyErr_SetString(PyExc_TypeError, "addCells expects int, list");
        return NULL;
    }
    if (!PyList_Check(clist)) {
        PyErr_SetString(PyExc_TypeError, "addCells expects int, list");
        return NULL;
    }
    hsTArray<plGBufferCell> cells;
    cells.setSize(PyList_Size(clist));
    for (size_t i=0; i<cells.getSize(); i++) {
        PyObject* cell = PyList_GetItem(clist, i);
        if (!pyGBufferCell_Check(cell)) {
            PyErr_SetString(PyExc_TypeError, "addCells expects a list of plGBufferCells");
            return NULL;
        }
        cells[i] = *((pyGBufferCell*)cell)->fThis;
    }
    self->fThis->addCells(buf, cells);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_clearDIIndices(pyDrawableSpans* self) {
    self->fThis->clearDIIndices();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_addDIIndex(pyDrawableSpans* self, PyObject* args) {
    pyDISpanIndex* idx;
    if (!PyArg_ParseTuple(args, "O", &idx)) {
        PyErr_SetString(PyExc_TypeError, "addDIIndex expects a plDISpanIndex");
        return NULL;
    }
    if (!pyDISpanIndex_Check((PyObject*)idx)) {
        PyErr_SetString(PyExc_TypeError, "addDIIndex expects a plDISpanIndex");
        return NULL;
    }
    self->fThis->addDIIndex(*idx->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_clearTransforms(pyDrawableSpans* self) {
    self->fThis->clearTransforms();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_addTransform(pyDrawableSpans* self, PyObject* args) {
    pyMatrix44* l2w;
    pyMatrix44* w2l;
    pyMatrix44* l2b;
    pyMatrix44* b2l;
    if (!PyArg_ParseTuple(args, "OOOO", &l2w, &w2l, &l2b, &b2l)) {
        PyErr_SetString(PyExc_TypeError, "addTransform expects 4 hsMatrix44s");
        return NULL;
    }
    if (!pyMatrix44_Check((PyObject*)l2w) || !pyMatrix44_Check((PyObject*)w2l) ||
        !pyMatrix44_Check((PyObject*)l2b) || !pyMatrix44_Check((PyObject*)b2l)) {
        PyErr_SetString(PyExc_TypeError, "addTransform expects 4 hsMatrix44s");
        return NULL;
    }
    self->fThis->addTransform(*l2w->fThis, *w2l->fThis, *l2b->fThis, *b2l->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_clearMaterials(pyDrawableSpans* self) {
    self->fThis->clearMaterials();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_addMaterial(pyDrawableSpans* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addMaterial expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addMaterial expects a plKey");
        return NULL;
    }
    self->fThis->addMaterial(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_BuildSpaceTree(pyDrawableSpans* self) {
    self->fThis->BuildSpaceTree();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawableSpans_getSpans(pyDrawableSpans* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumSpans());
    for (size_t i=0; i<self->fThis->getNumSpans(); i++)
        PyList_SET_ITEM(list, i, pyIcicle_FromIcicle((plIcicle*)self->fThis->getSpan(i)));
    return list;
}

static PyObject* pyDrawableSpans_getBGroups(pyDrawableSpans* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumBufferGroups());
    for (size_t i=0; i<self->fThis->getNumBufferGroups(); i++)
        PyList_SET_ITEM(list, i, pyGBufferGroup_FromGBufferGroup(self->fThis->getBuffer(i)));
    return list;
}

static PyObject* pyDrawableSpans_getDIIndices(pyDrawableSpans* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumDIIndices());
    for (size_t i=0; i<self->fThis->getNumDIIndices(); i++)
        PyList_SET_ITEM(list, i, pyDISpanIndex_FromDISpanIndex(self->fThis->getDIIndex(i)));
    return list;
}

static PyObject* pyDrawableSpans_getL2Ws(pyDrawableSpans* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumTransforms());
    for (size_t i=0; i<self->fThis->getNumTransforms(); i++)
        PyList_SET_ITEM(list, i, pyMatrix44_FromMatrix44(self->fThis->getLocalToWorld(i)));
    return list;
}

static PyObject* pyDrawableSpans_getW2Ls(pyDrawableSpans* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumTransforms());
    for (size_t i=0; i<self->fThis->getNumTransforms(); i++)
        PyList_SET_ITEM(list, i, pyMatrix44_FromMatrix44(self->fThis->getWorldToLocal(i)));
    return list;
}

static PyObject* pyDrawableSpans_getL2Bs(pyDrawableSpans* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumTransforms());
    for (size_t i=0; i<self->fThis->getNumTransforms(); i++)
        PyList_SET_ITEM(list, i, pyMatrix44_FromMatrix44(self->fThis->getLocalToBone(i)));
    return list;
}

static PyObject* pyDrawableSpans_getB2Ls(pyDrawableSpans* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumTransforms());
    for (size_t i=0; i<self->fThis->getNumTransforms(); i++)
        PyList_SET_ITEM(list, i, pyMatrix44_FromMatrix44(self->fThis->getBoneToLocal(i)));
    return list;
}

static PyObject* pyDrawableSpans_getLocalBounds(pyDrawableSpans* self, void*) {
    return pyBounds3Ext_FromBounds3Ext(self->fThis->getLocalBounds());
}

static PyObject* pyDrawableSpans_getWorldBounds(pyDrawableSpans* self, void*) {
    return pyBounds3Ext_FromBounds3Ext(self->fThis->getWorldBounds());
}

static PyObject* pyDrawableSpans_getMaxBounds(pyDrawableSpans* self, void*) {
    return pyBounds3Ext_FromBounds3Ext(self->fThis->getMaxWorldBounds());
}

static PyObject* pyDrawableSpans_getMaterials(pyDrawableSpans* self, void*) {
    PyObject* list = PyList_New(self->fThis->getMaterials().getSize());
    for (size_t i=0; i<self->fThis->getMaterials().getSize(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getMaterials()[i]));
    return list;
}

static PyObject* pyDrawableSpans_getSpaceTree(pyDrawableSpans* self, void*) {
    return pySpaceTree_FromSpaceTree(self->fThis->getSpaceTree());
}

static PyObject* pyDrawableSpans_getProps(pyDrawableSpans* self, void*) {
    return PyInt_FromLong(self->fThis->getProps());
}

static PyObject* pyDrawableSpans_getCriteria(pyDrawableSpans* self, void*) {
    return PyInt_FromLong(self->fThis->getCriteria());
}

static PyObject* pyDrawableSpans_getRenderLevel(pyDrawableSpans* self, void*) {
    return PyInt_FromLong(self->fThis->getRenderLevel());
}

static PyObject* pyDrawableSpans_getSceneNode(pyDrawableSpans* self, void*) {
    return pyKey_FromKey(self->fThis->getSceneNode());
}

static int pyDrawableSpans_setSpans(pyDrawableSpans* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add spans, use addIcicle()");
    return -1;
}

static int pyDrawableSpans_setBGroups(pyDrawableSpans* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add BufferGroups, use createBufferGroup()");
    return -1;
}

static int pyDrawableSpans_setDIIndices(pyDrawableSpans* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add DI Indices, use addDIIndex()");
    return -1;
}

static int pyDrawableSpans_setTransforms(pyDrawableSpans* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add transform matrices, use addTransform()");
    return -1;
}

static int pyDrawableSpans_setLocalBounds(pyDrawableSpans* self, PyObject* value, void*) {
    if (value == NULL || !pyBounds3Ext_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "localBounds should be an hsBounds3Ext");
        return -1;
    }
    self->fThis->setLocalBounds(*((pyBounds3Ext*)value)->fThis);
    return 0;
}

static int pyDrawableSpans_setWorldBounds(pyDrawableSpans* self, PyObject* value, void*) {
    if (value == NULL || !pyBounds3Ext_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "worldBounds should be an hsBounds3Ext");
        return -1;
    }
    self->fThis->setWorldBounds(*((pyBounds3Ext*)value)->fThis);
    return 0;
}

static int pyDrawableSpans_setMaxBounds(pyDrawableSpans* self, PyObject* value, void*) {
    if (value == NULL || !pyBounds3Ext_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxWorldBounds should be an hsBounds3Ext");
        return -1;
    }
    self->fThis->setMaxWorldBounds(*((pyBounds3Ext*)value)->fThis);
    return 0;
}

static int pyDrawableSpans_setMaterials(pyDrawableSpans* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add materials, use addMaterial()");
    return -1;
}

static int pyDrawableSpans_setSpaceTree(pyDrawableSpans* self, PyObject* value, void*) {
    if (value == NULL || !pySpaceTree_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "spaceTree should be a plSpaceTree");
        return -1;
    }
    ((pySpaceTree*)value)->fPyOwned = false;
    self->fThis->setSpaceTree(((pySpaceTree*)value)->fThis);
    return 0;
}

static int pyDrawableSpans_setProps(pyDrawableSpans* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "props should be an int");
        return -1;
    }
    self->fThis->setProps(PyInt_AsLong(value));
    return 0;
}

static int pyDrawableSpans_setCriteria(pyDrawableSpans* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "criteria should be an int");
        return -1;
    }
    self->fThis->setCriteria(PyInt_AsLong(value));
    return 0;
}

static int pyDrawableSpans_setRenderLevel(pyDrawableSpans* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "renderLevel should be an int");
        return -1;
    }
    unsigned int rlevel = PyInt_AsLong(value);
    self->fThis->setRenderLevel(rlevel);
    return 0;
}

static int pyDrawableSpans_setSceneNode(pyDrawableSpans* self, PyObject* value, void*) {
    if (value == NULL || !pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "sceneNode should be a plKey");
        return -1;
    }
    self->fThis->setSceneNode(*((pyKey*)value)->fThis);
    return 0;
}

static PyMethodDef pyDrawableSpans_Methods[] = {
    { "clearSpans", (PyCFunction)pyDrawableSpans_clearSpans, METH_NOARGS,
      "Remove all spans from this DrawableSpans object" },
    { "addIcicle", (PyCFunction)pyDrawableSpans_addIcicle, METH_VARARGS,
      "Params: icicle\n"
      "Add an Icicle span to this DrawableSpans object" },
    { "createBufferGroup", (PyCFunction)pyDrawableSpans_createBGroup, METH_VARARGS,
      "Params: format\n"
      "Create a buffer group for storing mesh information.  You MUST\n"
      "do this BEFORE adding verts, indices and cells to the DrawableSpans!" },
    { "deleteBufferGroup", (PyCFunction)pyDrawableSpans_deleteBGroup, METH_VARARGS,
      "Params: idx\n"
      "Delete a buffer group and all of its contents from the DrawableSpans" },
    { "getVerts", (PyCFunction)pyDrawableSpans_getVerts, METH_VARARGS,
      "Params: buffer, idx\n"
      "Retrieves a list of verts from the specified buffer and group" },
    { "getIndices", (PyCFunction)pyDrawableSpans_getIndices, METH_VARARGS,
      "Params: buffer, idx\n"
      "Retrieves a list of face-vertex indices (ungrouped) from the specified\n"
      "buffer and group" },
    { "getCells", (PyCFunction)pyDrawableSpans_getCells, METH_VARARGS,
      "Params: buffer, idx\n"
      "Retrieves a list of cells from the specified buffer and group" },
    { "addVerts", (PyCFunction)pyDrawableSpans_addVerts, METH_VARARGS,
      "Params: buffer, vert-list\n"
      "Adds a group of verts to the specified buffer" },
    { "addIndices", (PyCFunction)pyDrawableSpans_addIndices, METH_VARARGS,
      "Params: buffer, index-list\n"
      "Adds a group of indices (ungrouped) to the specified buffer" },
    { "addCells", (PyCFunction)pyDrawableSpans_addCells, METH_VARARGS,
      "Params: buffer, cell-list\n"
      "Adds a group of cells to the specified buffer" },
    { "clearDIIndices", (PyCFunction)pyDrawableSpans_clearDIIndices, METH_NOARGS,
      "Remove all DI Indices from the DrawableSpans object" },
    { "addDIIndex", (PyCFunction)pyDrawableSpans_addDIIndex, METH_VARARGS,
      "Add a DI Index to the DrawableSpans object" },
    { "clearTransforms", (PyCFunction)pyDrawableSpans_clearTransforms, METH_NOARGS,
      "Remove all transform matrices from the DrawableSpans" },
    { "addTransform", (PyCFunction)pyDrawableSpans_addTransform, METH_VARARGS,
      "Params: localToWorld, worldToLocal, localToBone, boneToLocal\n"
      "Adds a transform set to the DrawableSpans" },
    { "clearMaterials", (PyCFunction)pyDrawableSpans_clearMaterials, METH_NOARGS,
      "Remove all material refs from the DrawableSpans" },
    { "addMaterial", (PyCFunction)pyDrawableSpans_addMaterial, METH_VARARGS,
      "Params: key\n"
      "Add a material ref to the DrawableSpans" },
    { "BuildSpaceTree", (PyCFunction)pyDrawableSpans_BuildSpaceTree, METH_NOARGS,
      "Build a plSpaceTree for this draw spans object" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyDrawableSpans_GetSet[] = {
    { "spans", (getter)pyDrawableSpans_getSpans, (setter)pyDrawableSpans_setSpans, NULL, NULL },
    { "bufferGroups", (getter)pyDrawableSpans_getBGroups, (setter)pyDrawableSpans_setBGroups, NULL, NULL },
    { "DIIndices", (getter)pyDrawableSpans_getDIIndices, (setter)pyDrawableSpans_setDIIndices, NULL, NULL },
    { "localToWorlds", (getter)pyDrawableSpans_getL2Ws, (setter)pyDrawableSpans_setTransforms, NULL, NULL },
    { "worldToLocals", (getter)pyDrawableSpans_getW2Ls, (setter)pyDrawableSpans_setTransforms, NULL, NULL },
    { "localToBones", (getter)pyDrawableSpans_getL2Bs, (setter)pyDrawableSpans_setTransforms, NULL, NULL },
    { "boneToLocals", (getter)pyDrawableSpans_getB2Ls, (setter)pyDrawableSpans_setTransforms, NULL, NULL },
    { "localBounds", (getter)pyDrawableSpans_getLocalBounds, (setter)pyDrawableSpans_setLocalBounds, NULL, NULL },
    { "worldBounds", (getter)pyDrawableSpans_getWorldBounds, (setter)pyDrawableSpans_setWorldBounds, NULL, NULL },
    { "maxWorldBounds", (getter)pyDrawableSpans_getMaxBounds, (setter)pyDrawableSpans_setMaxBounds, NULL, NULL },
    { "materials", (getter)pyDrawableSpans_getMaterials, (setter)pyDrawableSpans_setMaterials, NULL, NULL },
    { "spaceTree", (getter)pyDrawableSpans_getSpaceTree, (setter)pyDrawableSpans_setSpaceTree, NULL, NULL },
    { "props", (getter)pyDrawableSpans_getProps, (setter)pyDrawableSpans_setProps, NULL, NULL },
    { "criteria", (getter)pyDrawableSpans_getCriteria, (setter)pyDrawableSpans_setCriteria, NULL, NULL },
    { "renderLevel", (getter)pyDrawableSpans_getRenderLevel, (setter)pyDrawableSpans_setRenderLevel, NULL, NULL },
    { "sceneNode", (getter)pyDrawableSpans_getSceneNode, (setter)pyDrawableSpans_setSceneNode, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyDrawableSpans_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plDrawableSpans",         /* tp_name */
    sizeof(pyDrawableSpans),            /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plDrawableSpans wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyDrawableSpans_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyDrawableSpans_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDrawableSpans_new,                /* tp_new */
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

PyObject* Init_pyDrawableSpans_Type() {
    pyDrawableSpans_Type.tp_base = &pyDrawable_Type;
    if (PyType_Ready(&pyDrawableSpans_Type) < 0)
        return NULL;

    Py_INCREF(&pyDrawableSpans_Type);
    return (PyObject*)&pyDrawableSpans_Type;
}

int pyDrawableSpans_Check(PyObject* obj) {
    if (obj->ob_type == &pyDrawableSpans_Type
        || PyType_IsSubtype(obj->ob_type, &pyDrawableSpans_Type))
        return 1;
    return 0;
}

PyObject* pyDrawableSpans_FromDrawableSpans(class plDrawableSpans* draw) {
    if (draw == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyDrawableSpans* pdraw = PyObject_New(pyDrawableSpans, &pyDrawableSpans_Type);
    pdraw->fThis = draw;
    pdraw->fPyOwned = false;
    return (PyObject*)pdraw;
}

}
