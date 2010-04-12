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

#ifndef _PYATCANIM_H
#define _PYATCANIM_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plATCAnim* fThis;
    bool fPyOwned;
} pyATCAnim;

typedef struct {
    PyObject_HEAD
    class plEmoteAnim* fThis;
    bool fPyOwned;
} pyEmoteAnim;

typedef struct {
    PyObject_HEAD
    class plAGAnimBink* fThis;
    bool fPyOwned;
} pyAGAnimBink;

extern PyTypeObject pyATCAnim_Type;
PyObject* Init_pyATCAnim_Type();
int pyATCAnim_Check(PyObject* obj);
PyObject* pyATCAnim_FromATCAnim(class plATCAnim* anim);

extern PyTypeObject pyEmoteAnim_Type;
PyObject* Init_pyEmoteAnim_Type();
int pyEmoteAnim_Check(PyObject* obj);
PyObject* pyEmoteAnim_FromEmoteAnim(class plEmoteAnim* anim);

extern PyTypeObject pyAGAnimBink_Type;
PyObject* Init_pyAGAnimBink_Type();
int pyAGAnimBink_Check(PyObject* obj);
PyObject* pyAGAnimBink_FromAGAnimBink(class plAGAnimBink* anim);

}

#endif
