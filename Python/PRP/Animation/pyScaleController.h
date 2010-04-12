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

#ifndef _PYSCALECONTROLLER_H
#define _PYSCALECONTROLLER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plScaleController* fThis;
    bool fPyOwned;
} pyScaleController;

typedef struct {
    PyObject_HEAD
    class plSimpleScaleController* fThis;
    bool fPyOwned;
} pySimpleScaleController;

extern PyTypeObject pyScaleController_Type;
PyObject* Init_pyScaleController_Type();
int pyScaleController_Check(PyObject* obj);
PyObject* pyScaleController_FromScaleController(class plScaleController* controller);

extern PyTypeObject pySimpleScaleController_Type;
PyObject* Init_pySimpleScaleController_Type();
int pySimpleScaleController_Check(PyObject* obj);
PyObject* pySimpleScaleController_FromSimpleScaleController(class plSimpleScaleController* controller);

}

#endif
