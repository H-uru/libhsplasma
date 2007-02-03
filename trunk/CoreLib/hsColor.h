#ifndef _HSCOLORRGBA_H
#define _HSCOLORRGBA_H

struct hsColorRGBA {
public:
    float r, g, b, a;

    inline void read(hsStream* S) {
        r = S->readFloat();
        g = S->readFloat();
        b = S->readFloat();
        a = S->readFloat();
    }

    inline void write(hsStream* S) {
        S->writeFloat(r);
        S->writeFloat(g);
        S->writeFloat(b);
        S->writeFloat(a);
    }
};

struct hsColor32 {
public:
    union {
        unsigned char b, g, r, a;
        unsigned int color;
    };

    inline void read(hsStream* S) { color = S->readInt(); }
    inline void write(hsStream* S) { S->writeInt(color); }
};

#endif
