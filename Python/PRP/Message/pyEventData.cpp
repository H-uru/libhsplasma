#include <Python.h>
#include <PRP/Message/proEventData.h>
#include "pyEventData.h"
#include "../../Stream/pyStream.h"
#include "../../ResManager/pyResManager.h"

extern "C" {

static void pyEventData_dealloc(pyEventData* self) {
    if (self->fPyOwned)
        delete self->fThis;
    self->ob_type->tp_free((PyObject*)self);
}

static int pyEventData___init__(pyEventData* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "proEventData is abstract");
    return NULL;
}

static PyObject* pyEventData_EventType(pyEventData* self) {
    return PyInt_FromLong(self->fThis->EventType());
}

static PyObject* pyEventData_Read(PyObject*, PyObject* args) {
    pyStream* stream;
    pyResManager* mgr;
    if (!PyArg_ParseTuple(args, "OO", &stream, &mgr)) {
        PyErr_SetString(PyExc_TypeError, "Read expects hsStream, plResManager");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyResManager_Check((PyObject*)mgr)) {
        PyErr_SetString(PyExc_TypeError, "Read expects hsStream, plResManager");
        return NULL;
    }
    proEventData* evt = proEventData::Read(stream->fThis, mgr->fThis);
    PyObject* pyEvt = pyEventData_FromEventData(evt);
    ((pyEventData*)pyEvt)->fPyOwned = true;
    return pyEvt;
}

static PyObject* pyEventData_write(pyEventData* self, PyObject* args) {
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

static PyMethodDef pyEventData_Methods[] = {
    { "EventType", (PyCFunction)pyEventData_EventType, METH_NOARGS,
      "Returns the EventData Class Type of this proEventData object" },
    { "Read", (PyCFunction)pyEventData_Read, METH_VARARGS | METH_STATIC,
      "Params: stream, resManager\n"
      "Read a proEventData object from `stream`" },
    { "write", (PyCFunction)pyEventData_write, METH_VARARGS,
      "Params: stream, resManager\n"
      "Write this proEventData object to `stream`" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyEventData_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.proEventData",            /* tp_name */
    sizeof(pyEventData),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyEventData_dealloc,    /* tp_dealloc */
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
    "proEventData wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyEventData_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyEventData___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pyEventData_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyEventData_Type() {
    if (PyType_Ready(&pyEventData_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyEventData_Type.tp_dict, "kCollision",
                         PyInt_FromLong(proEventData::kCollision));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kPicked",
                         PyInt_FromLong(proEventData::kPicked));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kControlKey",
                         PyInt_FromLong(proEventData::kControlKey));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kVariable",
                         PyInt_FromLong(proEventData::kVariable));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kFacing",
                         PyInt_FromLong(proEventData::kFacing));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kContained",
                         PyInt_FromLong(proEventData::kContained));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kActivate",
                         PyInt_FromLong(proEventData::kActivate));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kCallback",
                         PyInt_FromLong(proEventData::kCallback));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kResponderState",
                         PyInt_FromLong(proEventData::kResponderState));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kMultiStage",
                         PyInt_FromLong(proEventData::kMultiStage));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kSpawned",
                         PyInt_FromLong(proEventData::kSpawned));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kClickDrag",
                         PyInt_FromLong(proEventData::kClickDrag));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kCoop",
                         PyInt_FromLong(proEventData::kCoop));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kOfferLinkBook",
                         PyInt_FromLong(proEventData::kOfferLinkBook));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kBook",
                         PyInt_FromLong(proEventData::kBook));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kClimbingBlockerHit",
                         PyInt_FromLong(proEventData::kClimbingBlockerHit));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kNone",
                         PyInt_FromLong(proEventData::kNone));

    PyDict_SetItemString(pyEventData_Type.tp_dict, "kNumber",
                         PyInt_FromLong(proEventData::kNumber));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kKey",
                         PyInt_FromLong(proEventData::kKey));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kNotta",
                         PyInt_FromLong(proEventData::kNotta));

    PyDict_SetItemString(pyEventData_Type.tp_dict, "kEnterStage",
                         PyInt_FromLong(proEventData::kEnterStage));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kBeginningOfLoop",
                         PyInt_FromLong(proEventData::kBeginningOfLoop));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kAdvanceNextStage",
                         PyInt_FromLong(proEventData::kAdvanceNextStage));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kRegressPrevStage",
                         PyInt_FromLong(proEventData::kRegressPrevStage));
    PyDict_SetItemString(pyEventData_Type.tp_dict, "kNothing",
                         PyInt_FromLong(proEventData::kNothing));

    Py_INCREF(&pyEventData_Type);
    return (PyObject*)&pyEventData_Type;
}

int pyEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyEventData_Type))
        return 1;
    return 0;
}

PyObject* pyEventData_FromEventData(class proEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyEventData* pyobj = PyObject_New(pyEventData, &pyEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)evt;
}

}
