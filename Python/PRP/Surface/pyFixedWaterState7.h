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

#include <PRP/Surface/plFixedWaterState7.h>

extern "C" {

typedef struct {
    PyObject_HEAD
    class plFixedWaterState7* fThis;
    bool fPyOwned;
} pyFixedWaterState7;

extern PyTypeObject pyFixedWaterState7_Type;
PyObject* Init_pyFixedWaterState7_Type();
int pyFixedWaterState7_Check(PyObject* obj);
PyObject* pyFixedWaterState7_FromFixedWaterState7(class plFixedWaterState7* state);

typedef struct {
    PyObject_HEAD
    struct plFixedWaterState7::WaveState* fThis;
    bool fPyOwned;
} pyWaveState7;

extern PyTypeObject pyWaveState7_Type;
PyObject* Init_pyWaveState7_Type();
int pyWaveState7_Check(PyObject* obj);
PyObject* pyWaveState7_FromWaveState7(struct plFixedWaterState7::WaveState* state);

}

#endif
