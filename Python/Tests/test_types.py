# This file is part of HSPlasma.
#
# HSPlasma is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# HSPlasma is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.

import sys
from typing import Iterable, Type
import unittest

import PyHSPlasma

# Any class that needs some help to create itself, put that help here. Ideally,
# we only skip abstract classes.
CREATORS = {
    PyHSPlasma.pfPrcHelper: lambda: PyHSPlasma.pfPrcHelper(PyHSPlasma.hsRAMStream())
}

class TestTypeRefCount(unittest.TestCase):
    def __iter_types(self, obj) -> Iterable[Type]:
        for i in vars(obj).values():
            if isinstance(i, type):
                yield i
                yield from self.__iter_types(i)

    def runTest(self):
        for i in self.__iter_types(PyHSPlasma):
            with self.subTest(i.__name__):
                self.__test_type(i)

    def __test_type(self, pClass: Type):
        # In Python 3.8, heap types had a behavior change around how they are reference
        # counted. The short version of it is that in Python 3.8 and higher, the object
        # deallocate needs to also decrement the type object's reference count to ensure
        # that the type object is not leaked. So, the test is to create and immediately
        # discard every type that can be trivially constructed in PyHSPlasma. This should
        # be a no-op in terms of the type's reference count.
        # NOTE: At this time PyHSPlasma does NOT use any heap types at all, but this
        # is still worthwhile because it has caught crashes when simply instantiating some
        # PyHSPlasma types.
        initfunc = CREATORS.get(pClass, pClass)
        old_refcount = sys.getrefcount(pClass)
        try:
            initfunc()
        except Exception as e:
            raise unittest.SkipTest(f"cannot instantiate {pClass.__name__}") from e
        else:
            new_refcount = sys.getrefcount(pClass)
            self.assertEqual(new_refcount, old_refcount, "type refcount issue, check tp_dealloc")
