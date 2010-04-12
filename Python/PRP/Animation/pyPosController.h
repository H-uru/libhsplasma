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

#ifndef _PYPOSCONTROLLER_H
#define _PYPOSCONTROLLER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plPosController* fThis;
    bool fPyOwned;
} pyPosController;

typedef struct {
    PyObject_HEAD
    class plSimplePosController* fThis;
    bool fPyOwned;
} pySimplePosController;

typedef struct {
    PyObject_HEAD
    class plCompoundPosController* fThis;
    bool fPyOwned;
} pyCompoundPosController;

extern PyTypeObject pyPosController_Type;
PyObject* Init_pyPosController_Type();
int pyPosController_Check(PyObject* obj);
PyObject* pyPosController_FromPosController(class plPosController* controller);

extern PyTypeObject pySimplePosController_Type;
PyObject* Init_pySimplePosController_Type();
int pySimplePosController_Check(PyObject* obj);
PyObject* pySimplePosController_FromSimplePosController(class plSimplePosController* controller);

extern PyTypeObject pyCompoundPosController_Type;
PyObject* Init_pyCompoundPosController_Type();
int pyCompoundPosController_Check(PyObject* obj);
PyObject* pyCompoundPosController_FromCompoundPosController(class plCompoundPosController* controller);

}

#endif
