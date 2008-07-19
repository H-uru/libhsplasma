CXX = g++
CXXFLAGS = -I../core -fPIC -Wall -g -ansi -fno-rtti `python-config --cflags`
CXXLINK  = -L../core/lib -lPlasma

OBJDIR=out/

PYOBJ=\
	$(OBJDIR)Module.o \
	$(OBJDIR)pyStream.o \
	$(OBJDIR)pyFileStream.o

PYLIB=PyPlasma.so

all: $(PYLIB)

$(PYLIB): $(PYOBJ)
	$(CXX) $(CXXFLAGS) $(PYOBJ) $(CXXLINK) -shared -Wl-soname,PyPlasma.so -o $(PYLIB)

install:
	cp $(PYLIB) /usr/local/lib
	ldconfig

clean:
	rm -f $(PYOBJ)

distclean:
	rm -f $(PYLIB)

$(OBJDIR)Module.o: Module.cpp
	$(CXX) $(CXXFLAGS) -c Module.cpp -o $(OBJDIR)Module.o

$(OBJDIR)pyStream.o: Stream/pyStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pyStream.cpp -o $(OBJDIR)pyStream.o

$(OBJDIR)pyFileStream.o: Stream/pyFileStream.cpp
	$(CXX) $(CXXFLAGS) -c Stream/pyFileStream.cpp -o $(OBJDIR)pyFileStream.o
