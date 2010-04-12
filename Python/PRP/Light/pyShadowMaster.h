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

#ifndef _PYSHADOWMASTER_H
#define _PYSHADOWMASTER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plShadowMaster* fThis;
    bool fPyOwned;
} pyShadowMaster;

typedef struct {
    PyObject_HEAD
    class plPointShadowMaster* fThis;
    bool fPyOwned;
} pyPointShadowMaster;

typedef struct {
    PyObject_HEAD
    class plDirectShadowMaster* fThis;
    bool fPyOwned;
} pyDirectShadowMaster;

extern PyTypeObject pyShadowMaster_Type;
PyObject* Init_pyShadowMaster_Type();
int pyShadowMaster_Check(PyObject* obj);
PyObject* pyShadowMaster_FromShadowMaster(class plShadowMaster* obj);

extern PyTypeObject pyPointShadowMaster_Type;
PyObject* Init_pyPointShadowMaster_Type();
int pyPointShadowMaster_Check(PyObject* obj);
PyObject* pyPointShadowMaster_FromPointShadowMaster(class plPointShadowMaster* obj);

extern PyTypeObject pyDirectShadowMaster_Type;
PyObject* Init_pyDirectShadowMaster_Type();
int pyDirectShadowMaster_Check(PyObject* obj);
PyObject* pyDirectShadowMaster_FromDirectShadowMaster(class plDirectShadowMaster* obj);

}

#endif
