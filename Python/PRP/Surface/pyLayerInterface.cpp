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
#include <PRP/Surface/plLayer.h>
#include "pyGMatState.h"
#include "pyLayer.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Object/pySynchedObject.h"
#include "Math/pyMatrix.h"
#include "Sys/pyColor.h"

extern "C" {

static PyObject* pyLayerInterface_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plLayerInterface is abstract");
    return NULL;
}

static PyObject* pyLayerInterface_getUnderLay(pyLayerInterface* self, void*) {
    return pyKey_FromKey(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getUnderLay());
}

static PyObject* pyLayerInterface_getTexture(pyLayerInterface* self, void*) {
    return pyKey_FromKey(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getTexture());
}

static PyObject* pyLayerInterface_getVS(pyLayerInterface* self, void*) {
    return pyKey_FromKey(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getVertexShader());
}

static PyObject* pyLayerInterface_getPS(pyLayerInterface* self, void*) {
    return pyKey_FromKey(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getPixelShader());
}

static PyObject* pyLayerInterface_getXform(pyLayerInterface* self, void*) {
    return pyMatrix44_FromMatrix44(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getTransform());
}

static PyObject* pyLayerInterface_getBumpXform(pyLayerInterface* self, void*) {
    return pyMatrix44_FromMatrix44(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getBumpEnvTransform());
}

static PyObject* pyLayerInterface_getPreshade(pyLayerInterface* self, void*) {
    return pyColorRGBA_FromColorRGBA(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getPreshade());
}

static PyObject* pyLayerInterface_getRuntime(pyLayerInterface* self, void*) {
    return pyColorRGBA_FromColorRGBA(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getRuntime());
}

static PyObject* pyLayerInterface_getAmbient(pyLayerInterface* self, void*) {
    return pyColorRGBA_FromColorRGBA(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getAmbient());
}

static PyObject* pyLayerInterface_getSpecular(pyLayerInterface* self, void*) {
    return pyColorRGBA_FromColorRGBA(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getSpecular());
}

static PyObject* pyLayerInterface_getOpacity(pyLayerInterface* self, void*) {
    return PyFloat_FromDouble(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getOpacity());
}

static PyObject* pyLayerInterface_getUVWSrc(pyLayerInterface* self, void*) {
    return PyInt_FromLong(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getUVWSrc());
}

static PyObject* pyLayerInterface_getLODBias(pyLayerInterface* self, void*) {
    return PyFloat_FromDouble(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getLODBias());
}

static PyObject* pyLayerInterface_getSpecPower(pyLayerInterface* self, void*) {
    return PyFloat_FromDouble(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getSpecularPower());
}

static PyObject* pyLayerInterface_getState(pyLayerInterface* self, void*) {
    return pyGMatState_FromGMatState(plLayerInterface::Convert(IConvert((pyCreatable*)self))->getState());
}

static int pyLayerInterface_setUnderLay(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        plLayerInterface::Convert(IConvert((pyCreatable*)self))->setUnderLay(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "underLay should be a plKey");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setUnderLay(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setTexture(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        plLayerInterface::Convert(IConvert((pyCreatable*)self))->setTexture(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "texture should be a plKey");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setTexture(*((pyKey*)value)->fThis);
    return 0;
}


static int pyLayerInterface_setVS(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        plLayerInterface::Convert(IConvert((pyCreatable*)self))->setVertexShader(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "vertexShader should be a plKey");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setVertexShader(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setPS(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        plLayerInterface::Convert(IConvert((pyCreatable*)self))->setPixelShader(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "pixelShader should be a plKey");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setPixelShader(*((pyKey*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setXform(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        plLayerInterface::Convert(IConvert((pyCreatable*)self))->setTransform(hsMatrix44::Identity());
        return 0;
    }
    if (!pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "transform should be an hsMatrix44");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setTransform(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setBumpXform(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL) {
        plLayerInterface::Convert(IConvert((pyCreatable*)self))->setBumpEnvTransform(hsMatrix44::Identity());
        return 0;
    }
    if (!pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "bumpEnvTransform should be an hsMatrix44");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setBumpEnvTransform(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setPreshade(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "preshade should be an hsColorRGBA");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setPreshade(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setRuntime(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "runtime should be an hsColorRGBA");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setRuntime(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setAmbient(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ambient should be an hsColorRGBA");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setAmbient(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setSpecular(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "specular should be an hsColorRGBA");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setSpecular(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyLayerInterface_setOpacity(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "opacity should be a float");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setOpacity(PyFloat_AsDouble(value));
    return 0;
}

static int pyLayerInterface_setUVWSrc(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "UVWSrc should be an int");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setUVWSrc(PyInt_AsLong(value));
    return 0;
}

static int pyLayerInterface_setLODBias(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "LODBias should be a float");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setLODBias(PyFloat_AsDouble(value));
    return 0;
}

static int pyLayerInterface_setSpecPower(pyLayerInterface* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "specularPower should be a float");
        return -1;
    }
    plLayerInterface::Convert(IConvert((pyCreatable*)self))->setSpecularPower(PyFloat_AsDouble(value));
    return 0;
}

static int pyLayerInterface_setState(pyLayerInterface* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "state is not assignable");
    return -1;
}

static PyMethodDef pyLayerInterface_Methods[] = {
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
    PyVarObject_HEAD_INIT(NULL, 0)
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

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
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
    delete pylay->fThis;
    pylay->fThis = layer;
    pylay->fPyOwned = false;
    return (PyObject*)pylay;
}

}
