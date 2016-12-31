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

#include "pyATCAnim.h"

#include <PRP/Avatar/plATCAnim.h>
#include "pyAGAnim.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(ATCAnim, plATCAnim)

static PyObject* pyATCAnim_clearMarkers(pyATCAnim* self) {
    self->fThis->getMarkers().clear();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyATCAnim_clearLoops(pyATCAnim* self) {
    self->fThis->getLoops().clear();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyATCAnim_setMarker(pyATCAnim* self, PyObject* args) {
    const char* key;
    float pos;
    if (!PyArg_ParseTuple(args, "sf", &key, &pos)) {
        PyErr_SetString(PyExc_TypeError, "setMarker expects string, float");
        return NULL;
    }
    self->fThis->setMarker(key, pos);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyATCAnim_setLoop(pyATCAnim* self, PyObject* args) {
    const char* key;
    float begin, end;
    if (!PyArg_ParseTuple(args, "sff", &key, &begin, &end)) {
        PyErr_SetString(PyExc_TypeError, "setLoop expects string, float, float");
        return NULL;
    }
    self->fThis->setLoop(key, begin, end);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyATCAnim_getMarkers(pyATCAnim* self, void*) {
    plATCAnim* anim = self->fThis;
    PyObject* dict = PyDict_New();
    for (plATCAnim::marker_t::iterator it = anim->getMarkers().begin();
         it != anim->getMarkers().end(); it++) {
        PyDict_SetItemString(dict, it->first, PyFloat_FromDouble(it->second));
    }
    return dict;
}

static PyObject* pyATCAnim_getLoops(pyATCAnim* self, void*) {
    plATCAnim* anim = self->fThis;
    PyObject* dict = PyDict_New();
    for (plATCAnim::loop_t::iterator it = anim->getLoops().begin();
         it != anim->getLoops().end(); it++) {
        PyDict_SetItemString(dict, it->first,
                  Py_BuildValue("ff", it->second.first, it->second.second));
    }
    return dict;
}

static PyObject* pyATCAnim_getStops(pyATCAnim* self, void*) {
    plATCAnim* anim = self->fThis;
    PyObject* list = PyList_New(anim->getStops().size());
    for (size_t i = 0; i < anim->getStops().size(); i++)
        PyList_SET_ITEM(list, i, PyFloat_FromDouble(anim->getStops()[i]));
    return list;
}

static int pyATCAnim_setMarkers(pyATCAnim* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add markers, use setMarker()");
    return -1;
}

static int pyATCAnim_setLoops(pyATCAnim* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add loops, use setLoop()");
    return -1;
}

static int pyATCAnim_setStops(pyATCAnim* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setStops(std::vector<float>());
        return 0;
    } else if (PySequence_Check(value)) {
        std::vector<float> stops(PySequence_Size(value));
        for (size_t i=0; i<stops.size(); i++) {
            if (!PyFloat_Check(PySequence_GetItem(value, i))) {
                PyErr_SetString(PyExc_TypeError, "stops should be a sequence of floats");
                return -1;
            }
            stops[i] = PyFloat_AsDouble(PySequence_GetItem(value, i));
        }
        self->fThis->setStops(stops);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "stops should be a sequence of floats");
        return -1;
    }
}

static PyMethodDef pyATCAnim_Methods[] = {
    { "clearMarkers", (PyCFunction)pyATCAnim_clearMarkers, METH_NOARGS,
      "Remove all named markers from the anim" },
    { "clearLoops", (PyCFunction)pyATCAnim_clearLoops, METH_NOARGS,
      "Remove all named loops from the anim" },
    { "setMarker", (PyCFunction)pyATCAnim_setMarker, METH_VARARGS,
      "Params: key, position\n"
      "Add a named marker at the specified position" },
    { "setLoop", (PyCFunction)pyATCAnim_setLoop, METH_VARARGS,
      "Params: key, start, end\n"
      "Add a named loop to the specified range" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(float, ATCAnim, initial, getInitial, setInitial)
PY_PROPERTY(float, ATCAnim, loopStart, getLoopStart, setLoopStart)
PY_PROPERTY(float, ATCAnim, loopEnd, getLoopEnd, setLoopEnd)
PY_PROPERTY(bool, ATCAnim, autoStart, getAutoStart, setAutoStart)
PY_PROPERTY(bool, ATCAnim, loop, getDoLoop, setDoLoop)
PY_PROPERTY(unsigned char, ATCAnim, easeInType, getEaseInType, setEaseInType)
PY_PROPERTY(unsigned char, ATCAnim, easeOutType, getEaseOutType, setEaseOutType)
PY_PROPERTY(float, ATCAnim, easeInLength, getEaseInLength, setEaseInLength)
PY_PROPERTY(float, ATCAnim, easeInMin, getEaseInMin, setEaseInMin)
PY_PROPERTY(float, ATCAnim, easeInMax, getEaseInMax, setEaseInMax)
PY_PROPERTY(float, ATCAnim, easeOutLength, getEaseOutLength, setEaseOutLength)
PY_PROPERTY(float, ATCAnim, easeOutMin, getEaseOutMin, setEaseOutMin)
PY_PROPERTY(float, ATCAnim, easeOutMax, getEaseOutMax, setEaseOutMax)

static PyGetSetDef pyATCAnim_GetSet[] = {
    pyATCAnim_initial_getset,
    pyATCAnim_loopStart_getset,
    pyATCAnim_loopEnd_getset,
    pyATCAnim_autoStart_getset,
    pyATCAnim_loop_getset,
    pyATCAnim_easeInType_getset,
    pyATCAnim_easeOutType_getset,
    pyATCAnim_easeInLength_getset,
    pyATCAnim_easeInMin_getset,
    pyATCAnim_easeInMax_getset,
    pyATCAnim_easeOutLength_getset,
    pyATCAnim_easeOutMin_getset,
    pyATCAnim_easeOutMax_getset,
    { _pycs("markers"), (getter)pyATCAnim_getMarkers,
        (setter)pyATCAnim_setMarkers, NULL, NULL },
    { _pycs("loops"), (getter)pyATCAnim_getLoops,
        (setter)pyATCAnim_setLoops, NULL, NULL },
    { _pycs("stops"), (getter)pyATCAnim_getStops,
        (setter)pyATCAnim_setStops, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyATCAnim_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plATCAnim",             /* tp_name */
    sizeof(pyATCAnim),                  /* tp_basicsize */
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
    "plATCAnim wrapper",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyATCAnim_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    pyATCAnim_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyATCAnim_new,                      /* tp_new */
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

PyObject* Init_pyATCAnim_Type() {
    pyATCAnim_Type.tp_base = &pyAGAnim_Type;
    if (PyType_Ready(&pyATCAnim_Type) < 0)
        return NULL;

    Py_INCREF(&pyATCAnim_Type);
    return (PyObject*)&pyATCAnim_Type;
}

PY_PLASMA_IFC_METHODS(ATCAnim, plATCAnim)

}
