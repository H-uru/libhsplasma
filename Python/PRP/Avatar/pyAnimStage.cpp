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

PY_PLASMA_EMPTY_INIT(AnimStage)
PY_PLASMA_NEW(AnimStage, plAnimStage)

PY_PROPERTY(plAnimStage::PlayType, AnimStage, forwardType, getForwardType, setForwardType)
PY_PROPERTY(plAnimStage::PlayType, AnimStage, backType, getBackType, setBackType)
PY_PROPERTY(plAnimStage::AdvanceType, AnimStage, advanceType, getAdvanceType, setAdvanceType)
PY_PROPERTY(plAnimStage::AdvanceType, AnimStage, regressType, getRegressType, setRegressType)
PY_PROPERTY(ST::string, AnimStage, animName, getAnimName, setAnimName)
PY_PROPERTY(unsigned char, AnimStage, notify, getNotify, setNotify)
PY_PROPERTY(int, AnimStage, loops, getLoops, setLoops)

PY_GETSET_GETTER_DECL(AnimStage, advanceTo)
{
    if (self->fThis->doAdvanceTo())
        return pyPlasma_convert(self->fThis->getAdvanceTo());
    else
        Py_RETURN_NONE;
}

PY_GETSET_SETTER_DECL(AnimStage, advanceTo)
{
    PY_PROPERTY_CHECK_NULL(advanceTo)
    if (value == Py_None) {
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

PY_GETSET_GETTER_DECL(AnimStage, regressTo)
{
    if (self->fThis->doRegressTo())
        return pyPlasma_convert(self->fThis->getRegressTo());
    else
        Py_RETURN_NONE;
}

PY_GETSET_SETTER_DECL(AnimStage, regressTo)
{
    PY_PROPERTY_CHECK_NULL(regressTo)
    if (value == Py_None) {
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

PY_PLASMA_TYPE(AnimStage, plAnimStage, "plAnimStage wrapper")

PY_PLASMA_TYPE_INIT(AnimStage)
{
    pyAnimStage_Type.tp_init = pyAnimStage___init__;
    pyAnimStage_Type.tp_new = pyAnimStage_new;
    pyAnimStage_Type.tp_getset = pyAnimStage_GetSet;
    pyAnimStage_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyAnimStage_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(AnimStage, "kNotifyEnter", plAnimStage::kNotifyEnter);
    PY_TYPE_ADD_CONST(AnimStage, "kNotifyLoop", plAnimStage::kNotifyLoop);
    PY_TYPE_ADD_CONST(AnimStage, "kNotifyAdvance", plAnimStage::kNotifyAdvance);
    PY_TYPE_ADD_CONST(AnimStage, "kNotifyRegress", plAnimStage::kNotifyRegress);

    PY_TYPE_ADD_CONST(AnimStage, "kPlayNone", plAnimStage::kPlayNone);
    PY_TYPE_ADD_CONST(AnimStage, "kPlayKey", plAnimStage::kPlayKey);
    PY_TYPE_ADD_CONST(AnimStage, "kPlayAuto", plAnimStage::kPlayAuto);
    PY_TYPE_ADD_CONST(AnimStage, "kPlayMax", plAnimStage::kPlayMax);

    PY_TYPE_ADD_CONST(AnimStage, "kAdvanceNone", plAnimStage::kAdvanceNone);
    PY_TYPE_ADD_CONST(AnimStage, "kAdvanceOnMove", plAnimStage::kAdvanceOnMove);
    PY_TYPE_ADD_CONST(AnimStage, "kAdvanceAuto", plAnimStage::kAdvanceAuto);
    PY_TYPE_ADD_CONST(AnimStage, "kAdvanceOnAnyKey", plAnimStage::kAdvanceOnAnyKey);
    PY_TYPE_ADD_CONST(AnimStage, "kAdvanceMax", plAnimStage::kAdvanceMax);

    Py_INCREF(&pyAnimStage_Type);
    return (PyObject*)&pyAnimStage_Type;
}

PY_PLASMA_IFC_METHODS(AnimStage, plAnimStage)
