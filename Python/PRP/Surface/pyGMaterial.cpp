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

#include "pyGMaterial.h"

#include <PRP/Surface/hsGMaterial.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Object/pySynchedObject.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(GMaterial, hsGMaterial)

PY_METHOD_NOARGS(GMaterial, clearLayers, "Remove all layer keys from the material")
{
    self->fThis->clearLayers();
    Py_RETURN_NONE;
}

PY_METHOD_VA(GMaterial, addLayer,
    "Params: key\n"
    "Add a layer to the material")
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

PY_METHOD_VA(GMaterial, delLayer,
    "Params: idx\n"
    "Remove a layer from the material")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delLayer expects an int");
        return nullptr;
    }
    self->fThis->delLayer(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GMaterial, clearPiggyBacks,
    "Remove all piggy back keys from the material")
{
    self->fThis->clearPiggyBacks();
    Py_RETURN_NONE;
}

PY_METHOD_VA(GMaterial, addPiggyBack,
    "Params: key\n"
    "Add a piggy back to the material")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addPiggyBack expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addPiggyBack expects a plKey");
        return nullptr;
    }
    self->fThis->addPiggyBack(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GMaterial, delPiggyBack,
    "Params: idx\n"
    "Remove a piggy back from the material")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPiggyBack expects an int");
        return nullptr;
    }
    self->fThis->delPiggyBack(idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyGMaterial_Methods[] = {
    pyGMaterial_clearLayers_method,
    pyGMaterial_addLayer_method,
    pyGMaterial_delLayer_method,
    pyGMaterial_clearPiggyBacks_method,
    pyGMaterial_addPiggyBack_method,
    pyGMaterial_delPiggyBack_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(GMaterial, layers)
{
    PyObject* list = PyTuple_New(self->fThis->getLayers().size());
    for (size_t i=0; i<self->fThis->getLayers().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getLayers()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(GMaterial, layers, "To add layers, use addLayer()")
PY_PROPERTY_GETSET_DECL(GMaterial, layers)

PY_GETSET_GETTER_DECL(GMaterial, piggyBacks)
{
    PyObject* list = PyTuple_New(self->fThis->getPiggyBacks().size());
    for (size_t i=0; i<self->fThis->getPiggyBacks().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getPiggyBacks()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(GMaterial, piggyBacks, "To add piggy-backs, use addPiggyBack()")
PY_PROPERTY_GETSET_DECL(GMaterial, piggyBacks)

PY_PROPERTY(unsigned int, GMaterial, compFlags, getCompFlags, setCompFlags)
PY_PROPERTY(unsigned int, GMaterial, loadFlags, getLoadFlags, setLoadFlags)

static PyGetSetDef pyGMaterial_GetSet[] = {
    pyGMaterial_layers_getset,
    pyGMaterial_piggyBacks_getset,
    pyGMaterial_compFlags_getset,
    pyGMaterial_loadFlags_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GMaterial, hsGMaterial, "hsGMaterial wrapper")

PY_PLASMA_TYPE_INIT(GMaterial)
{
    pyGMaterial_Type.tp_new = pyGMaterial_new;
    pyGMaterial_Type.tp_methods = pyGMaterial_Methods;
    pyGMaterial_Type.tp_getset = pyGMaterial_GetSet;
    pyGMaterial_Type.tp_base = &pySynchedObject_Type;
    if (PyType_CheckAndReady(&pyGMaterial_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(GMaterial, "kCompShaded", hsGMaterial::kCompShaded);
    PY_TYPE_ADD_CONST(GMaterial, "kCompEnvironMap", hsGMaterial::kCompEnvironMap);
    PY_TYPE_ADD_CONST(GMaterial, "kCompProjectOnto", hsGMaterial::kCompProjectOnto);
    PY_TYPE_ADD_CONST(GMaterial, "kCompSoftShadow", hsGMaterial::kCompSoftShadow);
    PY_TYPE_ADD_CONST(GMaterial, "kCompSpecular", hsGMaterial::kCompSpecular);
    PY_TYPE_ADD_CONST(GMaterial, "kCompTwoSided", hsGMaterial::kCompTwoSided);
    PY_TYPE_ADD_CONST(GMaterial, "kCompDrawAsSplats", hsGMaterial::kCompDrawAsSplats);
    PY_TYPE_ADD_CONST(GMaterial, "kCompAdjusted", hsGMaterial::kCompAdjusted);
    PY_TYPE_ADD_CONST(GMaterial, "kCompNoSoftShadow", hsGMaterial::kCompNoSoftShadow);
    PY_TYPE_ADD_CONST(GMaterial, "kCompDynamic", hsGMaterial::kCompDynamic);
    PY_TYPE_ADD_CONST(GMaterial, "kCompDecal", hsGMaterial::kCompDecal);
    PY_TYPE_ADD_CONST(GMaterial, "kCompIsEmissive", hsGMaterial::kCompIsEmissive);
    PY_TYPE_ADD_CONST(GMaterial, "kCompIsLightMapped", hsGMaterial::kCompIsLightMapped);
    PY_TYPE_ADD_CONST(GMaterial, "kCompNeedsBlendChannel", hsGMaterial::kCompNeedsBlendChannel);

    Py_INCREF(&pyGMaterial_Type);
    return (PyObject*)&pyGMaterial_Type;
}

PY_PLASMA_IFC_METHODS(GMaterial, hsGMaterial)
