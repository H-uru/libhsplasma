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

#ifndef _PYSOUNDBUFFER_H
#define _PYSOUNDBUFFER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plWAVHeader* fThis;
    bool fPyOwned;
} pyWAVHeader;

typedef struct {
    PyObject_HEAD
    class plSoundBuffer* fThis;
    bool fPyOwned;
} pySoundBuffer;

extern PyTypeObject pyWAVHeader_Type;
PyObject* Init_pyWAVHeader_Type();
int pyWAVHeader_Check(PyObject* obj);
PyObject* pyWAVHeader_FromWAVHeader(class plWAVHeader& header);

extern PyTypeObject pySoundBuffer_Type;
PyObject* Init_pySoundBuffer_Type();
int pySoundBuffer_Check(PyObject* obj);
PyObject* pySoundBuffer_FromSoundBuffer(class plSoundBuffer* buf);

}

#endif
