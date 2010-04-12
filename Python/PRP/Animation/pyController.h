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

#ifndef _PYCONTROLLER_H
#define _PYCONTROLLER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plController* fThis;
    bool fPyOwned;
} pyController;

typedef struct {
    PyObject_HEAD
    class plCompoundController* fThis;
    bool fPyOwned;
} pyCompoundController;

typedef struct {
    PyObject_HEAD
    class plTMController* fThis;
    bool fPyOwned;
} pyTMController;

extern PyTypeObject pyController_Type;
PyObject* Init_pyController_Type();
int pyController_Check(PyObject* obj);
PyObject* pyController_FromController(class plController* controller);

extern PyTypeObject pyCompoundController_Type;
PyObject* Init_pyCompoundController_Type();
int pyCompoundController_Check(PyObject* obj);
PyObject* pyCompoundController_FromCompoundController(class plCompoundController* controller);

extern PyTypeObject pyTMController_Type;
PyObject* Init_pyTMController_Type();
int pyTMController_Check(PyObject* obj);
PyObject* pyTMController_FromTMController(class plTMController* controller);

}

#endif
