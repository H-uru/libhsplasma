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

#include "pyLinkToAgeMsg.h"

#include <PRP/Message/plLinkToAgeMsg.h>
#include "pyMessage.h"
#include "PRP/pyCreatable.h"
#include "PRP/Misc/pyAgeLinkInfo.h"
#include <PRP/Modifier/pyPythonFileMod.h>

extern "C" {

static PyObject* pyLinkToAgeMsg_new(PyTypeObject* type, PyObject* , PyObject* ) {
    pyLinkToAgeMsg* self = (pyLinkToAgeMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plLinkToAgeMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PY_GETSET_GETTER_DECL(LinkToAgeMsg, ageLink) {
    // This cannot be a subclass, since it's an inline member
    return pyAgeLinkStruct_FromAgeLinkStruct(&self->fThis->getAgeLink());
}

PY_GETSET_SETTER_DECL(LinkToAgeMsg, ageLink) {
    plAgeLinkStruct& als = self->fThis->getAgeLink();
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "ageLink cannot be deleted");
        return -1;
    } else if (pyAgeLinkStruct_Check(value)) {
        als = *((pyAgeLinkStruct*)value)->fThis;
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "ageLink expected type plAgeLinkStruct");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(LinkToAgeMsg, ageLink)

static PyGetSetDef pyLinkToAgeMsg_GetSet[] = {
    pyLinkToAgeMsg_ageLink_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyLinkToAgeMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plLinkToAgeMsg",        /* tp_name */
    sizeof(pyLinkToAgeMsg),             /* tp_basicsize */
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
    "plLinkToAgeMsg wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyLinkToAgeMsg_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLinkToAgeMsg_new,                 /* tp_new */
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

PyObject* Init_pyLinkToAgeMsg_Type() {
    pyLinkToAgeMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_Ready(&pyLinkToAgeMsg_Type) < 0)
        return NULL;

    Py_INCREF(&pyLinkToAgeMsg_Type);
    return (PyObject*)&pyLinkToAgeMsg_Type;
}

PY_PLASMA_IFC_METHODS(LinkToAgeMsg, plLinkToAgeMsg)

}
