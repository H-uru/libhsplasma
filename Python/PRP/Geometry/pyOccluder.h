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

#ifndef _PYOCCLUDER_H
#define _PYOCCLUDER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plCullPoly* fThis;
} pyCullPoly;

typedef struct {
    PyObject_HEAD
    class plOccluder* fThis;
    bool fPyOwned;
} pyOccluder;

typedef struct {
    PyObject_HEAD
    class plMobileOccluder* fThis;
    bool fPyOwned;
} pyMobileOccluder;

extern PyTypeObject pyCullPoly_Type;
PyObject* Init_pyCullPoly_Type();
int pyCullPoly_Check(PyObject* obj);
PyObject* pyCullPoly_FromCullPoly(const plCullPoly& poly);

extern PyTypeObject pyOccluder_Type;
PyObject* Init_pyOccluder_Type();
int pyOccluder_Check(PyObject* obj);
PyObject* pyOccluder_FromOccluder(class plOccluder* obj);

extern PyTypeObject pyMobileOccluder_Type;
PyObject* Init_pyMobileOccluder_Type();
int pyMobileOccluder_Check(PyObject* obj);
PyObject* pyMobileOccluder_FromMobileOccluder(class plMobileOccluder* obj);

}

#endif
