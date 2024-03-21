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

#include "pyClothingItem.h"

#include <PRP/Avatar/plClothingItem.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"
#include "Sys/pyColor.h"

PY_PLASMA_NEW(ClothingItem, plClothingItem)

PY_METHOD_VA(ClothingItem, getMesh,
    "Params: lod\n"
    "Gets the Key of the mesh for the specified LOD")
{
    Py_ssize_t lod = plClothingItem::kLODHigh;
    if (!PyArg_ParseTuple(args, "n", &lod)) {
        PyErr_SetString(PyExc_TypeError, "getMesh expects int");
        return nullptr;
    }

    if (lod >= 0 && lod < plClothingItem::LODLevels::kNumLODLevels)
        return pyPlasma_convert(self->fThis->getMesh(lod));

    PyErr_SetString(PyExc_IndexError, "mesh index out of range");
    return nullptr;
}

PY_METHOD_VA(ClothingItem, setMesh,
    "Params: lod, mesh\n"
    "Sets the Key of the mesh for the specified LOD")
{
    Py_ssize_t lod = plClothingItem::kLODHigh;
    pyKey* key;

    if (!PyArg_ParseTuple(args, "nO", &lod, &key)) {
        PyErr_SetString(PyExc_TypeError, "setMesh expects int, plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "setMesh expects plKey");
        return nullptr;
    }

    if (lod >= 0 && lod < plClothingItem::LODLevels::kNumLODLevels) {
        self->fThis->setMesh(lod, *(key->fThis));
        Py_RETURN_NONE;
    }

    PyErr_SetString(PyExc_IndexError, "mesh index out of range");
    return nullptr;
}

PY_METHOD_VA(ClothingItem, getElementTexture,
    "Params: element, layer\n"
    "Gets the Key of the texture for the specified element and layer")
{
    Py_ssize_t element, layer;
    if (!PyArg_ParseTuple(args, "nn", &element, &layer)) {
        PyErr_SetString(PyExc_TypeError, "getElementTexture expects int, int");
        return nullptr;
    }

    size_t element_s = size_t(element);
    size_t layer_s = size_t(layer);

    if (element_s < self->fThis->getNumElements()) {
        if (layer_s < plClothingItem::kLayerMax) {
            return pyPlasma_convert(self->fThis->getElementTexture(element_s, layer_s));
        }

        PyErr_SetString(PyExc_IndexError, "layer index out of range");
        return nullptr;
    }

    PyErr_SetString(PyExc_IndexError, "element index out of range");
    return nullptr;
}

PY_METHOD_VA(ClothingItem, setElementTexture,
    "Params: element idx, layer idx, texture\n"
    "Sets the texture of the specified element and layer")
{
    Py_ssize_t element, layer;
    pyKey* key;

    if (!PyArg_ParseTuple(args, "nnO", &element, &layer, &key)) {
        PyErr_SetString(PyExc_TypeError, "setElementTexture expects int, int, plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "setElementTexture expects plKey");
        return nullptr;
    }

    size_t element_s = size_t(element);
    size_t layer_s = size_t(layer);

    if (element_s < self->fThis->getNumElements()) {
        if (layer_s < plClothingItem::kLayerMax) {
            self->fThis->setElementTexture(element_s, layer_s, *(key->fThis));
            Py_RETURN_NONE;
        }

        PyErr_SetString(PyExc_IndexError, "layer index out of range");
        return nullptr;
    }

    PyErr_SetString(PyExc_IndexError, "element index out of range");
    return nullptr;
}

PY_METHOD_VA(ClothingItem, getElementName,
    "Params: element idx\n"
    "Gets the name of the specified element")
{
    Py_ssize_t element;
    if (!PyArg_ParseTuple(args, "n", &element)) {
        PyErr_SetString(PyExc_TypeError, "getElementName expects int");
        return nullptr;
    }

    size_t element_s = size_t(element);

    if (element_s < self->fThis->getNumElements())
        return pyPlasma_convert(self->fThis->getElementName(element_s));

    PyErr_SetString(PyExc_IndexError, "element index out of range");
    return nullptr;
}

PY_METHOD_VA(ClothingItem, setElementName,
    "Params: element idx, name\n"
    "Sets the name of the specified element")
{
    Py_ssize_t element;
    const char* name;
    if (!PyArg_ParseTuple(args, "ns", &element, &name)) {
        PyErr_SetString(PyExc_TypeError, "setElementName expects int, string");
        return nullptr;
    }

    size_t element_s = size_t(element);

    if (element_s < self->fThis->getNumElements()) {
        self->fThis->setElementName(element_s, name);
        Py_RETURN_NONE;
    }

    PyErr_SetString(PyExc_IndexError, "element index out of range");
    return nullptr;
}

PY_METHOD_VA(ClothingItem, addElement,
    "Params: element name\n"
    "Add an element to the clothingItem")
{
    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        PyErr_SetString(PyExc_TypeError, "addElement expects a string");
        return nullptr;
    }

    self->fThis->addElement(name);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ClothingItem, delElement,
    "Params: element idx\n"
    "Remove an element from the clothingItem")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delElement expects an int");
        return nullptr;
    }

    size_t idx_s = size_t(idx);

    if (idx_s < self->fThis->getNumElements()) {
        self->fThis->delElement(idx_s);
        Py_RETURN_NONE;
    }

    PyErr_SetString(PyExc_IndexError, "element index out of range");
    return nullptr;
}

PY_METHOD_NOARGS(ClothingItem, clearElements,
    "Remove all elements from the clothingItem")
{
    self->fThis->clearElements();
    Py_RETURN_NONE;
}

PyMethodDef pyClothingItem_Methods[] = {
    pyClothingItem_getMesh_method,
    pyClothingItem_setMesh_method,
    pyClothingItem_getElementTexture_method,
    pyClothingItem_setElementTexture_method,
    pyClothingItem_getElementName_method,
    pyClothingItem_setElementName_method,
    pyClothingItem_addElement_method,
    pyClothingItem_delElement_method,
    pyClothingItem_clearElements_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(ST::string, ClothingItem, itemName, getItemName, setItemName)
PY_PROPERTY(ST::string, ClothingItem, description, getDescription, setDescription)
PY_PROPERTY(ST::string, ClothingItem, customText, getCustomText, setCustomText)
PY_PROPERTY(plClothingItem::Groups, ClothingItem, group, getGroup, setGroup)
PY_PROPERTY(plClothingItem::Types, ClothingItem, type, getType, setType)
PY_PROPERTY(plClothingItem::Tilesets, ClothingItem, tileset, getTileset, setTileset)
PY_PROPERTY(unsigned char, ClothingItem, sortOrder, getSortOrder, setSortOrder)
PY_PROPERTY(plKey, ClothingItem, icon, getIcon, setIcon)
PY_PROPERTY(plKey, ClothingItem, accessory, getAccessory, setAccessory)
PY_PROPERTY(hsColorRGBA, ClothingItem, defaultTint1, getDefaultTint1, setDefaultTint1)
PY_PROPERTY(hsColorRGBA, ClothingItem, defaultTint2, getDefaultTint2, setDefaultTint2)
PY_PROPERTY_RO(ClothingItem, numElements, getNumElements)

PyGetSetDef pyClothingItem_GetSet[] = {
    pyClothingItem_itemName_getset,
    pyClothingItem_description_getset,
    pyClothingItem_customText_getset,
    pyClothingItem_group_getset,
    pyClothingItem_type_getset,
    pyClothingItem_tileset_getset,
    pyClothingItem_sortOrder_getset,
    pyClothingItem_icon_getset,
    pyClothingItem_accessory_getset,
    pyClothingItem_defaultTint1_getset,
    pyClothingItem_defaultTint2_getset,
    pyClothingItem_numElements_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ClothingItem, plClothingItem, "plClothingItem wrapper")

PY_PLASMA_TYPE_INIT(ClothingItem)
{
    pyClothingItem_Type.tp_new = pyClothingItem_new;
    pyClothingItem_Type.tp_methods = pyClothingItem_Methods;
    pyClothingItem_Type.tp_getset = pyClothingItem_GetSet;
    pyClothingItem_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyClothingItem_Type) < 0)
        return nullptr;

    /* LODLevel Konstants */
    PY_TYPE_ADD_CONST(ClothingItem, "kLODHigh", plClothingItem::kLODHigh);
    PY_TYPE_ADD_CONST(ClothingItem, "kLODMedium", plClothingItem::kLODMedium);
    PY_TYPE_ADD_CONST(ClothingItem, "kLODLow", plClothingItem::kLODLow);
    PY_TYPE_ADD_CONST(ClothingItem, "kNumLODLevels", plClothingItem::kNumLODLevels);

    /* ClothingLayer Konstants */
    PY_TYPE_ADD_CONST(ClothingItem, "kLayerBase", plClothingItem::kLayerBase);
    PY_TYPE_ADD_CONST(ClothingItem, "kLayerSkin", plClothingItem::kLayerSkin);
    PY_TYPE_ADD_CONST(ClothingItem, "kLayerSkinBlend1", plClothingItem::kLayerSkinBlend1);
    PY_TYPE_ADD_CONST(ClothingItem, "kLayerSkinBlend2", plClothingItem::kLayerSkinBlend2);
    PY_TYPE_ADD_CONST(ClothingItem, "kLayerSkinBlend3", plClothingItem::kLayerSkinBlend3);
    PY_TYPE_ADD_CONST(ClothingItem, "kLayerSkinBlend4", plClothingItem::kLayerSkinBlend4);
    PY_TYPE_ADD_CONST(ClothingItem, "kLayerSkinBlend5", plClothingItem::kLayerSkinBlend5);
    PY_TYPE_ADD_CONST(ClothingItem, "kLayerSkinBlend6", plClothingItem::kLayerSkinBlend6);
    PY_TYPE_ADD_CONST(ClothingItem, "kLayerTint1", plClothingItem::kLayerTint1);
    PY_TYPE_ADD_CONST(ClothingItem, "kLayerTint2", plClothingItem::kLayerTint2);
    PY_TYPE_ADD_CONST(ClothingItem, "kLayerMax", plClothingItem::kLayerMax);

    /* Tileset Konstants */
    PY_TYPE_ADD_CONST(ClothingItem, "kSetShirt", plClothingItem::kSetShirt);
    PY_TYPE_ADD_CONST(ClothingItem, "kSetFace", plClothingItem::kSetFace);
    PY_TYPE_ADD_CONST(ClothingItem, "kSetShoe", plClothingItem::kSetShoe);
    PY_TYPE_ADD_CONST(ClothingItem, "kSetPants", plClothingItem::kSetPants);
    PY_TYPE_ADD_CONST(ClothingItem, "kSetHand", plClothingItem::kSetHand);
    PY_TYPE_ADD_CONST(ClothingItem, "kSetPlayerBook", plClothingItem::kSetPlayerBook);
    PY_TYPE_ADD_CONST(ClothingItem, "kSetGlasses", plClothingItem::kSetGlasses);
    PY_TYPE_ADD_CONST(ClothingItem, "kSetKI", plClothingItem::kSetKI);
    PY_TYPE_ADD_CONST(ClothingItem, "kSetEye", plClothingItem::kSetEye);
    PY_TYPE_ADD_CONST(ClothingItem, "kSetBackpack", plClothingItem::kSetBackpack);

    /* Type Konstants */
    PY_TYPE_ADD_CONST(ClothingItem, "kTypePants", plClothingItem::kTypePants);
    PY_TYPE_ADD_CONST(ClothingItem, "kTypeShirt", plClothingItem::kTypeShirt);
    PY_TYPE_ADD_CONST(ClothingItem, "kTypeLeftHand", plClothingItem::kTypeLeftHand);
    PY_TYPE_ADD_CONST(ClothingItem, "kTypeRightHand", plClothingItem::kTypeRightHand);
    PY_TYPE_ADD_CONST(ClothingItem, "kTypeFace", plClothingItem::kTypeFace);
    PY_TYPE_ADD_CONST(ClothingItem, "kTypeHair", plClothingItem::kTypeHair);
    PY_TYPE_ADD_CONST(ClothingItem, "kTypeLeftFoot", plClothingItem::kTypeLeftFoot);
    PY_TYPE_ADD_CONST(ClothingItem, "kTypeRightFoot", plClothingItem::kTypeRightFoot);
    PY_TYPE_ADD_CONST(ClothingItem, "kTypeAccessory", plClothingItem::kTypeAccessory);

    /* Group Konstants */
    PY_TYPE_ADD_CONST(ClothingItem, "kClothingBaseMale", plClothingItem::kClothingBaseMale);
    PY_TYPE_ADD_CONST(ClothingItem, "kClothingBaseFemale", plClothingItem::kClothingBaseFemale);
    PY_TYPE_ADD_CONST(ClothingItem, "kClothingBaseNoOptions", plClothingItem::kClothingBaseNoOptions);

    Py_INCREF(&pyClothingItem_Type);
    return (PyObject*)&pyClothingItem_Type;
}

PY_PLASMA_IFC_METHODS(ClothingItem, plClothingItem)
