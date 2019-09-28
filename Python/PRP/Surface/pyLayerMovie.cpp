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

#include "pyLayerMovie.h"

#include <PRP/Surface/plLayerMovie.h>
#include "pyLayerAnimation.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(LayerMovie, plLayerMovie)

PY_PROPERTY_PATHLIKE(LayerMovie, movieName, getMovieName, setMovieName)

static PyGetSetDef pyLayerMovie_GetSet[] = {
    pyLayerMovie_movieName_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LayerMovie, plLayerMovie, "plLayerMovie wrapper")

PY_PLASMA_TYPE_INIT(LayerMovie)
{
    pyLayerMovie_Type.tp_new = pyLayerMovie_new;
    pyLayerMovie_Type.tp_getset = pyLayerMovie_GetSet;
    pyLayerMovie_Type.tp_base = &pyLayerAnimation_Type;
    if (PyType_CheckAndReady(&pyLayerMovie_Type) < 0)
        return nullptr;

    Py_INCREF(&pyLayerMovie_Type);
    return (PyObject*)&pyLayerMovie_Type;
}

PY_PLASMA_IFC_METHODS(LayerMovie, plLayerMovie)
