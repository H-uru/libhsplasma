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

#ifndef _PY_DETECTCONDITIONALOBJECT_H
#define _PY_DETECTCONDITIONALOBJECT_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLocalPlayerInBoxConditionalObject* fThis;
    bool fPyOwned;
} pyLocalPlayerInBoxConditionalObject;

extern PyTypeObject pyLocalPlayerInBoxConditionalObject_Type;
PyObject* Init_pyLocalPlayerInBoxConditionalObject_Type();
int pyLocalPlayerInBoxConditionalObject_Check(PyObject* obj);
PyObject* pyLocalPlayerInBoxConditionalObject_FromLocalPlayerInBoxConditionalObject(class plLocalPlayerInBoxConditionalObject* obj);

typedef struct {
    PyObject_HEAD
    class plLocalPlayerIntersectPlaneConditionalObject* fThis;
    bool fPyOwned;
} pyLocalPlayerIntersectPlaneConditionalObject;

extern PyTypeObject pyLocalPlayerIntersectPlaneConditionalObject_Type;
PyObject* Init_pyLocalPlayerIntersectPlaneConditionalObject_Type();
int pyLocalPlayerIntersectPlaneConditionalObject_Check(PyObject* obj);
PyObject* pyLocalPlayerIntersectPlaneConditionalObject_FromLocalPlayerIntersectPlaneConditionalObject(class plLocalPlayerIntersectPlaneConditionalObject* obj);

typedef struct {
    PyObject_HEAD
    class plObjectInBoxConditionalObject* fThis;
    bool fPyOwned;
} pyObjectInBoxConditionalObject;

extern PyTypeObject pyObjectInBoxConditionalObject_Type;
PyObject* Init_pyObjectInBoxConditionalObject_Type();
int pyObjectInBoxConditionalObject_Check(PyObject* obj);
PyObject* pyObjectInBoxConditionalObject_FromObjectInBoxConditionalObject(class plObjectInBoxConditionalObject* obj);

typedef struct {
    PyObject_HEAD
    class plObjectIntersectPlaneConditionalObject* fThis;
    bool fPyOwned;
} pyObjectIntersectPlaneConditionalObject;

extern PyTypeObject pyObjectIntersectPlaneConditionalObject_Type;
PyObject* Init_pyObjectIntersectPlaneConditionalObject_Type();
int pyObjectIntersectPlaneConditionalObject_Check(PyObject* obj);
PyObject* pyObjectIntersectPlaneConditionalObject_FromObjectIntersectPlaneConditionalObject(class plObjectIntersectPlaneConditionalObject* obj);

}

#endif
