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

#include "pyDetectorModifier.h"

#include <PRP/Physics/plDetectorModifier.h>
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Modifier/pyModifier.h"

extern "C" {

PY_PLASMA_NEW_MSG(DetectorModifier, "plDetectorModifier is abstract")

PY_METHOD_VA(DetectorModifier, addReceiver,
    "Params: key\n"
    "Adds a notification receiver to this detector")
{
    PyObject* receiver;
    if (!(PyArg_ParseTuple(args, "O", &receiver) && pyKey_Check(receiver))) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }

    self->fThis->addReceiver(*((pyKey*)receiver)->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DetectorModifier, clearReceivers,
    "Removes all receivers from this detector")
{
    self->fThis->clearReceivers();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DetectorModifier, delReceiver,
    "Params: idx\n"
    "Removes a receiver from this detector")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delReceiver expects an int");
        return NULL;
    }

    self->fThis->delReceiver((size_t)idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyDetectorModifier_Methods[] = {
    pyDetectorModifier_addReceiver_method,
    pyDetectorModifier_clearReceivers_method,
    pyDetectorModifier_delReceiver_method,
    PY_METHOD_TERMINATOR
};

static PyObject* pyDetectorModifier_getReceivers(pyDetectorModifier* self, void*) {
    plDetectorModifier* mod = self->fThis;
    PyObject* sequence = PyTuple_New(mod->getReceivers().size());
    for (size_t i = 0; i < mod->getReceivers().size(); ++i)
        PyTuple_SET_ITEM(sequence, i, pyKey_FromKey(mod->getReceivers()[i]));
    return sequence;
}

static int pyDetectorModifier_setReceivers(pyDetectorModifier* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add receivers, use addReceiver");
    return -1;
}

PY_PROPERTY(plKey, DetectorModifier, remoteMod, getRemoteMod, setRemoteMod)
PY_PROPERTY(plKey, DetectorModifier, proxy, getProxy, setProxy)

static PyGetSetDef pyDetectorModifier_GetSet[] = {
    { _pycs("receivers"), (getter)pyDetectorModifier_getReceivers,
        (setter)pyDetectorModifier_setReceivers, NULL, NULL },
    pyDetectorModifier_remoteMod_getset,
    pyDetectorModifier_proxy_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyDetectorModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDetectorModifier",    /* tp_name */
    sizeof(pyDetectorModifier),         /* tp_basicsize */
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
    "plDetectorModifier wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyDetectorModifier_Methods,         /* tp_methods */
    NULL,                               /* tp_members */
    pyDetectorModifier_GetSet,          /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDetectorModifier_new,             /* tp_new */
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

PyObject* Init_pyDetectorModifier_Type() {
    pyDetectorModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyDetectorModifier_Type) < 0)
        return NULL;

    Py_INCREF(&pyDetectorModifier_Type);
    return (PyObject*)&pyDetectorModifier_Type;
}

PY_PLASMA_IFC_METHODS(DetectorModifier, plDetectorModifier)

};
