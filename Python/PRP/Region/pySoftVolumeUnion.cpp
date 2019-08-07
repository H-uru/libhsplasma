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

PY_PLASMA_NEW(SoftVolumeUnion, plSoftVolumeUnion)

PY_PLASMA_TYPE(SoftVolumeUnion, plSoftVolumeUnion, "plSoftVolumeUnion wrapper")

PY_PLASMA_TYPE_INIT(SoftVolumeUnion)
{
    pySoftVolumeUnion_Type.tp_new = pySoftVolumeUnion_new;
    pySoftVolumeUnion_Type.tp_base = &pySoftVolumeComplex_Type;
    if (PyType_CheckAndReady(&pySoftVolumeUnion_Type) < 0)
        return nullptr;

    Py_INCREF(&pySoftVolumeUnion_Type);
    return (PyObject*)&pySoftVolumeUnion_Type;
}

PY_PLASMA_IFC_METHODS(SoftVolumeUnion, plSoftVolumeUnion)
