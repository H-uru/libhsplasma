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
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(LayerSDLAnimation, plLayerSDLAnimation)

PY_PROPERTY(ST::string, LayerSDLAnimation, varName, getVarName, setVarName)

static PyGetSetDef pyLayerSDLAnimation_GetSet[] = {
    pyLayerSDLAnimation_varName_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LayerSDLAnimation, plLayerSDLAnimation, "plLayerSDLAnimation wrapper")

PY_PLASMA_TYPE_INIT(LayerSDLAnimation)
{
    pyLayerSDLAnimation_Type.tp_new = pyLayerSDLAnimation_new;
    pyLayerSDLAnimation_Type.tp_getset = pyLayerSDLAnimation_GetSet;
    pyLayerSDLAnimation_Type.tp_base = &pyLayerAnimation_Type;
    if (PyType_CheckAndReady(&pyLayerSDLAnimation_Type) < 0)
        return nullptr;

    Py_INCREF(&pyLayerSDLAnimation_Type);
    return (PyObject*)&pyLayerSDLAnimation_Type;
}

PY_PLASMA_IFC_METHODS(LayerSDLAnimation, plLayerSDLAnimation)
