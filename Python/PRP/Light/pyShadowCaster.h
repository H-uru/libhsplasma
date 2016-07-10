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

#ifndef _PYSHADOWCASTER_H
#define _PYSHADOWCASTER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plShadowCaster* fThis;
    bool fPyOwned;
} pyShadowCaster;

extern PyTypeObject pyShadowCaster_Type;
PyObject* Init_pyShadowCaster_Type();
int pyShadowCaster_Check(PyObject* obj);
PyObject* pyShadowCaster_FromShadowCaster(class plShadowCaster* obj);

}

#endif
