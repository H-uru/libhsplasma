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

#include "pyObjectInVolumeDetector.h"

#include <PRP/Physics/plObjectInVolumeDetector.h>

PY_PLASMA_NEW(ObjectInVolumeAndFacingDetector, plObjectInVolumeAndFacingDetector)

PY_PROPERTY(float, ObjectInVolumeAndFacingDetector, facingTolerance,
            getFacingTolerance, setFacingTolerance)
PY_PROPERTY(bool, ObjectInVolumeAndFacingDetector, needWalkingForward,
            getNeedWalkingForward, setNeedWalkingForward)

static PyGetSetDef pyObjectInVolumeAndFacingDetector_GetSet[] = {
    pyObjectInVolumeAndFacingDetector_facingTolerance_getset,
    pyObjectInVolumeAndFacingDetector_needWalkingForward_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ObjectInVolumeAndFacingDetector, plObjectInVolumeAndFacingDetector,
               "plObjectInVolumeAndFacingDetector wrapper")

PY_PLASMA_TYPE_INIT(ObjectInVolumeAndFacingDetector)
{
    pyObjectInVolumeAndFacingDetector_Type.tp_new = pyObjectInVolumeAndFacingDetector_new;
    pyObjectInVolumeAndFacingDetector_Type.tp_getset = pyObjectInVolumeAndFacingDetector_GetSet;
    pyObjectInVolumeAndFacingDetector_Type.tp_base = &pyObjectInVolumeDetector_Type;
    if (PyType_CheckAndReady(&pyObjectInVolumeAndFacingDetector_Type) < 0)
        return nullptr;

    Py_INCREF(&pyObjectInVolumeAndFacingDetector_Type);
    return (PyObject*)&pyObjectInVolumeAndFacingDetector_Type;
}

PY_PLASMA_IFC_METHODS(ObjectInVolumeAndFacingDetector, plObjectInVolumeAndFacingDetector)
