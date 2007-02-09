#ifndef PLSPACEPREPNODE_H
#define PLSPACEPREPNODE_H

#include "../../CoreLib/hsBounds.h"

class plSpacePrepNode {
  class hsBounds3Ext fWorldBounds; //this+0x0
  short fIndex; //this+0x80
  short fDataIndex; //this+0x82
  class plSpacePrepNode * fChildren[2]; //this+0x84

public:
  plSpacePrepNode(const class plSpacePrepNode &);
  plSpacePrepNode::plSpacePrepNode();

private:

protected:
};

#endif
