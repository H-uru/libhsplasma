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

#ifndef _PYMATRIX_H
#define _PYMATRIX_H

extern "C" {

typedef struct {
    PyObject_HEAD
    struct hsMatrix33* fThis;
} pyMatrix33;

typedef struct {
    PyObject_HEAD
    struct hsMatrix44* fThis;
} pyMatrix44;

extern PyTypeObject pyMatrix33_Type;
PyObject* Init_pyMatrix33_Type();
int pyMatrix33_Check(PyObject* obj);
PyObject* pyMatrix33_FromMatrix33(const struct hsMatrix33& mat);

extern PyTypeObject pyMatrix44_Type;
PyObject* Init_pyMatrix44_Type();
int pyMatrix44_Check(PyObject* obj);
PyObject* pyMatrix44_FromMatrix44(const struct hsMatrix44& mat);

}

#endif
