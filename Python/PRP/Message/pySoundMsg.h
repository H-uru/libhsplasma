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

#ifndef _PY_SOUNDMSG_H
#define _PY_SOUNDMSG_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plSoundMsg* fThis;
    bool fPyOwned;
} pySoundMsg;

extern PyTypeObject pySoundMsg_Type;
PyObject* Init_pySoundMsg_Type();
int pySoundMsg_Check(PyObject* obj);
PyObject* pySoundMsg_FromSoundMsg(class plSoundMsg* obj);

}

#endif