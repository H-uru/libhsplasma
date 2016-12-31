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

#include "pyLightInfo.h"

#include <PRP/Light/plOmniLightInfo.h>
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(OmniLightInfo, plOmniLightInfo)

PY_PROPERTY(float, OmniLightInfo, attenConst, getAttenConst, setAttenConst)
PY_PROPERTY(float, OmniLightInfo, attenLinear, getAttenLinear, setAttenLinear)
PY_PROPERTY(float, OmniLightInfo, attenQuadratic, getAttenQuadratic, setAttenQuadratic)
PY_PROPERTY(float, OmniLightInfo, attenCutoff, getAttenCutoff, setAttenCutoff)

static PyGetSetDef pyOmniLightInfo_GetSet[] = {
    pyOmniLightInfo_attenConst_getset,
    pyOmniLightInfo_attenLinear_getset,
    pyOmniLightInfo_attenQuadratic_getset,
    pyOmniLightInfo_attenCutoff_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyOmniLightInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plOmniLightInfo",       /* tp_name */
    sizeof(pyOmniLightInfo),            /* tp_basicsize */
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
    "plOmniLightInfo wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyOmniLightInfo_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyOmniLightInfo_new,                /* tp_new */
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

PyObject* Init_pyOmniLightInfo_Type() {
    pyOmniLightInfo_Type.tp_base = &pyLightInfo_Type;
    if (PyType_Ready(&pyOmniLightInfo_Type) < 0)
        return NULL;

    Py_INCREF(&pyOmniLightInfo_Type);
    return (PyObject*)&pyOmniLightInfo_Type;
}

PY_PLASMA_IFC_METHODS(OmniLightInfo, plOmniLightInfo)

}
