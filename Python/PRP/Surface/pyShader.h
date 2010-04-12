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

#ifndef _PYSHADER_H
#define _PYSHADER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plShaderConst* fThis;
} pyShaderConst;

typedef struct {
    PyObject_HEAD
    class plShader* fThis;
    bool fPyOwned;
} pyShader;

extern PyTypeObject pyShaderConst_Type;
PyObject* Init_pyShaderConst_Type();
int pyShaderConst_Check(PyObject* obj);
PyObject* pyShaderConst_FromShaderConst(const class plShaderConst& sc);

extern PyTypeObject pyShader_Type;
PyObject* Init_pyShader_Type();
int pyShader_Check(PyObject* obj);
PyObject* pyShader_FromShader(class plShader* shader);

}

#endif
