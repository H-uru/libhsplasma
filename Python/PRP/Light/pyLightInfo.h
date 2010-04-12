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

#ifndef _PYLIGHTINFO_H
#define _PYLIGHTINFO_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLightInfo* fThis;
    bool fPyOwned;
} pyLightInfo;

typedef struct {
    PyObject_HEAD
    class plDirectionalLightInfo* fThis;
    bool fPyOwned;
} pyDirectionalLightInfo;

typedef struct {
    PyObject_HEAD
    class plLimitedDirLightInfo* fThis;
    bool fPyOwned;
} pyLimitedDirLightInfo;

typedef struct {
    PyObject_HEAD
    class plOmniLightInfo* fThis;
    bool fPyOwned;
} pyOmniLightInfo;

typedef struct {
    PyObject_HEAD
    class plSpotLightInfo* fThis;
    bool fPyOwned;
} pySpotLightInfo;

extern PyTypeObject pyLightInfo_Type;
PyObject* Init_pyLightInfo_Type();
int pyLightInfo_Check(PyObject* obj);
PyObject* pyLightInfo_FromLightInfo(class plLightInfo* light);

extern PyTypeObject pyDirectionalLightInfo_Type;
PyObject* Init_pyDirectionalLightInfo_Type();
int pyDirectionalLightInfo_Check(PyObject* obj);
PyObject* pyDirectionalLightInfo_FromDirectionalLightInfo(class plDirectionalLightInfo* light);

extern PyTypeObject pyLimitedDirLightInfo_Type;
PyObject* Init_pyLimitedDirLightInfo_Type();
int pyLimitedDirLightInfo_Check(PyObject* obj);
PyObject* pyLimitedDirLightInfo_FromLimitedDirLightInfo(class plLimitedDirLightInfo* light);

extern PyTypeObject pyOmniLightInfo_Type;
PyObject* Init_pyOmniLightInfo_Type();
int pyOmniLightInfo_Check(PyObject* obj);
PyObject* pyOmniLightInfo_FromOmniLightInfo(class plOmniLightInfo* light);

extern PyTypeObject pySpotLightInfo_Type;
PyObject* Init_pySpotLightInfo_Type();
int pySpotLightInfo_Check(PyObject* obj);
PyObject* pySpotLightInfo_FromSpotLightInfo(class plSpotLightInfo* light);

}

#endif
