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

#ifndef _PYAUDIBLE_H
#define _PYAUDIBLE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plAudible* fThis;
    bool fPyOwned;
    unsigned short fClsType;
} pyAudible;

typedef struct {
    PyObject_HEAD
    class plAudibleNull* fThis;
    bool fPyOwned;
    unsigned short fClsType;
} pyAudibleNull;

typedef struct {
    PyObject_HEAD
    class plWinAudible* fThis;
    bool fPyOwned;
    unsigned short fClsType;
} pyWinAudible;

typedef struct {
    PyObject_HEAD
    class pl2WayWinAudible* fThis;
    bool fPyOwned;
    unsigned short fClsType;
} py2WayWinAudible;

extern PyTypeObject pyAudible_Type;
PyObject* Init_pyAudible_Type();
int pyAudible_Check(PyObject* obj);
PyObject* pyAudible_FromAudible(class plAudible* obj);

extern PyTypeObject pyAudibleNull_Type;
PyObject* Init_pyAudibleNull_Type();
int pyAudibleNull_Check(PyObject* obj);
PyObject* pyAudibleNull_FromAudibleNull(class plAudibleNull* obj);

extern PyTypeObject pyWinAudible_Type;
PyObject* Init_pyWinAudible_Type();
int pyWinAudible_Check(PyObject* obj);
PyObject* pyWinAudible_FromWinAudible(class plWinAudible* obj);

extern PyTypeObject py2WayWinAudible_Type;
PyObject* Init_py2WayWinAudible_Type();
int py2WayWinAudible_Check(PyObject* obj);
PyObject* py2WayWinAudible_From2WayWinAudible(class pl2WayWinAudible* obj);

}

#endif
