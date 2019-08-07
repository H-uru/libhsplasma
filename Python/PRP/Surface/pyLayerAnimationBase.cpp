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

#include <PRP/Surface/plLayerAnimation.h>
#include "pyLayerAnimation.h"
#include "PRP/Animation/pyController.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(LayerAnimationBase, "plLayerAnimationBase is abstract")

PY_PROPERTY_CREATABLE(plController, Controller, LayerAnimationBase,
                      preshadeCtl, getPreshadeCtl, setPreshadeCtl)
PY_PROPERTY_CREATABLE(plController, Controller, LayerAnimationBase,
                      runtimeCtl, getRuntimeCtl, setRuntimeCtl)
PY_PROPERTY_CREATABLE(plController, Controller, LayerAnimationBase,
                      ambientCtl, getAmbientCtl, setAmbientCtl)
PY_PROPERTY_CREATABLE(plController, Controller, LayerAnimationBase,
                      specularCtl, getSpecularCtl, setSpecularCtl)
PY_PROPERTY_CREATABLE(plController, Controller, LayerAnimationBase,
                      opacityCtl, getOpacityCtl, setOpacityCtl)
PY_PROPERTY_CREATABLE(plController, Controller, LayerAnimationBase,
                      transformCtl, getTransformCtl, setTransformCtl)

static PyGetSetDef pyLayerAnimationBase_GetSet[] = {
    pyLayerAnimationBase_preshadeCtl_getset,
    pyLayerAnimationBase_runtimeCtl_getset,
    pyLayerAnimationBase_ambientCtl_getset,
    pyLayerAnimationBase_specularCtl_getset,
    pyLayerAnimationBase_opacityCtl_getset,
    pyLayerAnimationBase_transformCtl_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LayerAnimationBase, plLayerAnimationBase,
               "plLayerAnimationBase wrapper")

PY_PLASMA_TYPE_INIT(LayerAnimationBase)
{
    pyLayerAnimationBase_Type.tp_new = pyLayerAnimationBase_new;
    pyLayerAnimationBase_Type.tp_getset = pyLayerAnimationBase_GetSet;
    pyLayerAnimationBase_Type.tp_base = &pyLayerInterface_Type;
    if (PyType_CheckAndReady(&pyLayerAnimationBase_Type) < 0)
        return nullptr;

    Py_INCREF(&pyLayerAnimationBase_Type);
    return (PyObject*)&pyLayerAnimationBase_Type;
}

PY_PLASMA_IFC_METHODS(LayerAnimationBase, plLayerAnimationBase)
