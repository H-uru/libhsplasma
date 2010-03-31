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

uninstall:
	rm -f $(PREFIX)/lib/$(PLSLIB)

clean:
	rm -f $(PLSOBJ)

distclean:
	rm -f $(LIBDIR)/$(PLSLIB)

# HSPlasma Net Lib
$(OBJDIR)pnClient.o: pnClient.h pnClient.cpp
	$(CXX) $(CXXFLAGS) -c pnClient.cpp -o $@

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

$(OBJDIR)pnAuthClient.o: auth/pnAuthClient.h auth/pnAuthClient.cpp
	$(CXX) $(CXXFLAGS) -c auth/pnAuthClient.cpp -o $@

$(OBJDIR)pnVaultNode.o: auth/pnVaultNode.h auth/pnVaultNode.cpp
	$(CXX) $(CXXFLAGS) -c auth/pnVaultNode.cpp -o $@

$(OBJDIR)GameMessages.o: game/GameMessages.h game/GameMessages.cpp
	$(CXX) $(CXXFLAGS) -c game/GameMessages.cpp -o $@

$(OBJDIR)pnGameClient.o: game/pnGameClient.h game/pnGameClient.cpp
	$(CXX) $(CXXFLAGS) -c game/pnGameClient.cpp -o $@

$(OBJDIR)GateKeeperMessages.o: gate/GateKeeperMessages.h gate/GateKeeperMessages.cpp
	$(CXX) $(CXXFLAGS) -c gate/GateKeeperMessages.cpp -o $@

$(OBJDIR)pnGateKeeperClient.o: gate/pnGateKeeperClient.h gate/pnGateKeeperClient.cpp
	$(CXX) $(CXXFLAGS) -c gate/pnGateKeeperClient.cpp -o $@

$(OBJDIR)pnFileClient.o: file/pnFileClient.h file/pnFileClient.cpp
	$(CXX) $(CXXFLAGS) -c file/pnFileClient.cpp -o $@
