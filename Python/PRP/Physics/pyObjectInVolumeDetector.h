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

#ifndef _PY_OBJECTINVOLUMEDETECTOR_H
#define _PY_OBJECTINVOLUMEDETECTOR_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plObjectInVolumeDetector* fThis;
    bool fPyOwned;
} pyObjectInVolumeDetector;

extern PyTypeObject pyObjectInVolumeDetector_Type;
PyObject* Init_pyObjectInVolumeDetector_Type();
int pyObjectInVolumeDetector_Check(PyObject* obj);
PyObject* pyObjectInVolumeDetector_FromObjectInVolumeDetector(class plObjectInVolumeDetector* obj);

typedef struct {
    PyObject_HEAD
    class plObjectInVolumeAndFacingDetector* fThis;
    bool fPyOwned;
} pyObjectInVolumeAndFacingDetector;

extern PyTypeObject pyObjectInVolumeAndFacingDetector_Type;
PyObject* Init_pyObjectInVolumeAndFacingDetector_Type();
int pyObjectInVolumeAndFacingDetector_Check(PyObject* obj);
PyObject* pyObjectInVolumeAndFacingDetector_FromObjectInVolumeAndFacingDetector(class plObjectInVolumeAndFacingDetector* obj);

};

#endif
