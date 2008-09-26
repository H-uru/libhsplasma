CXX = g++
CXXFLAGS = -I../core -fPIC -Wall -g -ansi -fno-rtti `python-config --cflags`
CXXLINK  = -L../core/lib -lPlasma

OBJDIR=out/

PYOBJ=\
	$(OBJDIR)Module.o \
	$(OBJDIR)pyDebug.o \
	$(OBJDIR)pyMatrix44.o \
	$(OBJDIR)pyPlane3.o \
	$(OBJDIR)pyQuat.o \
	$(OBJDIR)pyVector3.o \
	$(OBJDIR)pyCreatable.o \
	$(OBJDIR)pyCreatableStub.o \
	$(OBJDIR)pySceneNode.o \
	$(OBJDIR)pySoundBuffer.o \
	$(OBJDIR)pyWAVHeader.o \
	$(OBJDIR)pyDISpanIndex.o \
	$(OBJDIR)pyDrawable.o \
	$(OBJDIR)pyDrawableSpans.o \
	$(OBJDIR)pyGBufferCell.o \
	$(OBJDIR)pyGBufferGroup.o \
	$(OBJDIR)pyGBufferTriangle.o \
	$(OBJDIR)pyGBufferVertex.o \
	$(OBJDIR)pyIcicle.o \
	$(OBJDIR)pyParticleSpan.o \
	$(OBJDIR)pySpaceTree.o \
	$(OBJDIR)pySpaceTreeNode.o \
	$(OBJDIR)pySpan.o \
	$(OBJDIR)pyVertexSpan.o \
	$(OBJDIR)pyKey.o \
	$(OBJDIR)pyKeyedObject.o \
	$(OBJDIR)pyLocation.o \
	$(OBJDIR)pyDirectionalLightInfo.o \
	$(OBJDIR)pyLightInfo.o \
	$(OBJDIR)pyLimitedDirLightInfo.o \
	$(OBJDIR)pyOmniLightInfo.o \
	$(OBJDIR)pySpotLightInfo.o \
	$(OBJDIR)pyRenderLevel.o \
	$(OBJDIR)pyAudioInterface.o \
	$(OBJDIR)pyCoordinateInterface.o \
	$(OBJDIR)pyDrawInterface.o \
	$(OBJDIR)pyObjInterface.o \
	$(OBJDIR)pySceneObject.o \
	$(OBJDIR)pySimulationInterface.o \
	$(OBJDIR)pySynchedObject.o \
	$(OBJDIR)pyGenericPhysical.o \
	$(OBJDIR)pyPhysical.o \
	$(OBJDIR)pySimDefs.o \
	$(OBJDIR)pyBounds.o \
	$(OBJDIR)pyBounds3.o \
	$(OBJDIR)pyBounds3Ext.o \
	$(OBJDIR)pyBoundsOriented.o \
	$(OBJDIR)pyBitmap.o \
	$(OBJDIR)pyGMaterial.o \
	$(OBJDIR)pyGMatState.o \
	$(OBJDIR)pyLayer.o \
	$(OBJDIR)pyLayerDepth.o \
	$(OBJDIR)pyLayerInterface.o \
	$(OBJDIR)pyMipmap.o \
	$(OBJDIR)pyShader.o \
	$(OBJDIR)pyShaderConst.o \
	$(OBJDIR)pyAgeInfo.o \
	$(OBJDIR)pyFactory.o \
	$(OBJDIR)pyResManager.o \
	$(OBJDIR)pyPageInfo.o \
	$(OBJDIR)pyEncryptedStream.o \
	$(OBJDIR)pyFileStream.o \
	$(OBJDIR)pyStream.o \
	$(OBJDIR)pyColor32.o \
	$(OBJDIR)pyColorRGBA.o \
	$(OBJDIR)pyBitVector.o

PYLIB=PyPlasma.so

all: $(PYLIB)

$(PYLIB): $(PYOBJ)
	$(CXX) $(CXXFLAGS) $(PYOBJ) $(CXXLINK) -shared -Wl-soname,PyPlasma.so -o $(PYLIB)

clean:
	rm -f $(PYOBJ)

distclean:
	rm -f $(PYLIB)

$(OBJDIR)Module.o: Module.cpp
	$(CXX) $(CXXFLAGS) -c Module.cpp -o $(OBJDIR)Module.o

$(OBJDIR)pyDebug.o: Debug/pyDebug.cpp
	$(CXX) $(CXXFLAGS) -c Debug/pyDebug.cpp -o $(OBJDIR)pyDebug.o

$(OBJDIR)pyMatrix44.o: Math/pyMatrix44.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyMatrix44.cpp -o $(OBJDIR)pyMatrix44.o

$(OBJDIR)pyPlane3.o: Math/pyPlane3.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyPlane3.cpp -o $(OBJDIR)pyPlane3.o

$(OBJDIR)pyQuat.o: Math/pyQuat.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyQuat.cpp -o $(OBJDIR)pyQuat.o

$(OBJDIR)pyVector3.o: Math/pyVector3.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyVector3.cpp -o $(OBJDIR)pyVector3.o

$(OBJDIR)pyCreatable.o: PRP/pyCreatable.cpp
	$(CXX) $(CXXFLAGS) -c PRP/pyCreatable.cpp -o $(OBJDIR)pyCreatable.o

$(OBJDIR)pyCreatableStub.o: PRP/pyCreatableStub.cpp
	$(CXX) $(CXXFLAGS) -c PRP/pyCreatableStub.cpp -o $(OBJDIR)pyCreatableStub.o

$(OBJDIR)pySceneNode.o: PRP/pySceneNode.cpp
	$(CXX) $(CXXFLAGS) -c PRP/pySceneNode.cpp -o $(OBJDIR)pySceneNode.o

$(OBJDIR)pySoundBuffer.o: PRP/Audio/pySoundBuffer.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/pySoundBuffer.cpp -o $(OBJDIR)pySoundBuffer.o

$(OBJDIR)pyWAVHeader.o: PRP/Audio/pyWAVHeader.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Audio/pyWAVHeader.cpp -o $(OBJDIR)pyWAVHeader.o

$(OBJDIR)pyDISpanIndex.o: PRP/Geometry/pyDISpanIndex.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyDISpanIndex.cpp -o $(OBJDIR)pyDISpanIndex.o

$(OBJDIR)pyDrawable.o: PRP/Geometry/pyDrawable.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyDrawable.cpp -o $(OBJDIR)pyDrawable.o

$(OBJDIR)pyDrawableSpans.o: PRP/Geometry/pyDrawableSpans.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyDrawableSpans.cpp -o $(OBJDIR)pyDrawableSpans.o

$(OBJDIR)pyGBufferCell.o: PRP/Geometry/pyGBufferCell.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyGBufferCell.cpp -o $(OBJDIR)pyGBufferCell.o

$(OBJDIR)pyGBufferGroup.o: PRP/Geometry/pyGBufferGroup.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyGBufferGroup.cpp -o $(OBJDIR)pyGBufferGroup.o

$(OBJDIR)pyGBufferTriangle.o: PRP/Geometry/pyGBufferTriangle.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyGBufferTriangle.cpp -o $(OBJDIR)pyGBufferTriangle.o

$(OBJDIR)pyGBufferVertex.o: PRP/Geometry/pyGBufferVertex.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyGBufferVertex.cpp -o $(OBJDIR)pyGBufferVertex.o

$(OBJDIR)pyIcicle.o: PRP/Geometry/pyIcicle.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyIcicle.cpp -o $(OBJDIR)pyIcicle.o

$(OBJDIR)pyParticleSpan.o: PRP/Geometry/pyParticleSpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyParticleSpan.cpp -o $(OBJDIR)pyParticleSpan.o

$(OBJDIR)pySpaceTree.o: PRP/Geometry/pySpaceTree.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pySpaceTree.cpp -o $(OBJDIR)pySpaceTree.o

$(OBJDIR)pySpaceTreeNode.o: PRP/Geometry/pySpaceTreeNode.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pySpaceTreeNode.cpp -o $(OBJDIR)pySpaceTreeNode.o

$(OBJDIR)pySpan.o: PRP/Geometry/pySpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pySpan.cpp -o $(OBJDIR)pySpan.o

$(OBJDIR)pyVertexSpan.o: PRP/Geometry/pyVertexSpan.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Geometry/pyVertexSpan.cpp -o $(OBJDIR)pyVertexSpan.o

$(OBJDIR)pyKey.o: PRP/KeyedObject/pyKey.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/pyKey.cpp -o $(OBJDIR)pyKey.o

$(OBJDIR)pyKeyedObject.o: PRP/KeyedObject/pyKeyedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/pyKeyedObject.cpp -o $(OBJDIR)pyKeyedObject.o

$(OBJDIR)pyLocation.o: PRP/KeyedObject/pyLocation.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/pyLocation.cpp -o $(OBJDIR)pyLocation.o

$(OBJDIR)pyDirectionalLightInfo.o: PRP/Light/pyDirectionalLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pyDirectionalLightInfo.cpp -o $(OBJDIR)pyDirectionalLightInfo.o

$(OBJDIR)pyLightInfo.o: PRP/Light/pyLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pyLightInfo.cpp -o $(OBJDIR)pyLightInfo.o

$(OBJDIR)pyLimitedDirLightInfo.o: PRP/Light/pyLimitedDirLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pyLimitedDirLightInfo.cpp -o $(OBJDIR)pyLimitedDirLightInfo.o

$(OBJDIR)pyOmniLightInfo.o: PRP/Light/pyOmniLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pyOmniLightInfo.cpp -o $(OBJDIR)pyOmniLightInfo.o

$(OBJDIR)pySpotLightInfo.o: PRP/Light/pySpotLightInfo.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Light/pySpotLightInfo.cpp -o $(OBJDIR)pySpotLightInfo.o

$(OBJDIR)pyRenderLevel.o: PRP/Misc/pyRenderLevel.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Misc/pyRenderLevel.cpp -o $(OBJDIR)pyRenderLevel.o

$(OBJDIR)pyAudioInterface.o: PRP/Object/pyAudioInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pyAudioInterface.cpp -o $(OBJDIR)pyAudioInterface.o

$(OBJDIR)pyCoordinateInterface.o: PRP/Object/pyCoordinateInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pyCoordinateInterface.cpp -o $(OBJDIR)pyCoordinateInterface.o

$(OBJDIR)pyDrawInterface.o: PRP/Object/pyDrawInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pyDrawInterface.cpp -o $(OBJDIR)pyDrawInterface.o

$(OBJDIR)pyObjInterface.o: PRP/Object/pyObjInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pyObjInterface.cpp -o $(OBJDIR)pyObjInterface.o

$(OBJDIR)pySceneObject.o: PRP/Object/pySceneObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pySceneObject.cpp -o $(OBJDIR)pySceneObject.o

$(OBJDIR)pySimulationInterface.o: PRP/Object/pySimulationInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pySimulationInterface.cpp -o $(OBJDIR)pySimulationInterface.o

$(OBJDIR)pySynchedObject.o: PRP/Object/pySynchedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pySynchedObject.cpp -o $(OBJDIR)pySynchedObject.o

$(OBJDIR)pyGenericPhysical.o: PRP/Physics/pyGenericPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/pyGenericPhysical.cpp -o $(OBJDIR)pyGenericPhysical.o

$(OBJDIR)pyPhysical.o: PRP/Physics/pyPhysical.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/pyPhysical.cpp -o $(OBJDIR)pyPhysical.o

$(OBJDIR)pySimDefs.o: PRP/Physics/pySimDefs.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Physics/pySimDefs.cpp -o $(OBJDIR)pySimDefs.o

$(OBJDIR)pyBounds.o: PRP/Region/pyBounds.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/pyBounds.cpp -o $(OBJDIR)pyBounds.o

$(OBJDIR)pyBounds3.o: PRP/Region/pyBounds3.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/pyBounds3.cpp -o $(OBJDIR)pyBounds3.o

$(OBJDIR)pyBounds3Ext.o: PRP/Region/pyBounds3Ext.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/pyBounds3Ext.cpp -o $(OBJDIR)pyBounds3Ext.o

$(OBJDIR)pyBoundsOriented.o: PRP/Region/pyBoundsOriented.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Region/pyBoundsOriented.cpp -o $(OBJDIR)pyBoundsOriented.o

$(OBJDIR)pyBitmap.o: PRP/Surface/pyBitmap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyBitmap.cpp -o $(OBJDIR)pyBitmap.o

$(OBJDIR)pyGMaterial.o: PRP/Surface/pyGMaterial.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyGMaterial.cpp -o $(OBJDIR)pyGMaterial.o

$(OBJDIR)pyGMatState.o: PRP/Surface/pyGMatState.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyGMatState.cpp -o $(OBJDIR)pyGMatState.o

$(OBJDIR)pyLayer.o: PRP/Surface/pyLayer.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayer.cpp -o $(OBJDIR)pyLayer.o

$(OBJDIR)pyLayerDepth.o: PRP/Surface/pyLayerDepth.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayerDepth.cpp -o $(OBJDIR)pyLayerDepth.o

$(OBJDIR)pyLayerInterface.o: PRP/Surface/pyLayerInterface.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyLayerInterface.cpp -o $(OBJDIR)pyLayerInterface.o

$(OBJDIR)pyMipmap.o: PRP/Surface/pyMipmap.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyMipmap.cpp -o $(OBJDIR)pyMipmap.o

$(OBJDIR)pyShader.o: PRP/Surface/pyShader.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyShader.cpp -o $(OBJDIR)pyShader.o

$(OBJDIR)pyShaderConst.o: PRP/Surface/pyShaderConst.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Surface/pyShaderConst.cpp -o $(OBJDIR)pyShaderConst.o

$(OBJDIR)pyAgeInfo.o: ResManager/pyAgeInfo.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/pyAgeInfo.cpp -o $(OBJDIR)pyAgeInfo.o

$(OBJDIR)pyFactory.o: ResManager/pyFactory.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/pyFactory.cpp -o $(OBJDIR)pyFactory.o

$(OBJDIR)pyResManager.o: ResManager/pyResManager.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/pyResManager.cpp -o $(OBJDIR)pyResManager.o

$(OBJDIR)pyPageInfo.o: ResManager/pyPageInfo.cpp
	$(CXX) $(CXXFLAGS) -c ResManager/pyPageInfo.cpp -o $(OBJDIR)pyPageInfo.o

$(OBJDIR)pyEncryptedStream.o: Stream/pyEncryptedStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pyEncryptedStream.cpp -o $(OBJDIR)pyEncryptedStream.o

$(OBJDIR)pyFileStream.o: Stream/pyFileStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pyFileStream.cpp -o $(OBJDIR)pyFileStream.o

$(OBJDIR)pyStream.o: Stream/pyStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pyStream.cpp -o $(OBJDIR)pyStream.o

$(OBJDIR)pyColor32.o: Sys/pyColor32.cpp
	$(CXX) $(CXXFLAGS) -c Sys/pyColor32.cpp -o $(OBJDIR)pyColor32.o

$(OBJDIR)pyColorRGBA.o: Sys/pyColorRGBA.cpp
	$(CXX) $(CXXFLAGS) -c Sys/pyColorRGBA.cpp -o $(OBJDIR)pyColorRGBA.o

$(OBJDIR)pyBitVector.o: Util/pyBitVector.cpp
	$(CXX) $(CXXFLAGS) -c Util/pyBitVector.cpp -o $(OBJDIR)pyBitVector.o
