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

#ifndef _PYAGELINKINFO_H
#define _PYAGELINKINFO_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plAgeLinkStruct* fThis;
    bool fPyOwned;
} pyAgeLinkStruct;

PyObject* Init_pyAgeLinkStruct_Type();
int pyAgeLinkStruct_Check(PyObject* obj);
PyObject* pyAgeLinkStruct_FromAgeLinkStruct(plAgeLinkStruct* als);

}

#endif