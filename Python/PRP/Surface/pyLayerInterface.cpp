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

#include "pyLayer.h"

#include <PRP/Surface/plLayer.h>
#include "pyGMatState.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Object/pySynchedObject.h"
#include "Math/pyMatrix.h"
#include "Sys/pyColor.h"

PY_PLASMA_NEW_MSG(LayerInterface, "plLayerInterface is abstract")

PY_PROPERTY(plKey, LayerInterface, underLay, getUnderLay, setUnderLay)
PY_PROPERTY(plKey, LayerInterface, texture, getTexture, setTexture)
PY_PROPERTY(plKey, LayerInterface, vertexShader, getVertexShader, setVertexShader)
PY_PROPERTY(plKey, LayerInterface, pixelShader, getPixelShader, setPixelShader)
PY_PROPERTY(hsMatrix44, LayerInterface, transform, getTransform, setTransform)
PY_PROPERTY(hsMatrix44, LayerInterface, bumpEnvTransform, getBumpEnvTransform,
            setBumpEnvTransform)
PY_PROPERTY(hsColorRGBA, LayerInterface, preshade, getPreshade, setPreshade)
PY_PROPERTY(hsColorRGBA, LayerInterface, runtime, getRuntime, setRuntime)
PY_PROPERTY(hsColorRGBA, LayerInterface, ambient, getAmbient, setAmbient)
PY_PROPERTY(hsColorRGBA, LayerInterface, specular, getSpecular, setSpecular)
PY_PROPERTY(float, LayerInterface, opacity, getOpacity, setOpacity)
PY_PROPERTY(unsigned int, LayerInterface, UVWSrc, getUVWSrc, setUVWSrc)
PY_PROPERTY(float, LayerInterface, LODBias, getLODBias, setLODBias)
PY_PROPERTY(float, LayerInterface, specularPower, getSpecularPower, setSpecularPower)
PY_PROPERTY_PROXY_RO(hsGMatState, LayerInterface, state, getState)

static PyGetSetDef pyLayerInterface_GetSet[] = {
    pyLayerInterface_underLay_getset,
    pyLayerInterface_texture_getset,
    pyLayerInterface_vertexShader_getset,
    pyLayerInterface_pixelShader_getset,
    pyLayerInterface_transform_getset,
    pyLayerInterface_bumpEnvTransform_getset,
    pyLayerInterface_preshade_getset,
    pyLayerInterface_runtime_getset,
    pyLayerInterface_ambient_getset,
    pyLayerInterface_specular_getset,
    pyLayerInterface_opacity_getset,
    pyLayerInterface_UVWSrc_getset,
    pyLayerInterface_LODBias_getset,
    pyLayerInterface_specularPower_getset,
    pyLayerInterface_state_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LayerInterface, plLayerInterface, "plLayerInterface wrapper")

PY_PLASMA_TYPE_INIT(LayerInterface)
{
    pyLayerInterface_Type.tp_new = pyLayerInterface_new;
    pyLayerInterface_Type.tp_getset = pyLayerInterface_GetSet;
    pyLayerInterface_Type.tp_base = &pySynchedObject_Type;
    if (PyType_CheckAndReady(&pyLayerInterface_Type) < 0)
        return nullptr;

    /* plLayerDirtyBits */
    PY_TYPE_ADD_CONST(LayerInterface, "kTransform", plLayerInterface::kTransform);
    PY_TYPE_ADD_CONST(LayerInterface, "kPreshadeColor", plLayerInterface::kPreshadeColor);
    PY_TYPE_ADD_CONST(LayerInterface, "kAmbientColor", plLayerInterface::kAmbientColor);
    PY_TYPE_ADD_CONST(LayerInterface, "kOpacity", plLayerInterface::kOpacity);
    PY_TYPE_ADD_CONST(LayerInterface, "kTexture", plLayerInterface::kTexture);
    PY_TYPE_ADD_CONST(LayerInterface, "kState", plLayerInterface::kState);
    PY_TYPE_ADD_CONST(LayerInterface, "kUVWSrc", plLayerInterface::kUVWSrc);
    PY_TYPE_ADD_CONST(LayerInterface, "kLODBias", plLayerInterface::kLODBias);
    PY_TYPE_ADD_CONST(LayerInterface, "kSpecularColor", plLayerInterface::kSpecularColor);
    PY_TYPE_ADD_CONST(LayerInterface, "kSpecularPower", plLayerInterface::kSpecularPower);
    PY_TYPE_ADD_CONST(LayerInterface, "kRuntimeColor", plLayerInterface::kRuntimeColor);
    PY_TYPE_ADD_CONST(LayerInterface, "kVertexShader", plLayerInterface::kVertexShader);
    PY_TYPE_ADD_CONST(LayerInterface, "kPixelShader", plLayerInterface::kPixelShader);
    PY_TYPE_ADD_CONST(LayerInterface, "kBumpEnvXfm", plLayerInterface::kBumpEnvXfm);
    PY_TYPE_ADD_CONST(LayerInterface, "kAllDirty", plLayerInterface::kAllDirty);

    /* plUVWSrcModifiers */
    PY_TYPE_ADD_CONST(LayerInterface, "kUVWPassThru", plLayerInterface::kUVWPassThru);
    PY_TYPE_ADD_CONST(LayerInterface, "kUVWIdxMask", plLayerInterface::kUVWIdxMask);
    PY_TYPE_ADD_CONST(LayerInterface, "kUVWNormal", plLayerInterface::kUVWNormal);
    PY_TYPE_ADD_CONST(LayerInterface, "kUVWPosition", plLayerInterface::kUVWPosition);
    PY_TYPE_ADD_CONST(LayerInterface, "kUVWReflect", plLayerInterface::kUVWReflect);

    Py_INCREF(&pyLayerInterface_Type);
    return (PyObject*)&pyLayerInterface_Type;
}

PY_PLASMA_IFC_METHODS(LayerInterface, plLayerInterface)
