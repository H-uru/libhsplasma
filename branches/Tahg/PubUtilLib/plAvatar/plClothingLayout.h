#ifndef PLCLOTHINGLAYOUT_H
#define PLCLOTHINGLAYOUT_H

#include "../../CoreLib/hsTArray.hpp"

class plClothingElement {
  char * fName; //this+0x0
  unsigned long fXPos; //this+0x4
  unsigned long fYPos; //this+0x8
  unsigned long fWidth; //this+0xc
  unsigned long fHeight; //this+0x10

public:
  plClothingElement::plClothingElement(char *, unsigned long, unsigned long, unsigned long, unsigned long){}
  plClothingElement::~plClothingElement(){}
  static void plClothingElement::GetElements(hsTArray<plClothingElement *> &){}
};

class plClothingLayout {
  char * fName; //this+0x0
  unsigned long fOrigWidth; //this+0x4
  hsTArray<plClothingElement *> fElements; //this+0x8

public:
  plClothingLayout(const class plClothingLayout &){}
  plClothingLayout::plClothingLayout(char *, unsigned long){}
  plClothingLayout::~plClothingLayout(){}
};

#endif
