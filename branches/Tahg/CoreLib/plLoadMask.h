#ifndef PLLOADMASK_H
#define PLLOADMASK_H

class plLoadMask {
  unsigned char fQuality[2]; //this+0x0
  unsigned short fMask; //this+0x0

public:
  plLoadMask(unsigned char, unsigned char){}
  plLoadMask::plLoadMask(){}
  plLoadMask::~plLoadMask(){}
  int plLoadMask::DontLoad(){}
  int plLoadMask::NeverLoads(){}
  int plLoadMask::IsUsed(){}
  int plLoadMask::MatchesQuality(int){}
  int MatchesCapability(int){}
  int MatchesQualityAndCapability(int, int){}
  int MatchesCurrentQuality(){}
  int MatchesCurrentCapability(){}
  int MatchesCurrent(){}
  unsigned char GetQualityMask(int){}
  class plLoadMask & plLoadMask::SetMask(unsigned char, unsigned char){}
  class plLoadMask & SetNever(){}
  class plLoadMask & plLoadMask::SetAlways(){}
  class plLoadMask & operator|=(const class plLoadMask &){}
  class plLoadMask & operator&=(const class plLoadMask &){}
  int plLoadMask::operator==(const class plLoadMask &){}
  int plLoadMask::operator!=(const class plLoadMask &){}
  int operator<(const class plLoadMask &){}
  void plLoadMask::Read(class hsStream *){}
  void plLoadMask::Write(class hsStream *){}
  static int plLoadMask::ComputeRepMasks(int, const int *, const int *, class plLoadMask *){}
  static unsigned long plLoadMask::ValidateReps(int, const int *, const int *){}
  static unsigned long plLoadMask::ValidateMasks(int, class plLoadMask *){}

protected:
  static void plLoadMask::SetGlobalQuality(int){}
  static void plLoadMask::SetGlobalCapability(int){}
  static unsigned char plLoadMask::IBitToMask(int){}
};

#endif
