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

#include "pyStereizer.h"

#include <PRP/Animation/plStereizer.h>
#include "Math/pyGeometry3.h"
#include "PRP/Modifier/pyModifier.h"

PY_PLASMA_NEW(Stereizer, plStereizer)

PY_PROPERTY(float, Stereizer, ambientDist, getAmbientDist, setAmbientDist)
PY_PROPERTY(float, Stereizer, transition, getTransition, setTransition)

PY_GETSET_GETTER_DECL(Stereizer, sepDist)
{
    PyObject* sepDist = PyTuple_New(2);
    PyTuple_SET_ITEM(sepDist, 0, pyPlasma_convert(self->fThis->getMinSepDist()));
    PyTuple_SET_ITEM(sepDist, 1, pyPlasma_convert(self->fThis->getMaxSepDist()));
    return sepDist;
}

PY_GETSET_SETTER_DECL(Stereizer, sepDist)
{
    PY_PROPERTY_CHECK_NULL(sepDist);

    pySequenceFastRef seq(value);
    if (!seq.isSequence() || seq.size() != 2) {
        PyErr_SetString(PyExc_TypeError, "sepDist should be a sequence of two floats");
        return -1;
    }

    PyObject* minObj = seq.get(0);
    PyObject* maxObj = seq.get(1);
    if (!pyPlasma_check<float>(minObj) || !pyPlasma_check<float>(maxObj)) {
        PyErr_SetString(PyExc_TypeError, "sepDist should be a sequence of two floats");
        return -1;
    }

    self->fThis->setSepDist(pyPlasma_get<float>(minObj), pyPlasma_get<float>(maxObj));
    return 0;
}

PY_PROPERTY_GETSET_DECL(Stereizer, sepDist)

PY_PROPERTY(float, Stereizer, tanAng, getTanAng, setTanAng)
PY_PROPERTY(hsVector3, Stereizer, initPos, getInitPos, setInitPos)

static PyGetSetDef pyStereizer_GetSet[] = {
    pyStereizer_ambientDist_getset,
    pyStereizer_transition_getset,
    pyStereizer_sepDist_getset,
    pyStereizer_tanAng_getset,
    pyStereizer_initPos_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Stereizer, plStereizer, "plStereizer wrapper")

PY_PLASMA_TYPE_INIT(Stereizer)
{
    pyStereizer_Type.tp_new = pyStereizer_new;
    pyStereizer_Type.tp_getset = pyStereizer_GetSet;
    pyStereizer_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyStereizer_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(Stereizer, "kLeftChannel", plStereizer::kLeftChannel);
    PY_TYPE_ADD_CONST(Stereizer, "kHasMaster", plStereizer::kHasMaster);

    Py_INCREF(&pyStereizer_Type);
    return (PyObject*)&pyStereizer_Type;
}

PY_PLASMA_IFC_METHODS(Stereizer, plStereizer)
