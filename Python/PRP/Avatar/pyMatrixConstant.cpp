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

#include "pyAGChannel.h"

#include <PRP/Avatar/plMatrixChannel.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(MatrixConstant, plMatrixConstant)

PY_PLASMA_TYPE(MatrixConstant, plMatrixConstant, "plMatrixConstant wrapper")

PY_PLASMA_TYPE_INIT(MatrixConstant)
{
    pyMatrixConstant_Type.tp_new = pyMatrixConstant_new;
    pyMatrixConstant_Type.tp_base = &pyMatrixChannel_Type;
    if (PyType_CheckAndReady(&pyMatrixConstant_Type) < 0)
        return nullptr;

    Py_INCREF(&pyMatrixConstant_Type);
    return (PyObject*)&pyMatrixConstant_Type;
}

PY_PLASMA_IFC_METHODS(MatrixConstant, plMatrixConstant)
