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

#ifndef _PYDRAWABLESPANS_H
#define _PYDRAWABLESPANS_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plDISpanIndex* fThis;
} pyDISpanIndex;

typedef struct {
    PyObject_HEAD
    class plDrawable* fThis;
    bool fPyOwned;
} pyDrawable;

typedef struct {
    PyObject_HEAD
    class plDrawableSpans* fThis;
    bool fPyOwned;
} pyDrawableSpans;

extern PyTypeObject pyDISpanIndex_Type;
PyObject* Init_pyDISpanIndex_Type();
int pyDISpanIndex_Check(PyObject* obj);
PyObject* pyDISpanIndex_FromDISpanIndex(const class plDISpanIndex& idx);

extern PyTypeObject pyDrawable_Type;
PyObject* Init_pyDrawable_Type();
int pyDrawable_Check(PyObject* obj);
PyObject* pyDrawable_FromDrawable(class plDrawable* draw);

extern PyTypeObject pyDrawableSpans_Type;
PyObject* Init_pyDrawableSpans_Type();
int pyDrawableSpans_Check(PyObject* obj);
PyObject* pyDrawableSpans_FromDrawableSpans(class plDrawableSpans* draw);

};

#endif
