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

#ifndef _PYMULTISTAGEBEHMOD_H
#define _PYMULTISTAGEBEHMOD_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plMultistageBehMod* fThis;
    bool fPyOwned;
} pyMultistageBehMod;

typedef struct {
    PyObject_HEAD
    class plAnimStage* fThis;
    bool fPyOwned;
} pyAnimStage;

extern PyTypeObject pyMultistageBehMod_Type;
PyObject* Init_pyMultistageBehMod_Type();
int pyMultistageBehMod_Check(PyObject* obj);
PyObject* pyMultistageBehMod_FromMultistageBehMod(class plMultistageBehMod* mod);

extern PyTypeObject pyAnimStage_Type;
PyObject* Init_pyAnimStage_Type();
int pyAnimStage_Check(PyObject* obj);
PyObject* pyAnimStage_FromAnimStage(class plAnimStage* obj);

}

#endif
