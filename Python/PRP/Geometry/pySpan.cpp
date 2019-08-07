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

#include <PRP/Geometry/plSpan.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Region/pyBounds.h"
#include "Stream/pyStream.h"
#include "Math/pyMatrix.h"

PY_PLASMA_DEALLOC(Span)
PY_PLASMA_EMPTY_INIT(Span)
PY_PLASMA_NEW(Span, plSpan)

PY_METHOD_NOARGS(Span, ClassName, "Returns the RTTI Class name of this Span object")
{
    return pyPlasma_convert(self->fThis->ClassName());
}

PY_METHOD_VA(Span, read,
    "Params: stream\n"
    "Read this Span object from the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return nullptr;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Span, write,
    "Params: stream\n"
    "Write this Span object to the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return nullptr;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Span, clearPermaLights, "Remove all Perma Lights from this Span")
{
    self->fThis->clearPermaLights();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Span, clearPermaProjs, "Remove all Perma Projs from this Span")
{
    self->fThis->clearPermaProjs();
    Py_RETURN_NONE;
}

PY_METHOD_VA(Span, addPermaLight,
    "Params: key\n"
    "Add a Perma Light to the span")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addPermaLight expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addPermaLight expects a plKey");
        return nullptr;
    }
    self->fThis->addPermaLight(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Span, addPermaProj,
    "Params: key\n"
    "Add a Perma Proj to the span")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addPermaProj expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addPermaProj expects a plKey");
        return nullptr;
    }
    self->fThis->addPermaProj(*key->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pySpan_Methods[] = {
    pySpan_ClassName_method,
    pySpan_read_method,
    pySpan_write_method,
    pySpan_clearPermaLights_method,
    pySpan_clearPermaProjs_method,
    pySpan_addPermaLight_method,
    pySpan_addPermaProj_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(Span, permaLights)
{
    PyObject* list = PyTuple_New(self->fThis->getPermaLights().size());
    for (size_t i=0; i<self->fThis->getPermaLights().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getPermaLights()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(Span, permaLights, "To add permaLights, use addPermaLight()")
PY_PROPERTY_GETSET_DECL(Span, permaLights)

PY_GETSET_GETTER_DECL(Span, permaProjs)
{
    PyObject* list = PyTuple_New(self->fThis->getPermaProjs().size());
    for (size_t i=0; i<self->fThis->getPermaProjs().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getPermaProjs()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(Span, permaProjs, "To add permaProjs, use addPermaProj()")
PY_PROPERTY_GETSET_DECL(Span, permaProjs)

PY_PROPERTY(plKey, Span, fog, getFogEnvironment, setFogEnvironment) // Backwards compatibility
PY_PROPERTY(plKey, Span, fogEnvironment, getFogEnvironment, setFogEnvironment)
PY_PROPERTY(hsMatrix44, Span, localToWorld, getLocalToWorld, setLocalToWorld)
PY_PROPERTY(hsMatrix44, Span, worldToLocal, getWorldToLocal, setLocalToWorld)
PY_PROPERTY(unsigned short, Span, subType, getSubType, setSubType)
PY_PROPERTY(unsigned int, Span, materialIdx, getMaterialIdx, setMaterialIdx)
PY_PROPERTY(unsigned char, Span, numMatrices, getNumMatrices, setNumMatrices)
PY_PROPERTY(unsigned int, Span, props, getProps, setProps)
PY_PROPERTY(unsigned int, Span, baseMatrix, getBaseMatrix, setBaseMatrix)
PY_PROPERTY(unsigned short, Span, maxBoneIdx, getMaxBoneIdx, setMaxBoneIdx)
PY_PROPERTY(unsigned short, Span, penBoneIdx, getPenBoneIdx, setPenBoneIdx)
PY_PROPERTY(unsigned short, Span, localUVWChans, getLocalUVWChans, setLocalUVWChans)
PY_PROPERTY(float, Span, minDist, getMinDist, setMinDist)
PY_PROPERTY(float, Span, maxDist, getMaxDist, setMaxDist)
PY_PROPERTY(float, Span, waterHeight, getWaterHeight, setWaterHeight)
PY_PROPERTY_BOUNDS(Bounds3Ext, Span, localBounds, getLocalBounds, setLocalBounds)
PY_PROPERTY_BOUNDS(Bounds3Ext, Span, worldBounds, getWorldBounds, setWorldBounds)

static PyGetSetDef pySpan_GetSet[] = {
    pySpan_fogEnvironment_getset,
    pySpan_fog_getset,
    pySpan_permaLights_getset,
    pySpan_permaProjs_getset,
    pySpan_localToWorld_getset,
    pySpan_worldToLocal_getset,
    pySpan_subType_getset,
    pySpan_materialIdx_getset,
    pySpan_numMatrices_getset,
    pySpan_props_getset,
    pySpan_baseMatrix_getset,
    pySpan_maxBoneIdx_getset,
    pySpan_penBoneIdx_getset,
    pySpan_localUVWChans_getset,
    pySpan_minDist_getset,
    pySpan_maxDist_getset,
    pySpan_waterHeight_getset,
    pySpan_localBounds_getset,
    pySpan_worldBounds_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Span, plSpan, "plSpan wrapper")

PY_PLASMA_TYPE_INIT(Span)
{
    pySpan_Type.tp_dealloc = pySpan_dealloc;
    pySpan_Type.tp_init = pySpan___init__;
    pySpan_Type.tp_new = pySpan_new;
    pySpan_Type.tp_methods = pySpan_Methods;
    pySpan_Type.tp_getset = pySpan_GetSet;
    if (PyType_CheckAndReady(&pySpan_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(Span, "kLiteMaterial", plSpan::kLiteMaterial);
    PY_TYPE_ADD_CONST(Span, "kPropNoDraw", plSpan::kPropNoDraw);
    PY_TYPE_ADD_CONST(Span, "kPropNoShadowCast", plSpan::kPropNoShadowCast);
    PY_TYPE_ADD_CONST(Span, "kPropFacesSortable", plSpan::kPropFacesSortable);
    PY_TYPE_ADD_CONST(Span, "kPropVolatile", plSpan::kPropVolatile);
    PY_TYPE_ADD_CONST(Span, "kWaterHeight", plSpan::kWaterHeight);
    PY_TYPE_ADD_CONST(Span, "kPropRunTimeLight", plSpan::kPropRunTimeLight);
    PY_TYPE_ADD_CONST(Span, "kPropReverseSort", plSpan::kPropReverseSort);
    PY_TYPE_ADD_CONST(Span, "kPropHasPermaLights", plSpan::kPropHasPermaLights);
    PY_TYPE_ADD_CONST(Span, "kPropHasPermaProjs", plSpan::kPropHasPermaProjs);
    PY_TYPE_ADD_CONST(Span, "kLiteVtxPreshaded", plSpan::kLiteVtxPreshaded);
    PY_TYPE_ADD_CONST(Span, "kLiteVtxNonPreshaded", plSpan::kLiteVtxNonPreshaded);
    PY_TYPE_ADD_CONST(Span, "kLiteProjection", plSpan::kLiteProjection);
    PY_TYPE_ADD_CONST(Span, "kLiteShadowErase", plSpan::kLiteShadowErase);
    PY_TYPE_ADD_CONST(Span, "kLiteShadow", plSpan::kLiteShadow);
    PY_TYPE_ADD_CONST(Span, "kPropMatHasSpecular", plSpan::kPropMatHasSpecular);
    PY_TYPE_ADD_CONST(Span, "kPropProjAsVtx", plSpan::kPropProjAsVtx);
    PY_TYPE_ADD_CONST(Span, "kPropSkipProjection", plSpan::kPropSkipProjection);
    PY_TYPE_ADD_CONST(Span, "kPropNoShadow", plSpan::kPropNoShadow);
    PY_TYPE_ADD_CONST(Span, "kPropForceShadow", plSpan::kPropForceShadow);
    PY_TYPE_ADD_CONST(Span, "kPropDisableNormal", plSpan::kPropDisableNormal);
    PY_TYPE_ADD_CONST(Span, "kPropCharacter", plSpan::kPropCharacter);
    PY_TYPE_ADD_CONST(Span, "kPartialSort", plSpan::kPartialSort);
    PY_TYPE_ADD_CONST(Span, "kVisLOS", plSpan::kVisLOS);

    // plSpanType
    PY_TYPE_ADD_CONST(Span, "kSpan", plSpan::kSpan);
    PY_TYPE_ADD_CONST(Span, "kVertexSpan", plSpan::kVertexSpan);
    PY_TYPE_ADD_CONST(Span, "kIcicleSpan", plSpan::kIcicleSpan);
    PY_TYPE_ADD_CONST(Span, "kNullSpan", plSpan::kNullSpan);
    PY_TYPE_ADD_CONST(Span, "kParticleSpan", plSpan::kParticleSpan);
    PY_TYPE_ADD_CONST(Span, "kParticleSet", plSpan::kParticleSet);

    Py_INCREF(&pySpan_Type);
    return (PyObject*)&pySpan_Type;
}

PY_PLASMA_IFC_METHODS(Span, plSpan)
