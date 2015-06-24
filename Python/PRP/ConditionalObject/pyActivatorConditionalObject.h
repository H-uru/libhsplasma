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

#ifndef _PY_ACTIVATORCONDITIONALOBJECT_H
#define _PY_ACTIVATORCONDITIONALOBJECT_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plActivatorConditionalObject* fThis;
    bool fPyOwned;
} pyActivatorConditionalObject;

extern PyTypeObject pyActivatorConditionalObject_Type;
PyObject* Init_pyActivatorConditionalObject_Type();
int pyActivatorConditionalObject_Check(PyObject* obj);
PyObject* pyActivatorConditionalObject_FromActivatorConditionalObject(class plActivatorConditionalObject* obj);

typedef struct {
    PyObject_HEAD
    class plActivatorActivatorConditionalObject* fThis;
    bool fPyOwned;
} pyActivatorActivatorConditionalObject;

extern PyTypeObject pyActivatorActivatorConditionalObject_Type;
PyObject* Init_pyActivatorActivatorConditionalObject_Type();
int pyActivatorActivatorConditionalObject_Check(PyObject* obj);
PyObject* pyActivatorActivatorConditionalObject_FromActivatorActivatorConditionalObject(class plActivatorActivatorConditionalObject* obj);

typedef struct {
    PyObject_HEAD
    class plVolActivatorConditionalObject* fThis;
    bool fPyOwned;
} pyVolActivatorConditionalObject;

extern PyTypeObject pyVolActivatorConditionalObject_Type;
PyObject* Init_pyVolActivatorConditionalObject_Type();
int pyVolActivatorConditionalObject_Check(PyObject* obj);
PyObject* pyVolActivatorConditionalObject_FromVolActivatorConditionalObject(class plVolActivatorConditionalObject* obj);

}

#endif
