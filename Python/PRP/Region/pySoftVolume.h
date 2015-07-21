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

#ifndef _PYSOFTVOLUME_H
#define _PYSOFTVOLUME_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plSoftVolume* fThis;
    bool fPyOwned;
} pySoftVolume;

typedef struct {
    PyObject_HEAD
    class plSoftVolumeSimple* fThis;
    bool fPyOwned;
} pySoftVolumeSimple;

extern PyTypeObject pySoftVolume_Type;
PyObject* Init_pySoftVolume_Type();
int pySoftVolume_Check(PyObject*);
PyObject* pySoftVolume_FromSoftVolume(class plSoftVolume*);

extern PyTypeObject pySoftVolumeSimple_Type;
PyObject* Init_pySoftVolumeSimple_Type();
int pySoftVolumeSimple_Check(PyObject*);
PyObject* pySoftVolumeSimple_FromSoftVolumeSimple(class plSoftVolumeSimple*);

}

#endif
