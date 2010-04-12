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

#ifndef _PYLOGICMODIFIER_H
#define _PYLOGICMODIFIER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLogicModBase* fThis;
    bool fPyOwned;
} pyLogicModBase;

typedef struct {
    PyObject_HEAD
    class plLogicModifier* fThis;
    bool fPyOwned;
} pyLogicModifier;

extern PyTypeObject pyLogicModBase_Type;
PyObject* Init_pyLogicModBase_Type();
int pyLogicModBase_Check(PyObject* obj);
PyObject* pyLogicModBase_FromLogicModBase(class plLogicModBase* mod);

extern PyTypeObject pyLogicModifier_Type;
PyObject* Init_pyLogicModifier_Type();
int pyLogicModifier_Check(PyObject* obj);
PyObject* pyLogicModifier_FromLogicModifier(class plLogicModifier* mod);

}

#endif
