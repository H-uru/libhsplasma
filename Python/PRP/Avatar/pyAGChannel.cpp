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

#include <PRP/Avatar/plAGChannel.h>
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyAGChannel_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plAGApplicator is abstract");
    return NULL;
}

static PyObject* pyAGChannel_getName(pyAGChannel* self, void*) {
    return PlStr_To_PyStr(self->fThis->getName());
}

static int pyAGChannel_setName(pyAGChannel* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "name should be a string");
        return -1;
    }
    self->fThis->setName(PyStr_To_PlStr(value));
    return 0;
}

static PyGetSetDef pyAGChannel_GetSet[] = {
    { _pycs("name"), (getter)pyAGChannel_getName, (setter)pyAGChannel_setName, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAGChannel_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAGChannel",           /* tp_name */
    sizeof(pyAGChannel),                /* tp_basicsize */
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
    "plAGChannel wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyAGChannel_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAGChannel_new,                    /* tp_new */
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

PyObject* Init_pyAGChannel_Type() {
    pyAGChannel_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyAGChannel_Type) < 0)
        return NULL;

    Py_INCREF(&pyAGChannel_Type);
    return (PyObject*)&pyAGChannel_Type;
}

PY_PLASMA_IFC_METHODS(AGChannel, plAGChannel)

}
