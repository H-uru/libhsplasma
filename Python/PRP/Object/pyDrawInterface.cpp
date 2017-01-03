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

#include <PRP/Object/plDrawInterface.h>
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_NEW(DrawInterface, plDrawInterface)

PY_METHOD_NOARGS(DrawInterface, clearDrawables,
    "Removes all drawables from the Draw Interface")
{
    self->fThis->clearDrawables();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawInterface, addDrawable,
    "Params: (key, idx,)\n"
    "Adds a drawable reference and key index to the Draw Interface")
{
    pyKey* draw;
    int key;
    if (!PyArg_ParseTuple(args, "Oi", &draw, &key)) {
        PyErr_SetString(PyExc_TypeError, "addDrawable expects plKey, int");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)draw)) {
        PyErr_SetString(PyExc_TypeError, "addDrawable expects plKey, int");
        return NULL;
    }
    self->fThis->addDrawable(*draw->fThis, key);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawInterface, delDrawable,
    "Params: idx\n"
    "Removes a drawable reference and key from the Draw Interface")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delDrawable expects an int");
        return NULL;
    }
    self->fThis->delDrawable(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DrawInterface, clearRegions,
    "Removes all regions from the Draw Interface")
{
    self->fThis->clearRegions();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawInterface, addRegion,
    "Params: key\n"
    "Adds a region to the Draw Interface")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addRegion expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addRegion expects a plKey");
        return NULL;
    }
    self->fThis->addRegion(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawInterface, delRegion,
    "Params: idx\n"
    "Removes a region from the Draw Interface")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delRegion expects an int");
        return NULL;
    }
    self->fThis->delRegion(idx);
    Py_RETURN_NONE;
}

static PyObject* pyDrawInterface_getDrawables(pyDrawInterface* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumDrawables());
    for (size_t i=0; i<self->fThis->getNumDrawables(); i++) {
        PyObject* tup = Py_BuildValue("(Oi)",
            pyKey_FromKey(self->fThis->getDrawable(i)),
            self->fThis->getDrawableKey(i));
        if (tup == NULL)
            return NULL;
        PyList_SET_ITEM(list, i, tup);
    }
    return list;
}

static PyObject* pyDrawInterface_getRegions(pyDrawInterface* self, void*) {
    PyObject* list = PyList_New(self->fThis->getRegions().size());
    for (size_t i=0; i<self->fThis->getRegions().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getRegions()[i]));
    return list;
}

static int pyDrawInterface_setDrawables(pyDrawInterface* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Drawables, use addDrawable");
    return -1;
}

static int pyDrawInterface_setRegions(pyDrawInterface* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Regions, use addRegion");
    return -1;
}

PyMethodDef pyDrawInterface_Methods[] = {
    pyDrawInterface_clearDrawables_method,
    pyDrawInterface_addDrawable_method,
    pyDrawInterface_delDrawable_method,
    pyDrawInterface_clearRegions_method,
    pyDrawInterface_addRegion_method,
    pyDrawInterface_delRegion_method,
    PY_METHOD_TERMINATOR
};

PyGetSetDef pyDrawInterface_GetSet[] = {
    { _pycs("drawables"), (getter)pyDrawInterface_getDrawables,
        (setter)pyDrawInterface_setDrawables,
        _pycs("Drawable references and keys"), NULL },
    { _pycs("regions"), (getter)pyDrawInterface_getRegions,
        (setter)pyDrawInterface_setRegions, _pycs("Drawable regions"), NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyDrawInterface_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDrawInterface",       /* tp_name */
    sizeof(pyDrawInterface),            /* tp_basicsize */
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
    "plDrawInterface wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyDrawInterface_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyDrawInterface_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDrawInterface_new,                /* tp_new */
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

PyObject* Init_pyDrawInterface_Type() {
    pyDrawInterface_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyDrawInterface_Type) < 0)
        return NULL;

    Py_INCREF(&pyDrawInterface_Type);
    return (PyObject*)&pyDrawInterface_Type;
}

PY_PLASMA_IFC_METHODS(DrawInterface, plDrawInterface)

}
