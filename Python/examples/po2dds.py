#! /usr/bin/env python

import PyPlasma
from PyPlasma import *
import sys

rm = plResManager()
rm.setVer(pvPots)

fi = hsFileStream()
fi.version = pvPots
fi.open(sys.argv[1]+'.po', fmRead)

ko = rm.ReadCreatable(fi)
mm = plMipmap.Convert(ko)

fo = hsFileStream()
fo.open(sys.argv[1]+'.dds', fmCreate)

mm.writeToStream(fo)

fo.close()
fi.close()
