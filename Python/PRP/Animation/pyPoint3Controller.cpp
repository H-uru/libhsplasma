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

#include "pyLeafController.h"

#include <PRP/Animation/plKeyControllers.hpp>
#include "PRP/pyCreatable.h"

PY_PLASMA_EMPTY_INIT(Point3Controller)
PY_PLASMA_NEW(Point3Controller, plPoint3Controller)

PY_PLASMA_TYPE(Point3Controller, plPoint3Controller, "plPoint3Controller wrapper")

PY_PLASMA_TYPE_INIT(Point3Controller)
{
    pyPoint3Controller_Type.tp_init = pyPoint3Controller___init__;
    pyPoint3Controller_Type.tp_new = pyPoint3Controller_new;
    pyPoint3Controller_Type.tp_base = &pyLeafController_Type;
    if (PyType_CheckAndReady(&pyPoint3Controller_Type) < 0)
        return nullptr;

    Py_INCREF(&pyPoint3Controller_Type);
    return (PyObject*)&pyPoint3Controller_Type;
}

PY_PLASMA_IFC_METHODS(Point3Controller, plPoint3Controller)
