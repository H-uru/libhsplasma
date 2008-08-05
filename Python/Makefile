CXX = g++
CXXFLAGS = -I../core -fPIC -Wall -g -ansi -fno-rtti `python-config --cflags`
CXXLINK  = -L../core/lib -lPlasma

OBJDIR=out/

PYOBJ=\
	$(OBJDIR)Module.o \
	$(OBJDIR)pyMatrix44.o \
	$(OBJDIR)pyVector3.o \
	$(OBJDIR)pyCreatable.o \
	$(OBJDIR)pyCreatableStub.o \
	$(OBJDIR)pySceneNode.o \
	$(OBJDIR)pyKey.o \
	$(OBJDIR)pyKeyedObject.o \
	$(OBJDIR)pyLocation.o \
	$(OBJDIR)pySceneObject.o \
	$(OBJDIR)pySynchedObject.o \
	$(OBJDIR)pyAgeInfo.o \
	$(OBJDIR)pyFactory.o \
	$(OBJDIR)pyResManager.o \
	$(OBJDIR)pyPageInfo.o \
	$(OBJDIR)pyEncryptedStream.o \
	$(OBJDIR)pyFileStream.o \
	$(OBJDIR)pyStream.o \
	$(OBJDIR)pyColor32.o \
	$(OBJDIR)pyColorRGBA.o \
	$(OBJDIR)pyBitVector.o \

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

$(OBJDIR)pyMatrix44.o: Math/pyMatrix44.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyMatrix44.cpp -o $(OBJDIR)pyMatrix44.o

$(OBJDIR)pyVector3.o: Math/pyVector3.cpp
	$(CXX) $(CXXFLAGS) -c Math/pyVector3.cpp -o $(OBJDIR)pyVector3.o

$(OBJDIR)pyCreatable.o: PRP/pyCreatable.cpp
	$(CXX) $(CXXFLAGS) -c PRP/pyCreatable.cpp -o $(OBJDIR)pyCreatable.o

$(OBJDIR)pyCreatableStub.o: PRP/pyCreatableStub.cpp
	$(CXX) $(CXXFLAGS) -c PRP/pyCreatableStub.cpp -o $(OBJDIR)pyCreatableStub.o

$(OBJDIR)pySceneNode.o: PRP/pySceneNode.cpp
	$(CXX) $(CXXFLAGS) -c PRP/pySceneNode.cpp -o $(OBJDIR)pySceneNode.o

$(OBJDIR)pyKey.o: PRP/KeyedObject/pyKey.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/pyKey.cpp -o $(OBJDIR)pyKey.o

$(OBJDIR)pyKeyedObject.o: PRP/KeyedObject/pyKeyedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/pyKeyedObject.cpp -o $(OBJDIR)pyKeyedObject.o

$(OBJDIR)pyLocation.o: PRP/KeyedObject/pyLocation.cpp
	$(CXX) $(CXXFLAGS) -c PRP/KeyedObject/pyLocation.cpp -o $(OBJDIR)pyLocation.o

$(OBJDIR)pySceneObject.o: PRP/Object/pySceneObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pySceneObject.cpp -o $(OBJDIR)pySceneObject.o

$(OBJDIR)pySynchedObject.o: PRP/Object/pySynchedObject.cpp
	$(CXX) $(CXXFLAGS) -c PRP/Object/pySynchedObject.cpp -o $(OBJDIR)pySynchedObject.o

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
