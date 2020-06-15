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

#include "pyGrassShaderMod.h"

#include "Math/pyGeometry3.h"
#include <PRP/Surface/plGrassShaderMod.h>

PY_PLASMA_NEW_MSG(GrassWave, "plGrassWave cannot be constructed")

PY_PROPERTY(hsVector3, GrassWave, dist, getDist, setDist)
PY_PROPERTY(float, GrassWave, dirX, getDirX, setDirX)
PY_PROPERTY(float, GrassWave, dirY, getDirY, setDirY)
PY_PROPERTY(float, GrassWave, speed, getSpeed, setSpeed)

static PyGetSetDef pyGrassWave_GetSet[] = {
    pyGrassWave_dist_getset,
    pyGrassWave_dirX_getset,
    pyGrassWave_dirY_getset,
    pyGrassWave_speed_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GrassWave, plGrassWave, "plGrassWave wrapper")

PY_PLASMA_TYPE_INIT(GrassWave)
{
    pyGrassWave_Type.tp_new = pyGrassWave_new;
    pyGrassWave_Type.tp_getset = pyGrassWave_GetSet;
    if (PyType_CheckAndReady(&pyGrassWave_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGrassWave_Type);
    return (PyObject*)&pyGrassWave_Type;
}

PY_PLASMA_IFC_METHODS(GrassWave, plGrassWave)
