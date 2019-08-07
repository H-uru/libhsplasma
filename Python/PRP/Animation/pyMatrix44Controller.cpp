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

PY_PLASMA_EMPTY_INIT(Matrix44Controller)
PY_PLASMA_NEW(Matrix44Controller, plMatrix44Controller)

PY_PLASMA_TYPE(Matrix44Controller, plMatrix44Controller,
               "plMatrix44Controller wrapper")

PY_PLASMA_TYPE_INIT(Matrix44Controller)
{
    pyMatrix44Controller_Type.tp_init = pyMatrix44Controller___init__;
    pyMatrix44Controller_Type.tp_new = pyMatrix44Controller_new;
    pyMatrix44Controller_Type.tp_base = &pyLeafController_Type;
    if (PyType_CheckAndReady(&pyMatrix44Controller_Type) < 0)
        return nullptr;

    Py_INCREF(&pyMatrix44Controller_Type);
    return (PyObject*)&pyMatrix44Controller_Type;
}

PY_PLASMA_IFC_METHODS(Matrix44Controller, plMatrix44Controller)
