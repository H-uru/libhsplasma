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

#include "pyRenderTarget.h"

#include <PRP/Surface/plRenderTarget.h>
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyCubicRenderTarget_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCubicRenderTarget* self = (pyCubicRenderTarget*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCubicRenderTarget();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCubicRenderTarget_getLeftFace(pyCubicRenderTarget* self, void*) {
    return pyRenderTarget_FromRenderTarget(self->fThis->getFace(plCubicRenderTarget::kLeftFace));
}

static PyObject* pyCubicRenderTarget_getRightFace(pyCubicRenderTarget* self, void*) {
    return pyRenderTarget_FromRenderTarget(self->fThis->getFace(plCubicRenderTarget::kRightFace));
}

static PyObject* pyCubicRenderTarget_getFrontFace(pyCubicRenderTarget* self, void*) {
    return pyRenderTarget_FromRenderTarget(self->fThis->getFace(plCubicRenderTarget::kFrontFace));
}

static PyObject* pyCubicRenderTarget_getBackFace(pyCubicRenderTarget* self, void*) {
    return pyRenderTarget_FromRenderTarget(self->fThis->getFace(plCubicRenderTarget::kBackFace));
}

static PyObject* pyCubicRenderTarget_getTopFace(pyCubicRenderTarget* self, void*) {
    return pyRenderTarget_FromRenderTarget(self->fThis->getFace(plCubicRenderTarget::kTopFace));
}

static PyObject* pyCubicRenderTarget_getBottomFace(pyCubicRenderTarget* self, void*) {
    return pyRenderTarget_FromRenderTarget(self->fThis->getFace(plCubicRenderTarget::kBottomFace));
}

static PyObject* pyCubicRenderTarget_getFaces(pyCubicRenderTarget* self, void*) {
    PyObject* facesTuple = PyTuple_New(plCubicRenderTarget::kNumFaces);
    for (size_t i = 0; i < plCubicRenderTarget::kNumFaces; ++i) {
        plRenderTarget* rt = self->fThis->getFace(i);
        PyTuple_SET_ITEM(facesTuple, i, ICreate(rt));
    }
    return facesTuple;
}

static PyGetSetDef pyCubicRenderTarget_GetSet[] = {
    { _pycs("leftFace"), (getter)pyCubicRenderTarget_getLeftFace, NULL, NULL, NULL },
    { _pycs("rightFace"), (getter)pyCubicRenderTarget_getRightFace, NULL, NULL, NULL },
    { _pycs("frontFace"), (getter)pyCubicRenderTarget_getFrontFace, NULL, NULL, NULL },
    { _pycs("backFace"), (getter)pyCubicRenderTarget_getBackFace, NULL, NULL, NULL },
    { _pycs("topFace"), (getter)pyCubicRenderTarget_getTopFace, NULL, NULL, NULL },
    { _pycs("bottomFace"), (getter)pyCubicRenderTarget_getBottomFace, NULL, NULL, NULL },
    { _pycs("faces"), (getter)pyCubicRenderTarget_getFaces, NULL, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCubicRenderTarget_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCubicRenderTarget",   /* tp_name */
    sizeof(pyCubicRenderTarget),        /* tp_basicsize */
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
    "plCubicRenderTarget wrapper",      /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyCubicRenderTarget_GetSet,         /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyCubicRenderTarget_new,            /* tp_new */
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

PyObject* Init_pyCubicRenderTarget_Type() {
    pyCubicRenderTarget_Type.tp_base = &pyRenderTarget_Type;
    if (PyType_Ready(&pyCubicRenderTarget_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyCubicRenderTarget_Type.tp_dict, "kLeftFace",
                         PyInt_FromLong(plCubicRenderTarget::kLeftFace));
    PyDict_SetItemString(pyCubicRenderTarget_Type.tp_dict, "kRightFace",
                         PyInt_FromLong(plCubicRenderTarget::kRightFace));
    PyDict_SetItemString(pyCubicRenderTarget_Type.tp_dict, "kFrontFace",
                         PyInt_FromLong(plCubicRenderTarget::kFrontFace));
    PyDict_SetItemString(pyCubicRenderTarget_Type.tp_dict, "kBackFace",
                         PyInt_FromLong(plCubicRenderTarget::kBackFace));
    PyDict_SetItemString(pyCubicRenderTarget_Type.tp_dict, "kTopFace",
                         PyInt_FromLong(plCubicRenderTarget::kTopFace));
    PyDict_SetItemString(pyCubicRenderTarget_Type.tp_dict, "kBottomFace",
                         PyInt_FromLong(plCubicRenderTarget::kBottomFace));

    Py_INCREF(&pyCubicRenderTarget_Type);
    return (PyObject*)&pyCubicRenderTarget_Type;
}

PY_PLASMA_IFC_METHODS(CubicRenderTarget, plCubicRenderTarget)

}
