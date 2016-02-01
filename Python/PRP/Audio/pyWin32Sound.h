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

#ifndef _PYWIN32SOUND_H
#define _PYWIN32SOUND_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plWin32Sound* fThis;
    bool fPyOwned;
} pyWin32Sound;

typedef struct {
    PyObject_HEAD
    class plWin32StreamingSound* fThis;
    bool fPyOwned;
} pyWin32StreamingSound;

extern PyTypeObject pyWin32Sound_Type;
PyObject* Init_pyWin32Sound_Type();
int pyWin32Sound_Check(PyObject* obj);
PyObject* pyWin32Sound_FromWin32Sound(class plWin32Sound* sound);

extern PyTypeObject pyWin32StreamingSound_Type;
PyObject* Init_pyWin32StreamingSound_Type();
int pyWin32StreamingSound_Check(PyObject* obj);
PyObject* pyWin32StreamingSound_FromWin32StreamingSound(class plWin32StreamingSound* sound);

}

#endif
