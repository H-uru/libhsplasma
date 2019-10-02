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

#include "pySDL.h"

#include <SDL/plSDLMgr.h>
#include "Stream/pyStream.h"

PY_PLASMA_DEALLOC(SDLMgr)
PY_PLASMA_EMPTY_INIT(SDLMgr)
PY_PLASMA_NEW(SDLMgr, plSDLMgr)

PY_METHOD_VA(SDLMgr, readDescriptors,
    "Params: filename or stream\n"
    "Reads SDL Descriptors from the provided filename or stream")
{
    ST::string filename;
    if (PyArg_ParseTuple(args, "O&", PyAnyString_PathDecoder, &filename)) {
        try {
            self->fThis->ReadDescriptors(filename);
        } catch (const hsException& ex) {
            PyErr_SetString(PyExc_IOError, ex.what());
            return nullptr;
        }
        Py_RETURN_NONE;
    }

    PyObject* stream;
    if (PyErr_Clear(), PyArg_ParseTuple(args, "O", &stream) && pyStream_Check(stream)) {
        try {
            self->fThis->ReadDescriptors(((pyStream*)stream)->fThis);
        } catch (const hsException& ex) {
            PyErr_SetString(PyExc_IOError, ex.what());
            return nullptr;
        }
        Py_RETURN_NONE;
    }

    PyErr_SetString(PyExc_TypeError, "readDescriptors expects a string, an hsStream, or an os.PathLike object");
    return nullptr;
}

PY_METHOD_NOARGS(SDLMgr, clearDescriptors,
    "Removes all SDL Descriptors")
{
    self->fThis->ClearDescriptors();
    Py_RETURN_NONE;
}

PY_METHOD_VA(SDLMgr, getDescriptor,
    "Params: name, version\n"
    "Gets a state descriptor by version, where version -1 is the latest")
{
    PyObject* name;
    int version = -1;
    if (!PyArg_ParseTuple(args, "O|i", &name, &version) || !pyPlasma_check<ST::string>(name)) {
        PyErr_SetString(PyExc_TypeError, "getDescriptor expects a string and an optional int");
        return nullptr;
    }

    return pyStateDescriptor_FromStateDescriptor(self->fThis->GetDescriptor(pyPlasma_get<ST::string>(name), version));
}

static PyMethodDef pySDLMgr_Methods[] = {
    pySDLMgr_readDescriptors_method,
    pySDLMgr_clearDescriptors_method,
    pySDLMgr_getDescriptor_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(SDLMgr, descriptorNames)
{
    auto descs = self->fThis->GetDescriptorNames();
    PyObject* tup = PyTuple_New(descs.size());
    for (size_t i = 0; i < descs.size(); ++i)
        PyTuple_SET_ITEM(tup, i, PyString_FromSTString(descs[i]));
    return tup;
}

PY_PROPERTY_GETSET_RO_DECL(SDLMgr, descriptorNames);

static PyGetSetDef pySDLMgr_GetSet[] = {
    pySDLMgr_descriptorNames_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SDLMgr, plSDLMgr, "plSDLMgr wrapper")

PY_PLASMA_TYPE_INIT(SDLMgr)
{
    pySDLMgr_Type.tp_dealloc = pySDLMgr_dealloc;
    pySDLMgr_Type.tp_init = pySDLMgr___init__;
    pySDLMgr_Type.tp_new = pySDLMgr_new;
    pySDLMgr_Type.tp_methods = pySDLMgr_Methods;
    pySDLMgr_Type.tp_getset = pySDLMgr_GetSet;
    if (PyType_CheckAndReady(&pySDLMgr_Type) < 0)
        return nullptr;

    Py_INCREF(&pySDLMgr_Type);
    return (PyObject*)& pySDLMgr_Type;
}

PY_PLASMA_IFC_METHODS(SDLMgr, plSDLMgr)
