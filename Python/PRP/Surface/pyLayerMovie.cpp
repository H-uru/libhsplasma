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
#include <PRP/Surface/plLayerMovie.h>
#include "pyLayerMovie.h"
#include "pyLayerAnimation.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyLayerMovie_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyLayerMovie* self = (pyLayerMovie*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plLayerMovie();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyLayerMovie_getMovieName(pyLayerMovie* self, void*) {
    return PlStr_To_PyStr(self->fThis->getMovieName());
}

static int pyLayerMovie_setMovieName(pyLayerMovie* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "movieName should be a string");
        return -1;
    }
    self->fThis->setMovieName(PyStr_To_PlStr(value));
    return 0;
}

static PyMethodDef pyLayerMovie_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLayerMovie_GetSet[] = {
    { "movieName", (getter)pyLayerMovie_getMovieName, (setter)pyLayerMovie_setMovieName, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLayerMovie_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plLayerMovie",            /* tp_name */
    sizeof(pyLayerMovie),               /* tp_basicsize */
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
    "plLayerMovie wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLayerMovie_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    pyLayerMovie_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLayerMovie_new,                   /* tp_new */
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

PyObject* Init_pyLayerMovie_Type() {
    pyLayerMovie_Type.tp_base = &pyLayerAnimation_Type;
    if (PyType_Ready(&pyLayerMovie_Type) < 0)
        return NULL;

    Py_INCREF(&pyLayerMovie_Type);
    return (PyObject*)&pyLayerMovie_Type;
}

int pyLayerMovie_Check(PyObject* obj) {
    if (obj->ob_type == &pyLayerMovie_Type
        || PyType_IsSubtype(obj->ob_type, &pyLayerMovie_Type))
        return 1;
    return 0;
}

PyObject* pyLayerMovie_FromLayerMovie(class plLayerMovie* layer) {
    if (layer == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLayerMovie* pyobj = PyObject_New(pyLayerMovie, &pyLayerMovie_Type);
    pyobj->fThis = layer;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
