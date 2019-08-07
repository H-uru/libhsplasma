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

#include <PRP/GUI/plImageLibMod.h>
#include "pyImageLibMod.h"
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(ImageLibMod, plImageLibMod)

PY_METHOD_VA(ImageLibMod, addImage,
    "Params: image key\n"
    "Add an image to the library")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addImage expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addImage expects a plKey");
        return nullptr;
    }
    self->fThis->addImage(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ImageLibMod, delImage,
    "Params: idx\n"
    "Remove an image from the library")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delImage expects an int");
        return nullptr;
    }
    self->fThis->delImage(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ImageLibMod, clearImages,
    "Remove all images from the library")
{
    self->fThis->clearImages();
    Py_RETURN_NONE;
}

static PyMethodDef pyImageLibMod_Methods[] = {
    pyImageLibMod_addImage_method,
    pyImageLibMod_delImage_method,
    pyImageLibMod_clearImages_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(ImageLibMod, images)
{
    PyObject* list = PyTuple_New(self->fThis->getImages().size());
    for (size_t i = 0; i<self->fThis->getImages().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getImages()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(ImageLibMod, images, "To add images, use addImage()")
PY_PROPERTY_GETSET_DECL(ImageLibMod, images)

static PyGetSetDef pyImageLibMod_GetSet[] = {
    pyImageLibMod_images_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ImageLibMod, pfImageLibMod, "plImageLibMod wrapper")

PY_PLASMA_TYPE_INIT(ImageLibMod)
{
    pyImageLibMod_Type.tp_new = pyImageLibMod_new;
    pyImageLibMod_Type.tp_methods = pyImageLibMod_Methods;
    pyImageLibMod_Type.tp_getset = pyImageLibMod_GetSet;
    pyImageLibMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyImageLibMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyImageLibMod_Type);
    return (PyObject*)&pyImageLibMod_Type;
}

PY_PLASMA_IFC_METHODS(ImageLibMod, plImageLibMod)
