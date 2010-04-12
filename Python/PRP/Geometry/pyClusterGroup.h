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

#ifndef _PYCLUSTERGROUP_H
#define _PYCLUSTERGROUP_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLODDist* fThis;
} pyLODDist;

typedef struct {
    PyObject_HEAD
    class plClusterGroup* fThis;
    bool fPyOwned;
} pyClusterGroup;

extern PyTypeObject pyLODDist_Type;
PyObject* Init_pyLODDist_Type();
PyObject* pyLODDist_FromLODDist(class plLODDist& dist);

extern PyTypeObject pyClusterGroup_Type;
PyObject* Init_pyClusterGroup_Type();
int pyClusterGroup_Check(PyObject* obj);
PyObject* pyClusterGroup_FromClusterGroup(class plClusterGroup* group);

}

#endif
