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

#ifndef _PYSOUND_H
#define _PYSOUND_H

// Nested struct :(
#include <PRP/Audio/plSound.h>

extern "C" {

typedef struct {
    PyObject_HEAD
    class plSound::plFadeParams* fThis;
} pyFadeParams;

typedef struct {
    PyObject_HEAD
    class plSound* fThis;
    bool fPyOwned;
} pySound;

extern PyTypeObject pyFadeParams_Type;
PyObject* Init_pyFadeParams_Type();
PyObject* pyFadeParams_FromFadeParams(class plSound::plFadeParams& params);

extern PyTypeObject pySound_Type;
PyObject* Init_pySound_Type();
int pySound_Check(PyObject* obj);
PyObject* pySound_FromSound(class plSound* sound);

}

#endif
