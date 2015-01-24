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
#include <PRP/Geometry/plDrawableSpans.h>
#include "pyDrawableSpans.h"
#include "PRP/KeyedObject/pyKeyedObject.h"

extern "C" {

static PyObject* pyDrawable_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plDrawable is abstract");
    return NULL;
}

PyTypeObject pyDrawable_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDrawable",            /* tp_name */
    sizeof(pyDrawable),                 /* tp_basicsize */
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
    "plDrawable wrapper",               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDrawable_new,                     /* tp_new */
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

PyObject* Init_pyDrawable_Type() {
    pyDrawable_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pyDrawable_Type) < 0)
        return NULL;

    // Properties
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kPropNoDraw",
                         PyInt_FromLong(plDrawable::kPropNoDraw));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kPropUNUSED",
                         PyInt_FromLong(plDrawable::kPropUNUSED));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kPropSortSpans",
                         PyInt_FromLong(plDrawable::kPropSortSpans));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kPropSortFaces",
                         PyInt_FromLong(plDrawable::kPropSortFaces));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kPropVolatile",
                         PyInt_FromLong(plDrawable::kPropVolatile));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kPropNoReSort",
                         PyInt_FromLong(plDrawable::kPropNoReSort));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kPropPartialSort",
                         PyInt_FromLong(plDrawable::kPropPartialSort));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kPropCharacter",
                         PyInt_FromLong(plDrawable::kPropCharacter));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kPropSortAsOne",
                         PyInt_FromLong(plDrawable::kPropSortAsOne));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kPropHasVisLOS",
                         PyInt_FromLong(plDrawable::kPropHasVisLOS));

    // Criteria
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kCritStatic",
                         PyInt_FromLong(plDrawable::kCritStatic));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kCritSortSpans",
                         PyInt_FromLong(plDrawable::kCritSortSpans));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kCritSortFaces",
                         PyInt_FromLong(plDrawable::kCritSortFaces));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kCritCharacter",
                         PyInt_FromLong(plDrawable::kCritCharacter));

    // plDrawableType
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kNormal",
                         PyInt_FromLong(plDrawable::kNormal));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kNonDrawable",
                         PyInt_FromLong(plDrawable::kNonDrawable));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kEnviron",
                         PyInt_FromLong(plDrawable::kEnviron));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kLightProxy",
                         PyInt_FromLong(plDrawable::kLightProxy));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kOccluderProxy",
                         PyInt_FromLong(plDrawable::kOccluderProxy));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kAudibleProxy",
                         PyInt_FromLong(plDrawable::kAudibleProxy));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kPhysicalProxy",
                         PyInt_FromLong(plDrawable::kPhysicalProxy));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kCoordinateProxy",
                         PyInt_FromLong(plDrawable::kCoordinateProxy));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kOccSnapProxy",
                         PyInt_FromLong(plDrawable::kOccSnapProxy));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kGenericProxy",
                         PyInt_FromLong(plDrawable::kGenericProxy));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kCameraProxy",
                         PyInt_FromLong(plDrawable::kCameraProxy));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kAllProxies",
                         PyInt_FromLong(plDrawable::kAllProxies));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kAllTypes",
                         PyInt_FromLong(plDrawable::kAllTypes));

    // plSubDrawableType
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kSubNormal",
                         PyInt_FromLong(plDrawable::kSubNormal));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kSubNonDrawable",
                         PyInt_FromLong(plDrawable::kSubNonDrawable));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kSubEnviron",
                         PyInt_FromLong(plDrawable::kSubEnviron));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kSubAllTypes",
                         PyInt_FromLong(plDrawable::kSubAllTypes));

    // Span ID masks
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kSpanTypeMask",
                         PyInt_FromLong(plDrawable::kSpanTypeMask));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kSpanIDMask",
                         PyInt_FromLong(plDrawable::kSpanIDMask));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kSpanTypeIcicle",
                         PyInt_FromLong(plDrawable::kSpanTypeIcicle));
    PyDict_SetItemString(pyDrawable_Type.tp_dict, "kSpanTypeParticleSpan",
                         PyInt_FromLong(plDrawable::kSpanTypeParticleSpan));

    Py_INCREF(&pyDrawable_Type);
    return (PyObject*)&pyDrawable_Type;
}

int pyDrawable_Check(PyObject* obj) {
    if (obj->ob_type == &pyDrawable_Type
        || PyType_IsSubtype(obj->ob_type, &pyDrawable_Type))
        return 1;
    return 0;
}

PyObject* pyDrawable_FromDrawable(class plDrawable* draw) {
    if (draw == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyDrawable* pdraw = PyObject_New(pyDrawable, &pyDrawable_Type);
    pdraw->fThis = draw;
    pdraw->fPyOwned = false;
    return (PyObject*)pdraw;
}

}
