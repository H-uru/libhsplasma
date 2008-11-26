#! /usr/bin/env python

from PyPlasma import *
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
