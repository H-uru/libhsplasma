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

#ifndef _PYPHYSICAL_H
#define _PYPHYSICAL_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plPhysical* fThis;
    bool fPyOwned;
} pyPhysical;

typedef struct {
    PyObject_HEAD
    class plGenericPhysical* fThis;
    bool fPyOwned;
} pyGenericPhysical;

extern PyTypeObject pySimDefs_Type;
PyObject* Init_pySimDefs_Type();

extern PyTypeObject pyPhysical_Type;
PyObject* Init_pyPhysical_Type();
int pyPhysical_Check(PyObject* obj);
PyObject* pyPhysical_FromPhysical(class plPhysical* phys);

extern PyTypeObject pyGenericPhysical_Type;
PyObject* Init_pyGenericPhysical_Type();
int pyGenericPhysical_Check(PyObject* obj);
PyObject* pyGenericPhysical_FromGenericPhysical(class plGenericPhysical* phys);

}

#endif
