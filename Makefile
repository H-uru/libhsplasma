CC = g++
CFLAGS += -O2 -fPIC -Wall -g

all:
	(cd trunk ; make)
	(make Tools/PageConvert)
	(make Tools/PlasmaCrypt)

Tools/PageConvert: Tools/src/PageConvert.cpp
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PageConvert.cpp -o Tools/PageConvert

Tools/PlasmaCrypt: Tools/src/PlasmaCrypt.cpp
	$(CC) $(CFLAGS) -Ltrunk/lib/ -lPlasma -Itrunk Tools/src/PlasmaCrypt.cpp -o Tools/PlasmaCrypt

install:
	(cd trunk ; make install)

clean:
	(cd trunk ; make clean)

distclean:
	(cd trunk ; make distclean)
	rm Tools/PageConvert
	rm Tools/PlasmaCrypt

