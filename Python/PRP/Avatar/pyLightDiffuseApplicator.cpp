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
#include <PRP/Avatar/plAGApplicator.h>
#include "pyAGApplicator.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyLightDiffuseApplicator_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyLightDiffuseApplicator* self = (pyLightDiffuseApplicator*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plLightDiffuseApplicator();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyMethodDef pyLightDiffuseApplicator_Methods[] = {
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyLightDiffuseApplicator_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plLightDiffuseApplicator", /* tp_name */
    sizeof(pyLightDiffuseApplicator),   /* tp_basicsize */
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
    "plLightDiffuseApplicator wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLightDiffuseApplicator_Methods,   /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLightDiffuseApplicator_new,       /* tp_new */
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

PyObject* Init_pyLightDiffuseApplicator_Type() {
    pyLightDiffuseApplicator_Type.tp_base = &pyAGApplicator_Type;
    if (PyType_Ready(&pyLightDiffuseApplicator_Type) < 0)
        return NULL;

    Py_INCREF(&pyLightDiffuseApplicator_Type);
    return (PyObject*)&pyLightDiffuseApplicator_Type;
}

int pyLightDiffuseApplicator_Check(PyObject* obj) {
    if (obj->ob_type == &pyLightDiffuseApplicator_Type
        || PyType_IsSubtype(obj->ob_type, &pyLightDiffuseApplicator_Type))
        return 1;
    return 0;
}

PyObject* pyLightDiffuseApplicator_FromLightDiffuseApplicator(class plLightDiffuseApplicator* app) {
    if (app == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLightDiffuseApplicator* pyobj = PyObject_New(pyLightDiffuseApplicator, &pyLightDiffuseApplicator_Type);
    delete pyobj->fThis;
    pyobj->fThis = app;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
