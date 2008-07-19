CXX = g++
CXXFLAGS = -I../core -fPIC -Wall -g -ansi -fno-rtti `python-config --cflags`
CXXLINK  = -L../core/lib -lPlasma

OBJDIR=out/

PYOBJ=\
	$(OBJDIR)Module.o \
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
