#include <Python.h>
#include <PRP/Physics/plGenericPhysical.h>
#include "pyPhysical.h"
#include "../KeyedObject/pyKey.h"
#include "../pyCreatable.h"
#include "../../Math/pyGeometry3.h"
#include "../../Util/pyBitVector.h"

extern "C" {

static PyObject* pyGenericPhysical_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyGenericPhysical* self = (pyGenericPhysical*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plGenericPhysical();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyGenericPhysical_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyGenericPhysical_FromGenericPhysical(plGenericPhysical::Convert(cre->fThis));
}

static PyMethodDef pyGenericPhysical_Methods[] = {
    { "Convert", (PyCFunction)pyGenericPhysical_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plGenericPhysical" },
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

static PyObject* pyGenericPhysical_getGroup(pyGenericPhysical* self, void*) {
    return PyInt_FromLong(self->fThis->getGroup());
}

static PyObject* pyGenericPhysical_getCat(pyGenericPhysical* self, void*) {
    return PyInt_FromLong(self->fThis->getCategory());
}

static PyObject* pyGenericPhysical_getLOSDBs(pyGenericPhysical* self, void*) {
    return PyInt_FromLong(self->fThis->getLOSDBs());
}

static PyObject* pyGenericPhysical_getReports(pyGenericPhysical* self, void*) {
    return PyInt_FromLong(self->fThis->getReportsOn());
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

static PyObject* pyGenericPhysical_getProps(pyGenericPhysical* self, void*) {
    return pyBitVector_FromBitVector(self->fThis->getProps());
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
    PyObject* list = PyList_New(self->fThis->getNumVerts());
    for (size_t i=0; i<self->fThis->getNumVerts(); i++)
        PyList_SET_ITEM(list, i, pyVector3_FromVector3(self->fThis->getVert(i)));
    return list;
}

static PyObject* pyGenericPhysical_getIndices(pyGenericPhysical* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumIndices());
    for (size_t i=0; i<self->fThis->getNumIndices(); i++)
        PyList_SET_ITEM(list, i, PyInt_FromLong(self->fThis->getIndex(i)));
    return list;
}

static PyObject* pyGenericPhysical_getTMDBuffer(pyGenericPhysical* self, void*) {
    return PyString_FromStringAndSize((const char*)self->fThis->getTMDBuffer(),
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

static int pyGenericPhysical_setGroup(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "group should be an int");
        return -1;
    }
    self->fThis->setGroup((plSimDefs::Group)PyInt_AsLong(value));
    return 0;
}

static int pyGenericPhysical_setCat(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "category should be an int");
        return -1;
    }
    self->fThis->setCategory(PyInt_AsLong(value));
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

static int pyGenericPhysical_setReports(pyGenericPhysical* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "reportsOn should be an int");
        return -1;
    }
    self->fThis->setReportsOn(PyInt_AsLong(value));
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

static int pyGenericPhysical_setProps(pyGenericPhysical* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "props cannot be assigned to");
    return -1;
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
        if (idx == NULL || !pyVector3_Check(idx)) {
            PyErr_SetString(PyExc_TypeError, "indices should be list of ints");
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
    } else if (!PyString_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "TMDBuffer should be a binary string");
        return -1;
    }
    char* buffer;
    int bufSize;
    PyString_AsStringAndSize(value, &buffer, &bufSize);
    self->fThis->setTMDBuffer(bufSize, (const unsigned char*)buffer);
    return 0;
}

static PyGetSetDef pyGenericPhysical_GetSet[] = {
    { "mass", (getter)pyGenericPhysical_getMass, (setter)pyGenericPhysical_setMass, NULL, NULL },
    { "friction", (getter)pyGenericPhysical_getFriction, (setter)pyGenericPhysical_setFriction, NULL, NULL },
    { "restitution", (getter)pyGenericPhysical_getRestitution, (setter)pyGenericPhysical_setRestitution, NULL, NULL },
    { "boundsType", (getter)pyGenericPhysical_getBounds, (setter)pyGenericPhysical_setBounds, NULL, NULL },
    { "group", (getter)pyGenericPhysical_getGroup, (setter)pyGenericPhysical_setGroup, NULL, NULL },
    { "category", (getter)pyGenericPhysical_getCat, (setter)pyGenericPhysical_setCat, NULL, NULL },
    { "LOSDBs", (getter)pyGenericPhysical_getLOSDBs, (setter)pyGenericPhysical_setLOSDBs, NULL, NULL },
    { "reportsOn", (getter)pyGenericPhysical_getReports, (setter)pyGenericPhysical_setReports, NULL, NULL },
    { "object", (getter)pyGenericPhysical_getObject, (setter)pyGenericPhysical_setObject, NULL, NULL },
    { "sceneNode", (getter)pyGenericPhysical_getSceneNode, (setter)pyGenericPhysical_setSceneNode, NULL, NULL },
    { "subWorld", (getter)pyGenericPhysical_getSubWorld, (setter)pyGenericPhysical_setSubWorld, NULL, NULL },
    { "soundGroup", (getter)pyGenericPhysical_getSoundGroup, (setter)pyGenericPhysical_setSoundGroup, NULL, NULL },
    { "pos", (getter)pyGenericPhysical_getPos, (setter)pyGenericPhysical_setPos, NULL, NULL },
    { "rot", (getter)pyGenericPhysical_getRot, (setter)pyGenericPhysical_setRot, NULL, NULL },
    { "props", (getter)pyGenericPhysical_getProps, (setter)pyGenericPhysical_setProps, NULL, NULL },
    { "dimensions", (getter)pyGenericPhysical_getDims, (setter)pyGenericPhysical_setDims, NULL, NULL },
    { "offset", (getter)pyGenericPhysical_getOffset, (setter)pyGenericPhysical_setOffset, NULL, NULL },
    { "radius", (getter)pyGenericPhysical_getRadius, (setter)pyGenericPhysical_setRadius, NULL, NULL },
    { "length", (getter)pyGenericPhysical_getLength, (setter)pyGenericPhysical_setLength, NULL, NULL },
    { "verts", (getter)pyGenericPhysical_getVerts, (setter)pyGenericPhysical_setVerts, NULL, NULL },
    { "indices", (getter)pyGenericPhysical_getIndices, (setter)pyGenericPhysical_setIndices, NULL, NULL },
    { "TMDBuffer", (getter)pyGenericPhysical_getTMDBuffer, (setter)pyGenericPhysical_setTMDBuffer, NULL, NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyGenericPhysical_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plGenericPhysical",       /* tp_name */
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
