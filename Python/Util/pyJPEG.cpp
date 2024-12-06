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

#include "pyJPEG.h"

#include "PRP/Surface/pyBitmap.h"
#include "Stream/pyStream.h"

#include <Util/plJPEG.h>

PY_PLASMA_EMPTY_INIT(JPEG)
PY_PLASMA_NEW_MSG(JPEG, "plJPEG cannot be constructed")

PY_METHOD_STATIC_VA(JPEG, DecompressJPEG,
    "Params: stream\n"
    "Read JPEG file from stream directly into a plMipmap")
{
    PyObject* streamObj;
    if (!PyArg_ParseTuple(args, "O", &streamObj)) {
        PyErr_SetString(PyExc_TypeError, "DecompressJPEG expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check(streamObj)) {
        PyErr_SetString(PyExc_TypeError, "DecompressJPEG expects an hsStream");
        return nullptr;
    }

    plMipmap* mm = plJPEG::DecompressJPEG(((pyStream*)streamObj)->fThis);

    // We're doing this manually because the new Mipmap object is being
    // released to Python code.
    pyMipmap* mmObj = nullptr;
    try {
        mmObj = PyObject_New(pyMipmap, &pyMipmap_Type);
    } catch (const hsJPEGException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return nullptr;
    }
    mmObj->fPyOwned = true;
    mmObj->fThis = mm;
    return (PyObject*)mmObj;
}

static PyMethodDef pyJPEG_Methods[] = {
    pyJPEG_DecompressJPEG_method,
    PY_METHOD_TERMINATOR,
};

PY_PLASMA_TYPE(JPEG, plJPEG, "plJPEG wrapper")

PY_PLASMA_TYPE_INIT(JPEG)
{
    pyJPEG_Type.tp_new = pyJPEG_new;
    pyJPEG_Type.tp_methods = pyJPEG_Methods;
    if (PyType_CheckAndReady(&pyJPEG_Type) < 0)
        return nullptr;

    Py_INCREF(&pyJPEG_Type);
    return (PyObject*)&pyJPEG_Type;
}
