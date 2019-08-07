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

#include "pyPhysical.h"

#include <PRP/Physics/plGenericPhysical.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"
#include "Math/pyGeometry3.h"
#include "Util/pyBitVector.h"

PY_PLASMA_NEW(GenericPhysical, plGenericPhysical)

PY_METHOD_VA(GenericPhysical, getProperty,
    "Params: flag\n"
    "Returns whether the specified property is set")
{
    int prop;
    if (!PyArg_ParseTuple(args, "i", &prop)) {
        PyErr_SetString(PyExc_TypeError, "getProperty expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getProperty(prop));
}

PY_METHOD_VA(GenericPhysical, setProperty,
    "Params: flag, value\n"
    "Sets the specified property")
{
    int prop, value;
    if (!PyArg_ParseTuple(args, "ii", &prop, &value)) {
        PyErr_SetString(PyExc_TypeError, "setProperty expects int, bool");
        return nullptr;
    }
    self->fThis->setProperty(prop, value != 0);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GenericPhysical, calcSphereBounds,
    "Params: points\n"
    "Calculates sphere bounds from a given point cloud")
{
    PyObject* pointsObj;
    if (!PyArg_ParseTuple(args, "O", &pointsObj)) {
        PyErr_SetString(PyExc_TypeError, "calcSphereBounds expects a sequence of hsVector3");
        return nullptr;
    }
    pySequenceFastRef points(pointsObj);
    if (!points.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "calcSphereBounds expects a sequence of hsVector3");
        return nullptr;
    }

    Py_ssize_t nPoints = points.size();
    std::vector<hsVector3> myPoints(nPoints);
    for (Py_ssize_t i = 0; i < nPoints; ++i) {
        PyObject* item = points.get(i);
        if (!pyPlasma_check<hsVector3>(item)) {
            PyErr_SetString(PyExc_TypeError, "calcSphereBounds expects a sequence of hsVector3");
            return nullptr;
        }
        myPoints[i] = pyPlasma_get<hsVector3>(item);
    }

    self->fThis->calcSphereBounds(myPoints.size(), &myPoints[0]);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GenericPhysical, calcBoxBounds,
    "Params: points\n"
    "Calculates box bounds from a given point cloud")
{
    PyObject* pointsObj;
    if (!PyArg_ParseTuple(args, "O", &pointsObj)) {
        PyErr_SetString(PyExc_TypeError, "calcBoxBounds expects a sequence of hsVector3");
        return nullptr;
    }
    pySequenceFastRef points(pointsObj);
    if (!points.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "calcBoxBounds expects a sequence of hsVector3");
        return nullptr;
    }

    Py_ssize_t nPoints = points.size();
    std::vector<hsVector3> myPoints(nPoints);
    for (Py_ssize_t i = 0; i < nPoints; ++i) {
        PyObject* item = points.get(i);
        if (!pyPlasma_check<hsVector3>(item)) {
            PyErr_SetString(PyExc_TypeError, "calcBoxBounds expects a sequence of hsVector3");
            return nullptr;
        }
        myPoints[i] = pyPlasma_get<hsVector3>(item);
    }

    self->fThis->calcBoxBounds(myPoints.size(), &myPoints[0]);
    Py_RETURN_NONE;
}

static PyMethodDef pyGenericPhysical_Methods[] = {
    pyGenericPhysical_getProperty_method,
    pyGenericPhysical_setProperty_method,
    pyGenericPhysical_calcSphereBounds_method,
    pyGenericPhysical_calcBoxBounds_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(GenericPhysical, verts)
{
    PyObject* list = PyTuple_New(self->fThis->getVerts().size());
    for (size_t i=0; i<self->fThis->getVerts().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getVerts()[i]));
    return list;
}

PY_GETSET_SETTER_DECL(GenericPhysical, verts)
{
    PY_PROPERTY_CHECK_NULL(verts)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "verts should be a sequence of hsVector3s");
        return -1;
    }
    Py_ssize_t nVerts = seq.size();
    std::vector<hsVector3> verts(nVerts);
    for (Py_ssize_t i=0; i<nVerts; i++) {
        PyObject* vert = seq.get(i);
        if (vert == nullptr || !pyPlasma_check<hsVector3>(vert)) {
            PyErr_SetString(PyExc_TypeError, "verts should be a sequence of hsVector3s");
            return -1;
        }
        verts[i] = pyPlasma_get<hsVector3>(vert);
    }
    self->fThis->getVerts() = verts;
    return 0;
}

PY_PROPERTY_GETSET_DECL(GenericPhysical, verts)

PY_GETSET_GETTER_DECL(GenericPhysical, indices)
{
    PyObject* list = PyTuple_New(self->fThis->getIndices().size());
    for (size_t i=0; i<self->fThis->getIndices().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getIndices()[i]));
    return list;
}

PY_GETSET_SETTER_DECL(GenericPhysical, indices)
{
    PY_PROPERTY_CHECK_NULL(indices)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "indices should be a sequence of ints");
        return -1;
    }
    Py_ssize_t nIndices = seq.size();
    std::vector<unsigned int> indices(nIndices);
    for (Py_ssize_t i=0; i<nIndices; i++) {
        PyObject* idx = seq.get(i);
        if (idx == nullptr || !pyPlasma_check<unsigned int>(idx)) {
            PyErr_SetString(PyExc_TypeError, "indices should be a sequence of ints");
            return -1;
        }
        indices[i] = pyPlasma_get<unsigned int>(idx);
    }
    self->fThis->getIndices() = indices;
    return 0;
}

PY_PROPERTY_GETSET_DECL(GenericPhysical, indices)

PY_PROPERTY(float, GenericPhysical, mass, getMass, setMass)
PY_PROPERTY(float, GenericPhysical, friction, getFriction, setFriction)
PY_PROPERTY(float, GenericPhysical, restitution, getRestitution, setRestitution)
PY_PROPERTY(plSimDefs::Bounds, GenericPhysical, boundsType, getBoundsType,
            setBoundsType)
PY_PROPERTY(unsigned int, GenericPhysical, memberGroup, getMemberGroup,
            setMemberGroup)
PY_PROPERTY(unsigned int, GenericPhysical, reportGroup, getReportGroup,
            setReportGroup)
PY_PROPERTY(unsigned int, GenericPhysical, collideGroup, getCollideGroup,
            setCollideGroup)
PY_PROPERTY(unsigned short, GenericPhysical, LOSDBs, getLOSDBs, setLOSDBs)
PY_PROPERTY(plKey, GenericPhysical, object, getObject, setObject)
PY_PROPERTY(plKey, GenericPhysical, sceneNode, getSceneNode, setSceneNode)
PY_PROPERTY(plKey, GenericPhysical, subWorld, getSubWorld, setSubWorld)
PY_PROPERTY(plKey, GenericPhysical, soundGroup, getSoundGroup, setSoundGroup)
PY_PROPERTY(hsVector3, GenericPhysical, pos, getPos, setPos)
PY_PROPERTY(hsQuat, GenericPhysical, rot, getRot, setRot)
PY_PROPERTY(hsVector3, GenericPhysical, dimensions, getDimensions, setDimensions)
PY_PROPERTY(hsVector3, GenericPhysical, offset, getOffset, setOffset)
PY_PROPERTY(float, GenericPhysical, radius, getRadius, setRadius)
PY_PROPERTY(float, GenericPhysical, length, getLength, setLength)

PY_GETSET_GETTER_DECL(GenericPhysical, TMDBuffer)
{
    return PyBytes_FromStringAndSize((const char*)self->fThis->getTMDBuffer(),
                                     self->fThis->getTMDSize());
}

PY_GETSET_SETTER_DECL(GenericPhysical, TMDBuffer)
{
    PY_PROPERTY_CHECK_NULL(TMDBuffer)
    if (value == Py_None) {
        self->fThis->setTMDBuffer(0, nullptr);
        return 0;
    } else if (!PyBytes_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "TMDBuffer should be a binary string");
        return -1;
    }
    char* buffer;
    Py_ssize_t bufSize;
    PyBytes_AsStringAndSize(value, &buffer, &bufSize);
    self->fThis->setTMDBuffer(bufSize, (const unsigned char*)buffer);
    return 0;
}

PY_PROPERTY_GETSET_DECL(GenericPhysical, TMDBuffer)

static PyGetSetDef pyGenericPhysical_GetSet[] = {
    pyGenericPhysical_mass_getset,
    pyGenericPhysical_friction_getset,
    pyGenericPhysical_restitution_getset,
    pyGenericPhysical_boundsType_getset,
    pyGenericPhysical_memberGroup_getset,
    pyGenericPhysical_reportGroup_getset,
    pyGenericPhysical_collideGroup_getset,
    pyGenericPhysical_LOSDBs_getset,
    pyGenericPhysical_object_getset,
    pyGenericPhysical_sceneNode_getset,
    pyGenericPhysical_subWorld_getset,
    pyGenericPhysical_soundGroup_getset,
    pyGenericPhysical_pos_getset,
    pyGenericPhysical_rot_getset,
    pyGenericPhysical_dimensions_getset,
    pyGenericPhysical_offset_getset,
    pyGenericPhysical_radius_getset,
    pyGenericPhysical_length_getset,
    pyGenericPhysical_verts_getset,
    pyGenericPhysical_indices_getset,
    pyGenericPhysical_TMDBuffer_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GenericPhysical, plGenericPhysical, "plGenericPhysical wrapper")

PY_PLASMA_TYPE_INIT(GenericPhysical)
{
    pyGenericPhysical_Type.tp_new = pyGenericPhysical_new;
    pyGenericPhysical_Type.tp_methods = pyGenericPhysical_Methods;
    pyGenericPhysical_Type.tp_getset = pyGenericPhysical_GetSet;
    pyGenericPhysical_Type.tp_base = &pyPhysical_Type;
    if (PyType_CheckAndReady(&pyGenericPhysical_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGenericPhysical_Type);
    return (PyObject*)&pyGenericPhysical_Type;
}

PY_PLASMA_IFC_METHODS(GenericPhysical, plGenericPhysical)
