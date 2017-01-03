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

#include "pyController.h"

#include <PRP/Animation/plTMController.h>
#include "pyPosController.h"
#include "pyRotController.h"
#include "pyScaleController.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_EMPTY_INIT(TMController)
PY_PLASMA_NEW(TMController, plTMController)

PY_METHOD_NOARGS(TMController, convertToCompoundController,
    "Converts this controller to a plCompoundController")
{
    return ICreate(self->fThis->convertToCompoundController());
}

static PyMethodDef pyTMController_Methods[] = {
    pyTMController_convertToCompoundController_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_CREATABLE(plPosController, PosController, TMController, pos,
                      getPosController, setPosController)
PY_PROPERTY_CREATABLE(plRotController, RotController, TMController, rot,
                      getRotController, setRotController)
PY_PROPERTY_CREATABLE(plScaleController, ScaleController, TMController, scale,
                      getScaleController, setScaleController)

static PyGetSetDef pyTMController_GetSet[] = {
    pyTMController_pos_getset,
    pyTMController_rot_getset,
    pyTMController_scale_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyTMController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plTMController",        /* tp_name */
    sizeof(pyTMController),             /* tp_basicsize */
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
    "plTMController wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyTMController_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyTMController_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyTMController___init__,            /* tp_init */
    NULL,                               /* tp_alloc */
    pyTMController_new,                 /* tp_new */
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

PyObject* Init_pyTMController_Type() {
    pyTMController_Type.tp_base = &pyController_Type;
    if (PyType_Ready(&pyTMController_Type) < 0)
        return NULL;

    Py_INCREF(&pyTMController_Type);
    return (PyObject*)&pyTMController_Type;
}

PY_PLASMA_IFC_METHODS(TMController, plTMController)

}
