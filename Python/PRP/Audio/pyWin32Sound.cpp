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

#include "pyWin32Sound.h"

#include <PRP/Audio/plWin32Sound.h>
#include "pySound.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW_MSG(Win32Sound, "plWin32Sound is abstract")

PY_PROPERTY(unsigned char, Win32Sound, channel, getChannel, setChannel)

static PyGetSetDef pyWin32Sound_GetSet[] = {
    pyWin32Sound_channel_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyWin32Sound_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plWin32Sound",          /* tp_name */
    sizeof(pyWin32Sound),               /* tp_basicsize */
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
    "plWin32Sound wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyWin32Sound_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyWin32Sound_new,                   /* tp_new */
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

PyObject* Init_pyWin32Sound_Type() {
    pyWin32Sound_Type.tp_base = &pySound_Type;
    if (PyType_Ready(&pyWin32Sound_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(Win32Sound, "kLeftChannel", plWin32Sound::kLeftChannel);
    PY_TYPE_ADD_CONST(Win32Sound, "kRightChannel", plWin32Sound::kRightChannel);

    Py_INCREF(&pyWin32Sound_Type);
    return (PyObject*)&pyWin32Sound_Type;
}

PY_PLASMA_IFC_METHODS(Win32Sound, plWin32Sound)

}
