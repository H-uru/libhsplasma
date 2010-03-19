#!/usr/bin/python
# -*- coding: utf-8 -*-

# This script reads a bunch of prp and age files to check whether libHSPlasma shows any error messages or other problems.
# Files can be specified by their name or as file pattern (like "*.prp").
# The first argument can also be "-v" to show not only errors but also warnings, and "-vv" to show all debug output.
# by Diafero

import sys, glob
import PyHSPlasma

width = 80

def overprint(text):
    sys.stdout.write("\r"+text+(" "*(width-len(text))))
    sys.stdout.flush()

if len(sys.argv) == 1:
    print "Usage: %s [-v|-vv] filename..." % sys.argv[0]
    sys.exit(0)

args = sys.argv[1:]
if args[0] == '-vv':
    args = args[1:]
    PyHSPlasma.plDebug.Init(PyHSPlasma.plDebug.kDLAll)
elif args[0] == '-v':
    args = args[1:]
    PyHSPlasma.plDebug.Init(PyHSPlasma.plDebug.kDLWarning)
else:
    PyHSPlasma.plDebug.Init(PyHSPlasma.plDebug.kDLError)

rm = PyHSPlasma.plResManager()
for files in args:
    for file in glob.iglob(files): # do the globbing on Windows, too
        overprint("Reading "+file+"...")
        if file.lower().endswith(".prp"):
            rm.UnloadPage(rm.ReadPage(file).location)
        elif file.lower().endswith(".age"):
            rm.UnloadAge(rm.ReadAge(file, True).name)
        else:
            print "Error: Unknown file type!";
overprint("Done!")
sys.stdout.write("\n")
