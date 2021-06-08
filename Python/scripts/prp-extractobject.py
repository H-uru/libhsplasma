#!/usr/bin/python
# -*- coding: utf-8 -*-

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

# This script extracts an object from a prp file and dumps it into anotehr file.
# The object is *not* parsed and re-packed, so this is not necessarily the same as e.g. exporting in PrpShop!
# by Diafero

import sys
import PyHSPlasma

if len(sys.argv) != 5:
    print("Usage: %s filename typename objectname outfile" % sys.argv[0])
    sys.exit(0)

rm = PyHSPlasma.plResManager()
page = rm.ReadPage(sys.argv[1], True)
type = PyHSPlasma.plFactory.ClassIndex(sys.argv[2])
if type < 0:
    print("Type '%s' is invalid" % sys.argv[2])
    sys.exit(1)
keys = rm.getKeys(page.location, type)

for key in keys:
    if key.name != sys.argv[3]: continue
    # get the data
    data = key.object.stub.getData()
    # and save it
    f = open(sys.argv[4], 'w')
    f.write(data)
    f.close()
    print("Data successfully written to %s" % sys.argv[4])
    sys.exit(0)

print("Could not find object %s of type %s" % (sys.argv[3], sys.argv[2]))
sys.exit(1)
