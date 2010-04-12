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

#ifndef _PYBOUNDS_H
#define _PYBOUNDS_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsBounds* fThis;
} pyBounds;

typedef struct {
    PyObject_HEAD
    class hsBounds3* fThis;
} pyBounds3;

typedef struct {
    PyObject_HEAD
    class hsBounds3Ext* fThis;
} pyBounds3Ext;

typedef struct {
    PyObject_HEAD
    class hsBoundsOriented* fThis;
} pyBoundsOriented;

extern PyTypeObject pyBounds_Type;
PyObject* Init_pyBounds_Type();
int pyBounds_Check(PyObject* obj);
PyObject* pyBounds_FromBounds(const class hsBounds& bound);

extern PyTypeObject pyBounds3_Type;
PyObject* Init_pyBounds3_Type();
int pyBounds3_Check(PyObject* obj);
PyObject* pyBounds3_FromBounds3(const class hsBounds3& bound);

extern PyTypeObject pyBounds3Ext_Type;
PyObject* Init_pyBounds3Ext_Type();
int pyBounds3Ext_Check(PyObject* obj);
PyObject* pyBounds3Ext_FromBounds3Ext(const class hsBounds3Ext& bound);

extern PyTypeObject pyBoundsOriented_Type;
PyObject* Init_pyBoundsOriented_Type();
int pyBoundsOriented_Check(PyObject* obj);
PyObject* pyBoundsOriented_FromBoundsOriented(const class hsBoundsOriented& bound);

}

#endif
