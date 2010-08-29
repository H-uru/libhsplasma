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

#ifndef _PYKEYEDOBJECT_H
#define _PYKEYEDOBJECT_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsKeyedObject* fThis;
    bool fPyOwned;
} pyKeyedObject;

typedef struct {
    PyObject_HEAD
    class hsKeyedObjectStub* fThis;
    bool fPyOwned;
} pyKeyedObjectStub;

extern PyTypeObject pyKeyedObject_Type;
PyObject* Init_pyKeyedObject_Type();
int pyKeyedObject_Check(PyObject* obj);
PyObject* pyKeyedObject_FromKeyedObject(class hsKeyedObject* obj);

extern PyTypeObject pyKeyedObjectStub_Type;
PyObject* Init_pyKeyedObjectStub_Type();
int pyKeyedObjectStub_Check(PyObject* obj);
PyObject* pyKeyedObjectStub_FromKeyedObjectStub(class hsKeyedObjectStub* obj);

}

#endif
