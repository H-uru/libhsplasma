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

#ifndef _PYDDSURFACE_H
#define _PYDDSURFACE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plDDSurface* fThis;
    bool fPyOwned;
} pyDDSurface;


extern PyTypeObject pyDDSurface_Type;
PyObject* Init_pyDDSurface_Type();
int pyDDSurface_Check(PyObject* obj);
PyObject* pyDDSurface_FromDDSurface(class plDDSurface* dds);

}

#endif
