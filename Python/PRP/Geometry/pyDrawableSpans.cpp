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

#include "pyDrawableSpans.h"

#include <PRP/Geometry/plDrawableSpans.h>
#include "pySpan.h"
#include "pyGBufferGroup.h"
#include "pyGeometrySpan.h"
#include "pySpaceTree.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Region/pyBounds.h"
#include "Math/pyMatrix.h"

PY_PLASMA_NEW(DrawableSpans, plDrawableSpans)

PY_METHOD_NOARGS(DrawableSpans, clearSpans,
    "Remove all spans from this DrawableSpans object")
{
    self->fThis->clearSpans();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawableSpans, addIcicle,
    "Params: icicle\n"
    "Add an Icicle span to this DrawableSpans object")
{
    pyIcicle* ice;
    if (!PyArg_ParseTuple(args, "O", &ice)) {
        PyErr_SetString(PyExc_TypeError, "addIcicle expects a plIcicle");
        return NULL;
    }
    if (!pyIcicle_Check((PyObject*)ice)) {
        PyErr_SetString(PyExc_TypeError, "addIcicle expects a plIcicle");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->addIcicle(*ice->fThis));
}

PY_METHOD_VA(DrawableSpans, createBufferGroup,
    "Params: format\n"
    "Create a buffer group for storing mesh information.  You MUST\n"
    "do this BEFORE adding verts, indices and cells to the DrawableSpans!")
{
    int fmt;
    if (!PyArg_ParseTuple(args, "i", &fmt)) {
        PyErr_SetString(PyExc_TypeError, "createBufferGroup expects an int");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->createBufferGroup(fmt));
}

PY_METHOD_VA(DrawableSpans, deleteBufferGroup,
    "Params: idx\n"
    "Delete a buffer group and all of its contents from the DrawableSpans")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "deleteBufferGroup expects an int");
        return NULL;
    }
    self->fThis->deleteBufferGroup(idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawableSpans, getVerts,
    "Params: buffer, idx\n"
    "Retrieves a list of verts from the specified buffer and group")
{
    pyIcicle* ice;
    if (!PyArg_ParseTuple(args, "O", &ice)) {
        PyErr_SetString(PyExc_TypeError, "getVerts expects a plIcicle");
        return NULL;
    }
    if (!pyIcicle_Check((PyObject*)ice)) {
        PyErr_SetString(PyExc_TypeError, "getVerts expects a plIcicle");
        return NULL;
    }
    std::vector<plGBufferVertex> verts = self->fThis->getVerts(ice->fThis);
    PyObject* list = PyTuple_New(verts.size());
    for (size_t i=0; i<verts.size(); i++)
        PyTuple_SET_ITEM(list, i, pyGBufferVertex_FromGBufferVertex(verts[i]));
    return list;
}

PY_METHOD_VA(DrawableSpans, getIndices,
    "Params: buffer, idx\n"
    "Retrieves a list of face-vertex indices (ungrouped) from the specified\n"
    "buffer and group")
{
    pyIcicle* ice;
    if (!PyArg_ParseTuple(args, "O", &ice)) {
        PyErr_SetString(PyExc_TypeError, "getIndices expects a plIcicle");
        return NULL;
    }
    if (!pyIcicle_Check((PyObject*)ice)) {
        PyErr_SetString(PyExc_TypeError, "getIndices expects a plIcicle");
        return NULL;
    }
    std::vector<unsigned short> indices = self->fThis->getIndices(ice->fThis);
    PyObject* list = PyTuple_New(indices.size());
    for (size_t i=0; i<indices.size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(indices[i]));
    return list;
}

PY_METHOD_VA(DrawableSpans, getCells,
    "Params: buffer, idx\n"
    "Retrieves a list of cells from the specified buffer and group")
{
    int buf, idx;
    if (!PyArg_ParseTuple(args, "ii", &buf, &idx)) {
        PyErr_SetString(PyExc_TypeError, "getCells expects int, int");
        return NULL;
    }
    std::vector<plGBufferCell> cells = self->fThis->getCells(buf, idx);
    PyObject* list = PyTuple_New(cells.size());
    for (size_t i=0; i<cells.size(); i++)
        PyTuple_SET_ITEM(list, i, pyGBufferCell_FromGBufferCell(cells[i]));
    return list;
}

PY_METHOD_VA(DrawableSpans, addVerts,
    "Params: buffer, vert-list\n"
    "Adds a group of verts to the specified buffer")
{
    int buf;
    PyObject* vlistObj;
    if (!PyArg_ParseTuple(args,  "iO", &buf, &vlistObj)) {
        PyErr_SetString(PyExc_TypeError, "addVerts expects int, sequence(plGBufferVertex)");
        return NULL;
    }
    pySequenceFastRef vlist(vlistObj);
    if (!vlist.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "addVerts expects int, sequence(plGBufferVertex)");
        return NULL;
    }
    std::vector<plGBufferVertex> verts(vlist.size());
    for (size_t i=0; i<verts.size(); i++) {
        PyObject* vert = vlist.get(i);
        if (!pyGBufferVertex_Check(vert)) {
            PyErr_SetString(PyExc_TypeError, "addVerts expects a sequence of plGBufferVertexes");
            return NULL;
        }
        verts[i] = *((pyGBufferVertex*)vert)->fThis;
    }
    self->fThis->addVerts(buf, verts);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawableSpans, addIndices,
    "Params: buffer, index-list\n"
    "Adds a group of indices (ungrouped) to the specified buffer")
{
    int buf;
    PyObject* ilistObj;
    if (!PyArg_ParseTuple(args,  "iO", &buf, &ilistObj)) {
        PyErr_SetString(PyExc_TypeError, "addIndices expects int, sequence(int)");
        return NULL;
    }
    pySequenceFastRef ilist(ilistObj);
    if (!ilist.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "addIndices expects int, sequence(int)");
        return NULL;
    }
    std::vector<unsigned short> indices(ilist.size());
    for (size_t i=0; i<indices.size(); i++) {
        PyObject* index = ilist.get(i);
        if (!pyPlasma_check<unsigned short>(index)) {
            PyErr_SetString(PyExc_TypeError, "addIndices expects a sequence of ints");
            return NULL;
        }
        indices[i] = pyPlasma_get<unsigned short>(index);
    }
    self->fThis->addIndices(buf, indices);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawableSpans, addCells,
    "Params: buffer, cell-list\n"
    "Adds a group of cells to the specified buffer")
{
    int buf;
    PyObject* clistObj;
    if (!PyArg_ParseTuple(args,  "iO", &buf, &clistObj)) {
        PyErr_SetString(PyExc_TypeError, "addCells expects int, sequence(plGBufferCell)");
        return NULL;
    }
    pySequenceFastRef clist(clistObj);
    if (!clist.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "addCells expects int, sequence(plGBufferCell)");
        return NULL;
    }
    std::vector<plGBufferCell> cells(clist.size());
    for (size_t i=0; i<cells.size(); i++) {
        PyObject* cell = clist.get(i);
        if (!pyGBufferCell_Check(cell)) {
            PyErr_SetString(PyExc_TypeError, "addCells expects a sequence of plGBufferCells");
            return NULL;
        }
        cells[i] = *((pyGBufferCell*)cell)->fThis;
    }
    self->fThis->addCells(buf, cells);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DrawableSpans, clearDIIndices,
    "Remove all DI Indices from the DrawableSpans object")
{
    self->fThis->clearDIIndices();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawableSpans, addDIIndex,
    "Add a DI Index to the DrawableSpans object")
{
    pyDISpanIndex* idx;
    if (!PyArg_ParseTuple(args, "O", &idx)) {
        PyErr_SetString(PyExc_TypeError, "addDIIndex expects a plDISpanIndex");
        return NULL;
    }
    if (!pyDISpanIndex_Check((PyObject*)idx)) {
        PyErr_SetString(PyExc_TypeError, "addDIIndex expects a plDISpanIndex");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->addDIIndex(*idx->fThis));
}

PY_METHOD_NOARGS(DrawableSpans, clearTransforms,
    "Remove all transform matrices from the DrawableSpans")
{
    self->fThis->clearTransforms();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawableSpans, addTransform,
    "Params: localToWorld, worldToLocal, localToBone, boneToLocal\n"
    "Adds a transform set to the DrawableSpans")
{
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
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DrawableSpans, clearMaterials,
    "Remove all material refs from the DrawableSpans")
{
    self->fThis->clearMaterials();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawableSpans, addMaterial,
    "Params: key\n"
    "Add a material ref to the DrawableSpans")
{
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
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DrawableSpans, calcBounds,
    "(Re-)Calculate the bounds for all icicles and the DrawableSpans")
{
    self->fThis->calcBounds();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DrawableSpans, BuildSpaceTree,
    "Build a plSpaceTree for this draw spans object")
{
    self->fThis->BuildSpaceTree();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawableSpans, composeGeometry,
    "Params: clearSpans\n"
    "Populates the DrawableSpans from its source spans")
{
    bool clearSpans = true;
    bool calcBounds = false;
    if (!PyArg_ParseTuple(args, "|bb", &clearSpans, &calcBounds)) {
        PyErr_SetString(PyExc_TypeError, "composeGeometry expects two optional bools");
        return NULL;
    }
    self->fThis->composeGeometry(clearSpans, calcBounds);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawableSpans, decomposeGeometry,
    "Params: clearColors\n"
    "Decompose the DrawableSpans into source spans")
{
    bool clearColors = true;
    if (!PyArg_ParseTuple(args, "|b", &clearColors)) {
        PyErr_SetString(PyExc_TypeError, "decomposeGeometry expects an optional bool");
        return NULL;
    }
    self->fThis->decomposeGeometry(clearColors);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawableSpans, buildDIIndex,
    "Params: spans"
    "Builds and returns the offset of the DISpanIndex created for a mesh composed of a set of source spans")
{
    PyObject* seqObj;
    if (!PyArg_ParseTuple(args, "O", &seqObj)) {
        PyErr_SetString(PyExc_TypeError, "buildDIIndex expects a sequence of plGeometrySpan");
        return NULL;
    }
    pySequenceFastRef seq(seqObj);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "buildDIIndex expects a sequence of plGeometrySpan");
        return NULL;
    }

    std::vector<plGeometrySpan*> spans(seq.size());
    for (size_t i = 0; i < spans.size(); ++i) {
        PyObject* o = seq.get(i);
        if (pyGeometrySpan_Check(o))
            spans[i] = ((pyGeometrySpan*)o)->fThis;
        else {
            PyErr_SetString(PyExc_TypeError, "buildDIIndex expects a sequence of plGeometrySpan");
            return NULL;
        }
    }
    return pyPlasma_convert(self->fThis->buildDIIndex(spans));
}

PY_METHOD_VA(DrawableSpans, addSourceSpan,
    "Params: span\n"
    "Add a GeometrySpan to this DrawableSpans' sources")
{
    pyGeometrySpan* span;
    if (!PyArg_ParseTuple(args, "O", &span)) {
        PyErr_SetString(PyExc_TypeError, "addSourceSpan expects a plGeometrySpan");
        return NULL;
    }
    if (!pyGeometrySpan_Check((PyObject*)span)) {
        PyErr_SetString(PyExc_TypeError, "addSourceSpan expects a plGeometrySpan");
        return NULL;
    }
    span->fPyOwned = false;
    return pyPlasma_convert(self->fThis->addSourceSpan(span->fThis));
}

static PyMethodDef pyDrawableSpans_Methods[] = {
    pyDrawableSpans_clearSpans_method,
    pyDrawableSpans_addIcicle_method,
    pyDrawableSpans_createBufferGroup_method,
    pyDrawableSpans_deleteBufferGroup_method,
    pyDrawableSpans_getVerts_method,
    pyDrawableSpans_getIndices_method,
    pyDrawableSpans_getCells_method,
    pyDrawableSpans_addVerts_method,
    pyDrawableSpans_addIndices_method,
    pyDrawableSpans_addCells_method,
    pyDrawableSpans_clearDIIndices_method,
    pyDrawableSpans_addDIIndex_method,
    pyDrawableSpans_clearTransforms_method,
    pyDrawableSpans_addTransform_method,
    pyDrawableSpans_clearMaterials_method,
    pyDrawableSpans_addMaterial_method,
    pyDrawableSpans_calcBounds_method,
    pyDrawableSpans_BuildSpaceTree_method,
    pyDrawableSpans_composeGeometry_method,
    pyDrawableSpans_decomposeGeometry_method,
    pyDrawableSpans_buildDIIndex_method,
    pyDrawableSpans_addSourceSpan_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(DrawableSpans, spans) {
    PyObject* list = PyTuple_New(self->fThis->getNumSpans());
    for (size_t i=0; i<self->fThis->getNumSpans(); i++)
        PyTuple_SET_ITEM(list, i, ICreateSpan(self->fThis->getSpan(i)));
    return list;
}

PY_PROPERTY_SETTER_MSG(DrawableSpans, spans, "To add spans, use addIcicle()")
PY_PROPERTY_GETSET_DECL(DrawableSpans, spans)

PY_GETSET_GETTER_DECL(DrawableSpans, bufferGroups) {
    PyObject* list = PyTuple_New(self->fThis->getNumBufferGroups());
    for (size_t i=0; i<self->fThis->getNumBufferGroups(); i++)
        PyTuple_SET_ITEM(list, i, pyGBufferGroup_FromGBufferGroup(self->fThis->getBuffer(i)));
    return list;
}

PY_PROPERTY_SETTER_MSG(DrawableSpans, bufferGroups,
                       "To add BufferGroups, use createBufferGroup()")
PY_PROPERTY_GETSET_DECL(DrawableSpans, bufferGroups)

PY_GETSET_GETTER_DECL(DrawableSpans, DIIndices) {
    PyObject* list = PyTuple_New(self->fThis->getNumDIIndices());
    for (size_t i=0; i<self->fThis->getNumDIIndices(); i++)
        PyTuple_SET_ITEM(list, i, pyDISpanIndex_FromDISpanIndex(self->fThis->getDIIndex(i)));
    return list;
}

PY_PROPERTY_SETTER_MSG(DrawableSpans, DIIndices, "To add DI Indices, use addDIIndex()")
PY_PROPERTY_GETSET_DECL(DrawableSpans, DIIndices)

PY_GETSET_GETTER_DECL(DrawableSpans, localToWorlds) {
    PyObject* list = PyTuple_New(self->fThis->getNumTransforms());
    for (size_t i=0; i<self->fThis->getNumTransforms(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getLocalToWorld(i)));
    return list;
}

PY_PROPERTY_SETTER_MSG(DrawableSpans, localToWorlds,
                       "To add transform matrices, use addTransform()")
PY_PROPERTY_GETSET_DECL(DrawableSpans, localToWorlds)

PY_GETSET_GETTER_DECL(DrawableSpans, worldToLocals)  {
    PyObject* list = PyTuple_New(self->fThis->getNumTransforms());
    for (size_t i=0; i<self->fThis->getNumTransforms(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getWorldToLocal(i)));
    return list;
}

PY_PROPERTY_SETTER_MSG(DrawableSpans, worldToLocals,
                       "To add transform matrices, use addTransform()")
PY_PROPERTY_GETSET_DECL(DrawableSpans, worldToLocals)

PY_GETSET_GETTER_DECL(DrawableSpans, localToBones) {
    PyObject* list = PyTuple_New(self->fThis->getNumTransforms());
    for (size_t i=0; i<self->fThis->getNumTransforms(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getLocalToBone(i)));
    return list;
}

PY_PROPERTY_SETTER_MSG(DrawableSpans, localToBones,
                       "To add transform matrices, use addTransform()")
PY_PROPERTY_GETSET_DECL(DrawableSpans, localToBones)

PY_GETSET_GETTER_DECL(DrawableSpans, boneToLocals) {
    PyObject* list = PyTuple_New(self->fThis->getNumTransforms());
    for (size_t i=0; i<self->fThis->getNumTransforms(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getBoneToLocal(i)));
    return list;
}

PY_PROPERTY_SETTER_MSG(DrawableSpans, boneToLocals,
                       "To add transform matrices, use addTransform()")
PY_PROPERTY_GETSET_DECL(DrawableSpans, boneToLocals)

PY_GETSET_GETTER_DECL(DrawableSpans, materials) {
    PyObject* list = PyTuple_New(self->fThis->getMaterials().size());
    for (size_t i=0; i<self->fThis->getMaterials().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getMaterials()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(DrawableSpans, materials, "To add materials, use addMaterial()")
PY_PROPERTY_GETSET_DECL(DrawableSpans, materials)

PY_GETSET_GETTER_DECL(DrawableSpans, sourceSpans) {
    PyObject* list = PyTuple_New(self->fThis->getSourceSpans().size());
    for (size_t i = 0; i < self->fThis->getSourceSpans().size(); ++i)
        PyTuple_SET_ITEM(list, i, pyGeometrySpan_FromGeometrySpan(self->fThis->getSourceSpans()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(DrawableSpans, sourceSpans, "To add sourceSpans, use addSourceSpan()")
PY_PROPERTY_GETSET_DECL(DrawableSpans, sourceSpans)

PY_PROPERTY_BOUNDS(Bounds3Ext, DrawableSpans, localBounds, getLocalBounds, setLocalBounds)
PY_PROPERTY_BOUNDS(Bounds3Ext, DrawableSpans, worldBounds, getWorldBounds, setWorldBounds)
PY_PROPERTY_BOUNDS(Bounds3Ext, DrawableSpans, maxWorldBounds, getMaxWorldBounds, setMaxWorldBounds)
PY_PROPERTY_CREATABLE(plSpaceTree, SpaceTree, DrawableSpans, spaceTree, getSpaceTree, setSpaceTree)
PY_PROPERTY(unsigned int, DrawableSpans, props, getProps, setProps)
PY_PROPERTY(unsigned int, DrawableSpans, criteria, getCriteria, setCriteria)
PY_PROPERTY(unsigned int, DrawableSpans, renderLevel, getRenderLevel, setRenderLevel)
PY_PROPERTY(plKey, DrawableSpans, sceneNode, getSceneNode, setSceneNode)

static PyGetSetDef pyDrawableSpans_GetSet[] = {
    pyDrawableSpans_spans_getset,
    pyDrawableSpans_bufferGroups_getset,
    pyDrawableSpans_DIIndices_getset,
    pyDrawableSpans_localToWorlds_getset,
    pyDrawableSpans_worldToLocals_getset,
    pyDrawableSpans_localToBones_getset,
    pyDrawableSpans_boneToLocals_getset,
    pyDrawableSpans_localBounds_getset,
    pyDrawableSpans_worldBounds_getset,
    pyDrawableSpans_maxWorldBounds_getset,
    pyDrawableSpans_materials_getset,
    pyDrawableSpans_spaceTree_getset,
    pyDrawableSpans_props_getset,
    pyDrawableSpans_criteria_getset,
    pyDrawableSpans_renderLevel_getset,
    pyDrawableSpans_sceneNode_getset,
    pyDrawableSpans_sourceSpans_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DrawableSpans, plDrawableSpans, "plDrawableSpans wrapper")

PY_PLASMA_TYPE_INIT(DrawableSpans) {
    pyDrawableSpans_Type.tp_new = pyDrawableSpans_new;
    pyDrawableSpans_Type.tp_methods = pyDrawableSpans_Methods;
    pyDrawableSpans_Type.tp_getset = pyDrawableSpans_GetSet;
    pyDrawableSpans_Type.tp_base = &pyDrawable_Type;
    if (PyType_CheckAndReady(&pyDrawableSpans_Type) < 0)
        return NULL;

    Py_INCREF(&pyDrawableSpans_Type);
    return (PyObject*)&pyDrawableSpans_Type;
}

PY_PLASMA_IFC_METHODS(DrawableSpans, plDrawableSpans)
