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

#ifndef _PYKEY_H
#define _PYKEY_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plKey* fThis;
} pyKey;

typedef struct {
    PyObject_HEAD
    class plLocation* fThis;
} pyLocation;

extern PyTypeObject pyKey_Type;
PyObject* Init_pyKey_Type();
int pyKey_Check(PyObject* obj);
PyObject* pyKey_FromKey(class plKey key);

extern PyTypeObject pyLocation_Type;
PyObject* Init_pyLocation_Type();
int pyLocation_Check(PyObject* obj);
PyObject* pyLocation_FromLocation(const class plLocation& loc);

};

#endif
