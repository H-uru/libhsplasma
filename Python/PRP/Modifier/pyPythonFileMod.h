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

#ifndef _PYPYTHONFILEMOD_H
#define _PYPYTHONFILEMOD_H

extern "C" {

typedef struct {
    PyObject_HEAD
    struct plPythonParameter* fThis;
} pyPythonParameter;

typedef struct {
    PyObject_HEAD
    class plPythonFileMod* fThis;
    bool fPyOwned;
} pyPythonFileMod;

extern PyTypeObject pyPythonParameter_Type;
PyObject* Init_pyPythonParameter_Type();
int pyPythonParameter_Check(PyObject* obj);
PyObject* pyPythonParameter_FromPythonParameter(const struct plPythonParameter& param);

extern PyTypeObject pyPythonFileMod_Type;
PyObject* Init_pyPythonFileMod_Type();
int pyPythonFileMod_Check(PyObject* obj);
PyObject* pyPythonFileMod_FromPythonFileMod(class plPythonFileMod* mod);

}

#endif
