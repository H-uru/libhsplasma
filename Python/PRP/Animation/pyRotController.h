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

#ifndef _PYROTCONTROLLER_H
#define _PYROTCONTROLLER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plRotController* fThis;
    bool fPyOwned;
} pyRotController;

typedef struct {
    PyObject_HEAD
    class plSimpleRotController* fThis;
    bool fPyOwned;
} pySimpleRotController;

typedef struct {
    PyObject_HEAD
    class plCompoundRotController* fThis;
    bool fPyOwned;
} pyCompoundRotController;

extern PyTypeObject pyRotController_Type;
PyObject* Init_pyRotController_Type();
int pyRotController_Check(PyObject* obj);
PyObject* pyRotController_FromRotController(class plRotController* controller);

extern PyTypeObject pySimpleRotController_Type;
PyObject* Init_pySimpleRotController_Type();
int pySimpleRotController_Check(PyObject* obj);
PyObject* pySimpleRotController_FromSimpleRotController(class plSimpleRotController* controller);

extern PyTypeObject pyCompoundRotController_Type;
PyObject* Init_pyCompoundRotController_Type();
int pyCompoundRotController_Check(PyObject* obj);
PyObject* pyCompoundRotController_FromCompoundRotController(class plCompoundRotController* controller);

}

#endif
