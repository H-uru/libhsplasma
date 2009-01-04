#include <Python.h>
#include <PRP/Surface/plLayer.h>
#include "pyGMatState.h"
#include "pyLayer.h"
#include "../pyCreatable.h"
#include "../KeyedObject/pyKey.h"
#include "../Object/pySynchedObject.h"
#include "../../Math/pyMatrix.h"
#include "../../Sys/pyColor.h"

extern "C" {

static PyObject* pyLayerInterface_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plLayerInterface is abstract");
    return NULL;
}

static PyObject* pyLayerInterface_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyLayerInterface_FromLayerInterface(plLayerInterface::Convert(cre->fThis));
}

static PyObject* pyLayerInterface_getUnderLay(pyLayerInterface* self, void*) {
    return pyKey_FromKey(self->fThis->getUnderLay());
}

static PyObject* pyLayerInterface_getTexture(pyLayerInterface* self, void*) {
    return pyKey_FromKey(self->fThis->getTexture());
}

static PyObject* pyLayerInterface_getVS(pyLayerInterface* self, void*) {
    return pyKey_FromKey(self->fThis->getVertexShader());
}

static PyObject* pyLayerInterface_getPS(pyLayerInterface* self, void*) {
    return pyKey_FromKey(self->fThis->getPixelShader());
}

static PyObject* pyLayerInterface_getXform(pyLayerInterface* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getTransform());
}

static PyObject* pyLayerInterface_getBumpXform(pyLayerInterface* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getBumpEnvTransform());
}

static PyObject* pyLayerInterface_getPreshade(pyLayerInterface* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getPreshade());
}

static PyObject* pyLayerInterface_getRuntime(pyLayerInterface* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getRuntime());
}

static PyObject* pyLayerInterface_getAmbient(pyLayerInterface* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getAmbient());
}

static PyObject* pyLayerInterface_getSpecular(pyLayerInterface* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getSpecular());
}

static PyObject* pyLayerInterface_getOpacity(pyLayerInterface* self, void*) {
    return PyFloat_FromDouble(self->fThis->getOpacity());
}

static PyObject* pyLayerInterface_getUVWSrc(pyLayerInterface* self, void*) {
    return PyInt_FromLong(self->fThis->getUVWSrc());
}

static PyObject* pyLayerInterface_getLODBias(pyLayerInterface* self, void*) {
    return PyFloat_FromDouble(self->fThis->getLODBias());
}

static PyObject* pyLayerInterface_getSpecPower(pyLayerInterface* self, void*) {
    return PyFloat_FromDouble(self->fThis->getSpecularPower());
}

static PyObject* pyLayerInterface_getState(pyLayerInterface* self, void*) {
	return pyGMatState_FromGMatState(self->fThis->getState());
}

static int pyLayerInterface_setUnderLay(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setUnderLay(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "underLay should be a plKey");
        return -1;
    }
    self->fThis->setUnderLay(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setTexture(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setTexture(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "texture should be a plKey");
        return -1;
    }
    self->fThis->setTexture(*((pyKey*)value)->fThis);
    return 0;
}


static int pyLayerInterface_setVS(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setVertexShader(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "vertexShader should be a plKey");
        return -1;
    }
    self->fThis->setVertexShader(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setPS(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setPixelShader(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "pixelShader should be a plKey");
        return -1;
    }
    self->fThis->setPixelShader(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setXform(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setTransform(hsMatrix44::Identity());
        return 0;
    }
    if (!pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "transform should be an hsMatrix44");
        return -1;
    }
    self->fThis->setTransform(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setBumpXform(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setBumpEnvTransform(hsMatrix44::Identity());
        return 0;
    }
    if (!pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "bumpEnvTransform should be an hsMatrix44");
        return -1;
    }
    self->fThis->setBumpEnvTransform(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setPreshade(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "preshade should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setPreshade(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setRuntime(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "runtime should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setRuntime(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setAmbient(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ambient should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setAmbient(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setSpecular(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "specular should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setSpecular(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setOpacity(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "opacity should be a float");
        return -1;
    }
    self->fThis->setOpacity(PyFloat_AsDouble(value));
    return 0;
}

static int pyLayerInterface_setUVWSrc(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "UVWSrc should be an int");
        return -1;
    }
    self->fThis->setUVWSrc(PyInt_AsLong(value));
    return 0;
}

static int pyLayerInterface_setLODBias(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "LODBias should be a float");
        return -1;
    }
    self->fThis->setLODBias(PyFloat_AsDouble(value));
    return 0;
}

static int pyLayerInterface_setSpecPower(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "specularPower should be a float");
        return -1;
    }
    self->fThis->setSpecularPower(PyFloat_AsDouble(value));
    return 0;
}

static int pyLayerInterface_setState(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !pyGMatState_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "state should be an hsGMatState");
        return -1;
    }
    self->fThis->setState(*((pyGMatState*)value)->fThis);
    return 0;
}

static PyMethodDef pyLayerInterface_Methods[] = {
    { "Convert", (PyCFunction)pyLayerInterface_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plLayerInterface" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLayerInterface_GetSet[] = {
    { "underLay", (getter)pyLayerInterface_getUnderLay, (setter)pyLayerInterface_setUnderLay, NULL, NULL },
    { "texture", (getter)pyLayerInterface_getTexture, (setter)pyLayerInterface_setTexture, NULL, NULL },
    { "vertexShader", (getter)pyLayerInterface_getVS, (setter)pyLayerInterface_setVS, NULL, NULL },
    { "pixelShader", (getter)pyLayerInterface_getPS, (setter)pyLayerInterface_setPS, NULL, NULL },
    { "transform", (getter)pyLayerInterface_getXform, (setter)pyLayerInterface_setXform, NULL, NULL },
    { "bumpEnvTransform", (getter)pyLayerInterface_getBumpXform, (setter)pyLayerInterface_setBumpXform, NULL, NULL },
    { "preshade", (getter)pyLayerInterface_getPreshade, (setter)pyLayerInterface_setPreshade, NULL, NULL },
    { "runtime", (getter)pyLayerInterface_getRuntime, (setter)pyLayerInterface_setRuntime, NULL, NULL },
    { "ambient", (getter)pyLayerInterface_getAmbient, (setter)pyLayerInterface_setAmbient, NULL, NULL },
    { "specular", (getter)pyLayerInterface_getSpecular, (setter)pyLayerInterface_setSpecular, NULL, NULL },
    { "opacity", (getter)pyLayerInterface_getOpacity, (setter)pyLayerInterface_setOpacity, NULL, NULL },
    { "UVWSrc", (getter)pyLayerInterface_getUVWSrc, (setter)pyLayerInterface_setUVWSrc, NULL, NULL },
    { "LODBias", (getter)pyLayerInterface_getLODBias, (setter)pyLayerInterface_setLODBias, NULL, NULL },
    { "specularPower", (getter)pyLayerInterface_getSpecPower, (setter)pyLayerInterface_setSpecPower, NULL, NULL },
	{ "state", (getter)pyLayerInterface_getState, (setter)pyLayerInterface_setState, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLayerInterface_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plLayerInterface",        /* tp_name */
    sizeof(pyLayerInterface),           /* tp_basicsize */
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
    "plLayerInterface wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLayerInterface_Methods,           /* tp_methods */
    NULL,                               /* tp_members */
    pyLayerInterface_GetSet,            /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLayerInterface_new,               /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyLayerInterface_Type() {
    pyLayerInterface_Type.tp_base = &pySynchedObject_Type;
    if (PyType_Ready(&pyLayerInterface_Type) < 0)
        return NULL;

    /* plLayerDirtyBits */
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kTransform",
                         PyInt_FromLong(plLayerInterface::kTransform));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kPreshadeColor",
                         PyInt_FromLong(plLayerInterface::kPreshadeColor));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kAmbientColor",
                         PyInt_FromLong(plLayerInterface::kAmbientColor));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kOpacity",
                         PyInt_FromLong(plLayerInterface::kOpacity));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kTexture",
                         PyInt_FromLong(plLayerInterface::kTexture));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kState",
                         PyInt_FromLong(plLayerInterface::kState));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kUVWSrc",
                         PyInt_FromLong(plLayerInterface::kUVWSrc));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kLODBias",
                         PyInt_FromLong(plLayerInterface::kLODBias));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kSpecularColor",
                         PyInt_FromLong(plLayerInterface::kSpecularColor));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kSpecularPower",
                         PyInt_FromLong(plLayerInterface::kSpecularPower));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kRuntimeColor",
                         PyInt_FromLong(plLayerInterface::kRuntimeColor));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kVertexShader",
                         PyInt_FromLong(plLayerInterface::kVertexShader));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kPixelShader",
                         PyInt_FromLong(plLayerInterface::kPixelShader));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kBumpEnvXfm",
                         PyInt_FromLong(plLayerInterface::kBumpEnvXfm));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kAllDirty",
                         PyInt_FromLong(plLayerInterface::kAllDirty));

    /* plUVWSrcModifiers */
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kUVWPassThru",
                         PyInt_FromLong(plLayerInterface::kUVWPassThru));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kUVWIdxMask",
                         PyInt_FromLong(plLayerInterface::kUVWIdxMask));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kUVWNormal",
                         PyInt_FromLong(plLayerInterface::kUVWNormal));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kUVWPosition",
                         PyInt_FromLong(plLayerInterface::kUVWPosition));
    PyDict_SetItemString(pyLayerInterface_Type.tp_dict, "kUVWReflect",
                         PyInt_FromLong(plLayerInterface::kUVWReflect));

    Py_INCREF(&pyLayerInterface_Type);
    return (PyObject*)&pyLayerInterface_Type;
}

int pyLayerInterface_Check(PyObject* obj) {
    if (obj->ob_type == &pyLayerInterface_Type
        || PyType_IsSubtype(obj->ob_type, &pyLayerInterface_Type))
        return 1;
    return 0;
}

PyObject* pyLayerInterface_FromLayerInterface(class plLayerInterface* layer) {
    if (layer == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLayerInterface* pylay = PyObject_New(pyLayerInterface, &pyLayerInterface_Type);
    pylay->fThis = layer;
    pylay->fPyOwned = false;
    return (PyObject*)pylay;
}

}
