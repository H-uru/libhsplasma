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

#include "pyGeometrySpan.h"

#include "pyTempVertex.h"
#include "Math/pyMatrix.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Region/pyBounds.h"

PY_PLASMA_NEW(GeometrySpan, plGeometrySpan)

PY_METHOD_VA(GeometrySpan, addPermaLight,
    "Params: light\n"
    "Adds a permalight")
{
    PyObject* light;
    if (!(PyArg_ParseTuple(args, "O", &light) && pyKey_Check(light))) {
        PyErr_SetString(PyExc_TypeError, "addPermaLight expects a plKey");
        return nullptr;
    }

    self->fThis->addPermaLight(pyPlasma_get<plKey>(light));
    Py_RETURN_NONE;
}

PY_METHOD_VA(GeometrySpan, delPermaLight,
    "Params: idx\n"
    "Removes a permalight")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPermaLight expects an int");
        return nullptr;
    }

    self->fThis->delPermaLight((size_t)idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GeometrySpan, clearPermaLight, "Clears all permalights")
{
    self->fThis->clearPermaLights();
    Py_RETURN_NONE;
}

PY_METHOD_VA(GeometrySpan, addPermaProj,
    "Params: light\n"
    "Adds a permaproj")
{
    PyObject* light;
    if (!(PyArg_ParseTuple(args, "O", &light) && pyKey_Check(light))) {
        PyErr_SetString(PyExc_TypeError, "addPermaProj expects a plKey");
        return nullptr;
    }

    self->fThis->addPermaProj(pyPlasma_get<plKey>(light));
    Py_RETURN_NONE;
}

PY_METHOD_VA(GeometrySpan, delPermaProj,
    "Params: idx\n"
    "Removes a permaproj")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPermaProj expects an int");
        return nullptr;
    }

    self->fThis->delPermaProj((size_t)idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GeometrySpan, clearPermaProj, "Clears all permaprojs")
{
    self->fThis->clearPermaProjs();
    Py_RETURN_NONE;
}

static PyMethodDef pyGeometrySpan_Methods[] = {
    pyGeometrySpan_addPermaLight_method,
    pyGeometrySpan_delPermaLight_method,
    pyGeometrySpan_clearPermaLight_method,
    pyGeometrySpan_addPermaProj_method,
    pyGeometrySpan_delPermaProj_method,
    pyGeometrySpan_clearPermaProj_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(GeometrySpan, indices)
{
    PyObject* list = PyTuple_New(self->fThis->getIndices().size());
    for (size_t i = 0; i < self->fThis->getIndices().size(); ++i)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getIndices()[i]));
    return list;
}

PY_GETSET_SETTER_DECL(GeometrySpan, indices)
{
    PY_PROPERTY_CHECK_NULL(indices)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "indices should be a sequence of unsigned shorts");
        return -1;
    }
    Py_ssize_t count = seq.size();
    std::vector<unsigned short> idxVec(count);
    for (Py_ssize_t i = 0; i < count; ++i) {
        PyObject* idx = seq.get(i);
        if (!pyPlasma_check<unsigned short>(idx)) {
            PyErr_SetString(PyExc_TypeError, "indices should be a sequence of unsigned shorts");
            return -1;
        }
        idxVec[i] = pyPlasma_get<unsigned short>(idx);
    }
    self->fThis->setIndices(idxVec);
    return 0;
}

PY_PROPERTY_GETSET_DECL(GeometrySpan, indices)

PY_GETSET_GETTER_DECL(GeometrySpan, vertices)
{
    std::vector<plGeometrySpan::TempVertex> verts = self->fThis->getVertices();
    PyObject* list = PyTuple_New(verts.size());
    for (size_t i = 0; i < verts.size(); ++i)
        PyTuple_SET_ITEM(list, i, pyTempVertex_FromTempVertex(verts[i]));
    return list;
}

PY_GETSET_SETTER_DECL(GeometrySpan, vertices)
{
    PY_PROPERTY_CHECK_NULL(vertices)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "vertices should be a sequence of TempVertex");
        return -1;
    }
    Py_ssize_t count = seq.size();
    std::vector<plGeometrySpan::TempVertex> verts(count);
    for (Py_ssize_t i = 0; i < count; ++i) {
        PyObject* vert = seq.get(i);
        if (!pyTempVertex_Check(vert)) {
            PyErr_SetString(PyExc_TypeError, "vertices should be a sequence of TempVertex");
            return -1;
        }
        verts[i] = *((pyTempVertex*)vert)->fThis;
    }
    self->fThis->setVertices(verts);
    return 0;
}

PY_PROPERTY_GETSET_DECL(GeometrySpan, vertices)

PY_GETSET_GETTER_DECL(GeometrySpan, permaLights)
{
    const std::vector<plKey>& lights = self->fThis->getPermaLights();
    PyObject* tup = PyTuple_New(lights.size());
    for (size_t i = 0; i < lights.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyPlasma_convert(lights[i]));
    return tup;
}

PY_PROPERTY_SETTER_MSG(GeometrySpan, permaLights, "To add PermaLights, use addPermaLight")
PY_PROPERTY_GETSET_DECL(GeometrySpan, permaLights)

PY_GETSET_GETTER_DECL(GeometrySpan, permaProjs)
{
    const std::vector<plKey>& lights = self->fThis->getPermaProjs();
    PyObject* tup = PyTuple_New(lights.size());
    for (size_t i = 0; i < lights.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyPlasma_convert(lights[i]));
    return tup;
}

PY_PROPERTY_SETTER_MSG(GeometrySpan, permaProjs, "To add PermaProjs, use addPermaLight")
PY_PROPERTY_GETSET_DECL(GeometrySpan, permaProjs)

PY_PROPERTY(unsigned int, GeometrySpan, baseMatrix, getBaseMatrix, setBaseMatrix)
PY_PROPERTY(plKey, GeometrySpan, fogEnvironment, getFogEnvironment, setFogEnvironment)
PY_PROPERTY(unsigned int, GeometrySpan, format, getFormat, setFormat)
PY_PROPERTY_BOUNDS(Bounds3Ext, GeometrySpan, localBounds, getLocalBounds, setLocalBounds)
PY_PROPERTY(hsMatrix44, GeometrySpan, localToWorld, getLocalToWorld, setLocalToWorld)
PY_PROPERTY(unsigned int, GeometrySpan, localUVWChans, getLocalUVWChans, setLocalUVWChans)
PY_PROPERTY(plKey, GeometrySpan, material, getMaterial, setMaterial)
PY_PROPERTY(unsigned int, GeometrySpan, maxBoneIdx, getMaxBoneIdx, setMaxBoneIdx)
PY_PROPERTY(float, GeometrySpan, maxDist, getMaxDist, setMaxDist)
PY_PROPERTY(float, GeometrySpan, minDist, getMinDist, setMinDist)
PY_PROPERTY_RO(GeometrySpan, numIndices, getNumIndices)
PY_PROPERTY(unsigned int, GeometrySpan, numMatrices, getNumMatrices, setNumMatrices)
PY_PROPERTY_RO(GeometrySpan, numVertices, getNumVertices)
PY_PROPERTY(unsigned int, GeometrySpan, penBoneIdx, getPenBoneIdx, setPenBoneIdx)
PY_PROPERTY(unsigned int, GeometrySpan, props, getProps, setProps)
PY_PROPERTY(float, GeometrySpan, waterHeight, getWaterHeight, setWaterHeight)
PY_PROPERTY_BOUNDS(Bounds3Ext, GeometrySpan, worldBounds, getWorldBounds, setWorldBounds)
PY_PROPERTY(hsMatrix44, GeometrySpan, worldToLocal, getWorldToLocal, setWorldToLocal)

static PyGetSetDef pyGeometrySpan_GetSet[] = {
    pyGeometrySpan_baseMatrix_getset,
    pyGeometrySpan_fogEnvironment_getset,
    pyGeometrySpan_format_getset,
    pyGeometrySpan_indices_getset,
    pyGeometrySpan_localBounds_getset,
    pyGeometrySpan_localToWorld_getset,
    pyGeometrySpan_localUVWChans_getset,
    pyGeometrySpan_material_getset,
    pyGeometrySpan_maxBoneIdx_getset,
    pyGeometrySpan_maxDist_getset,
    pyGeometrySpan_minDist_getset,
    pyGeometrySpan_numIndices_getset,
    pyGeometrySpan_numMatrices_getset,
    pyGeometrySpan_numVertices_getset,
    pyGeometrySpan_penBoneIdx_getset,
    pyGeometrySpan_props_getset,
    pyGeometrySpan_vertices_getset,
    pyGeometrySpan_waterHeight_getset,
    pyGeometrySpan_worldBounds_getset,
    pyGeometrySpan_worldToLocal_getset,
    pyGeometrySpan_permaLights_getset,
    pyGeometrySpan_permaProjs_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GeometrySpan, plGeometrySpan, "plGeometrySpan wrapper")

PY_PLASMA_TYPE_INIT(GeometrySpan)
{
    pyGeometrySpan_Type.tp_new = pyGeometrySpan_new;
    pyGeometrySpan_Type.tp_methods = pyGeometrySpan_Methods;
    pyGeometrySpan_Type.tp_getset = pyGeometrySpan_GetSet;
    if (PyType_CheckAndReady(&pyGeometrySpan_Type) < 0)
        return nullptr;

    // Format
    PY_TYPE_ADD_CONST(GeometrySpan, "kUVCountMask", plGeometrySpan::kUVCountMask);
    PY_TYPE_ADD_CONST(GeometrySpan, "kSkinNoWeights", plGeometrySpan::kSkinNoWeights);
    PY_TYPE_ADD_CONST(GeometrySpan, "kSkin1Weight", plGeometrySpan::kSkin1Weight);
    PY_TYPE_ADD_CONST(GeometrySpan, "kSkin2Weights", plGeometrySpan::kSkin2Weights);
    PY_TYPE_ADD_CONST(GeometrySpan, "kSkin3Weights", plGeometrySpan::kSkin3Weights);
    PY_TYPE_ADD_CONST(GeometrySpan, "kSkinWeightMask", plGeometrySpan::kSkinWeightMask);
    PY_TYPE_ADD_CONST(GeometrySpan, "kSkinIndices", plGeometrySpan::kSkinIndices);

    // Properties
    PY_TYPE_ADD_CONST(GeometrySpan, "kLiteMaterial", plGeometrySpan::kLiteMaterial);
    PY_TYPE_ADD_CONST(GeometrySpan, "kPropRunTimeLight", plGeometrySpan::kPropRunTimeLight);
    PY_TYPE_ADD_CONST(GeometrySpan, "kPropNoPreShade", plGeometrySpan::kPropNoPreShade);
    PY_TYPE_ADD_CONST(GeometrySpan, "kLiteVtxPreshaded", plGeometrySpan::kLiteVtxPreshaded);
    PY_TYPE_ADD_CONST(GeometrySpan, "kLiteVtxNonPreshaded", plGeometrySpan::kLiteVtxNonPreshaded);
    PY_TYPE_ADD_CONST(GeometrySpan, "kLiteMask", plGeometrySpan::kLiteMask);
    PY_TYPE_ADD_CONST(GeometrySpan, "kRequiresBlending", plGeometrySpan::kRequiresBlending);
    PY_TYPE_ADD_CONST(GeometrySpan, "kInstanced", plGeometrySpan::kInstanced);
    PY_TYPE_ADD_CONST(GeometrySpan, "kUserOwned", plGeometrySpan::kUserOwned);
    PY_TYPE_ADD_CONST(GeometrySpan, "kPropNoShadow", plGeometrySpan::kPropNoShadow);
    PY_TYPE_ADD_CONST(GeometrySpan, "kPropForceShadow", plGeometrySpan::kPropForceShadow);
    PY_TYPE_ADD_CONST(GeometrySpan, "kDiffuseFoldedIn", plGeometrySpan::kDiffuseFoldedIn);
    PY_TYPE_ADD_CONST(GeometrySpan, "kPropReverseSort", plGeometrySpan::kPropReverseSort);
    PY_TYPE_ADD_CONST(GeometrySpan, "kWaterHeight", plGeometrySpan::kWaterHeight);
    PY_TYPE_ADD_CONST(GeometrySpan, "kFirstInstance", plGeometrySpan::kFirstInstance);
    PY_TYPE_ADD_CONST(GeometrySpan, "kPartialSort", plGeometrySpan::kPartialSort);
    PY_TYPE_ADD_CONST(GeometrySpan, "kVisLOS", plGeometrySpan::kVisLOS);
    PY_TYPE_ADD_CONST(GeometrySpan, "kPropNoShadowCast", plGeometrySpan::kPropNoShadowCast);

    // TempVertex class thing
    PyDict_SetItemString(pyGeometrySpan_Type.tp_dict, "TempVertex",
                         Init_pyTempVertex_Type());

    Py_INCREF(&pyGeometrySpan_Type);
    return (PyObject*)&pyGeometrySpan_Type;
}

PY_PLASMA_IFC_METHODS(GeometrySpan, plGeometrySpan)
