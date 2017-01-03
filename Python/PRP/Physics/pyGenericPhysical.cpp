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

extern "C" {

PY_PLASMA_NEW(GenericPhysical, plGenericPhysical)

PY_METHOD_VA(GenericPhysical, getProperty,
    "Params: flag\n"
    "Returns whether the specified property is set")
{
    int prop;
    if (!PyArg_ParseTuple(args, "i", &prop)) {
        PyErr_SetString(PyExc_TypeError, "getProperty expects an int");
        return NULL;
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
        return NULL;
    }
    self->fThis->setProperty(prop, value != 0);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GenericPhysical, calcSphereBounds,
    "Params: points\n"
    "Calculates sphere bounds from a given point cloud")
{
    PyObject* points;
    if (!(PyArg_ParseTuple(args, "O", &points) && PySequence_Check(points))) {
        PyErr_SetString(PyExc_TypeError, "calcSphereBounds expects a sequence of hsVector3");
        return NULL;
    }

    hsVector3* myPoints = new hsVector3[PySequence_Length(points)];
    for (Py_ssize_t i = 0; i < PySequence_Length(points); ++i) {
        PyObject* item = PySequence_GetItem(points, i);
        if (!pyVector3_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "calcSphereBounds expects a sequence of hsVector3");
            Py_XDECREF(item);
            delete[] myPoints;
            return NULL;
        }

        myPoints[i] = *((pyVector3*)item)->fThis;
        Py_DECREF(item);
    }

    self->fThis->calcSphereBounds(PySequence_Length(points), myPoints);
    delete[] myPoints;

    Py_RETURN_NONE;
}

PY_METHOD_VA(GenericPhysical, calcBoxBounds,
    "Params: points\n"
    "Calculates box bounds from a given point cloud")
{
    PyObject* points;
    if (!(PyArg_ParseTuple(args, "O", &points) && PySequence_Check(points))) {
        PyErr_SetString(PyExc_TypeError, "calcBoxBounds expects a sequence of hsVector3");
        return NULL;
    }

    hsVector3* myPoints = new hsVector3[PySequence_Length(points)];
    for (Py_ssize_t i = 0; i < PySequence_Length(points); ++i) {
        PyObject* item = PySequence_GetItem(points, i);
        if (!pyVector3_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "calcBoxBounds expects a sequence of hsVector3");
            Py_XDECREF(item);
            delete[] myPoints;
            return NULL;
        }

        myPoints[i] = *((pyVector3*)item)->fThis;
        Py_DECREF(item);
    }

    self->fThis->calcBoxBounds(PySequence_Length(points), myPoints);
    delete[] myPoints;

    Py_RETURN_NONE;
}

static PyMethodDef pyGenericPhysical_Methods[] = {
    pyGenericPhysical_getProperty_method,
    pyGenericPhysical_setProperty_method,
    pyGenericPhysical_calcSphereBounds_method,
    pyGenericPhysical_calcBoxBounds_method,
    PY_METHOD_TERMINATOR
};

static PyObject* pyGenericPhysical_getVerts(pyGenericPhysical* self, void*) {
    PyObject* list = PyList_New(self->fThis->getVerts().size());
    for (size_t i=0; i<self->fThis->getVerts().size(); i++)
        PyList_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getVerts()[i]));
    return list;
}

static PyObject* pyGenericPhysical_getIndices(pyGenericPhysical* self, void*) {
    PyObject* list = PyList_New(self->fThis->getIndices().size());
    for (size_t i=0; i<self->fThis->getIndices().size(); i++)
        PyList_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getIndices()[i]));
    return list;
}

static int pyGenericPhysical_setVerts(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setVerts(0, NULL);
        return 0;
    } else if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "verts should be list of hsVector3s");
        return -1;
    }
    size_t nVerts = PyList_Size(value);
    if (nVerts == 0) {
        self->fThis->setVerts(0, NULL);
        return 0;
    }
    hsVector3* verts = new hsVector3[nVerts];
    for (size_t i=0; i<nVerts; i++) {
        PyObject* vert = PyList_GetItem(value, i);
        if (vert == NULL || !pyVector3_Check(vert)) {
            PyErr_SetString(PyExc_TypeError, "verts should be list of hsVector3s");
            delete[] verts;
            return -1;
        }
        verts[i] = *((pyVector3*)vert)->fThis;
    }
    self->fThis->setVerts(nVerts, verts);
    delete[] verts;
    return 0;
}

static int pyGenericPhysical_setIndices(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setIndices(0, NULL);
        return 0;
    } else if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "indices should be list of ints");
        return -1;
    }
    size_t nIndices = PyList_Size(value);
    if (nIndices == 0) {
        self->fThis->setIndices(0, NULL);
        return 0;
    }
    unsigned int* indices = new unsigned int[nIndices];
    for (size_t i=0; i<nIndices; i++) {
        PyObject* idx = PyList_GetItem(value, i);
        if (idx == NULL || !PyInt_Check(idx)) {
            PyErr_SetString(PyExc_TypeError, "indices should be list of ints");
            delete[] indices;
            return -1;
        }
        indices[i] = PyInt_AsLong(idx);
    }
    self->fThis->setIndices(nIndices, indices);
    delete[] indices;
    return 0;
}

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

PY_GETSET_GETTER_DECL(GenericPhysical, TMDBuffer) {
    return PyBytes_FromStringAndSize((const char*)self->fThis->getTMDBuffer(),
                                     self->fThis->getTMDSize());
}

PY_GETSET_SETTER_DECL(GenericPhysical, TMDBuffer) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "TMDBuffer cannot be deleted");
        return -1;
    } else if (value == Py_None) {
        self->fThis->setTMDBuffer(0, NULL);
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
    { _pycs("verts"), (getter)pyGenericPhysical_getVerts,
        (setter)pyGenericPhysical_setVerts, NULL, NULL },
    { _pycs("indices"), (getter)pyGenericPhysical_getIndices,
        (setter)pyGenericPhysical_setIndices, NULL, NULL },
    pyGenericPhysical_TMDBuffer_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyGenericPhysical_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plGenericPhysical",     /* tp_name */
    sizeof(pyPhysical),                 /* tp_basicsize */
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
    "plGenericPhysical wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyGenericPhysical_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    pyGenericPhysical_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyGenericPhysical_new,              /* tp_new */
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

PyObject* Init_pyGenericPhysical_Type() {
    pyGenericPhysical_Type.tp_base = &pyPhysical_Type;
    if (PyType_Ready(&pyGenericPhysical_Type) < 0)
        return NULL;

    Py_INCREF(&pyGenericPhysical_Type);
    return (PyObject*)&pyGenericPhysical_Type;
}

PY_PLASMA_IFC_METHODS(GenericPhysical, plGenericPhysical)

}
