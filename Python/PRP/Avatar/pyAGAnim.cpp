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

#include "pyAGAnim.h"

#include <PRP/Avatar/plAGAnim.h>
#include "pyAGApplicator.h"
#include "PRP/pyCreatable.h"
#include "PRP/Object/pySynchedObject.h"

extern "C" {

PY_PLASMA_NEW(AGAnim, plAGAnim)

static PyObject* pyAGAnim_clearApps(pyAGAnim* self) {
    self->fThis->clearApplicators();
    Py_RETURN_NONE;
}

static PyObject* pyAGAnim_addApplicator(pyAGAnim* self, PyObject* args) {
    pyAGApplicator* app;
    if (!PyArg_ParseTuple(args, "O", &app)) {
        PyErr_SetString(PyExc_TypeError, "addApplicator expects a plAGApplicator");
        return NULL;
    }
    if (!pyAGApplicator_Check((PyObject*)app)) {
        PyErr_SetString(PyExc_TypeError, "addApplicator expects a plAGApplicator");
        return NULL;
    }
    self->fThis->addApplicator(app->fThis);
    app->fPyOwned = false;
    Py_RETURN_NONE;
}

static PyObject* pyAGAnim_delApplicator(pyAGAnim* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delApplicator expects an int");
        return NULL;
    }
    self->fThis->delApplicator(idx);
    Py_RETURN_NONE;
}

static PyObject* pyAGAnim_getApps(pyAGAnim* self, void*) {
    plAGAnim* anim = self->fThis;
    PyObject* list = PyList_New(anim->getApplicators().size());
    for (size_t i=0; i < anim->getApplicators().size(); i++)
        PyList_SET_ITEM(list, i, ICreate(anim->getApplicators()[i]));
    return list;
}

static int pyAGAnim_setApps(pyAGAnim* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add applicators, use addApplicator()");
    return -1;
}

static PyMethodDef pyAGAnim_Methods[] = {
    { "clearApplicators", (PyCFunction)pyAGAnim_clearApps, METH_NOARGS,
      "Remove all plAGApplicators from the anim" },
    { "addApplicator", (PyCFunction)pyAGAnim_addApplicator, METH_VARARGS,
      "Params: applicator\n"
      "Add a plAGApplicator to the anim" },
    { "delApplicator", (PyCFunction)pyAGAnim_delApplicator, METH_VARARGS,
      "Params: idx\n"
      "Delete a plAGApplicator from the anim" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(float, AGAnim, blend, getBlend, setBlend)
PY_PROPERTY(float, AGAnim, start, getStart, setStart)
PY_PROPERTY(float, AGAnim, end, getEnd, setEnd)
PY_PROPERTY(plString, AGAnim, name, getName, setName)

static PyGetSetDef pyAGAnim_GetSet[] = {
    pyAGAnim_blend_getset,
    pyAGAnim_start_getset,
    pyAGAnim_end_getset,
    pyAGAnim_name_getset,
    { _pycs("applicators"), (getter)pyAGAnim_getApps, (setter)pyAGAnim_setApps, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyAGAnim_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAGAnim",              /* tp_name */
    sizeof(pyAGAnim),                   /* tp_basicsize */
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
    "plAGAnim wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAGAnim_Methods,                   /* tp_methods */
    NULL,                               /* tp_members */
    pyAGAnim_GetSet,                    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAGAnim_new,                       /* tp_new */
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

PyObject* Init_pyAGAnim_Type() {
    pyAGAnim_Type.tp_base = &pySynchedObject_Type;
    if (PyType_Ready(&pyAGAnim_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyAGAnim_Type.tp_dict, "kBodyUnknown",
                         PyInt_FromLong(plAGAnim::kBodyUnknown));
    PyDict_SetItemString(pyAGAnim_Type.tp_dict, "kBodyUpper",
                         PyInt_FromLong(plAGAnim::kBodyUpper));
    PyDict_SetItemString(pyAGAnim_Type.tp_dict, "kBodyFull",
                         PyInt_FromLong(plAGAnim::kBodyFull));
    PyDict_SetItemString(pyAGAnim_Type.tp_dict, "kBodyLower",
                         PyInt_FromLong(plAGAnim::kBodyLower));
    PyDict_SetItemString(pyAGAnim_Type.tp_dict, "kBodyMax",
                         PyInt_FromLong(plAGAnim::kBodyMax));

    Py_INCREF(&pyAGAnim_Type);
    return (PyObject*)&pyAGAnim_Type;
}

PY_PLASMA_IFC_METHODS(AGAnim, plAGAnim)

}
