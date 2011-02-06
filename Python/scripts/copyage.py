#!/bin/env python
# -*- coding: utf-8 -*-
# copyage.py: Copy one age to another, with a new name and sequence prefix
# Copyright (C) 2010 Branan Purvine-Riley
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import PyHSPlasma
from PyHSPlasma import plResManager
from PyHSPlasma import plLocation

from optparse import OptionParser
import os.path
import shutil

manager = plResManager(PyHSPlasma.pvPots)

dummy_sum = "whatdoyousee\x08\x00\x00\x00\x66\x1E\x41\xB2\x15\xE4\x5F\x9B"

def changeAgeProperties(age_file, new_prefix, new_name):
  filename = os.path.abspath(age_file)
  oldfni = filename.replace(".age", ".fni")
  age = manager.ReadAge(filename, True)
  age.seqPrefix = new_prefix
  dirname = os.path.dirname(age_file)
  agename = os.path.basename(age_file)
  agename = agename.replace(age.name, new_name)
  filename = os.path.join(dirname, agename)
  newfni = filename.replace(".age", ".fni")
  sumfilename = filename.replace(".age", ".sum")
  shutil.copy(oldfni, newfni)
  sumfile = open(sumfilename, 'w')
  sumfile.write(dummy_sum)
  sumfile.close()
  age.name = new_name
  manager.WriteAge(filename, age)
  for loc in manager.getLocations():
    loc2 = plLocation(loc.version)
    loc2.page = loc.page
    loc2.prefix = new_prefix
    manager.ChangeLocation(loc, loc2)
    page = manager.FindPage(loc2)
    page.age = new_name
    manager.WritePage(page.getFilename(manager.getVer()), page)

def main():
  parser = OptionParser(usage="usage: %prog [options] agefile")
  parser.add_option("-p", "--prefix", dest="prefix", help="The new sequence prefix", metavar="PREFIX", type="int")
  parser.add_option("-n", "--name", dest="agename", help="The new age name", metavar="NAME")
  (options, args) = parser.parse_args()
  if len(args) == 0 or options.prefix is None or options.agename is None:
    parser.print_help()
    return
  changeAgeProperties(args[0], options.prefix, options.agename)

if __name__ == "__main__":
  main()
