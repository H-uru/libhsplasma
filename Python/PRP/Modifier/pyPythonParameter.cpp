#include <PyPlasma.h>
#include <PRP/Modifier/plPythonFileMod.h>
#include "pyPythonFileMod.h"
#include "PRP/KeyedObject/pyKey.h"
#include "Stream/pyStream.h"
#include "ResManager/pyResManager.h"

extern "C" {

static void pyPythonParameter_dealloc(pyPythonParameter* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyPythonParameter___init__(pyPythonParameter* self, PyObject* args, PyObject* kwds) {
    pyPythonParameter* init = NULL;

    if (PyErr_Clear(), PyArg_ParseTuple(args, "|O", &init)) {
        if (init == NULL)
            return 0;
        if (pyPythonParameter_Check((PyObject*)init)) {
            delete self->fThis;
            self->fThis = new plPythonParameter(*init->fThis);
        } else {
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

static PyObject* pyPythonParameter_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyPythonParameter* self = (pyPythonParameter*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new plPythonParameter();
    return (PyObject*)self;
}

static PyObject* pyPythonParameter_read(pyPythonParameter* self, PyObject* args) {
    pyStream* stream;
    pyResManager* mgr;
    if (!PyArg_ParseTuple(args, "OO", &stream, &mgr)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plResManager");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyResManager_Check((PyObject*)mgr)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plResManager");
        return NULL;
    }
    self->fThis->read(stream->fThis, mgr->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyPythonParameter_write(pyPythonParameter* self, PyObject* args) {
    pyStream* stream;
    pyResManager* mgr;
    if (!PyArg_ParseTuple(args, "OO", &stream, &mgr)) {
        PyErr_SetString(PyExc_TypeError, "write expects hsStream, plResManager");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyResManager_Check((PyObject*)mgr)) {
        PyErr_SetString(PyExc_TypeError, "write expects hsStream, plResManager");
        return NULL;
    }
    self->fThis->write(stream->fThis, mgr->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyPythonParameter_getID(pyPythonParameter* self, void*) {
    return PyInt_FromLong(self->fThis->fID);
}

static PyObject* pyPythonParameter_getType(pyPythonParameter* self, void*) {
    return PyInt_FromLong(self->fThis->fValueType);
}

static PyObject* pyPythonParameter_getKey(pyPythonParameter* self, void*) {
    return pyKey_FromKey(self->fThis->fObjKey);
}

static PyObject* pyPythonParameter_getString(pyPythonParameter* self, void*) {
    return PlStr_To_PyStr(self->fThis->fStrValue);
}

static PyObject* pyPythonParameter_getInt(pyPythonParameter* self, void*) {
    return PyInt_FromLong(self->fThis->fIntValue);
}

static PyObject* pyPythonParameter_getFloat(pyPythonParameter* self, void*) {
    return PyFloat_FromDouble(self->fThis->fFloatValue);
}

static PyObject* pyPythonParameter_getBool(pyPythonParameter* self, void*) {
    return PyBool_FromLong(self->fThis->fBoolValue ? 1 : 0);
}

static int pyPythonParameter_setID(pyPythonParameter* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "id should be an int");
        return -1;
    }
    self->fThis->fID = PyInt_AsLong(value);
    return 0;
}

static int pyPythonParameter_setType(pyPythonParameter* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "valueType should be an int");
        return -1;
    }
    self->fThis->fValueType = PyInt_AsLong(value);
    return 0;
}

static int pyPythonParameter_setKey(pyPythonParameter* self, PyObject* value, void*) {
    if (value == NULL || !pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "objKey should be a plKey");
        return -1;
    }
    self->fThis->fObjKey = *((pyKey*)value)->fThis;
    return 0;
}

static int pyPythonParameter_setString(pyPythonParameter* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "strValue should be a string");
        return -1;
    }
    self->fThis->fStrValue = PyStr_To_PlStr(value);
    return 0;
}

static int pyPythonParameter_setInt(pyPythonParameter* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "intValue should be an int");
        return -1;
    }
    self->fThis->fIntValue = PyInt_AsLong(value);
    return 0;
}

static int pyPythonParameter_setFloat(pyPythonParameter* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "floatValue should be a float");
        return -1;
    }
    self->fThis->fFloatValue = PyFloat_AsDouble(value);
    return 0;
}

static int pyPythonParameter_setBool(pyPythonParameter* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "boolValue should be a bool");
        return -1;
    }
    self->fThis->fBoolValue = (PyInt_AsLong(value) == 0) ? false : true;
    return 0;
}

static PyMethodDef pyPythonParameter_Methods[] = {
    { "read", (PyCFunction)pyPythonParameter_read, METH_VARARGS,
      "Params: stream, mgr\n"
      "Reads this object from `stream`" },
    { "write", (PyCFunction)pyPythonParameter_write, METH_VARARGS,
      "Params: stream, mgr\n"
      "Writes this object to `stream`" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyPythonParameter_GetSet[] = {
    { "id", (getter)pyPythonParameter_getID, (setter)pyPythonParameter_setID, NULL, NULL },
    { "valueType", (getter)pyPythonParameter_getType, (setter)pyPythonParameter_setType, NULL, NULL },
    { "objKey", (getter)pyPythonParameter_getKey, (setter)pyPythonParameter_setKey, NULL, NULL },
    { "strValue", (getter)pyPythonParameter_getString, (setter)pyPythonParameter_setString, NULL, NULL },
    { "intValue", (getter)pyPythonParameter_getInt, (setter)pyPythonParameter_setInt, NULL, NULL },
    { "floatValue", (getter)pyPythonParameter_getFloat, (setter)pyPythonParameter_setFloat, NULL, NULL },
    { "boolValue", (getter)pyPythonParameter_getBool, (setter)pyPythonParameter_setBool, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyPythonParameter_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plPythonParameter",       /* tp_name */
    sizeof(pyPythonParameter),          /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyPythonParameter_dealloc,  /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plPythonParameter wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyPythonParameter_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    pyPythonParameter_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyPythonParameter___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyPythonParameter_new,              /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyPythonParameter_Type() {
    if (PyType_Ready(&pyPythonParameter_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kInt",
                         PyInt_FromLong(plPythonParameter::kInt));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kFloat",
                         PyInt_FromLong(plPythonParameter::kFloat));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kBoolean",
                         PyInt_FromLong(plPythonParameter::kBoolean));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kString",
                         PyInt_FromLong(plPythonParameter::kString));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kSceneObject",
                         PyInt_FromLong(plPythonParameter::kSceneObject));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kSceneObjectList",
                         PyInt_FromLong(plPythonParameter::kSceneObjectList));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kActivator",
                         PyInt_FromLong(plPythonParameter::kActivator));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kResponder",
                         PyInt_FromLong(plPythonParameter::kResponder));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kDynamicText",
                         PyInt_FromLong(plPythonParameter::kDynamicText));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kGUIDialog",
                         PyInt_FromLong(plPythonParameter::kGUIDialog));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kExcludeRegion",
                         PyInt_FromLong(plPythonParameter::kExcludeRegion));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kAnimation",
                         PyInt_FromLong(plPythonParameter::kAnimation));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kAnimationName",
                         PyInt_FromLong(plPythonParameter::kAnimationName));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kBehavior",
                         PyInt_FromLong(plPythonParameter::kBehavior));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kMaterial",
                         PyInt_FromLong(plPythonParameter::kMaterial));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kGUIPopUpMenu",
                         PyInt_FromLong(plPythonParameter::kGUIPopUpMenu));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kGUISkin",
                         PyInt_FromLong(plPythonParameter::kGUISkin));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kWaterComponent",
                         PyInt_FromLong(plPythonParameter::kWaterComponent));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kSwimCurrentInterface",
                         PyInt_FromLong(plPythonParameter::kSwimCurrentInterface));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kClusterComponent",
                         PyInt_FromLong(plPythonParameter::kClusterComponent));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kMaterialAnimation",
                         PyInt_FromLong(plPythonParameter::kMaterialAnimation));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kGrassShaderComponent",
                         PyInt_FromLong(plPythonParameter::kGrassShaderComponent));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kGlobalSDLVar",
                         PyInt_FromLong(plPythonParameter::kGlobalSDLVar));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kSubtitle",
                         PyInt_FromLong(plPythonParameter::kSubtitle));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kBlowerComponent",
                         PyInt_FromLong(plPythonParameter::kBlowerComponent));
    PyDict_SetItemString(pyPythonParameter_Type.tp_dict, "kNone",
                         PyInt_FromLong(plPythonParameter::kNone));

    Py_INCREF(&pyPythonParameter_Type);
    return (PyObject*)&pyPythonParameter_Type;
}

int pyPythonParameter_Check(PyObject* obj) {
    if (obj->ob_type == &pyPythonParameter_Type
        || PyType_IsSubtype(obj->ob_type, &pyPythonParameter_Type))
        return 1;
    return 0;
}

PyObject* pyPythonParameter_FromPythonParameter(const plPythonParameter& sc) {
    pyPythonParameter* psc = PyObject_New(pyPythonParameter, &pyPythonParameter_Type);
    psc->fThis = new plPythonParameter(sc);
    return (PyObject*)psc;
}

}
