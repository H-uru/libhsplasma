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

#ifndef _PYWAVESET_H
#define _PYWAVESET_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plWaveSetBase* fThis;
    bool fPyOwned;
} pyWaveSetBase;

extern PyTypeObject pyWaveSetBase_Type;
PyObject* Init_pyWaveSetBase_Type();
int pyWaveSetBase_Check(PyObject* obj);
PyObject* pyWaveSetBase_FromWaveSetBase(class plWaveSetBase* state);

typedef struct {
    PyObject_HEAD
    class plWaveSet7* fThis;
    bool fPyOwned;
} pyWaveSet7;

extern PyTypeObject pyWaveSet7_Type;
PyObject* Init_pyWaveSet7_Type();
int pyWaveSet7_Check(PyObject* obj);
PyObject* pyWaveSet7_FromWaveSet7(class plWaveSet7* state);

}

#endif
