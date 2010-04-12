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

#ifndef _PYMSGFORWARDER_H
#define _PYMSGFORWARDER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plMsgForwarder* fThis;
    bool fPyOwned;
} pyMsgForwarder;

extern PyTypeObject pyMsgForwarder_Type;
PyObject* Init_pyMsgForwarder_Type();
int pyMsgForwarder_Check(PyObject* obj);
PyObject* pyMsgForwarder_FromMsgForwarder(class plMsgForwarder* msg);

}

#endif
