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

#include "pyAGChannel.h"

#include <PRP/Avatar/plScalarChannel.h>
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyScalarTimeScale_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyScalarTimeScale* self = (pyScalarTimeScale*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plScalarTimeScale();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyMethodDef pyScalarTimeScale_Methods[] = {
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyScalarTimeScale_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plScalarTimeScale",     /* tp_name */
    sizeof(pyScalarTimeScale),          /* tp_basicsize */
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
    "plScalarTimeScale wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyScalarTimeScale_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyScalarTimeScale_new,              /* tp_new */
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

PyObject* Init_pyScalarTimeScale_Type() {
    pyScalarTimeScale_Type.tp_base = &pyScalarChannel_Type;
    if (PyType_Ready(&pyScalarTimeScale_Type) < 0)
        return NULL;

    Py_INCREF(&pyScalarTimeScale_Type);
    return (PyObject*)&pyScalarTimeScale_Type;
}

int pyScalarTimeScale_Check(PyObject* obj) {
    if (obj->ob_type == &pyScalarTimeScale_Type
        || PyType_IsSubtype(obj->ob_type, &pyScalarTimeScale_Type))
        return 1;
    return 0;
}

PyObject* pyScalarTimeScale_FromScalarTimeScale(class plScalarTimeScale* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyScalarTimeScale* pyobj = PyObject_New(pyScalarTimeScale, &pyScalarTimeScale_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
