#!/usr/bin/env python

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

from PyHSPlasma import *
import sys

rm = plResManager()
rm.setVer(pvPots)

fi = hsFileStream(pvPots)
fi.open(sys.argv[1]+'.po', fmRead)

mm = plMipmap.Convert(rm.ReadCreatable(fi))

fo = hsFileStream()
fo.open(sys.argv[1]+'.dds', fmCreate)

mm.writeToStream(fo)

fo.close()
fi.close()
