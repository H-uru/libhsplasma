#include "plSDL.h"

unsigned int plSDL::VariableLengthRead(hsStream* S, size_t size) {
    if (size < 0x100)
        return S->readByte();
    else if (size < 0x10000)
        return S->readShort();
    else
        return S->readInt();
}

void plSDL::VariableLengthWrite(hsStream* S, size_t size, unsigned int value) {
    if (size < 0x100)
        S->writeByte(value);
    else if (size < 0x10000)
        S->writeShort(value);
    else
        S->writeInt(value);
}
