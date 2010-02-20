include ../config.mf

CXXFLAGS += -I../core
CXXLINK  += -L../lib -lPlasma -lssl
OBJDIR=out/

PLSOBJ=\
	$(OBJDIR)pnSocket.o

PLSLIB=libPlasmaNet.so
LIBDIR=../lib

all: $(LIBDIR)/$(PLSLIB)

$(LIBDIR)/$(PLSLIB): $(PLSOBJ)
	$(CXX) $(CXXFLAGS) $(CXXLINK) $(PLSOBJ) -shared -Wl,-soname,$(PLSLIB) -o $@

install:
	cp $(LIBDIR)/$(PLSLIB) $(PREFIX)/lib
	ldconfig

uninstall:
	rm -f $(PREFIX)/lib/$(PLSLIB)

clean:
	rm -f $(PLSOBJ)

distclean:
	rm -f $(LIBDIR)/$(PLSLIB)

# Plasma Net Lib
$(OBJDIR)pnSocket.o: pnSocket.h pnSocket.cpp
	$(CXX) $(CXXFLAGS) -c pnSocket.cpp -o $@
