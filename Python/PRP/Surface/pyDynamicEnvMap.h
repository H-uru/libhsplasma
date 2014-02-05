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

#ifndef _PYDYNAMICENVMAP_H
#define _PYDYNAMICENVMAP_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plDynamicEnvMap* fThis;
    bool fPyOwned;
} pyDynamicEnvMap;

typedef struct {
    PyObject_HEAD
    class plDynamicCamMap* fThis;
    bool fPyOwned;
} pyDynamicCamMap;

extern PyTypeObject pyDynamicEnvMap_Type;
PyObject* Init_pyDynamicEnvMap_Type();
int pyDynamicEnvMap_Check(PyObject* obj);
PyObject* pyDynamicEnvMap_FromDynamicEnvMap(class plDynamicEnvMap* dem);

extern PyTypeObject pyDynamicCamMap_Type;
PyObject* Init_pyDynamicCamMap_Type();
int pyDynamicCamMap_Check(PyObject* obj);
PyObject* pyDynamicCamMap_FromDynamicCamMap(class plDynamicCamMap* dcm);

}

#endif
