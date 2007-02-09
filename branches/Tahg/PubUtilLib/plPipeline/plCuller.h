#ifndef PLCULLER_H
#define PLCULLER_H


class plCuller {

public:
  plCuller::plCuller(const class plCuller &){}
  plCuller::plCuller(){}
  plCuller::~plCuller(){}
  void Harvest(const class plSpaceTree *, class hsTArray<short> &){}
};

#endif
