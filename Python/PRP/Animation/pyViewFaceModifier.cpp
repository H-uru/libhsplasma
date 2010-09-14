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
#include <PRP/Animation/plViewFaceModifier.h>
#include "pyViewFaceModifier.h"
#include "PRP/Modifier/pyModifier.h"
#include "PRP/Region/pyBounds.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"
#include "Math/pyGeometry3.h"
#include "Math/pyMatrix.h"

extern "C" {

static PyObject* pyViewFaceModifier_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyViewFaceModifier* self = (pyViewFaceModifier*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plViewFaceModifier();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyViewFaceModifier_getScale(pyViewFaceModifier* self, void*) {
    return pyVector3_FromVector3(self->fThis->getScale());
}

static PyObject* pyViewFaceModifier_getOffset(pyViewFaceModifier* self, void*) {
    return pyVector3_FromVector3(self->fThis->getOffset());
}

static PyObject* pyViewFaceModifier_getL2P(pyViewFaceModifier* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getLocalToParent());
}

static PyObject* pyViewFaceModifier_getP2L(pyViewFaceModifier* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getParentToLocal());
}

static PyObject* pyViewFaceModifier_getFaceObj(pyViewFaceModifier* self, void*) {
    return pyKey_FromKey(self->fThis->getFaceObj());
}

static PyObject* pyViewFaceModifier_getMaxBounds(pyViewFaceModifier* self, void*) {
    return pyBounds3Ext_FromBounds3Ext(self->fThis->getMaxBounds());
}

static int pyViewFaceModifier_setScale(pyViewFaceModifier* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "scale should be an hsVector3");
        return -1;
    }
    self->fThis->setScale(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyViewFaceModifier_setOffset(pyViewFaceModifier* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "offset should be an hsVector3");
        return -1;
    }
    self->fThis->setOffset(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyViewFaceModifier_setL2P(pyViewFaceModifier* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "localToParent should be an hsMatrix44");
        return -1;
    }
    self->fThis->setLocalToParent(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyViewFaceModifier_setP2L(pyViewFaceModifier* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "parentToLocal should be an hsMatrix44");
        return -1;
    }
    self->fThis->setParentToLocal(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyViewFaceModifier_setFaceObj(pyViewFaceModifier* self, PyObject* value, void*) {
    if (value == NULL || !pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "faceObj should be a plKey");
        return -1;
    }
    self->fThis->setFaceObj(*((pyKey*)value)->fThis);
    return 0;
}

static int pyViewFaceModifier_setMaxBounds(pyViewFaceModifier* self, PyObject* value, void*) {
    if (value == NULL || !pyBounds3Ext_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxBounds should be an hsBounds3Ext");
        return -1;
    }
    self->fThis->setMaxBounds(*((pyBounds3Ext*)value)->fThis);
    return 0;
}

static PyMethodDef pyViewFaceModifier_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyViewFaceModifier_GetSet[] = {
    { "scale", (getter)pyViewFaceModifier_getScale, (setter)pyViewFaceModifier_setScale, NULL, NULL },
    { "offset", (getter)pyViewFaceModifier_getOffset, (setter)pyViewFaceModifier_setOffset, NULL, NULL },
    { "localToParent", (getter)pyViewFaceModifier_getL2P, (setter)pyViewFaceModifier_setL2P, NULL, NULL },
    { "parentToLocal", (getter)pyViewFaceModifier_getP2L, (setter)pyViewFaceModifier_setP2L, NULL, NULL },
    { "faceObj", (getter)pyViewFaceModifier_getFaceObj, (setter)pyViewFaceModifier_setFaceObj, NULL, NULL },
    { "maxBounds", (getter)pyViewFaceModifier_getMaxBounds, (setter)pyViewFaceModifier_setMaxBounds, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyViewFaceModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plViewFaceModifier",      /* tp_name */
    sizeof(pyViewFaceModifier),         /* tp_basicsize */
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
    "plViewFaceModifier wrapper",       /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyViewFaceModifier_Methods,         /* tp_methods */
    NULL,                               /* tp_members */
    pyViewFaceModifier_GetSet,          /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyViewFaceModifier_new,             /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyViewFaceModifier_Type() {
    pyViewFaceModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyViewFaceModifier_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kPivotFace",
                         PyInt_FromLong(plViewFaceModifier::kPivotFace));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kPivotFavorY",
                         PyInt_FromLong(plViewFaceModifier::kPivotFavorY));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kPivotY",
                         PyInt_FromLong(plViewFaceModifier::kPivotY));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kPivotTumple",
                         PyInt_FromLong(plViewFaceModifier::kPivotTumple));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kScale",
                         PyInt_FromLong(plViewFaceModifier::kScale));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kFaceCam",
                         PyInt_FromLong(plViewFaceModifier::kFaceCam));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kFaceList",
                         PyInt_FromLong(plViewFaceModifier::kFaceList));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kFacePlay",
                         PyInt_FromLong(plViewFaceModifier::kFacePlay));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kFaceObj",
                         PyInt_FromLong(plViewFaceModifier::kFaceObj));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kOffset",
                         PyInt_FromLong(plViewFaceModifier::kOffset));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kOffsetLocal",
                         PyInt_FromLong(plViewFaceModifier::kOffsetLocal));
    PyDict_SetItemString(pyViewFaceModifier_Type.tp_dict, "kMaxBounds",
                         PyInt_FromLong(plViewFaceModifier::kMaxBounds));

    Py_INCREF(&pyViewFaceModifier_Type);
    return (PyObject*)&pyViewFaceModifier_Type;
}

int pyViewFaceModifier_Check(PyObject* obj) {
    if (obj->ob_type == &pyViewFaceModifier_Type
        || PyType_IsSubtype(obj->ob_type, &pyViewFaceModifier_Type))
        return 1;
    return 0;
}

PyObject* pyViewFaceModifier_FromViewFaceModifier(class plViewFaceModifier* mod) {
    if (mod == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyViewFaceModifier* pymod = PyObject_New(pyViewFaceModifier, &pyViewFaceModifier_Type);
    pymod->fThis = mod;
    pymod->fPyOwned = false;
    return (PyObject*)pymod;
}

}
