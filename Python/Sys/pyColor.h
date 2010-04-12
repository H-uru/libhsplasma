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

#ifndef _PYCOLOR_H

extern "C" {

typedef struct {
    PyObject_HEAD
    struct hsColorRGBA* fThis;
} pyColorRGBA;

typedef struct {
    PyObject_HEAD
    struct hsColor32* fThis;
} pyColor32;

extern PyTypeObject pyColorRGBA_Type;
PyObject* Init_pyColorRGBA_Type();
int pyColorRGBA_Check(PyObject* obj);
PyObject* pyColorRGBA_FromColorRGBA(const struct hsColorRGBA& color);

extern PyTypeObject pyColor32_Type;
PyObject* Init_pyColor32_Type();
int pyColor32_Check(PyObject* obj);
PyObject* pyColor32_FromColor32(const struct hsColor32& color);

}

#endif
