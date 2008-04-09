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
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasmaCore -lPlasma -Itrunk Tools/src/PageConvert.cpp -o Tools/PageConvert

Tools/PlasmaCrypt: Tools/src/PlasmaCrypt.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasmaCore -Itrunk -DLEKEY Tools/src/PlasmaCrypt.cpp -o Tools/PlasmaCrypt

Tools/PrpPack: Tools/src/PrpPack.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasmaCore -lPlasma -Itrunk Tools/src/PrpPack.cpp -o Tools/PrpPack

Tools/PrcExtract: Tools/src/PrcExtract.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasmaCore -lPlasma -Itrunk Tools/src/PrcExtract.cpp -o Tools/PrcExtract

Tools/PageList: Tools/src/PageList.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasmaCore -lPlasma -Itrunk Tools/src/PageList.cpp -o Tools/PageList

Tools/PageExplorer: PageExplorer/PageExplorer.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) `wx-config --cxxflags` -Ltrunk/lib/ -lPlasmaCore -lPlasma -Itrunk PageExplorer/PageExplorer.cpp PageExplorer/ExplorerFrm.cpp -o Tools/PageExplorer `wx-config --libs`

Misc/TypeMap: Misc/TypeMap.cpp
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasmaCore -lPlasma -Itrunk Misc/TypeMap.cpp -o Misc/TypeMap

install:
	(cd trunk ; make install)
	cp Tools/PageConvert /usr/local/bin/
	cp Tools/PlasmaCrypt /usr/local/bin/
	cp Tools/PrpPack /usr/local/bin/
	cp Tools/PrcExtract /usr/local/bin/
	cp Tools/PageList /usr/local/bin/
	cp Tools/PageExplorer /usr/local/bin
	chmod +x Tools/eoaedit Tools/uruedit
	cp Tools/eoaedit Tools/uruedit /usr/local/bin/

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
