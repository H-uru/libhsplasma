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

#include "pyPNG.h"

#include "PRP/Surface/pyBitmap.h"
#include "Stream/pyStream.h"

#include <Util/plPNG.h>

PY_PLASMA_EMPTY_INIT(PNG)
PY_PLASMA_NEW_MSG(PNG, "plPNG cannot be constructed")

PY_METHOD_STATIC_VA(PNG, DecompressPNG,
    "Params: stream\n"
    "Read PNG file from stream directly into a plMipmap")
{
    PyObject* streamObj;
    if (!PyArg_ParseTuple(args, "O", &streamObj)) {
        PyErr_SetString(PyExc_TypeError, "DecompressPNG expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check(streamObj)) {
        PyErr_SetString(PyExc_TypeError, "DecompressPNG expects an hsStream");
        return nullptr;
    }

    plMipmap* mm = nullptr;
    try {
        mm = plPNG::DecompressPNG(((pyStream*)streamObj)->fThis);
    } catch (const hsPNGException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return nullptr;
    }

    // We're doing this manually because the new Mipmap object is being
    // released to Python code.
    pyMipmap* mmObj = PyObject_New(pyMipmap, &pyMipmap_Type);
    mmObj->fPyOwned = true;
    mmObj->fThis = mm;
    return (PyObject*)mmObj;
}

static PyMethodDef pyPNG_Methods[] = {
    pyPNG_DecompressPNG_method,
    PY_METHOD_TERMINATOR,
};

PY_PLASMA_TYPE(PNG, plPNG, "plPNG wrapper")

PY_PLASMA_TYPE_INIT(PNG)
{
    pyPNG_Type.tp_new = pyPNG_new;
    pyPNG_Type.tp_methods = pyPNG_Methods;
    if (PyType_CheckAndReady(&pyPNG_Type) < 0)
        return nullptr;

    Py_INCREF(&pyPNG_Type);
    return (PyObject*)&pyPNG_Type;
}
