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

#ifndef _PYLAYERMOVIE_H
#define _PYLAYERMOVIE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLayerMovie* fThis;
    bool fPyOwned;
} pyLayerMovie;

typedef struct {
    PyObject_HEAD
    class plLayerAVI* fThis;
    bool fPyOwned;
} pyLayerAVI;

typedef struct {
    PyObject_HEAD
    class plLayerBink* fThis;
    bool fPyOwned;
} pyLayerBink;

extern PyTypeObject pyLayerMovie_Type;
PyObject* Init_pyLayerMovie_Type();
int pyLayerMovie_Check(PyObject* obj);
PyObject* pyLayerMovie_FromLayerMovie(class plLayerMovie* layer);

extern PyTypeObject pyLayerAVI_Type;
PyObject* Init_pyLayerAVI_Type();
int pyLayerAVI_Check(PyObject* obj);
PyObject* pyLayerAVI_FromLayerAVI(class plLayerAVI* layer);

extern PyTypeObject pyLayerBink_Type;
PyObject* Init_pyLayerBink_Type();
int pyLayerBink_Check(PyObject* obj);
PyObject* pyLayerBink_FromLayerBink(class plLayerBink* layer);

}

#endif
