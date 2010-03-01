include config.mf

CXXFLAGS += -Icore

all:
	(cd core ; $(MAKE))
ifneq ($(MAKE_NET),no)
	(cd net ; $(MAKE))
endif
ifneq ($(PYTHON_VER),no)
	(cd Python ; $(MAKE))
endif
	($(MAKE) bin/PageConvert)
	($(MAKE) bin/PlasmaCrypt)
	($(MAKE) bin/PrpPack)
	($(MAKE) bin/PrcExtract)
	($(MAKE) bin/PageList)
	($(MAKE) bin/prcc)
	($(MAKE) bin/prcdc)
	($(MAKE) bin/Prp2Obj)
	($(MAKE) bin/PyPack)
	($(MAKE) bin/prpmod)
	($(MAKE) bin/prpgrep)
#	($(MAKE) bin/prp-fuse)
	($(MAKE) bin/PlasmaSum)
	($(MAKE) Misc/TypeMap)

bin/PageConvert: Tools/src/PageConvert.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/PageConvert.cpp -o $@

bin/PlasmaCrypt: Tools/src/PlasmaCrypt.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/PlasmaCrypt.cpp -o $@

bin/PrpPack: Tools/src/PrpPack.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/PrpPack.cpp -o $@

bin/PrcExtract: Tools/src/PrcExtract.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/PrcExtract.cpp -o $@

bin/PageList: Tools/src/PageList.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/PageList.cpp -o $@

bin/prcc: Tools/src/prcc.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/prcc.cpp -o $@

bin/prcdc: Tools/src/prcdc.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/prcdc.cpp -o $@

bin/Prp2Obj: Tools/src/Prp2Obj.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/Prp2Obj.cpp -o $@

bin/PyPack: Tools/src/PyPack.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/PyPack.cpp -o $@

bin/prpmod: Tools/src/prpmod.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/prpmod.cpp -o $@

bin/prpgrep: Tools/src/prpgrep.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/prpgrep.cpp -o $@

#lib/prp-fuse: Tools/src/prp-fuse.cpp lib/libHSPlasma.$(LIBSUFFIX)
#	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma -lfuse Tools/src/prp-fuse.cpp -o $@

bin/PlasmaSum: Tools/src/PlasmaSum.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Tools/src/PlasmaSum.cpp -o $@

Misc/TypeMap: Misc/TypeMap.cpp lib/libHSPlasma.$(LIBSUFFIX)
	$(CXX) $(CXXFLAGS) -Llib -lHSPlasma Misc/TypeMap.cpp -o $@

install:
	(cd core ; $(MAKE) install)
ifneq ($(MAKE_NET),no)
	(cd net ; $(MAKE) install)
endif
ifneq ($(PYTHON_VER),no)
	(cd Python ; $(MAKE) install)
endif
	cp bin/PageConvert $(PREFIX)/bin/
	cp bin/PlasmaCrypt $(PREFIX)/bin/
	cp bin/PrpPack $(PREFIX)/bin/
	cp bin/PrcExtract $(PREFIX)/bin/
	cp bin/PageList $(PREFIX)/bin/
	cp bin/prcc $(PREFIX)/bin/
	cp bin/prcdc $(PREFIX)/bin/
	cp bin/Prp2Obj $(PREFIX)/bin/
	cp bin/PyPack $(PREFIX)/bin/
	cp bin/prpmod $(PREFIX)/bin/
	cp bin/prpgrep $(PREFIX)/bin/
#	cp bin/prp-fuse $(PREFIX)/bin/
	cp bin/PlasmaSum $(PREFIX)/bin/
	chmod +x bin/eoaedit bin/uruedit
	cp bin/eoaedit bin/uruedit $(PREFIX)/bin/

uninstall:
	(cd core ; $(MAKE) uninstall)
ifneq ($(MAKE_NET),no)
	(cd net ; $(MAKE) uninstall)
endif
ifneq ($(PYTHON_VER),no)
	(cd Python ; $(MAKE) uninstall)
endif
	rm -f $(PREFIX)/bin/PageConvert
	rm -f $(PREFIX)/bin/PlasmaCrypt
	rm -f $(PREFIX)/bin/PrpPack
	rm -f $(PREFIX)/bin/PrcExtract
	rm -f $(PREFIX)/bin/PageList
	rm -f $(PREFIX)/bin/prcc
	rm -f $(PREFIX)/bin/prcdc
	rm -f $(PREFIX)/bin/Prp2Obj
	rm -f $(PREFIX)/bin/PyPack
	rm -f $(PREFIX)/bin/prpmod
	rm -f $(PREFIX)/bin/prpgrep
#	rm -f $(PREFIX)/bin/prp-fuse
	rm -f $(PREFIX)/bin/PlasmaSum
	rm -f $(PREFIX)/bin/eoaedit
	rm -f $(PREFIX)/bin/uruedit

clean:
	(cd core ; $(MAKE) clean)
ifneq ($(MAKE_NET),no)
	(cd net ; $(MAKE) clean)
endif
ifneq ($(PYTHON_VER),no)
	(cd Python ; $(MAKE) clean)
endif

distclean:
	(cd core ; $(MAKE) distclean)
ifneq ($(MAKE_NET),no)
	(cd net ; $(MAKE) distclean)
endif
ifneq ($(PYTHON_VER),no)
	(cd Python ; $(MAKE) distclean)
endif
	rm -f bin/PageConvert
	rm -f bin/PlasmaCrypt
	rm -f bin/PrpPack
	rm -f bin/PrcExtract
	rm -f bin/PageList
	rm -f bin/prcc
	rm -f bin/prcdc
	rm -f bin/Prp2Obj
	rm -f bin/PyPack
	rm -f bin/prpmod
	rm -f bin/prpgrep
#	rm -f bin/prp-fuse
	rm -f bin/PlasmaSum
	rm -f Misc/TypeMap
