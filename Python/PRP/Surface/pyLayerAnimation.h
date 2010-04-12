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

#ifndef _PYLAYERANIMATION_H
#define _PYLAYERANIMATION_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLayerAnimationBase* fThis;
    bool fPyOwned;
} pyLayerAnimationBase;

typedef struct {
    PyObject_HEAD
    class plLayerAnimation* fThis;
    bool fPyOwned;
} pyLayerAnimation;

typedef struct {
    PyObject_HEAD
    class plLayerLinkAnimation* fThis;
    bool fPyOwned;
} pyLayerLinkAnimation;

typedef struct {
    PyObject_HEAD
    class plLayerSDLAnimation* fThis;
    bool fPyOwned;
} pyLayerSDLAnimation;

extern PyTypeObject pyLayerAnimationBase_Type;
PyObject* Init_pyLayerAnimationBase_Type();
int pyLayerAnimationBase_Check(PyObject* obj);
PyObject* pyLayerAnimationBase_FromLayerAnimationBase(class plLayerAnimationBase* layer);

extern PyTypeObject pyLayerAnimation_Type;
PyObject* Init_pyLayerAnimation_Type();
int pyLayerAnimation_Check(PyObject* obj);
PyObject* pyLayerAnimation_FromLayerAnimation(class plLayerAnimation* layer);

extern PyTypeObject pyLayerLinkAnimation_Type;
PyObject* Init_pyLayerLinkAnimation_Type();
int pyLayerLinkAnimation_Check(PyObject* obj);
PyObject* pyLayerLinkAnimation_FromLayerLinkAnimation(class plLayerLinkAnimation* layer);

extern PyTypeObject pyLayerSDLAnimation_Type;
PyObject* Init_pyLayerSDLAnimation_Type();
int pyLayerSDLAnimation_Check(PyObject* obj);
PyObject* pyLayerSDLAnimation_FromLayerSDLAnimation(class plLayerSDLAnimation* layer);

}

#endif
