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

#include "pyObjInterface.h"

#include <PRP/Object/plObjInterface.h>
#include "pySynchedObject.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "Util/pyBitVector.h"

extern "C" {

PY_PLASMA_NEW_MSG(ObjInterface, "plObjInterface is abstract")

static PyObject* pyObjInterface_getProp(pyObjInterface* self, PyObject* args) {
    int prop;
    if (!PyArg_ParseTuple(args, "i", &prop)) {
        PyErr_SetString(PyExc_TypeError, "getProperty expects an int");
        return NULL;
    }
    return PyBool_FromLong(self->fThis->getProperty(prop) ? 1 : 0);
}

static PyObject* pyObjInterface_setProp(pyObjInterface* self, PyObject* args) {
    int prop, value;
    if (!PyArg_ParseTuple(args, "ii", &prop, &value)) {
        PyErr_SetString(PyExc_TypeError, "setProperty expects int, bool");
        return NULL;
    }
    self->fThis->setProperty(prop, value != 0);
    Py_INCREF(Py_None);
    return Py_None;
}

PyMethodDef pyObjInterface_Methods[] = {
    { "getProperty", (PyCFunction)pyObjInterface_getProp, METH_VARARGS,
      "Params: flag\n"
      "Returns whether the specified property is set" },
    { "setProperty", (PyCFunction)pyObjInterface_setProp, METH_VARARGS,
      "Params: flag, value\n"
      "Sets the specified property" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(plKey, ObjInterface, owner, getOwner, setOwner)

PyGetSetDef pyObjInterface_GetSet[] = {
    pyObjInterface_owner_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyObjInterface_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plObjInterface",        /* tp_name */
    sizeof(pyObjInterface),             /* tp_basicsize */
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
    "plObjInterface wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyObjInterface_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyObjInterface_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyObjInterface_new,                 /* tp_new */
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

PyObject* Init_pyObjInterface_Type() {
    pyObjInterface_Type.tp_base = &pySynchedObject_Type;
    if (PyType_Ready(&pyObjInterface_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyObjInterface_Type.tp_dict, "kDisable",
                         PyInt_FromLong(plObjInterface::kDisable));

    Py_INCREF(&pyObjInterface_Type);
    return (PyObject*)&pyObjInterface_Type;
}

PY_PLASMA_IFC_METHODS(ObjInterface, plObjInterface)

}
