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

#ifndef _PYBITMAP_H
#define _PYBITMAP_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plBitmap* fThis;
    bool fPyOwned;
    unsigned short fClsType;
} pyBitmap;

typedef struct {
    PyObject_HEAD
    class plMipmap* fThis;
    bool fPyOwned;
    unsigned short fClsType;
} pyMipmap;

extern PyTypeObject pyBitmap_Type;
PyObject* Init_pyBitmap_Type();
int pyBitmap_Check(PyObject* obj);
PyObject* pyBitmap_FromBitmap(class plBitmap* img);

extern PyTypeObject pyMipmap_Type;
PyObject* Init_pyMipmap_Type();
int pyMipmap_Check(PyObject* obj);
PyObject* pyMipmap_FromMipmap(class plMipmap* img);

}

#endif
