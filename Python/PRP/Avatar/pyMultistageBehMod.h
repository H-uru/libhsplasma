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

#ifndef _PYMULTISTAGEBEHMOD_H
#define _PYMULTISTAGEBEHMOD_H

#include "PyPlasma.h"
#include <PRP/Avatar/plAnimStage.h>

PY_WRAP_PLASMA(MultistageBehMod, class plMultistageBehMod);
PY_WRAP_PLASMA(AnimStage, class plAnimStage);

/* Python property helpers */
inline PyObject* pyPlasma_convert(plAnimStage::PlayType value)
{
    return PyInt_FromLong((long)value);
}

inline PyObject* pyPlasma_convert(plAnimStage::AdvanceType value)
{
    return PyInt_FromLong((long)value);
}

template <>
inline int pyPlasma_check<plAnimStage::PlayType>(PyObject* value) {
    return PyInt_Check(value);
}

template <>
inline int pyPlasma_check<plAnimStage::AdvanceType>(PyObject* value)
{
    return PyInt_Check(value);
}

template <>
inline plAnimStage::PlayType pyPlasma_get(PyObject* value)
{
    return (plAnimStage::PlayType)PyInt_AsLong(value);
}

template <>
inline plAnimStage::AdvanceType pyPlasma_get(PyObject* value)
{
    return (plAnimStage::AdvanceType)PyInt_AsLong(value);
}

#endif
