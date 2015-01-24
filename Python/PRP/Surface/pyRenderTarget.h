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

#ifndef _PYRENDERTARGET_H
#define _PYRENDERTARGET_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plRenderTarget* fThis;
    bool fPyOwned;
} pyRenderTarget;

typedef struct {
    PyObject_HEAD
    class plCubicRenderTarget* fThis;
    bool fPyOwned;
} pyCubicRenderTarget;

extern PyTypeObject pyRenderTarget_Type;
PyObject* Init_pyRenderTarget_Type();
int pyRenderTarget_Check(PyObject* obj);
PyObject* pyRenderTarget_FromRenderTarget(class plRenderTarget* rt);

extern PyTypeObject pyCubicRenderTarget_Type;
PyObject* Init_pyCubicRenderTarget_Type();
int pyCubicRenderTarget_Check(PyObject* obj);
PyObject* pyCubicRenderTarget_FromCubicRenderTarget(class plCubicRenderTarget* crt);

}

#endif
