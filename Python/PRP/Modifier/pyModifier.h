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

#ifndef _PYMODIFIER_H
#define _PYMODIFIER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plModifier* fThis;
    bool fPyOwned;
} pyModifier;

typedef struct {
    PyObject_HEAD
    class plSingleModifier* fThis;
    bool fPyOwned;
} pySingleModifier;

typedef struct {
    PyObject_HEAD
    class plMultiModifier* fThis;
    bool fPyOwned;
} pyMultiModifier;

extern PyTypeObject pyModifier_Type;
PyObject* Init_pyModifier_Type();
int pyModifier_Check(PyObject* obj);
PyObject* pyModifier_FromModifier(class plModifier* mod);

extern PyTypeObject pySingleModifier_Type;
PyObject* Init_pySingleModifier_Type();
int pySingleModifier_Check(PyObject* obj);
PyObject* pySingleModifier_FromSingleModifier(class plSingleModifier* mod);

extern PyTypeObject pyMultiModifier_Type;
PyObject* Init_pyMultiModifier_Type();
int pyMultiModifier_Check(PyObject* obj);
PyObject* pyMultiModifier_FromMultiModifier(class plMultiModifier* mod);

}

#endif
