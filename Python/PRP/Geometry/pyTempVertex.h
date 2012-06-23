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

#ifndef _PYTEMPVERTEX_H
#define _PYTEMPVERTEX_H

// Nested struct :(
#include <PRP/Geometry/plGeometrySpan.h>

extern "C" {

typedef struct {
    PyObject_HEAD
    plGeometrySpan::TempVertex* fThis;
    bool fPyOwned;
} pyTempVertex;

extern PyTypeObject pyTempVertex_Type;
PyObject* Init_pyTempVertex_Type();
int pyTempVertex_Check(PyObject* obj);
PyObject* pyTempVertex_FromTempVertex(const plGeometrySpan::TempVertex& vtx);

};

#endif
