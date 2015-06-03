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

#ifndef _PY_DETECTORMODIFIER_H
#define _PY_DETECTORMODIFIER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plDetectorModifier* fThis;
    bool fPyOwned;
} pyDetectorModifier;

extern PyTypeObject pyDetectorModifier_Type;
PyObject* Init_pyDetectorModifier_Type();
int pyDetectorModifier_Check(PyObject* obj);
PyObject* pyDetectorModifier_FromDetectorModifier(class plDetectorModifier* obj);

typedef struct {
    PyObject_HEAD
    class plPickingDetector* fThis;
    bool fPyOwned;
} pyPickingDetector;

extern PyTypeObject pyPickingDetector_Type;
PyObject* Init_pyPickingDetector_Type();
int pyPickingDetector_Check(PyObject* obj);
PyObject* pyPickingDetector_FromPickingDetector(class plPickingDetector* obj);

}

#endif
