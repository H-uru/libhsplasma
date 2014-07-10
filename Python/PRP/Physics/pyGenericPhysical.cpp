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
#include <PRP/Physics/plGenericPhysical.h>
#include "pyPhysical.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"
#include "Math/pyGeometry3.h"
#include "Util/pyBitVector.h"

extern "C" {

static PyObject* pyGenericPhysical_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyGenericPhysical* self = (pyGenericPhysical*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plGenericPhysical();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyGenericPhysical_getProp(pyGenericPhysical* self, PyObject* args) {
    int prop;
    if (!PyArg_ParseTuple(args, "i", &prop)) {
        PyErr_SetString(PyExc_TypeError, "getProperty expects an int");
        return NULL;
    }
    return PyBool_FromLong(self->fThis->getProperty(prop) ? 1 : 0);
}

static PyObject* pyGenericPhysical_setProp(pyGenericPhysical* self, PyObject* args) {
    int prop, value;
    if (!PyArg_ParseTuple(args, "ii", &prop, &value)) {
        PyErr_SetString(PyExc_TypeError, "setProperty expects int, bool");
        return NULL;
    }
    self->fThis->setProperty(prop, value != 0);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGenericPhysical_calcSphereBounds(pyGenericPhysical* self, PyObject* args) {
    PyObject* points;
    if (!(PyArg_ParseTuple(args, "O", &points) && PySequence_Check(points))) {
        PyErr_SetString(PyExc_TypeError, "calcSphereBounds expects a sequence of hsVector3");
        return NULL;
    }

    hsVector3* myPoints = new hsVector3[PySequence_Length(points)];
    for (size_t i = 0; i < PySequence_Length(points); ++i) {
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

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyGenericPhysical_Methods[] = {
    { "getProperty", (PyCFunction)pyGenericPhysical_getProp, METH_VARARGS,
      "Params: flag\n"
      "Returns whether the specified property is set" },
    { "setProperty", (PyCFunction)pyGenericPhysical_setProp, METH_VARARGS,
      "Params: flag, value\n"
      "Sets the specified property" },
    { "calcSphereBounds", (PyCFunction)pyGenericPhysical_calcSphereBounds, METH_VARARGS,
      "Params: points\n"
      "Calculates sphere bounds from a given point cloud" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pyGenericPhysical_getMass(pyGenericPhysical* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMass());
}

static PyObject* pyGenericPhysical_getFriction(pyGenericPhysical* self, void*) {
    return PyFloat_FromDouble(self->fThis->getFriction());
}

static PyObject* pyGenericPhysical_getRestitution(pyGenericPhysical* self, void*) {
    return PyFloat_FromDouble(self->fThis->getRestitution());
}

static PyObject* pyGenericPhysical_getBounds(pyGenericPhysical* self, void*) {
    return PyInt_FromLong(self->fThis->getBoundsType());
}

static PyObject* pyGenericPhysical_getMemberGroup(pyGenericPhysical* self, void*) {
    return PyInt_FromLong(self->fThis->getMemberGroup());
}

static PyObject* pyGenericPhysical_getReportGroup(pyGenericPhysical* self, void*) {
    return PyInt_FromLong(self->fThis->getReportGroup());
}

static PyObject* pyGenericPhysical_getCollideGroup(pyGenericPhysical* self, void*) {
    return PyInt_FromLong(self->fThis->getCollideGroup());
}

static PyObject* pyGenericPhysical_getLOSDBs(pyGenericPhysical* self, void*) {
    return PyInt_FromLong(self->fThis->getLOSDBs());
}

static PyObject* pyGenericPhysical_getObject(pyGenericPhysical* self, void*) {
    return pyKey_FromKey(self->fThis->getObject());
}

static PyObject* pyGenericPhysical_getSceneNode(pyGenericPhysical* self, void*) {
    return pyKey_FromKey(self->fThis->getSceneNode());
}

static PyObject* pyGenericPhysical_getSubWorld(pyGenericPhysical* self, void*) {
    return pyKey_FromKey(self->fThis->getSubWorld());
}

static PyObject* pyGenericPhysical_getSoundGroup(pyGenericPhysical* self, void*) {
    return pyKey_FromKey(self->fThis->getSoundGroup());
}

static PyObject* pyGenericPhysical_getPos(pyGenericPhysical* self, void*) {
    return pyVector3_FromVector3(self->fThis->getPos());
}

static PyObject* pyGenericPhysical_getRot(pyGenericPhysical* self, void*) {
    return pyQuat_FromQuat(self->fThis->getRot());
}

static PyObject* pyGenericPhysical_getDims(pyGenericPhysical* self, void*) {
    return pyVector3_FromVector3(self->fThis->getDimensions());
}

static PyObject* pyGenericPhysical_getOffset(pyGenericPhysical* self, void*) {
    return pyVector3_FromVector3(self->fThis->getOffset());
}

static PyObject* pyGenericPhysical_getRadius(pyGenericPhysical* self, void*) {
    return PyFloat_FromDouble(self->fThis->getRadius());
}

static PyObject* pyGenericPhysical_getLength(pyGenericPhysical* self, void*) {
    return PyFloat_FromDouble(self->fThis->getLength());
}

static PyObject* pyGenericPhysical_getVerts(pyGenericPhysical* self, void*) {
    PyObject* list = PyList_New(self->fThis->getVerts().size());
    for (size_t i=0; i<self->fThis->getVerts().size(); i++)
        PyList_SET_ITEM(list, i, pyVector3_FromVector3(self->fThis->getVerts()[i]));
    return list;
}

static PyObject* pyGenericPhysical_getIndices(pyGenericPhysical* self, void*) {
    PyObject* list = PyList_New(self->fThis->getIndices().size());
    for (size_t i=0; i<self->fThis->getIndices().size(); i++)
        PyList_SET_ITEM(list, i, PyInt_FromLong(self->fThis->getIndices()[i]));
    return list;
}

static PyObject* pyGenericPhysical_getTMDBuffer(pyGenericPhysical* self, void*) {
    return PyBytes_FromStringAndSize((const char*)self->fThis->getTMDBuffer(),
                                     self->fThis->getTMDSize());
}

static int pyGenericPhysical_setMass(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "mass should be a float");
        return -1;
    }
    self->fThis->setMass(PyFloat_AsDouble(value));
    return 0;
}

static int pyGenericPhysical_setFriction(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "friction should be a float");
        return -1;
    }
    self->fThis->setFriction(PyFloat_AsDouble(value));
    return 0;
}

static int pyGenericPhysical_setRestitution(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "restitution should be a float");
        return -1;
    }
    self->fThis->setRestitution(PyFloat_AsDouble(value));
    return 0;
}

static int pyGenericPhysical_setBounds(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "boundsType should be an int");
        return -1;
    }
    self->fThis->setBoundsType((plSimDefs::Bounds)PyInt_AsLong(value));
    return 0;
}

static int pyGenericPhysical_setMemberGroup(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "memberGroup should be an int");
        return -1;
    }
    self->fThis->setMemberGroup(PyInt_AsLong(value));
    return 0;
}

static int pyGenericPhysical_setReportGroup(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "reportGroup should be an int");
        return -1;
    }
    self->fThis->setReportGroup(PyInt_AsLong(value));
    return 0;
}

static int pyGenericPhysical_setCollideGroup(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "collideGroup should be an int");
        return -1;
    }
    self->fThis->setCollideGroup(PyInt_AsLong(value));
    return 0;
}

static int pyGenericPhysical_setLOSDBs(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "LOSDBs should be an int");
        return -1;
    }
    self->fThis->setLOSDBs(PyInt_AsLong(value));
    return 0;
}

static int pyGenericPhysical_setObject(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setObject(plKey());
        return 0;
    } else if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "object should be a plKey");
        return -1;
    }
    self->fThis->setObject(*((pyKey*)value)->fThis);
    return 0;
}

static int pyGenericPhysical_setSceneNode(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setSceneNode(plKey());
        return 0;
    } else if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "sceneNode should be a plKey");
        return -1;
    }
    self->fThis->setSceneNode(*((pyKey*)value)->fThis);
    return 0;
}

static int pyGenericPhysical_setSubWorld(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setSubWorld(plKey());
        return 0;
    } else if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "subWorld should be a plKey");
        return -1;
    }
    self->fThis->setSubWorld(*((pyKey*)value)->fThis);
    return 0;
}

static int pyGenericPhysical_setSoundGroup(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setSoundGroup(plKey());
        return 0;
    } else if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "soundGroup should be a plKey");
        return -1;
    }
    self->fThis->setSoundGroup(*((pyKey*)value)->fThis);
    return 0;
}

static int pyGenericPhysical_setPos(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "pos should be an hsVector3");
        return -1;
    }
    self->fThis->setPos(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyGenericPhysical_setRot(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !pyQuat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "rot should be an hsQuat");
        return -1;
    }
    self->fThis->setRot(*((pyQuat*)value)->fThis);
    return 0;
}

static int pyGenericPhysical_setDims(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "dimensions should be an hsVector3");
        return -1;
    }
    self->fThis->setDimensions(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyGenericPhysical_setOffset(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "offset should be an hsVector3");
        return -1;
    }
    self->fThis->setOffset(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyGenericPhysical_setRadius(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "radius should be a float");
        return -1;
    }
    self->fThis->setRadius(PyFloat_AsDouble(value));
    return 0;
}

static int pyGenericPhysical_setLength(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "length should be a float");
        return -1;
    }
    self->fThis->setLength(PyFloat_AsDouble(value));
    return 0;
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

static int pyGenericPhysical_setTMDBuffer(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL) {
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

static PyGetSetDef pyGenericPhysical_GetSet[] = {
    { _pycs("mass"), (getter)pyGenericPhysical_getMass,
        (setter)pyGenericPhysical_setMass, NULL, NULL },
    { _pycs("friction"), (getter)pyGenericPhysical_getFriction,
        (setter)pyGenericPhysical_setFriction, NULL, NULL },
    { _pycs("restitution"), (getter)pyGenericPhysical_getRestitution,
        (setter)pyGenericPhysical_setRestitution, NULL, NULL },
    { _pycs("boundsType"), (getter)pyGenericPhysical_getBounds,
        (setter)pyGenericPhysical_setBounds, NULL, NULL },
    { _pycs("memberGroup"), (getter)pyGenericPhysical_getMemberGroup,
        (setter)pyGenericPhysical_setMemberGroup, NULL, NULL },
    { _pycs("reportGroup"), (getter)pyGenericPhysical_getReportGroup,
        (setter)pyGenericPhysical_setReportGroup, NULL, NULL },
    { _pycs("collideGroup"), (getter)pyGenericPhysical_getCollideGroup,
        (setter)pyGenericPhysical_setCollideGroup, NULL, NULL },
    { _pycs("LOSDBs"), (getter)pyGenericPhysical_getLOSDBs,
        (setter)pyGenericPhysical_setLOSDBs, NULL, NULL },
    { _pycs("object"), (getter)pyGenericPhysical_getObject,
        (setter)pyGenericPhysical_setObject, NULL, NULL },
    { _pycs("sceneNode"), (getter)pyGenericPhysical_getSceneNode,
        (setter)pyGenericPhysical_setSceneNode, NULL, NULL },
    { _pycs("subWorld"), (getter)pyGenericPhysical_getSubWorld,
        (setter)pyGenericPhysical_setSubWorld, NULL, NULL },
    { _pycs("soundGroup"), (getter)pyGenericPhysical_getSoundGroup,
        (setter)pyGenericPhysical_setSoundGroup, NULL, NULL },
    { _pycs("pos"), (getter)pyGenericPhysical_getPos,
        (setter)pyGenericPhysical_setPos, NULL, NULL },
    { _pycs("rot"), (getter)pyGenericPhysical_getRot,
        (setter)pyGenericPhysical_setRot, NULL, NULL },
    { _pycs("dimensions"), (getter)pyGenericPhysical_getDims,
        (setter)pyGenericPhysical_setDims, NULL, NULL },
    { _pycs("offset"), (getter)pyGenericPhysical_getOffset,
        (setter)pyGenericPhysical_setOffset, NULL, NULL },
    { _pycs("radius"), (getter)pyGenericPhysical_getRadius,
        (setter)pyGenericPhysical_setRadius, NULL, NULL },
    { _pycs("length"), (getter)pyGenericPhysical_getLength,
        (setter)pyGenericPhysical_setLength, NULL, NULL },
    { _pycs("verts"), (getter)pyGenericPhysical_getVerts,
        (setter)pyGenericPhysical_setVerts, NULL, NULL },
    { _pycs("indices"), (getter)pyGenericPhysical_getIndices,
        (setter)pyGenericPhysical_setIndices, NULL, NULL },
    { _pycs("TMDBuffer"), (getter)pyGenericPhysical_getTMDBuffer,
        (setter)pyGenericPhysical_setTMDBuffer, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
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

int pyGenericPhysical_Check(PyObject* obj) {
    if (obj->ob_type == &pyGenericPhysical_Type
        || PyType_IsSubtype(obj->ob_type, &pyGenericPhysical_Type))
        return 1;
    return 0;
}

PyObject* pyGenericPhysical_FromGenericPhysical(class plGenericPhysical* phys) {
    if (phys == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyGenericPhysical* pyphys = PyObject_New(pyGenericPhysical, &pyGenericPhysical_Type);
    pyphys->fThis = phys;
    pyphys->fPyOwned = false;
    return (PyObject*)pyphys;
}

}
