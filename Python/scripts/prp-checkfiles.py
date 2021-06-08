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

# This script reads a bunch of prp and age files to check whether libHSPlasma shows any error messages or other problems.
# Call "./prp-checkfiles.py --help" for a list of options.
# by Diafero

import sys, glob, os
from optparse import OptionParser
import PyHSPlasma

width = 80
kTmpFile = "tmpcomparefile.prp"


def readObjects(location):
    data = []
    # read all the objects
    for type in rm.getTypes(location):
        while len(data) <= type:
            data.append({}) # fill array
        for key in rm.getKeys(location, type):
            if key.exists() and key.isLoaded():
                data[type][key.name] = key.object.stub.getData()
    return data


def checkObjectsEqual(objs1, objs2, ignorePhysics):
    if len(objs1) != len(objs2):
        raise Exception('Number of types changed')
    for type in range(0, len(objs1)):
        typeName = PyHSPlasma.plFactory.ClassName(type, rm.getVer())
        # compare the objects of this type
        for name in objs1[type].keys():
            if not name in objs2[type].keys():
                print('Type [%04X]%s, object %s missing' % (type, typeName, name))
            if ignorePhysics and type == PyHSPlasma.plFactory.kGenericPhysical: continue
            obj1 = objs1[type][name]
            obj2 = objs2[type][name]
            if len(obj1) != len(obj2):
                print('Type [%04X]%s, object %s changed changed size (%d => %d)' % (type, typeName, name, len(obj1), len(obj2)))
            if obj1 != obj2:
                print('Type [%04X]%s, object %s changed but stay same size' % (type, typeName, name))
        # check if something got added
        for name in objs2[type].keys():
            if not name in objs1[type].keys():
                print('Type [%04X]%s, object %s added' % (type, typeName, name))


def compareFiles(file1, file2, ignorePhysics):
    # read old objects
    location = rm.ReadPage(file1, True).location
    oldObjects = readObjects(location)
    rm.UnloadPage(location)
    # read new objects
    location = rm.ReadPage(file2, True).location
    newObjects = readObjects(location)
    rm.UnloadPage(location)
    # now compare the objects
    checkObjectsEqual(oldObjects, newObjects, ignorePhysics)


def overprint(text):
    sys.stdout.write("\r"+text+(" "*(width-len(text))))
    sys.stdout.flush()


### Main app
parser = OptionParser()
parser.add_option("-v", "--verbose",
                  action="count", dest="verbose", default=0,
                  help="If set one time, warnings are printed. If set two or more times, all debug messages are printed.")
parser.add_option("-c", "--check-repack",
                  action="store_true", dest="checkrepack", default=False,
                  help="Re-pack the prp files and compare to the original file (does nothing for age files)")
parser.add_option("-k", "--keep-repacked",
                  action="store_true", dest="keeprepack", default=False,
                  help="Do not remove the temporary repacked file (has no effect if --check-repack is not given)")
parser.add_option("-p", "--ignore-physics",
                  action="store_true", dest="ignorephysics", default=False,
                  help="Do not compare re-packed physicals (has no effect if --check-repack is not given)")
(options, args) = parser.parse_args()

# set verbose level
if options.verbose >= 2:
    PyHSPlasma.plDebug.Init(PyHSPlasma.plDebug.kDLAll)
elif options.verbose == 1:
    PyHSPlasma.plDebug.Init(PyHSPlasma.plDebug.kDLWarning)
else: # options.verbose == 0
    PyHSPlasma.plDebug.Init(PyHSPlasma.plDebug.kDLError)

# read files
rm = PyHSPlasma.plResManager()
for files in args:
    for file in glob.iglob(files): # do the globbing on Windows, too
        overprint("Reading "+file+"...")
        if file.lower().endswith(".prp"):
            page = rm.ReadPage(file)
            if options.checkrepack:
                overprint("Writing "+file+"...")
                rm.WritePage(kTmpFile, page)
            rm.UnloadPage(page.location)
            if options.checkrepack:
                overprint("Comparing "+file+"...")
                compareFiles(file, kTmpFile, options.ignorephysics)
                if not options.keeprepack: os.remove(kTmpFile)
        elif file.lower().endswith(".age"):
            age = rm.ReadAge(file, True) # readPages=True
            for pageNum in range(0, age.getNumPages()):
                loc = age.getPageLoc(pageNum, rm.getVer())
                page = rm.FindPage(loc)
                if (page == None):
                    raise Exception("Unable to completely load age "+age.name+": Can't find page "+str(loc))
            rm.UnloadAge(age.name)
        else:
            print("Error: Unknown file type!")
overprint("Done!")
sys.stdout.write("\n")
