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

#ifndef _PYCREATABLE_H
#define _PYCREATABLE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plCreatable* fThis;
    bool fPyOwned;
} pyCreatable;

typedef struct {
    PyObject_HEAD
    class plCreatableStub* fThis;
    bool fPyOwned;
} pyCreatableStub;

extern PyTypeObject pyCreatable_Type;
PyObject* Init_pyCreatable_Type();
int pyCreatable_Check(PyObject* obj);
PyObject* pyCreatable_FromCreatable(class plCreatable* pCre);

extern PyTypeObject pyCreatableStub_Type;
PyObject* Init_pyCreatableStub_Type();
int pyCreatableStub_Check(PyObject* obj);

};

#endif
