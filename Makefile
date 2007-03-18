CC = g++
CFLAGS += -O2 -fPIC -Wall -g

all:
	(cd trunk ; make)
	(make Tools/PageConvert)
	(make Tools/PlasmaCrypt)
	(make Tools/PrpPack)
	(make Tools/PrcExtract)
	(cd AgeMaker ; make)

Tools/PageConvert: Tools/src/PageConvert.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PageConvert.cpp -o Tools/PageConvert

Tools/PlasmaCrypt: Tools/src/PlasmaCrypt.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk -DLEKEY Tools/src/PlasmaCrypt.cpp -o Tools/PlasmaCrypt

Tools/PrpPack: Tools/src/PrpPack.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PrpPack.cpp -o Tools/PrpPack

Tools/PrcExtract: Tools/src/PrcExtract.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PrcExtract.cpp -o Tools/PrcExtract

install:
	(cd trunk ; make install)
	cp Tools/PageConvert /usr/local/bin/
	cp Tools/PlasmaCrypt /usr/local/bin/
	cp Tools/PrpPack /usr/local/bin/
	cp Tools/PrcExtract /usr/local/bin/
	chmod +x Tools/eoaedit Tools/uruedit
	cp Tools/eoaedit Tools/uruedit /usr/local/bin/

clean:
	(cd trunk ; make clean)
	(cd AgeMaker ; make clean)

distclean:
	(cd trunk ; make distclean)
	rm Tools/PageConvert
	rm Tools/PlasmaCrypt
	rm Tools/PrpPack
	rm Tools/PrcExtract
	(cd AgeMaker ; make distclean)

