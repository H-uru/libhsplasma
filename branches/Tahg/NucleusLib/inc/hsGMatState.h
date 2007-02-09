#ifndef HSGMATSTATE_H
#define HSGMATSTATE_H


class hsGMatState {
	enum StateIdx
	{
		kBlend,
		kClamp,
		kShade,
		kZ,
		kMisc
	};
  unsigned long fBlendFlags; //this+0x0
  unsigned long fClampFlags; //this+0x4
  unsigned long fShadeFlags; //this+0x8
  unsigned long fZFlags; //this+0xc
  unsigned long fMiscFlags; //this+0x10

public:
	hsGMatState(){}
  static unsigned long Differs(unsigned long, unsigned long){}
  static unsigned long hsGMatState::Differs(unsigned long, unsigned long, unsigned long){}
  unsigned long operator!=(const class hsGMatState &){}
  unsigned long hsGMatState::Value(int){}
  unsigned long & hsGMatState::operator[](const int){}
  class hsGMatState & hsGMatState::operator|=(const class hsGMatState &){}
  class hsGMatState & operator+=(const class hsGMatState &){}
  class hsGMatState & hsGMatState::operator-=(const class hsGMatState &){}
  void hsGMatState::Read(class hsStream *){}
  void hsGMatState::Write(class hsStream *){}
  hsGMatState::hsGMatState(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long){}
  void hsGMatState::Reset(){}
  void hsGMatState::Clear(const class hsGMatState &){}
  void hsGMatState::Composite(const class hsGMatState &, const class hsGMatState &, const class hsGMatState &){}
};

#endif
