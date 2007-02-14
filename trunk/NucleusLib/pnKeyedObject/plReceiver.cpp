#include "plReceiver.h"

plReceiver::plReceiver(PlasmaVer pv) { }
plReceiver::~plReceiver() { }

short plReceiver::ClassIndex() { return -1; }

bool plReceiver::msgReceive(plMessage * msg) { return false; }

