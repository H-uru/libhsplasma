include ../config.mf

CXXFLAGS += -I. -I../core $(CXXFLAGS_NET)
CXXLINK  += -L../lib -lPlasma $(CXXLINK_NET)
OBJDIR=out/

PLSOBJ=\
	$(OBJDIR)pnNetMsg.o \
	$(OBJDIR)pnSocket.o \
	$(OBJDIR)pnBigInteger.o \
	$(OBJDIR)pnRC4.o \
	$(OBJDIR)pnSha1.o \
	$(OBJDIR)AuthMessages.o \
	$(OBJDIR)pnVaultNode.o

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
$(OBJDIR)pnNetMsg.o: pnNetMsg.h pnNetMsg.cpp
	$(CXX) $(CXXFLAGS) -c pnNetMsg.cpp -o $@

$(OBJDIR)pnSocket.o: pnSocket.h pnSocket.cpp
	$(CXX) $(CXXFLAGS) -c pnSocket.cpp -o $@

$(OBJDIR)pnBigInteger.o: crypt/pnBigInteger.h crypt/pnBigInteger.cpp
	$(CXX) $(CXXFLAGS) -c crypt/pnBigInteger.cpp -o $@

$(OBJDIR)pnRC4.o: crypt/pnRC4.h crypt/pnRC4.cpp
	$(CXX) $(CXXFLAGS) -c crypt/pnRC4.cpp -o $@

$(OBJDIR)pnSha1.o: crypt/pnSha1.h crypt/pnSha1.cpp
	$(CXX) $(CXXFLAGS) -c crypt/pnSha1.cpp -o $@

$(OBJDIR)AuthMessages.o: auth/AuthMessages.h auth/AuthMessages.cpp
	$(CXX) $(CXXFLAGS) -c auth/AuthMessages.cpp -o $@

$(OBJDIR)pnVaultNode.o: auth/pnVaultNode.h auth/pnVaultNode.cpp
	$(CXX) $(CXXFLAGS) -c auth/pnVaultNode.cpp -o $@
