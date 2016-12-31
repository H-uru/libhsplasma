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

#include "pyGBufferGroup.h"

#include <PRP/Geometry/plGBufferGroup.h>

extern "C" {

PY_PLASMA_VALUE_DEALLOC(GBufferCell)
PY_PLASMA_EMPTY_INIT(GBufferCell)
PY_PLASMA_VALUE_NEW(GBufferCell, plGBufferCell)

PY_PROPERTY_MEMBER(unsigned int, GBufferCell, vtxStart, fVtxStart)
PY_PROPERTY_MEMBER(unsigned int, GBufferCell, colorStart, fColorStart)
PY_PROPERTY_MEMBER(unsigned int, GBufferCell, length, fLength)

static PyGetSetDef pyGBufferCell_GetSet[] = {
    pyGBufferCell_vtxStart_getset,
    pyGBufferCell_colorStart_getset,
    pyGBufferCell_length_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyGBufferCell_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plGBufferCell",         /* tp_name */
    sizeof(pyGBufferCell),              /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyGBufferCell_dealloc,              /* tp_dealloc */
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
    "plGBufferCell wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyGBufferCell_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyGBufferCell___init__,             /* tp_init */
    NULL,                               /* tp_alloc */
    pyGBufferCell_new,                  /* tp_new */
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

PyObject* Init_pyGBufferCell_Type() {
    if (PyType_Ready(&pyGBufferCell_Type) < 0)
        return NULL;

    Py_INCREF(&pyGBufferCell_Type);
    return (PyObject*)&pyGBufferCell_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(GBufferCell, plGBufferCell)

}
