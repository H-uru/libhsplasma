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

#ifndef _PYRESMANAGER_H
#define _PYRESMANAGER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plResManager* fThis;
} pyResManager;

typedef struct {
    PyObject_HEAD
    class plPageInfo* fThis;
    bool fPyOwned;
} pyPageInfo;

typedef struct {
    PyObject_HEAD
    class plAgeInfo* fThis;
    bool fPyOwned;
} pyAgeInfo;

extern PyTypeObject pyResManager_Type;
PyObject* Init_pyResManager_Type();
int pyResManager_Check(PyObject* obj);

extern PyTypeObject pyFactory_Type;
PyObject* Init_pyFactory_Type();

extern PyTypeObject pyPageInfo_Type;
PyObject* Init_pyPageInfo_Type();
int pyPageInfo_Check(PyObject* obj);
PyObject* pyPageInfo_FromPageInfo(class plPageInfo* page);

extern PyTypeObject pyAgeInfo_Type;
PyObject* Init_pyAgeInfo_Type();
int pyAgeInfo_Check(PyObject* obj);
PyObject* pyAgeInfo_FromAgeInfo(class plAgeInfo* page);

}

#endif
