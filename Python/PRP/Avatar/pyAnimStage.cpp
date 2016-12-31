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

#include "pyMultistageBehMod.h"

#include <PRP/Avatar/plAnimStage.h>
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_EMPTY_INIT(AnimStage)
PY_PLASMA_NEW(AnimStage, plAnimStage)

PY_PROPERTY(plAnimStage::PlayType, AnimStage, forwardType, getForwardType, setForwardType)
PY_PROPERTY(plAnimStage::PlayType, AnimStage, backType, getBackType, setBackType)
PY_PROPERTY(plAnimStage::AdvanceType, AnimStage, advanceType, getAdvanceType, setAdvanceType)
PY_PROPERTY(plAnimStage::AdvanceType, AnimStage, regressType, getRegressType, setRegressType)
PY_PROPERTY(plString, AnimStage, animName, getAnimName, setAnimName)
PY_PROPERTY(unsigned char, AnimStage, notify, getNotify, setNotify)
PY_PROPERTY(int, AnimStage, loops, getLoops, setLoops)

PY_GETSET_GETTER_DECL(AnimStage, advanceTo) {
    if (self->fThis->doAdvanceTo())
        return pyPlasma_convert(self->fThis->getAdvanceTo());
    else
        Py_RETURN_NONE;
}

PY_GETSET_SETTER_DECL(AnimStage, advanceTo) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "advanceTo cannot be deleted");
        return -1;
    } else if (value == Py_None) {
        self->fThis->setAdvanceTo(false);
        return 0;
    } else if (pyPlasma_check<unsigned int>(value)) {
        self->fThis->setAdvanceTo(true, pyPlasma_get<unsigned int>(value));
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "advanceTo should be an int or None");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(AnimStage, advanceTo)

PY_GETSET_GETTER_DECL(AnimStage, regressTo) {
    if (self->fThis->doRegressTo())
        return pyPlasma_convert(self->fThis->getRegressTo());
    else
        Py_RETURN_NONE;
}

PY_GETSET_SETTER_DECL(AnimStage, regressTo) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "regressTo cannot be deleted");
        return -1;
    } else if (value == Py_None) {
        self->fThis->setRegressTo(false);
        return 0;
    } else if (pyPlasma_check<unsigned int>(value)) {
        self->fThis->setRegressTo(true, pyPlasma_get<unsigned int>(value));
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "regressTo should be an int or None");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(AnimStage, regressTo)

static PyGetSetDef pyAnimStage_GetSet[] = {
    pyAnimStage_forwardType_getset,
    pyAnimStage_backType_getset,
    pyAnimStage_advanceType_getset,
    pyAnimStage_regressType_getset,
    pyAnimStage_animName_getset,
    pyAnimStage_notify_getset,
    pyAnimStage_loops_getset,
    pyAnimStage_advanceTo_getset,
    pyAnimStage_regressTo_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyAnimStage_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAnimStage",           /* tp_name */
    sizeof(pyAnimStage),                /* tp_basicsize */
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
    "plAnimStage wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyAnimStage_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyAnimStage___init__,               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAnimStage_new,                    /* tp_new */
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

PyObject* Init_pyAnimStage_Type() {
    pyAnimStage_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyAnimStage_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kNotifyEnter",
                         PyInt_FromLong(plAnimStage::kNotifyEnter));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kNotifyLoop",
                         PyInt_FromLong(plAnimStage::kNotifyLoop));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kNotifyAdvance",
                         PyInt_FromLong(plAnimStage::kNotifyAdvance));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kNotifyRegress",
                         PyInt_FromLong(plAnimStage::kNotifyRegress));

    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kPlayNone",
                         PyInt_FromLong(plAnimStage::kPlayNone));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kPlayKey",
                         PyInt_FromLong(plAnimStage::kPlayKey));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kPlayAuto",
                         PyInt_FromLong(plAnimStage::kPlayAuto));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kPlayMax",
                         PyInt_FromLong(plAnimStage::kPlayMax));

    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kAdvanceNone",
                         PyInt_FromLong(plAnimStage::kAdvanceNone));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kAdvanceOnMove",
                         PyInt_FromLong(plAnimStage::kAdvanceOnMove));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kAdvanceAuto",
                         PyInt_FromLong(plAnimStage::kAdvanceAuto));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kAdvanceOnAnyKey",
                         PyInt_FromLong(plAnimStage::kAdvanceOnAnyKey));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kAdvanceMax",
                         PyInt_FromLong(plAnimStage::kAdvanceMax));

    Py_INCREF(&pyAnimStage_Type);
    return (PyObject*)&pyAnimStage_Type;
}

PY_PLASMA_IFC_METHODS(AnimStage, plAnimStage)

}
