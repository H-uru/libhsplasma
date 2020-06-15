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

#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Modifier/pyModifier.h"
#include <PRP/Surface/plGrassShaderMod.h>

PY_PLASMA_NEW(GrassShaderMod, plGrassShaderMod)

PY_GETSET_GETTER_DECL(GrassShaderMod, waves)
{
    PyObject* waves = PyTuple_New(plGrassShaderMod::kNumWaves);
    for (size_t i = 0; i < plGrassShaderMod::kNumWaves; ++i)
        PyTuple_SET_ITEM(waves, i, pyGrassWave_FromGrassWave(&self->fThis->getWave(i)));
    return waves;
}

PY_PROPERTY_GETSET_RO_DECL(GrassShaderMod, waves)
PY_PROPERTY(plKey, GrassShaderMod, material, getMaterial, setMaterial)

static PyGetSetDef pyGrassShaderMod_GetSet[] = {
    pyGrassShaderMod_waves_getset,
    pyGrassShaderMod_material_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GrassShaderMod, plGrassShaderMod, "plGrassShaderMod wrapper")

PY_PLASMA_TYPE_INIT(GrassShaderMod)
{
    pyGrassShaderMod_Type.tp_new = pyGrassShaderMod_new;
    pyGrassShaderMod_Type.tp_getset = pyGrassShaderMod_GetSet;
    pyGrassShaderMod_Type.tp_base = &pyModifier_Type;
    if (PyType_CheckAndReady(&pyGrassShaderMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGrassShaderMod_Type);
    return (PyObject*)&pyGrassShaderMod_Type;
}

PY_PLASMA_IFC_METHODS(GrassShaderMod, plGrassShaderMod)
