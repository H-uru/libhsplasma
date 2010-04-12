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

#ifndef _PYATCEASECURVES_H
#define _PYATCEASECURVES_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plATCEaseCurve* fThis;
    bool fPyOwned;
} pyATCEaseCurve;

typedef struct {
    PyObject_HEAD
    class plSplineEaseCurve* fThis;
    bool fPyOwned;
} pySplineEaseCurve;

typedef struct {
    PyObject_HEAD
    class plConstAccelEaseCurve* fThis;
    bool fPyOwned;
} pyConstAccelEaseCurve;

extern PyTypeObject pyATCEaseCurve_Type;
PyObject* Init_pyATCEaseCurve_Type();
int pyATCEaseCurve_Check(PyObject* obj);
PyObject* pyATCEaseCurve_FromATCEaseCurve(class plATCEaseCurve* curve);

extern PyTypeObject pySplineEaseCurve_Type;
PyObject* Init_pySplineEaseCurve_Type();
int pySplineEaseCurve_Check(PyObject* obj);
PyObject* pySplineEaseCurve_FromSplineEaseCurve(class plSplineEaseCurve* curve);

extern PyTypeObject pyConstAccelEaseCurve_Type;
PyObject* Init_pyConstAccelEaseCurve_Type();
int pyConstAccelEaseCurve_Check(PyObject* obj);
PyObject* pyConstAccelEaseCurve_FromConstAccelEaseCurve(class plConstAccelEaseCurve* curve);

}

#endif
