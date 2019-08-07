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

#include "pyLayerAnimation.h"

#include <PRP/Surface/plLayerAnimation.h>
#include "PRP/Animation/pyAnimTimeConvert.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(LayerAnimation, plLayerAnimation)

PY_PROPERTY_PROXY_RO(plAnimTimeConvert, LayerAnimation, timeConvert, getTimeConvert)

static PyGetSetDef pyLayerAnimation_GetSet[] = {
    pyLayerAnimation_timeConvert_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LayerAnimation, plLayerAnimation, "plLayerAnimation wrapper")

PY_PLASMA_TYPE_INIT(LayerAnimation)
{
    pyLayerAnimation_Type.tp_new = pyLayerAnimation_new;
    pyLayerAnimation_Type.tp_getset = pyLayerAnimation_GetSet;
    pyLayerAnimation_Type.tp_base = &pyLayerAnimationBase_Type;
    if (PyType_CheckAndReady(&pyLayerAnimation_Type) < 0)
        return nullptr;

    Py_INCREF(&pyLayerAnimation_Type);
    return (PyObject*)&pyLayerAnimation_Type;
}

PY_PLASMA_IFC_METHODS(LayerAnimation, plLayerAnimation)
