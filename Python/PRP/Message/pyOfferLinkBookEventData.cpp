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

PY_PLASMA_NEW(OfferLinkBookEventData, proOfferLinkBookEventData)

PY_PROPERTY(plKey, OfferLinkBookEventData, offerer, getOfferer, setOfferer)
PY_PROPERTY(int, OfferLinkBookEventData, targetAge, getTargetAge, setTargetAge)
PY_PROPERTY(int, OfferLinkBookEventData, offeree, getOfferee, setOfferee)

static PyGetSetDef pyOfferLinkBookEventData_GetSet[] = {
    pyOfferLinkBookEventData_offerer_getset,
    pyOfferLinkBookEventData_targetAge_getset,
    pyOfferLinkBookEventData_offeree_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(OfferLinkBookEventData, proOfferLinkBookEventData,
               "proOfferLinkBookEventData wrapper")

PY_PLASMA_TYPE_INIT(OfferLinkBookEventData)
{
    pyOfferLinkBookEventData_Type.tp_new = pyOfferLinkBookEventData_new;
    pyOfferLinkBookEventData_Type.tp_getset = pyOfferLinkBookEventData_GetSet;
    pyOfferLinkBookEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyOfferLinkBookEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyOfferLinkBookEventData_Type);
    return (PyObject*)&pyOfferLinkBookEventData_Type;
}

PY_PLASMA_IFC_METHODS(OfferLinkBookEventData, proOfferLinkBookEventData)
