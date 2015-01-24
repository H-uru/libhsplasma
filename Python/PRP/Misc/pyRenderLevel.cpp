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
#include <PRP/Misc/plRenderLevel.h>
#include "pyRenderLevel.h"

extern "C" {

static PyObject* pyRenderLevel_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot construct plRenderLevel objects");
    return NULL;
}

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

    PyDict_SetItemString(pyRenderLevel_Type.tp_dict, "kOpaqueMajorLevel",
                         PyInt_FromLong(plRenderLevel::kOpaqueMajorLevel));
    PyDict_SetItemString(pyRenderLevel_Type.tp_dict, "kFBMajorLevel",
                         PyInt_FromLong(plRenderLevel::kFBMajorLevel));
    PyDict_SetItemString(pyRenderLevel_Type.tp_dict, "kDefRendMajorLevel",
                         PyInt_FromLong(plRenderLevel::kDefRendMajorLevel));
    PyDict_SetItemString(pyRenderLevel_Type.tp_dict, "kBlendRendMajorLevel",
                         PyInt_FromLong(plRenderLevel::kBlendRendMajorLevel));
    PyDict_SetItemString(pyRenderLevel_Type.tp_dict, "kLateRendMajorLevel",
                         PyInt_FromLong(plRenderLevel::kLateRendMajorLevel));
    PyDict_SetItemString(pyRenderLevel_Type.tp_dict, "kMajorShift",
                         PyInt_FromLong(plRenderLevel::kMajorShift));
    PyDict_SetItemString(pyRenderLevel_Type.tp_dict, "kDefRendMinorLevel",
                         PyInt_FromLong(plRenderLevel::kDefRendMinorLevel));
    PyDict_SetItemString(pyRenderLevel_Type.tp_dict, "kOpaqueMinorLevel",
                         PyInt_FromLong(plRenderLevel::kOpaqueMinorLevel));
    PyDict_SetItemString(pyRenderLevel_Type.tp_dict, "kMinorLevelMask",
                         PyInt_FromLong(plRenderLevel::kMinorLevelMask));
    PyDict_SetItemString(pyRenderLevel_Type.tp_dict, "kAvatarRendMinorLevel",
                         PyInt_FromLong(plRenderLevel::kAvatarRendMinorLevel));

    Py_INCREF(&pyRenderLevel_Type);
    return (PyObject*)&pyRenderLevel_Type;
}

}
