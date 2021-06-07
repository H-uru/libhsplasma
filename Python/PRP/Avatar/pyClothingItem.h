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

#ifndef _PYCLOTHINGITEM_H
#define _PYCLOTHINGITEM_H

#include "PyPlasma.h"
#include "PRP/Avatar/plClothingItem.h"

PY_WRAP_PLASMA(ClothingItem, class plClothingItem)

/* Python property helpers */
inline PyObject* pyPlasma_convert(plClothingItem::Tilesets value) { return PyInt_FromLong((long)value); }
inline PyObject* pyPlasma_convert(plClothingItem::Types value) { return PyInt_FromLong((long)value); }
inline PyObject* pyPlasma_convert(plClothingItem::Groups value) { return PyInt_FromLong((long)value); }

template <> inline int pyPlasma_check<plClothingItem::Tilesets>(PyObject* value) { return PyAnyInt_Check(value); }
template <> inline int pyPlasma_check<plClothingItem::Types>(PyObject* value) { return PyAnyInt_Check(value); }
template <> inline int pyPlasma_check<plClothingItem::Groups>(PyObject* value) { return PyAnyInt_Check(value); }

template <> inline plClothingItem::Tilesets pyPlasma_get(PyObject* value) { return (plClothingItem::Tilesets)PyLong_AsLong(value); }
template <> inline plClothingItem::Types pyPlasma_get(PyObject* value) { return (plClothingItem::Types)PyLong_AsLong(value); }
template <> inline plClothingItem::Groups pyPlasma_get(PyObject* value) { return (plClothingItem::Groups)PyLong_AsLong(value); }

#endif
