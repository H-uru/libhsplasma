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

#include "pyRenderLevel.h"

#include <PRP/Misc/plRenderLevel.h>

extern "C" {

PY_PLASMA_NEW_MSG(RenderLevel, "Cannot construct plRenderLevel objects")

PyTypeObject pyRenderLevel_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plRenderLevel",         /* tp_name */
    sizeof(PyObject),                   /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plRenderLevel constants",          /* tp_doc */

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
    pyRenderLevel_new,                  /* tp_new */
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

PyObject* Init_pyRenderLevel_Type() {
    if (PyType_Ready(&pyRenderLevel_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(RenderLevel, "kOpaqueMajorLevel", plRenderLevel::kOpaqueMajorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kFBMajorLevel", plRenderLevel::kFBMajorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kDefRendMajorLevel", plRenderLevel::kDefRendMajorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kBlendRendMajorLevel", plRenderLevel::kBlendRendMajorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kLateRendMajorLevel", plRenderLevel::kLateRendMajorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kMajorShift", plRenderLevel::kMajorShift);
    PY_TYPE_ADD_CONST(RenderLevel, "kDefRendMinorLevel", plRenderLevel::kDefRendMinorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kOpaqueMinorLevel", plRenderLevel::kOpaqueMinorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kMinorLevelMask", plRenderLevel::kMinorLevelMask);
    PY_TYPE_ADD_CONST(RenderLevel, "kAvatarRendMinorLevel", plRenderLevel::kAvatarRendMinorLevel);

    Py_INCREF(&pyRenderLevel_Type);
    return (PyObject*)&pyRenderLevel_Type;
}

}
