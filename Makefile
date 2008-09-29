CC = g++
CFLAGS += -fPIC -Wall -g -ansi -fno-rtti

all:
	(cd core ; make)
	(cd Python ; make)
	(make Tools/PageConvert)
	(make Tools/PlasmaCrypt)
	(make Tools/PrpPack)
	(make Tools/PrcExtract)
	(make Tools/PageList)
	(make Tools/prcc)
	(make Tools/prcdc)
	(make Tools/Prp2Obj)
	(make Tools/PageEditor)
	(make Misc/TypeMap)

Tools/PageConvert: Tools/src/PageConvert.cpp core/lib/libPlasma.so
	$(CC) $(CFLAGS) -Lcore/lib/ -lPlasma -Icore Tools/src/PageConvert.cpp -o Tools/PageConvert

Tools/PlasmaCrypt: Tools/src/PlasmaCrypt.cpp core/lib/libPlasma.so
	$(CC) $(CFLAGS) -Lcore/lib/ -lPlasma -Icore Tools/src/PlasmaCrypt.cpp -o Tools/PlasmaCrypt

Tools/PrpPack: Tools/src/PrpPack.cpp core/lib/libPlasma.so
	$(CC) $(CFLAGS) -Lcore/lib/ -lPlasma -Icore Tools/src/PrpPack.cpp -o Tools/PrpPack

Tools/PrcExtract: Tools/src/PrcExtract.cpp core/lib/libPlasma.so
	$(CC) $(CFLAGS) -Lcore/lib/ -lPlasma -Icore Tools/src/PrcExtract.cpp -o Tools/PrcExtract

Tools/PageList: Tools/src/PageList.cpp core/lib/libPlasma.so
	$(CC) $(CFLAGS) -Lcore/lib/ -lPlasma -Icore Tools/src/PageList.cpp -o Tools/PageList

Tools/prcc: Tools/src/prcc.cpp core/lib/libPlasma.so
	$(CC) $(CFLAGS) -Lcore/lib/ -lPlasma -Icore Tools/src/prcc.cpp -o Tools/prcc

Tools/prcdc: Tools/src/prcdc.cpp core/lib/libPlasma.so
	$(CC) $(CFLAGS) -Lcore/lib/ -lPlasma -Icore Tools/src/prcdc.cpp -o Tools/prcdc

Tools/Prp2Obj: Tools/src/Prp2Obj.cpp core/lib/libPlasma.so
	$(CC) $(CFLAGS) -Lcore/lib/ -lPlasma -Icore Tools/src/Prp2Obj.cpp -o Tools/Prp2Obj

Tools/PageEditor: PageEditor/PageEditor.cpp PageEditor/ExplorerFrm.cpp PageEditor/wxPlasmaTextCtrl.cpp core/lib/libPlasma.so
	$(CC) $(CFLAGS) `wx-config --cxxflags --libs std,stc` -Lcore/lib/ -lPlasma -Icore PageEditor/PageEditor.cpp PageEditor/ExplorerFrm.cpp PageEditor/wxPlasmaTextCtrl.cpp -o Tools/PageEditor

Misc/TypeMap: Misc/TypeMap.cpp core/lib/libPlasma.so
	$(CC) $(CFLAGS) -Lcore/lib/ -lPlasma -Icore Misc/TypeMap.cpp -o Misc/TypeMap

install:
	(cd core ; make install)
	cp Tools/PageConvert /usr/local/bin/
	cp Tools/PlasmaCrypt /usr/local/bin/
	cp Tools/PrpPack /usr/local/bin/
	cp Tools/PrcExtract /usr/local/bin/
	cp Tools/PageList /usr/local/bin/
	cp Tools/prcc /usr/local/bin/
	cp Tools/prcdc /usr/local/bin/
	cp Tools/Prp2Obj /usr/local/bin/
	cp Tools/PageEditor /usr/local/bin/
	chmod +x Tools/eoaedit Tools/uruedit
	cp Tools/eoaedit Tools/uruedit /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/PageConvert
	rm -f /usr/local/bin/PlasmaCrypt
	rm -f /usr/local/bin/PrpPack
	rm -f /usr/local/bin/PrcExtract
	rm -f /usr/local/bin/PageList
	rm -f /usr/local/bin/prcc
	rm -f /usr/local/bin/prcdc
	rm -f /usr/local/bin/Prp2Obj
	rm -f /usr/local/bin/PageEditor
	rm -f /usr/local/bin/eoaedit
	rm -f /usr/local/bin/uruedit

clean:
	(cd core ; make clean)
	(cd Python ; make clean)

distclean:
	(cd core ; make distclean)
	(cd Python ; make distclean)
	rm -f Tools/PageConvert
	rm -f Tools/PlasmaCrypt
	rm -f Tools/PrpPack
	rm -f Tools/PrcExtract
	rm -f Tools/PageList
	rm -f Tools/prcc
	rm -f Tools/prcdc
	rm -f Tools/Prp2Obj
	rm -f Tools/PageEditor
	rm -f Misc/TypeMap
