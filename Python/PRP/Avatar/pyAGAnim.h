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

#ifndef _PYAGANIM_H
#define _PYAGANIM_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plAGAnim* fThis;
    bool fPyOwned;
} pyAGAnim;

typedef struct {
    PyObject_HEAD
    class plAgeGlobalAnim* fThis;
    bool fPyOwned;
} pyAgeGlobalAnim;

extern PyTypeObject pyAGAnim_Type;
PyObject* Init_pyAGAnim_Type();
int pyAGAnim_Check(PyObject* obj);
PyObject* pyAGAnim_FromAGAnim(class plAGAnim* anim);

extern PyTypeObject pyAgeGlobalAnim_Type;
PyObject* Init_pyAgeGlobalAnim_Type();
int pyAgeGlobalAnim_Check(PyObject* obj);
PyObject* pyAgeGlobalAnim_FromAgeGlobalAnim(class plAgeGlobalAnim* anim);

}

#endif
