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

#include "pyCollisionDetector.h"

#include <PRP/Physics/plCollisionDetector.h>
#include "pyDetectorModifier.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(CollisionDetector, "plCollisionDetector is abstract")

PY_PROPERTY(unsigned char, CollisionDetector, type, getType, setType)

static PyGetSetDef pyCollisionDetector_GetSet[] = {
    pyCollisionDetector_type_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CollisionDetector, plCollisionDetector, "plCollisionDetector wrapper")

PY_PLASMA_TYPE_INIT(CollisionDetector)
{
    pyCollisionDetector_Type.tp_new = pyCollisionDetector_new;
    pyCollisionDetector_Type.tp_getset = pyCollisionDetector_GetSet;
    pyCollisionDetector_Type.tp_base = &pyDetectorModifier_Type;
    if (PyType_CheckAndReady(&pyCollisionDetector_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(CollisionDetector, "kTypeEnter", plCollisionDetector::kTypeEnter);
    PY_TYPE_ADD_CONST(CollisionDetector, "kTypeExit", plCollisionDetector::kTypeExit);
    PY_TYPE_ADD_CONST(CollisionDetector, "kTypeAny", plCollisionDetector::kTypeAny);
    PY_TYPE_ADD_CONST(CollisionDetector, "kTypeUnEnter", plCollisionDetector::kTypeUnEnter);
    PY_TYPE_ADD_CONST(CollisionDetector, "kTypeUnExit", plCollisionDetector::kTypeUnExit);
    PY_TYPE_ADD_CONST(CollisionDetector, "kTypeBump", plCollisionDetector::kTypeBump);

    Py_INCREF(&pyCollisionDetector_Type);
    return (PyObject*)&pyCollisionDetector_Type;
}

PY_PLASMA_IFC_METHODS(CollisionDetector, plCollisionDetector)
