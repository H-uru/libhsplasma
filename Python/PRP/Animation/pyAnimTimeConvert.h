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

#ifndef _PYANIMTIMECONVERT_H
#define _PYANIMTIMECONVERT_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plAnimTimeConvert* fThis;
    bool fPyOwned;
} pyAnimTimeConvert;

extern PyTypeObject pyAnimTimeConvert_Type;
PyObject* Init_pyAnimTimeConvert_Type();
int pyAnimTimeConvert_Check(PyObject* obj);
PyObject* pyAnimTimeConvert_FromAnimTimeConvert(class plAnimTimeConvert* atc);

}

#endif
