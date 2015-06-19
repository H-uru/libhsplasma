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

#ifndef _PY_COLLISIONDETECTOR_H
#define _PY_COLLISIONDETECTOR_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plCollisionDetector* fThis;
    bool fPyOwned;
} pyCollisionDetector;

extern PyTypeObject pyCollisionDetector_Type;
PyObject* Init_pyCollisionDetector_Type();
int pyCollisionDetector_Check(PyObject* obj);
PyObject* pyCollisionDetector_FromCollisionDetector(class plCollisionDetector* obj);

typedef struct {
    PyObject_HEAD
    class plSubworldRegionDetector* fThis;
    bool fPyOwned;
} pySubworldRegionDetector;

extern PyTypeObject pySubworldRegionDetector_Type;
PyObject* Init_pySubworldRegionDetector_Type();
int pySubworldRegionDetector_Check(PyObject* obj);
PyObject* pySubworldRegionDetector_FromSubworldRegionDetector(class plSubworldRegionDetector* obj);

typedef struct {
    PyObject_HEAD
    class plPanicLinkRegion* fThis;
    bool fPyOwned;
} pyPanicLinkRegion;

extern PyTypeObject pyPanicLinkRegion_Type;
PyObject* Init_pyPanicLinkRegion_Type();
int pyPanicLinkRegion_Check(PyObject* obj);
PyObject* pyPanicLinkRegion_FromPanicLinkRegion(class plPanicLinkRegion* obj);

};

#endif
