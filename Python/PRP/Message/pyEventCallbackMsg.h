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

#ifndef _PYEVENTCALLBACKMSG_H
#define _PYEVENTCALLBACKMSG_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plEventCallbackMsg* fThis;
    bool fPyOwned;
} pyEventCallbackMsg;

extern PyTypeObject pyEventCallbackMsg_Type;
PyObject* Init_pyEventCallbackMsg_Type();
int pyEventCallbackMsg_Check(PyObject* obj);
PyObject* pyEventCallbackMsg_FromEventCallbackMsg(class plEventCallbackMsg* msg);

}

#endif
