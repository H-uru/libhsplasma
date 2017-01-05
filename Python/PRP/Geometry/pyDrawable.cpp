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

#include "pyDrawableSpans.h"

#include <PRP/Geometry/plDrawableSpans.h>
#include "PRP/KeyedObject/pyKeyedObject.h"

extern "C" {

PY_PLASMA_NEW_MSG(Drawable, "plDrawable is abstract")

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
    PY_TYPE_ADD_CONST(Drawable, "kPropNoDraw", plDrawable::kPropNoDraw);
    PY_TYPE_ADD_CONST(Drawable, "kPropUNUSED", plDrawable::kPropUNUSED);
    PY_TYPE_ADD_CONST(Drawable, "kPropSortSpans", plDrawable::kPropSortSpans);
    PY_TYPE_ADD_CONST(Drawable, "kPropSortFaces", plDrawable::kPropSortFaces);
    PY_TYPE_ADD_CONST(Drawable, "kPropVolatile", plDrawable::kPropVolatile);
    PY_TYPE_ADD_CONST(Drawable, "kPropNoReSort", plDrawable::kPropNoReSort);
    PY_TYPE_ADD_CONST(Drawable, "kPropPartialSort", plDrawable::kPropPartialSort);
    PY_TYPE_ADD_CONST(Drawable, "kPropCharacter", plDrawable::kPropCharacter);
    PY_TYPE_ADD_CONST(Drawable, "kPropSortAsOne", plDrawable::kPropSortAsOne);
    PY_TYPE_ADD_CONST(Drawable, "kPropHasVisLOS", plDrawable::kPropHasVisLOS);

    // Criteria
    PY_TYPE_ADD_CONST(Drawable, "kCritStatic", plDrawable::kCritStatic);
    PY_TYPE_ADD_CONST(Drawable, "kCritSortSpans", plDrawable::kCritSortSpans);
    PY_TYPE_ADD_CONST(Drawable, "kCritSortFaces", plDrawable::kCritSortFaces);
    PY_TYPE_ADD_CONST(Drawable, "kCritCharacter", plDrawable::kCritCharacter);

    // plDrawableType
    PY_TYPE_ADD_CONST(Drawable, "kNormal", plDrawable::kNormal);
    PY_TYPE_ADD_CONST(Drawable, "kNonDrawable", plDrawable::kNonDrawable);
    PY_TYPE_ADD_CONST(Drawable, "kEnviron", plDrawable::kEnviron);
    PY_TYPE_ADD_CONST(Drawable, "kLightProxy", plDrawable::kLightProxy);
    PY_TYPE_ADD_CONST(Drawable, "kOccluderProxy", plDrawable::kOccluderProxy);
    PY_TYPE_ADD_CONST(Drawable, "kAudibleProxy", plDrawable::kAudibleProxy);
    PY_TYPE_ADD_CONST(Drawable, "kPhysicalProxy", plDrawable::kPhysicalProxy);
    PY_TYPE_ADD_CONST(Drawable, "kCoordinateProxy", plDrawable::kCoordinateProxy);
    PY_TYPE_ADD_CONST(Drawable, "kOccSnapProxy", plDrawable::kOccSnapProxy);
    PY_TYPE_ADD_CONST(Drawable, "kGenericProxy", plDrawable::kGenericProxy);
    PY_TYPE_ADD_CONST(Drawable, "kCameraProxy", plDrawable::kCameraProxy);
    PY_TYPE_ADD_CONST(Drawable, "kAllProxies", plDrawable::kAllProxies);
    PY_TYPE_ADD_CONST(Drawable, "kAllTypes", plDrawable::kAllTypes);

    // plSubDrawableType
    PY_TYPE_ADD_CONST(Drawable, "kSubNormal", plDrawable::kSubNormal);
    PY_TYPE_ADD_CONST(Drawable, "kSubNonDrawable", plDrawable::kSubNonDrawable);
    PY_TYPE_ADD_CONST(Drawable, "kSubEnviron", plDrawable::kSubEnviron);
    PY_TYPE_ADD_CONST(Drawable, "kSubAllTypes", plDrawable::kSubAllTypes);

    // Span ID masks
    PY_TYPE_ADD_CONST(Drawable, "kSpanTypeMask", plDrawable::kSpanTypeMask);
    PY_TYPE_ADD_CONST(Drawable, "kSpanIDMask", plDrawable::kSpanIDMask);
    PY_TYPE_ADD_CONST(Drawable, "kSpanTypeIcicle", plDrawable::kSpanTypeIcicle);
    PY_TYPE_ADD_CONST(Drawable, "kSpanTypeParticleSpan", plDrawable::kSpanTypeParticleSpan);

    Py_INCREF(&pyDrawable_Type);
    return (PyObject*)&pyDrawable_Type;
}

PY_PLASMA_IFC_METHODS(Drawable, plDrawable)

}
