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

#ifndef _PYRESPONDERMSG_H
#define _PYRESPONDERMSG_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plResponderMsg* fThis;
    bool fPyOwned;
} pyResponderMsg;

extern PyTypeObject pyResponderMsg_Type;
PyObject* Init_pyResponderMsg_Type();
int pyResponderMsg_Check(PyObject* obj);
PyObject* pyResponderMsg_FromResponderMsg(class plResponderMsg* msg);

typedef struct {
    PyObject_HEAD
    class plOneShotMsg* fThis;
    bool fPyOwned;
} pyOneShotMsg;

extern PyTypeObject pyOneShotMsg_Type;
PyObject* Init_pyOneShotMsg_Type();
int pyOneShotMsg_Check(PyObject* obj);
PyObject* pyOneShotMsg_FromOneShotMsg(class plOneShotMsg* msg);

}

#endif
