#include <Python.h>
#include <PRP/Object/plSimulationInterface.h>
#include "pyObjInterface.h"
#include "../pyCreatable.h"
#include "../KeyedObject/pyKey.h"

extern "C" {

static PyObject* pySimulationInterface_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySimulationInterface* self = (pySimulationInterface*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSimulationInterface();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySimulationInterface_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pySimulationInterface_FromSimulationInterface(plSimulationInterface::Convert(cre->fThis));
}

static PyObject* pySimulationInterface_getPhysical(pySimulationInterface* self, void*) {
    return pyKey_FromKey(self->fThis->getPhysical());
}

static int pySimulationInterface_setPhysical(pySimulationInterface* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setPhysical(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setPhysical(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "physical should be a plKey");
        return -1;
    }
}

PyMethodDef pySimulationInterface_Methods[] = {
    { "Convert", (PyCFunction)pySimulationInterface_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plSimulationInterface" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pySimulationInterface_GetSet[] = {
    { "physical", (getter)pySimulationInterface_getPhysical, (setter)pySimulationInterface_setPhysical,
      "The Physical key", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySimulationInterface_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plSimulationInterface",   /* tp_name */
    sizeof(pySimulationInterface),      /* tp_basicsize */
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
    "plSimulationInterface wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySimulationInterface_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pySimulationInterface_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySimulationInterface_new,          /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pySimulationInterface_Type() {
    pySimulationInterface_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pySimulationInterface_Type) < 0)
        return NULL;

    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kWeightless",
                         PyInt_FromLong(plSimulationInterface::kWeightless));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kPinned",
                         PyInt_FromLong(plSimulationInterface::kPinned));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kWarp",
                         PyInt_FromLong(plSimulationInterface::kWarp));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kUpright",
                         PyInt_FromLong(plSimulationInterface::kUpright));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kPassive",
                         PyInt_FromLong(plSimulationInterface::kPassive));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kRotationForces",
                         PyInt_FromLong(plSimulationInterface::kRotationForces));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kCameraAvoidObject",
                         PyInt_FromLong(plSimulationInterface::kCameraAvoidObject));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kPhysAnim",
                         PyInt_FromLong(plSimulationInterface::kPhysAnim));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kStartInactive",
                         PyInt_FromLong(plSimulationInterface::kStartInactive));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kNoSynchronize",
                         PyInt_FromLong(plSimulationInterface::kNoSynchronize));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kSuppressed",
                         PyInt_FromLong(plSimulationInterface::kSuppressed));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kNoOwnershipChange",
                         PyInt_FromLong(plSimulationInterface::kNoOwnershipChange));
    PyDict_SetItemString(pySimulationInterface_Type.tp_dict, "kAvAnimPushable",
                         PyInt_FromLong(plSimulationInterface::kAvAnimPushable));

    Py_INCREF(&pySimulationInterface_Type);
    return (PyObject*)&pySimulationInterface_Type;
}

int pySimulationInterface_Check(PyObject* obj) {
    if (obj->ob_type == &pySimulationInterface_Type
        || PyType_IsSubtype(obj->ob_type, &pySimulationInterface_Type))
        return 1;
    return 0;
}

PyObject* pySimulationInterface_FromSimulationInterface(class plSimulationInterface* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySimulationInterface* intf = PyObject_New(pySimulationInterface, &pySimulationInterface_Type);
    intf->fThis = obj;
    intf->fPyOwned = false;
    return (PyObject*)intf;
}

}
