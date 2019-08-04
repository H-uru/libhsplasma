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

#ifndef _PYFIXEDWATERSTATE7_H
#define _PYFIXEDWATERSTATE7_H

#include "PyPlasma.h"
#include <PRP/Surface/plFixedWaterState7.h>

PY_WRAP_PLASMA(FixedWaterState7, plFixedWaterState7);
PY_WRAP_PLASMA(WaveState7, plFixedWaterState7::WaveState);

/* Python property helpers */
inline PyObject* pyPlasma_convert(plFixedWaterState7* value)
{
    return pyFixedWaterState7_FromFixedWaterState7(value);
}

inline PyObject* pyPlasma_convert(plFixedWaterState7::WaveState* value)
{
    return pyWaveState7_FromWaveState7(value);
}

template <>
inline int pyPlasma_check<plFixedWaterState7>(PyObject* value) {
    return pyFixedWaterState7_Check(value);
}

template <>
inline int pyPlasma_check<plFixedWaterState7::WaveState>(PyObject* value)
{
    return pyWaveState7_Check(value);
}

template <>
inline plFixedWaterState7* pyPlasma_get(PyObject* value)
{
    return ((pyFixedWaterState7*)value)->fThis;
}

template <>
inline plFixedWaterState7::WaveState* pyPlasma_get(PyObject* value)
{
    return ((pyWaveState7*)value)->fThis;
}

#endif
