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

#ifndef _PYRESPONDERMODIFIER_H
#define _PYRESPONDERMODIFIER_H

#include <PRP/Modifier/plResponderModifier.h>

extern "C" {

typedef struct {
    PyObject_HEAD
    class plResponderModifier::plResponderCmd* fThis;
    bool fPyOwned;
} pyResponderModifier_Cmd;

typedef struct {
    PyObject_HEAD
    class plResponderModifier::plResponderState* fThis;
    bool fPyOwned;
} pyResponderModifier_State;

typedef struct {
    PyObject_HEAD
    class plResponderModifier* fThis;
    bool fPyOwned;
} pyResponderModifier;

typedef struct {
    PyObject_HEAD
    class plResponderEnableMsg* fThis;
    bool fPyOwned;
} pyResponderEnableMsg;

extern PyTypeObject pyResponderModifier_Cmd_Type;
PyObject* Init_pyResponderModifier_Cmd_Type();
int pyResponderModifier_Cmd_Check(PyObject* obj);
PyObject* pyResponderModifier_Cmd_FromResponderCmd(class plResponderModifier::plResponderCmd* cmd);

extern PyTypeObject pyResponderModifier_State_Type;
PyObject* Init_pyResponderModifier_State_Type();
int pyResponderModifier_State_Check(PyObject* obj);
PyObject* pyResponderModifier_State_FromResponderState(class plResponderModifier::plResponderState* state);

extern PyTypeObject pyResponderModifier_Type;
PyObject* Init_pyResponderModifier_Type();
int pyResponderModifier_Check(PyObject* obj);
PyObject* pyResponderModifier_FromResponderModifier(class plResponderModifier* mod);

extern PyTypeObject pyResponderEnableMsg_Type;
PyObject* Init_pyResponderEnableMsg_Type();
int pyResponderEnableMsg_Check(PyObject* obj);
PyObject* pyResponderEnableMsg_FromResponderEnableMsg(class plResponderEnableMsg* mod);

}

#endif
