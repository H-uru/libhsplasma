include ../config.mf

CXXFLAGS += -I. -I../core $(CXXFLAGS_NET)
CXXLINK  += -L../lib -lHSPlasma $(CXXLINK_NET)
OBJDIR=out/

PLSOBJ=\
	$(OBJDIR)pnClient.o \
	$(OBJDIR)pnNetMsg.o \
	$(OBJDIR)pnSocket.o \
	$(OBJDIR)pnBigInteger.o \
	$(OBJDIR)pnRC4.o \
	$(OBJDIR)pnSha1.o \
	$(OBJDIR)AuthMessages.o \
	$(OBJDIR)pnAuthClient.o \
	$(OBJDIR)pnVaultNode.o \
	$(OBJDIR)GameMessages.o \
	$(OBJDIR)pnGameClient.o \
	$(OBJDIR)GateKeeperMessages.o \
	$(OBJDIR)pnGateKeeperClient.o \
	$(OBJDIR)pnFileClient.o

PLSHEADERS=\
	pnClient.h \
	pnNetMsg.h \
	pnSocket.h \
	Protocol.h \
	auth/AuthMessages.h \
	auth/pnAuthClient.h \
	auth/pnVaultNode.h \
	crypt/pnBigInteger.h \
	crypt/pnRC4.h \
	crypt/pnSha1.h \
	file/FileMessages.h \
	file/pnFileClient.h \
	game/GameMessages.h \
	game/pnGameClient.h \
	gate/GateKeeperMessages.h \
	gate/pnGateKeeperClient.h

PLSLIB=libHSPlasmaNet.$(LIBSUFFIX)
LIBDIR=../lib

all: $(LIBDIR)/$(PLSLIB)

$(LIBDIR)/$(PLSLIB): $(PLSOBJ)
	$(CXX) $(CXXFLAGS) $(CXXLINK) $(PLSOBJ) $(LINKLIB)$(PLSLIB) -o $@

install:
	cp $(LIBDIR)/$(PLSLIB) $(PREFIX)/lib
ifneq ($(LIBSUFFIX),dylib)
	ldconfig
endif

install-dev: install
	mkdir -p $(PREFIX)/include/libhsplasmanet
	cp --parents $(PLSHEADERS) $(PREFIX)/include/libhsplasmanet

uninstall:
	rm -f $(PREFIX)/lib/$(PLSLIB)
	rm -rf $(PREFIX)/include/libhsplasmanet

clean:
	rm -f $(PLSOBJ)

distclean:
	rm -f $(LIBDIR)/$(PLSLIB)

# HSPlasma Net Lib
$(OBJDIR)pnClient.o: $(PLSHEADERS) pnClient.cpp
	$(CXX) $(CXXFLAGS) -c pnClient.cpp -o $@

$(OBJDIR)pnNetMsg.o: $(PLSHEADERS) pnNetMsg.cpp
	$(CXX) $(CXXFLAGS) -c pnNetMsg.cpp -o $@

$(OBJDIR)pnSocket.o: $(PLSHEADERS) pnSocket.cpp
	$(CXX) $(CXXFLAGS) -c pnSocket.cpp -o $@

$(OBJDIR)pnBigInteger.o: $(PLSHEADERS) crypt/pnBigInteger.cpp
	$(CXX) $(CXXFLAGS) -c crypt/pnBigInteger.cpp -o $@

$(OBJDIR)pnRC4.o: $(PLSHEADERS) crypt/pnRC4.cpp
	$(CXX) $(CXXFLAGS) -c crypt/pnRC4.cpp -o $@

$(OBJDIR)pnSha1.o: $(PLSHEADERS) crypt/pnSha1.cpp
	$(CXX) $(CXXFLAGS) -c crypt/pnSha1.cpp -o $@

$(OBJDIR)AuthMessages.o: $(PLSHEADERS) auth/AuthMessages.cpp
	$(CXX) $(CXXFLAGS) -c auth/AuthMessages.cpp -o $@

$(OBJDIR)pnAuthClient.o: $(PLSHEADERS) auth/pnAuthClient.cpp
	$(CXX) $(CXXFLAGS) -c auth/pnAuthClient.cpp -o $@

$(OBJDIR)pnVaultNode.o: $(PLSHEADERS) auth/pnVaultNode.cpp
	$(CXX) $(CXXFLAGS) -c auth/pnVaultNode.cpp -o $@

$(OBJDIR)GameMessages.o: $(PLSHEADERS) game/GameMessages.cpp
	$(CXX) $(CXXFLAGS) -c game/GameMessages.cpp -o $@

$(OBJDIR)pnGameClient.o: $(PLSHEADERS) game/pnGameClient.cpp
	$(CXX) $(CXXFLAGS) -c game/pnGameClient.cpp -o $@

$(OBJDIR)GateKeeperMessages.o: $(PLSHEADERS) gate/GateKeeperMessages.cpp
	$(CXX) $(CXXFLAGS) -c gate/GateKeeperMessages.cpp -o $@

$(OBJDIR)pnGateKeeperClient.o: $(PLSHEADERS) gate/pnGateKeeperClient.cpp
	$(CXX) $(CXXFLAGS) -c gate/pnGateKeeperClient.cpp -o $@

$(OBJDIR)pnFileClient.o: $(PLSHEADERS) file/pnFileClient.cpp
	$(CXX) $(CXXFLAGS) -c file/pnFileClient.cpp -o $@
