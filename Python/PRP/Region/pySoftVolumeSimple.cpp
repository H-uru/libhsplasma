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

#include "pySoftVolume.h"

#include <PRP/Region/plSoftVolume.h>
#include "pyVolumeIsect.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(SoftVolumeSimple, plSoftVolumeSimple)

PY_PROPERTY_CREATABLE(plVolumeIsect, VolumeIsect, SoftVolumeSimple, volume,
                      getVolume, setVolume)
PY_PROPERTY(float, SoftVolumeSimple, softDist, getSoftDist, setSoftDist)

PyGetSetDef pySoftVolumeSimple_GetSet[] = {
    pySoftVolumeSimple_volume_getset,
    pySoftVolumeSimple_softDist_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SoftVolumeSimple, plSoftVolumeSimple, "plSoftVolumeSimple wrapper")

PY_PLASMA_TYPE_INIT(SoftVolumeSimple)
{
    pySoftVolumeSimple_Type.tp_new = pySoftVolumeSimple_new;
    pySoftVolumeSimple_Type.tp_getset = pySoftVolumeSimple_GetSet;
    pySoftVolumeSimple_Type.tp_base = &pySoftVolume_Type;
    if (PyType_CheckAndReady(&pySoftVolumeSimple_Type) < 0)
        return nullptr;

    Py_INCREF(&pySoftVolumeSimple_Type);
    return (PyObject*)&pySoftVolumeSimple_Type;
}

PY_PLASMA_IFC_METHODS(SoftVolumeSimple, plSoftVolumeSimple)
