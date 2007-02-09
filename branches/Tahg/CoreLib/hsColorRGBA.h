#ifndef HSCOLORRGBA_H
#define HSCOLORRGBA_H

struct hsColor32 {
public:
    unsigned char r, g, b, a;
};

struct hsColorRGBA {
  float r; //this+0x0
  float g; //this+0x4
  float b; //this+0x8
  float a; //this+0xc

public:
  struct hsColor32 ToRGBA32(){}
  struct hsColorRGBA & hsColorRGBA::Set(float, float, float, float){}
  int hsColorRGBA::operator==(const struct hsColorRGBA &){}
  int hsColorRGBA::operator!=(const struct hsColorRGBA &){}
  struct hsColorRGBA & hsColorRGBA::operator+=(const struct hsColorRGBA &){}
  struct hsColorRGBA & hsColorRGBA::operator*=(const float){}
  struct hsColorRGBA & hsColorRGBA::operator*=(const struct hsColorRGBA &){}
  struct hsColorRGBA & operator-=(const struct hsColorRGBA &){}
  struct hsColorRGBA & hsColorRGBA::FromARGB32(unsigned long){}
  unsigned long hsColorRGBA::ToARGB32(){}
  void hsColorRGBA::Read(class hsStream *){}
  void hsColorRGBA::Write(class hsStream *){}
};

#endif
