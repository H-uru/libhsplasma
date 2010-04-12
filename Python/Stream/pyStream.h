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

#ifndef _PYSTREAM_H
#define _PYSTREAM_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsStream* fThis;
} pyStream;

typedef struct {
    PyObject_HEAD
    class hsFileStream* fThis;
} pyFileStream;

typedef struct {
    PyObject_HEAD
    class plEncryptedStream* fThis;
} pyEncryptedStream;

typedef struct {
    PyObject_HEAD
    class hsRAMStream* fThis;
} pyRAMStream;


extern PyTypeObject pyStream_Type;
PyObject* Init_pyStream_Type();
int pyStream_Check(PyObject* obj);

extern PyTypeObject pyFileStream_Type;
PyObject* Init_pyFileStream_Type();

extern PyTypeObject pyEncryptedStream_Type;
PyObject* Init_pyEncryptedStream_Type();

extern PyTypeObject pyRAMStream_Type;
PyObject* Init_pyRAMStream_Type();

}

#endif
