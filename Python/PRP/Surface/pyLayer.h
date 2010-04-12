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

#ifndef _PYLAYER_H
#define _PYLAYER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLayerInterface* fThis;
    bool fPyOwned;
} pyLayerInterface;

typedef struct {
    PyObject_HEAD
    class plLayer* fThis;
    bool fPyOwned;
} pyLayer;

typedef struct {
    PyObject_HEAD
    class plLayerDepth* fThis;
    bool fPyOwned;
} pyLayerDepth;

extern PyTypeObject pyLayerInterface_Type;
PyObject* Init_pyLayerInterface_Type();
int pyLayerInterface_Check(PyObject* obj);
PyObject* pyLayerInterface_FromLayerInterface(class plLayerInterface* layer);

extern PyTypeObject pyLayer_Type;
PyObject* Init_pyLayer_Type();
int pyLayer_Check(PyObject* obj);
PyObject* pyLayer_FromLayer(class plLayer* layer);

extern PyTypeObject pyLayerDepth_Type;
PyObject* Init_pyLayerDepth_Type();
int pyLayerDepth_Check(PyObject* obj);
PyObject* pyLayerDepth_FromLayerDepth(class plLayerDepth* layer);

}

#endif
