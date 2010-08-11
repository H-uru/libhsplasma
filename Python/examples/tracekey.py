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

from PyHSPlasma import *
import sys

refStack = []

def proEventData_hasRef(evt, ref):
    if evt is None:
        return False

    if evt.EventType() == proEventData.kCollision:
        obj = proCollisionEventData.Convert(evt)
        if obj.hitter == ref: return True
        if obj.hittee == ref: return True
    if evt.EventType() == proEventData.kPicked:
        obj = proPickedEventData.Convert(evt)
        if obj.picker == ref: return True
        if obj.picked == ref: return True
    if evt.EventType() == proEventData.kVariable:
        obj = proVariableEventData.Convert(evt)
        if obj.key == ref: return True
    if evt.EventType() == proEventData.kFacing:
        obj = proFacingEventData.Convert(evt)
        if obj.facer == ref: return True
        if obj.facee == ref: return True
    if evt.EventType() == proEventData.kContained:
        obj = proContainedEventData.Convert(evt)
        if obj.contained == ref: return True
        if obj.container == ref: return True
    if evt.EventType() == proEventData.kMultiStage:
        obj = proMultiStageEventData.Convert(evt)
        if obj.avatar == ref: return True
    if evt.EventType() == proEventData.kSpawned:
        obj = proSpawnedEventData.Convert(evt)
        if obj.spawner == ref: return True
        if obj.spawnee == ref: return True
    if evt.EventType() == proEventData.kOfferLinkBook:
        obj = proOfferLinkBookEventData.Convert(evt)
        if obj.offerer == ref: return True
    if evt.EventType() == proEventData.kClimbingBlockerHit:
        obj = proClimbingBlockerHitEventData.Convert(evt)
        if obj.blocker == ref: return True


def hasRef(cre, ref):
    if cre is None:
        return False

    # Keyed Objects
    if cre.ClassInstance(plFactory.kAudioInterface):
        obj = plAudioInterface.Convert(cre)
        if obj.audible == ref: return True
    if cre.ClassInstance(plFactory.kClusterGroup):
        obj = plClusterGroup.Convert(cre)
        if obj.material == ref: return True
        if obj.sceneNode == ref: return True
        if obj.drawable == ref: return True
        if ref in obj.regions: return True
        if ref in obj.lights: return True
    if cre.ClassInstance(plFactory.kCoordinateInterface):
        obj = plCoordinateInterface.Convert(cre)
        if ref in obj.children: return True
    if cre.ClassInstance(plFactory.kDrawableSpans):
        obj = plDrawableSpans.Convert(cre)
        for span in obj.spans:
            if span.fog == ref: return True
            if ref in span.permaLights: return True
            if ref in span.permaProjs: return True
        if ref in obj.materials: return True
        if obj.sceneNode == ref: return True
    if cre.ClassInstance(plFactory.kDrawInterface):
        obj = plDrawInterface.Convert(cre)
        for dk in obj.drawables:
            if dk[0] == ref: return True
        if ref in obj.regions: return True
    if cre.ClassInstance(plFactory.kGenericPhysical):
        obj = plGenericPhysical.Convert(cre)
        if obj.object == ref: return True
        if obj.sceneNode == ref: return True
        if obj.subWorld == ref: return True
        if obj.soundGroup == ref: return True
    if cre.ClassInstance(plFactory.kInterfaceInfoModifier):
        obj = plInterfaceInfoModifier.Convert(cre)
        if ref in obj.intfKeys: return True
    if cre.ClassInstance(plFactory.kLightInfo):
        obj = plLightInfo.Convert(cre)
        if obj.projection == ref: return True
        if obj.softVolume == ref: return True
        if obj.sceneNode == ref: return True
        if ref in obj.visRegions: return True
    if cre.ClassInstance(plFactory.kLogicModBase):
        obj = plLogicModBase.Convert(cre)
        for cmd in obj.commands:
            if hasRef(cmd, ref): return True
        if hasRef(obj.notify, ref): return True
    if cre.ClassInstance(plFactory.kLogicModifier):
        obj = plLogicModifier.Convert(cre)
        if ref in obj.conditions: return True
    if cre.ClassInstance(plFactory.kMsgForwarder):
        obj = plMsgForwarder.Convert(cre)
        if ref in obj.forwardKeys: return True
    if cre.ClassInstance(plFactory.kObjInterface):
        obj = plObjInterface.Convert(cre)
        if obj.owner == ref: return True
    if cre.ClassInstance(plFactory.kOccluder):
        obj = plOccluder.Convert(cre)
        if obj.sceneNode == ref: return True
    if cre.ClassInstance(plFactory.kPythonFileMod):
        obj = plPythonFileMod.Convert(cre)
        if ref in obj.receivers: return True
        for param in obj.parameters:
            if param.objKey == ref: return True
    if cre.ClassInstance(plFactory.kResponderModifier):
        obj = plResponderModifier.Convert(cre)
        for state in obj.states:
            for cmd in state.commands:
                if hasRef(cmd.msg, ref): return True
    if cre.ClassInstance(plFactory.kSceneNode):
        obj = plSceneNode.Convert(cre)
        if ref in obj.sceneObjects: return True
        if ref in obj.poolObjects: return True
    if cre.ClassInstance(plFactory.kSceneObject):
        obj = plSceneObject.Convert(cre)
        if obj.audio == ref: return True
        if obj.draw == ref: return True
        if obj.sim == ref: return True
        if obj.coord == ref: return True
        if ref in obj.modifiers: return True
        if ref in obj.interfaces: return True
        if obj.sceneNode == ref: return True
    if cre.ClassInstance(plFactory.kSimulationInterface):
        obj = plSimulationInterface.Convert(cre)
        if obj.physical == ref: return True
    if cre.ClassInstance(plFactory.kViewFaceModifier):
        obj = plViewFaceModifier.Convert(cre)
        if obj.faceObj == ref: return True
    if cre.ClassInstance(plFactory.kWinAudible):
        obj = plWinAudible.Convert(cre)
        if obj.sceneNode == ref: return True
        if ref in obj.sounds: return True
    if cre.ClassInstance(plFactory.kLayer):
        obj = plLayer.Convert(cre)
        if obj.underLay == ref: return True
        if obj.texture == ref: return True
        if obj.vertexShader == ref: return True
        if obj.pixelShader == ref: return True

    # Non-Keyed objects
    if cre.ClassInstance(plFactory.kMessage):
        obj = plMessage.Convert(cre)
        if obj.sender == ref: return True
        if ref in obj.receivers: return True
    if cre.ClassInstance(plFactory.kNotifyMsg):
        obj = plNotifyMsg.Convert(cre)
        for evt in obj.events:
            if proEventData_hasRef(evt, ref): return True

    return False


def fmtKey(key):
    return "%s [%s]" % (key.name, plFactory.ClassName(key.type))

def dumpTree(key, indent):
    if key in refStack: return
    refStack.append(key)

    for i in range(indent):
        print "   ",
    print fmtKey(key)

    for type in rm.getTypes(page.location):
        for k in rm.getKeys(page.location, type):
            if (k is not None) and hasRef(k.object, key):
                dumpTree(k, indent+1)
    refStack.pop()

####
if len(sys.argv) != 4:
    print "Usage: tracekey.py filename typename keyname"
    sys.exit(1)

rm = plResManager()
page = rm.ReadPage(sys.argv[1])
type = plFactory.ClassIndex(sys.argv[2])
skey = None

if type < 0:
    print "Type '%s' is invalid" % sys.argv[2]
    sys.exit(1)

for loc in rm.getLocations():
    klist = rm.getKeys(loc, type)
    for k in klist:
        if k.name == sys.argv[3]:
            skey = k

if skey is None:
    print "The specified key is not referenced in the PRP"
    sys.exit(1)

dumpTree(skey, 0)
