CC = g++
CFLAGS += -O2 -fPIC -Wall -g

all:
	(cd trunk ; make)
	(make Tools/PageConvert)
	(make Tools/PlasmaCrypt)
	(make Tools/PrpCheat)
	(cd AgeMaker ; make)

Tools/PageConvert: Tools/src/PageConvert.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PageConvert.cpp -o Tools/PageConvert

Tools/PlasmaCrypt: Tools/src/PlasmaCrypt.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PlasmaCrypt.cpp -o Tools/PlasmaCrypt

Tools/PrpCheat: Tools/src/PrpCheat.cpp trunk/lib/libPlasma.so
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PrpCheat.cpp -o Tools/PrpCheat

install:
	(cd trunk ; make install)
	cp Tools/PageConvert /usr/local/bin/
	cp Tools/PlasmaCrypt /usr/local/bin/
	cp Tools/PrpCheat /usr/local/bin/
	chmod +x Tools/eoaedit Tools/uruedit
	cp Tools/eoaedit Tools/uruedit /usr/local/bin/

clean:
	(cd trunk ; make clean)
	(cd AgeMaker ; make clean)

distclean:
	(cd trunk ; make distclean)
	rm Tools/PageConvert
	rm Tools/PlasmaCrypt
	rm Tools/PrpCheat
	(cd AgeMaker ; make distclean)

