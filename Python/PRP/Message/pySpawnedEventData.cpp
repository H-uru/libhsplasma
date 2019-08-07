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

#include "pyEventData.h"

#include <PRP/Message/proEventData.h>
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(SpawnedEventData, proSpawnedEventData)

PY_PROPERTY(plKey, SpawnedEventData, spawner, getSpawner, setSpawner)
PY_PROPERTY(plKey, SpawnedEventData, spawnee, getSpawnee, setSpawnee)

static PyGetSetDef pySpawnedEventData_GetSet[] = {
    pySpawnedEventData_spawner_getset,
    pySpawnedEventData_spawnee_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SpawnedEventData, proSpawnedEventData, "proSpawnedEventData wrapper")

PY_PLASMA_TYPE_INIT(SpawnedEventData)
{
    pySpawnedEventData_Type.tp_new = pySpawnedEventData_new;
    pySpawnedEventData_Type.tp_getset = pySpawnedEventData_GetSet;
    pySpawnedEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pySpawnedEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pySpawnedEventData_Type);
    return (PyObject*)&pySpawnedEventData_Type;
}

PY_PLASMA_IFC_METHODS(SpawnedEventData, proSpawnedEventData)
