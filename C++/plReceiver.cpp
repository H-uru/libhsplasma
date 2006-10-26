#include "plReceiver.h"

plReceiver::plReceiver() { }
plReceiver::~plReceiver() { }

plKey * plReceiver::getKey() { return &key; }
void plReceiver::setKey(plKey * k) { key = *k; }

void plReceiver::read(hsStream * S) { }
void plReceiver::write(hsStream * S) { }

const char* plReceiver::getTypeName() { return ""; }
const int plReceiver::getTypeNum() { return -1; }

//bool msgReceive(plMessage * msg) { return false; }

