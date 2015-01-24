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
#include <PRP/Surface/plCubicEnvironmap.h>
#include "pyCubicEnvironmap.h"
#include "pyBitmap.h"

extern "C" {

static PyObject* pyCubicEnvironmap_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCubicEnvironmap* self = (pyCubicEnvironmap*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCubicEnvironmap();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCubicEnvironmap_getLeftFace(pyCubicEnvironmap* self, void*) {
    return pyMipmap_FromMipmap(self->fThis->getFace(plCubicEnvironmap::Faces::kLeftFace));
}

static PyObject* pyCubicEnvironmap_getRightFace(pyCubicEnvironmap* self, void*) {
    return pyMipmap_FromMipmap(self->fThis->getFace(plCubicEnvironmap::Faces::kRightFace));
}

static PyObject* pyCubicEnvironmap_getFrontFace(pyCubicEnvironmap* self, void*) {
    return pyMipmap_FromMipmap(self->fThis->getFace(plCubicEnvironmap::Faces::kFrontFace));
}

static PyObject* pyCubicEnvironmap_getBackFace(pyCubicEnvironmap* self, void*) {
    return pyMipmap_FromMipmap(self->fThis->getFace(plCubicEnvironmap::Faces::kBackFace));
}

static PyObject* pyCubicEnvironmap_getTopFace(pyCubicEnvironmap* self, void*) {
    return pyMipmap_FromMipmap(self->fThis->getFace(plCubicEnvironmap::Faces::kTopFace));
}

static PyObject* pyCubicEnvironmap_getBottomFace(pyCubicEnvironmap* self, void*) {
    return pyMipmap_FromMipmap(self->fThis->getFace(plCubicEnvironmap::Faces::kBottomFace));
}

static int pyCubicEnvironmap_setLeftFace(pyCubicEnvironmap* self, PyObject* value, void*) {
    if (value == NULL || !pyMipmap_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "leftFace should be a plMipmap");
        return -1;
    }
    self->fThis->setFace(plCubicEnvironmap::Faces::kLeftFace, reinterpret_cast<pyMipmap *>(value)->fThis);
    return 0;
}

static int pyCubicEnvironmap_setRightFace(pyCubicEnvironmap* self, PyObject* value, void*) {
    if (value == NULL || !pyMipmap_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "rightFace should be a plMipmap");
        return -1;
    }
    self->fThis->setFace(plCubicEnvironmap::Faces::kRightFace, reinterpret_cast<pyMipmap *>(value)->fThis);
    return 0;
}

static int pyCubicEnvironmap_setFrontFace(pyCubicEnvironmap* self, PyObject* value, void*) {
    if (value == NULL || !pyMipmap_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "frontFace should be a plMipmap");
        return -1;
    }
    self->fThis->setFace(plCubicEnvironmap::Faces::kFrontFace, reinterpret_cast<pyMipmap *>(value)->fThis);
    return 0;
}

static int pyCubicEnvironmap_setBackFace(pyCubicEnvironmap* self, PyObject* value, void*) {
    if (value == NULL || !pyMipmap_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "backFace should be a plMipmap");
        return -1;
    }
    self->fThis->setFace(plCubicEnvironmap::Faces::kBackFace, reinterpret_cast<pyMipmap *>(value)->fThis);
    return 0;
}

static int pyCubicEnvironmap_setTopFace(pyCubicEnvironmap* self, PyObject* value, void*) {
    if (value == NULL || !pyMipmap_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "topFace should be a plMipmap");
        return -1;
    }
    self->fThis->setFace(plCubicEnvironmap::Faces::kTopFace, reinterpret_cast<pyMipmap *>(value)->fThis);
    return 0;
}

static int pyCubicEnvironmap_setBottomFace(pyCubicEnvironmap* self, PyObject* value, void*) {
    if (value == NULL || !pyMipmap_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "bottomFace should be a plMipmap");
        return -1;
    }
    self->fThis->setFace(plCubicEnvironmap::Faces::kBottomFace, reinterpret_cast<pyMipmap *>(value)->fThis);
    return 0;
}

static PyGetSetDef pyCubicEnvironmap_GetSet[] = {
    { _pycs("leftFace"), (getter)pyCubicEnvironmap_getLeftFace, (setter)pyCubicEnvironmap_setLeftFace, NULL, NULL },
    { _pycs("rightFace"), (getter)pyCubicEnvironmap_getRightFace, (setter)pyCubicEnvironmap_setRightFace, NULL, NULL },
    { _pycs("frontFace"), (getter)pyCubicEnvironmap_getFrontFace, (setter)pyCubicEnvironmap_setFrontFace, NULL, NULL },
    { _pycs("backFace"), (getter)pyCubicEnvironmap_getBackFace, (setter)pyCubicEnvironmap_setBackFace, NULL, NULL },
    { _pycs("topFace"), (getter)pyCubicEnvironmap_getTopFace, (setter)pyCubicEnvironmap_setTopFace, NULL, NULL },
    { _pycs("bottomFace"), (getter)pyCubicEnvironmap_getBottomFace, (setter)pyCubicEnvironmap_setBottomFace, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCubicEnvironmap_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCubicEnvironmap",     /* tp_name */
    sizeof(pyCubicEnvironmap),          /* tp_basicsize */
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
    "plCubicEnvironmap wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyCubicEnvironmap_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyCubicEnvironmap_new,              /* tp_new */
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

PyObject* Init_pyCubicEnvironmap_Type() {
    pyCubicEnvironmap_Type.tp_base = &pyBitmap_Type;
    if (PyType_Ready(&pyCubicEnvironmap_Type) < 0)
        return NULL;

    Py_INCREF(&pyCubicEnvironmap_Type);
    return (PyObject*)&pyCubicEnvironmap_Type;
}

int pyCubicEnvironmap_Check(PyObject* obj) {
    if (obj->ob_type == &pyCubicEnvironmap_Type
        || PyType_IsSubtype(obj->ob_type, &pyCubicEnvironmap_Type))
        return 1;
    return 0;
}

PyObject* pyCubicEnvironmap_FromCubicEnvironmap(class plCubicEnvironmap* cem) {
    if (cem == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCubicEnvironmap* pycem = PyObject_New(pyCubicEnvironmap, &pyCubicEnvironmap_Type);
    pycem->fThis = cem;
    pycem->fPyOwned = false;
    return (PyObject*)pycem;
}

}
