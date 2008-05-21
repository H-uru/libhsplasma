CC = g++
CFLAGS += -fPIC -Wall -g -ansi -fno-rtti

all:
	(cd trunk ; make)
	(make Tools/PageConvert)
	(make Tools/PlasmaCrypt)
	(make Tools/PrpPack)
	(make Tools/PrcExtract)
	(make Tools/PageList)
	(make Tools/PageExplorer)
	(make Misc/TypeMap)

Tools/PageConvert: Tools/src/PageConvert.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PageConvert.cpp -o Tools/PageConvert

Tools/PlasmaCrypt: Tools/src/PlasmaCrypt.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk -DLEKEY Tools/src/PlasmaCrypt.cpp -o Tools/PlasmaCrypt

Tools/PrpPack: Tools/src/PrpPack.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PrpPack.cpp -o Tools/PrpPack

Tools/PrcExtract: Tools/src/PrcExtract.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PrcExtract.cpp -o Tools/PrcExtract

Tools/PageList: Tools/src/PageList.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PageList.cpp -o Tools/PageList

Tools/PageExplorer: PageExplorer/PageExplorer.cpp PageExplorer/ExplorerFrm.cpp PageExplorer/wxPlasmaTextCtrl.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) `wx-config --cxxflags --libs std,stc` -Ltrunk/lib/ -lPlasma -Itrunk PageExplorer/PageExplorer.cpp PageExplorer/ExplorerFrm.cpp PageExplorer/wxPlasmaTextCtrl.cpp -o Tools/PageExplorer

Misc/TypeMap: Misc/TypeMap.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Misc/TypeMap.cpp -o Misc/TypeMap

install:
	(cd trunk ; make install)
	cp Tools/PageConvert /usr/local/bin/
	cp Tools/PlasmaCrypt /usr/local/bin/
	cp Tools/PrpPack /usr/local/bin/
	cp Tools/PrcExtract /usr/local/bin/
	cp Tools/PageList /usr/local/bin/
	cp Tools/PageExplorer /usr/local/bin/
	chmod +x Tools/eoaedit Tools/uruedit
	cp Tools/eoaedit Tools/uruedit /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/PageConvert
	rm -f /usr/local/bin/PlasmaCrypt
	rm -f /usr/local/bin/PrpPack
	rm -f /usr/local/bin/PrcExtract
	rm -f /usr/local/bin/PageList
	rm -f /usr/local/bin/PageExplorer
	rm -f /usr/local/bin/eoaedit
	rm -f /usr/local/bin/uruedit

clean:
	(cd trunk ; make clean)

distclean:
	(cd trunk ; make distclean)
	rm -f Tools/PageConvert
	rm -f Tools/PlasmaCrypt
	rm -f Tools/PrpPack
	rm -f Tools/PrcExtract
	rm -f Tools/PageList
	rm -f Tools/PageExplorer
	rm -f Misc/TypeMap
