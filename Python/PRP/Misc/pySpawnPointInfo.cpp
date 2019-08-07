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

#include "pySpawnPointInfo.h"

#include <PRP/Misc/plSpawnPointInfo.h>

PY_PLASMA_NEW(SpawnPointInfo, plSpawnPointInfo)

PY_PROPERTY(ST::string, SpawnPointInfo, title, getTitle, setTitle)
PY_PROPERTY(ST::string, SpawnPointInfo, spawnPt, getSpawnPt, setSpawnPt)
PY_PROPERTY(ST::string, SpawnPointInfo, cameraStack, getCameraStack, setCameraStack)

PyGetSetDef pySpawnPointInfo_GetSet[] = {
    pySpawnPointInfo_title_getset,
    pySpawnPointInfo_spawnPt_getset,
    pySpawnPointInfo_cameraStack_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SpawnPointInfo, plSpawnPointInfo, "plSpawnPointInfo wrapper")

PY_PLASMA_TYPE_INIT(SpawnPointInfo)
{
    pySpawnPointInfo_Type.tp_new = pySpawnPointInfo_new;
    pySpawnPointInfo_Type.tp_getset = pySpawnPointInfo_GetSet;
    if (PyType_CheckAndReady(&pySpawnPointInfo_Type) < 0)
        return nullptr;

    Py_INCREF(&pySpawnPointInfo_Type);
    return (PyObject*)&pySpawnPointInfo_Type;
}

PY_PLASMA_IFC_METHODS(SpawnPointInfo, plSpawnPointInfo)
