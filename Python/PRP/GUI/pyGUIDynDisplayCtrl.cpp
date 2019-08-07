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

#include <PRP/GUI/pfGUIDynDisplayCtrl.h>
#include "pyGUIDynDisplayCtrl.h"
#include "PRP/GUI/pyGUIControlMod.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(GUIDynDisplayCtrl, pfGUIDynDisplayCtrl)

PY_METHOD_VA(GUIDynDisplayCtrl, addTextMap,
    "Params: animation key\n"
    "Add a text map to the dynamic display control")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addTextMap expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addTextMap expects a plKey");
        return nullptr;
    }
    self->fThis->addTextMap(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIDynDisplayCtrl, delTextMap,
    "Params: idx\n"
    "Remove a text map from the dynamic display control")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delTextMap expects an int");
        return nullptr;
    }
    self->fThis->delTextMap(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GUIDynDisplayCtrl, clearTextMaps,
    "Remove all text maps from the dynamic display control")
{
    self->fThis->clearTextMaps();
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIDynDisplayCtrl, addLayer,
    "Params: animation key\n"
    "Add a layer to the dynamic display control")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addLayer expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addLayer expects a plKey");
        return nullptr;
    }
    self->fThis->addLayer(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIDynDisplayCtrl, delLayer,
    "Params: idx\n"
    "Remove a layer from the dynamic display control")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delLayer expects an int");
        return nullptr;
    }
    self->fThis->delLayer(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GUIDynDisplayCtrl, clearLayers,
    "Remove all layers from the dynamic display control")
{
    self->fThis->clearLayers();
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIDynDisplayCtrl, addMaterial,
    "Params: animation key\n"
    "Add a material to the dynamic display control")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addMaterial expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addMaterial expects a plKey");
        return nullptr;
    }
    self->fThis->addMaterial(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIDynDisplayCtrl, delMaterial,
    "Params: idx\n"
    "Remove a material from the dynamic display control")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delMaterial expects an int");
        return nullptr;
    }
    self->fThis->delMaterial(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GUIDynDisplayCtrl, clearMaterials,
    "Remove all materials from the dynamic display control")
{
    self->fThis->clearMaterials();
    Py_RETURN_NONE;
}

static PyMethodDef pyGUIDynDisplayCtrl_Methods[] = {
    pyGUIDynDisplayCtrl_addTextMap_method,
    pyGUIDynDisplayCtrl_delTextMap_method,
    pyGUIDynDisplayCtrl_clearTextMaps_method,
    pyGUIDynDisplayCtrl_addLayer_method,
    pyGUIDynDisplayCtrl_delLayer_method,
    pyGUIDynDisplayCtrl_clearLayers_method,
    pyGUIDynDisplayCtrl_addMaterial_method,
    pyGUIDynDisplayCtrl_delMaterial_method,
    pyGUIDynDisplayCtrl_clearMaterials_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(GUIDynDisplayCtrl, textMaps)
{
    PyObject* list = PyTuple_New(self->fThis->getTextMaps().size());
    for (size_t i = 0; i<self->fThis->getTextMaps().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getTextMaps()[i]));
    return list;
}
PY_PROPERTY_SETTER_MSG(GUIDynDisplayCtrl, textMaps, "To add textMaps, use addTextMaps()")
PY_PROPERTY_GETSET_DECL(GUIDynDisplayCtrl, textMaps)

PY_GETSET_GETTER_DECL(GUIDynDisplayCtrl, layers)
{
    PyObject* list = PyTuple_New(self->fThis->getLayers().size());
    for (size_t i = 0; i<self->fThis->getLayers().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getLayers()[i]));
    return list;
}
PY_PROPERTY_SETTER_MSG(GUIDynDisplayCtrl, layers, "To add layers, use addLayer()")
PY_PROPERTY_GETSET_DECL(GUIDynDisplayCtrl, layers)

PY_GETSET_GETTER_DECL(GUIDynDisplayCtrl, materials)
{
    PyObject* list = PyTuple_New(self->fThis->getMaterials().size());
    for (size_t i = 0; i<self->fThis->getMaterials().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getMaterials()[i]));
    return list;
}
PY_PROPERTY_SETTER_MSG(GUIDynDisplayCtrl, materials, "To add materials, use addMaterial()")
PY_PROPERTY_GETSET_DECL(GUIDynDisplayCtrl, materials)

static PyGetSetDef pyGUIDynDisplayCtrl_GetSet[] = {
    pyGUIDynDisplayCtrl_textMaps_getset,
    pyGUIDynDisplayCtrl_layers_getset,
    pyGUIDynDisplayCtrl_materials_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIDynDisplayCtrl, pfGUIDynDisplayCtrl, "pfGUIDynDisplayCtrl wrapper")

PY_PLASMA_TYPE_INIT(GUIDynDisplayCtrl)
{
    pyGUIDynDisplayCtrl_Type.tp_new = pyGUIDynDisplayCtrl_new;
    pyGUIDynDisplayCtrl_Type.tp_methods = pyGUIDynDisplayCtrl_Methods;
    pyGUIDynDisplayCtrl_Type.tp_getset = pyGUIDynDisplayCtrl_GetSet;
    pyGUIDynDisplayCtrl_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_CheckAndReady(&pyGUIDynDisplayCtrl_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGUIDynDisplayCtrl_Type);
    return (PyObject*)&pyGUIDynDisplayCtrl_Type;
}

PY_PLASMA_IFC_METHODS(GUIDynDisplayCtrl, pfGUIDynDisplayCtrl)
