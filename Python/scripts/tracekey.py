#! /usr/bin/env python

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

from __future__ import print_function
from PyHSPlasma import *
import sys

refStack = []

def proEventData_hasRef(evt, ref):
    if evt is None:
        return False

    if evt.EventType() == proEventData.kCollision:
        if evt.hitter == ref: return True
        if evt.hittee == ref: return True
    if evt.EventType() == proEventData.kPicked:
        if evt.picker == ref: return True
        if evt.picked == ref: return True
    if evt.EventType() == proEventData.kVariable:
        if evt.key == ref: return True
    if evt.EventType() == proEventData.kFacing:
        if evt.facer == ref: return True
        if evt.facee == ref: return True
    if evt.EventType() == proEventData.kContained:
        if evt.contained == ref: return True
        if evt.container == ref: return True
    if evt.EventType() == proEventData.kMultiStage:
        if evt.avatar == ref: return True
    if evt.EventType() == proEventData.kSpawned:
        if evt.spawner == ref: return True
        if evt.spawnee == ref: return True
    if evt.EventType() == proEventData.kOfferLinkBook:
        if evt.offerer == ref: return True
    if evt.EventType() == proEventData.kClimbingBlockerHit:
        if evt.blocker == ref: return True


def hasRef(cre, ref):
    if cre is None:
        return False

    # Keyed Objects
    if cre.ClassInstance(plFactory.kAudioInterface):
        if cre.audible == ref: return True
    if cre.ClassInstance(plFactory.kClusterGroup):
        if cre.material == ref: return True
        if cre.sceneNode == ref: return True
        if cre.drawable == ref: return True
        if ref in cre.regions: return True
        if ref in cre.lights: return True
    if cre.ClassInstance(plFactory.kCoordinateInterface):
        if ref in cre.children: return True
    if cre.ClassInstance(plFactory.kDrawableSpans):
        for span in cre.spans:
            if span.fog == ref: return True
            if ref in span.permaLights: return True
            if ref in span.permaProjs: return True
        if ref in cre.materials: return True
        if cre.sceneNode == ref: return True
    if cre.ClassInstance(plFactory.kDrawInterface):
        for dk in cre.drawables:
            if dk[0] == ref: return True
        if ref in cre.regions: return True
    if cre.ClassInstance(plFactory.kGenericPhysical):
        if cre.cre.ct == ref: return True
        if cre.sceneNode == ref: return True
        if cre.subWorld == ref: return True
        if cre.soundGroup == ref: return True
    if cre.ClassInstance(plFactory.kInterfaceInfoModifier):
        if ref in cre.intfKeys: return True
    if cre.ClassInstance(plFactory.kLightInfo):
        if cre.projection == ref: return True
        if cre.softVolume == ref: return True
        if cre.sceneNode == ref: return True
        if ref in cre.visRegions: return True
    if cre.ClassInstance(plFactory.kLogicModBase):
        for cmd in cre.commands:
            if hasRef(cmd, ref): return True
        if hasRef(cre.notify, ref): return True
    if cre.ClassInstance(plFactory.kLogicModifier):
        if ref in cre.conditions: return True
    if cre.ClassInstance(plFactory.kMsgForwarder):
        if ref in cre.forwardKeys: return True
    if cre.ClassInstance(plFactory.kObjInterface):
        if cre.owner == ref: return True
    if cre.ClassInstance(plFactory.kOccluder):
        if cre.sceneNode == ref: return True
    if cre.ClassInstance(plFactory.kPythonFileMod):
        if ref in cre.receivers: return True
        for param in cre.parameters:
            if param.cre.ey == ref: return True
    if cre.ClassInstance(plFactory.kResponderModifier):
        for state in cre.states:
            for cmd in state.commands:
                if hasRef(cmd.msg, ref): return True
    if cre.ClassInstance(plFactory.kSceneNode):
        if ref in cre.sceneObjects: return True
        if ref in cre.poolObjects: return True
    if cre.ClassInstance(plFactory.kSceneObject):
        if cre.audio == ref: return True
        if cre.draw == ref: return True
        if cre.sim == ref: return True
        if cre.coord == ref: return True
        if ref in cre.modifiers: return True
        if ref in cre.interfaces: return True
        if cre.sceneNode == ref: return True
    if cre.ClassInstance(plFactory.kSimulationInterface):
        if cre.physical == ref: return True
    if cre.ClassInstance(plFactory.kViewFaceModifier):
        if cre.faceObj == ref: return True
    if cre.ClassInstance(plFactory.kWinAudible):
        if cre.sceneNode == ref: return True
        if ref in cre.sounds: return True
    if cre.ClassInstance(plFactory.kLayer):
        if cre.underLay == ref: return True
        if cre.texture == ref: return True
        if cre.vertexShader == ref: return True
        if cre.pixelShader == ref: return True

    # Non-Keyed cre.cts
    if cre.ClassInstance(plFactory.kMessage):
        if cre.sender == ref: return True
        if ref in cre.receivers: return True
    if cre.ClassInstance(plFactory.kNotifyMsg):
        for evt in cre.events:
            if proEventData_hasRef(evt, ref): return True

    return False


def fmtKey(key):
    return "%s [%s]" % (key.name, plFactory.ClassName(key.type))

def dumpTree(key, indent):
    if key in refStack: return
    refStack.append(key)

    #for i in range(indent):
    #    print("   ", end='')
    print("%s%s" % ('   '*indent, fmtKey(key)))

    for type in rm.getTypes(page.location):
        for k in rm.getKeys(page.location, type):
            if (k is not None) and hasRef(k.object, key):
                dumpTree(k, indent+1)
    refStack.pop()

####
if len(sys.argv) != 4:
    print("Usage: tracekey.py filename typename keyname")
    sys.exit(1)

rm = plResManager()
page = rm.ReadPage(sys.argv[1])
type = plFactory.ClassIndex(sys.argv[2])
skey = None

if type < 0:
    print("Type '%s' is invalid" % sys.argv[2])
    sys.exit(1)

for loc in rm.getLocations():
    klist = rm.getKeys(loc, type)
    for k in klist:
        if k.name == sys.argv[3]:
            skey = k

if skey is None:
    print("The specified key is not referenced in the PRP")
    sys.exit(1)

dumpTree(skey, 0)
