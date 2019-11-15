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

#include "pyCreatable.h"

#include <PRP/plCreatable.h>
#include <Stream/hsRAMStream.h>
#include "Stream/pyStream.h"
#include "ResManager/pyResManager.h"

PY_PLASMA_DEALLOC(Creatable)
PY_PLASMA_EMPTY_INIT(Creatable)
PY_PLASMA_NEW_MSG(Creatable, "plCreatable is abstract")

PY_METHOD_NOARGS(Creatable, ClassIndex,
    "Returns the Creatable Class Index of this Creatable")
{
    return pyPlasma_convert(self->fThis->ClassIndex());
}

PY_METHOD_VA(Creatable, ClassIndexVer,
    "Params: version\n"
    "Returns the Creatable Class Index of this Creatable for\n"
    "the specified Plasma version")
{
    int ver;
    if (!PyArg_ParseTuple(args, "i", &ver)) {
        PyErr_SetString(PyExc_TypeError, "ClassIndexVer expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->ClassIndex((PlasmaVer)ver));
}

PY_METHOD_NOARGS(Creatable, ClassName,
    "Returns the Creatable Name of this Creatable")
{
    return pyPlasma_convert(self->fThis->ClassName());
}

PY_METHOD_VA(Creatable, ClassInstance,
    "Params: classId\n"
    "Returns true if this Creatable is an instance or subclass\n"
    "of `classId`")
{
    int classId;
    if (!PyArg_ParseTuple(args, "i", &classId)) {
        PyErr_SetString(PyExc_TypeError, "ClassInstance expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->ClassInstance(classId));
}

PY_METHOD_NOARGS(Creatable, isStub,
    "Returns true if this Creatable is a stub (plCreatableStub)")
{
    return pyPlasma_convert(self->fThis->isStub());
}

PY_METHOD_VA(Creatable, read,
    "Params: stream, resManager\n"
    "Read this Creatable from `stream`")
{
    pyStream* stream;
    pyResManager* mgr;
    if (!PyArg_ParseTuple(args, "OO", &stream, &mgr)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plResManager");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyResManager_Check((PyObject*)mgr)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plResManager");
        return nullptr;
    }
    self->fThis->read(stream->fThis, mgr->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Creatable, write,
    "Params: stream, resManager\n"
    "Write this Creatable to `stream`")
{
    pyStream* stream;
    pyResManager* mgr;
    if (!PyArg_ParseTuple(args, "OO", &stream, &mgr)) {
        PyErr_SetString(PyExc_TypeError, "write expects hsStream, plResManager");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyResManager_Check((PyObject*)mgr)) {
        PyErr_SetString(PyExc_TypeError, "write expects hsStream, plResManager");
        return nullptr;
    }
    self->fThis->write(stream->fThis, mgr->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Creatable, toPrc,
    "Params: exclude\n"
    "Writes this creatable to a PRC document and returns it as a string.")
{
    pfPrcHelper::PrcExclude exclude = pfPrcHelper::kNone;
    if (!PyArg_ParseTuple(args, "|i", &exclude)) {
        PyErr_SetString(PyExc_TypeError, "toPrc expects an optional int");
        return nullptr;
    }

    try {
        return pyPlasma_convert(self->fThis->toPrc(exclude));
    } catch (const std::exception& ex) {
        PyErr_SetString(PyExc_IOError, ex.what());
        return nullptr;
    }
}

static PyMethodDef pyCreatable_Methods[] = {
    pyCreatable_ClassIndex_method,
    pyCreatable_ClassIndexVer_method,
    pyCreatable_ClassName_method,
    pyCreatable_ClassInstance_method,
    pyCreatable_isStub_method,
    pyCreatable_read_method,
    pyCreatable_write_method,
    pyCreatable_toPrc_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(Creatable, plCreatable, "plCreatable wrapper")

PY_PLASMA_TYPE_INIT(Creatable)
{
    pyCreatable_Type.tp_dealloc = pyCreatable_dealloc;
    pyCreatable_Type.tp_init = pyCreatable___init__;
    pyCreatable_Type.tp_new = pyCreatable_new;
    pyCreatable_Type.tp_methods = pyCreatable_Methods;
    if (PyType_CheckAndReady(&pyCreatable_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCreatable_Type);
    return (PyObject*)&pyCreatable_Type;
}

PY_PLASMA_IFC_METHODS(Creatable, plCreatable)
