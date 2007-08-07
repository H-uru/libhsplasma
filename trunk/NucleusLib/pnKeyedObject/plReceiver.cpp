#include "plReceiver.h"

plReceiver::plReceiver() { }
plReceiver::~plReceiver() { }

IMPLEMENT_CREATABLE(plReceiver, kReceiver, plCreatable)

bool plReceiver::msgReceive(plMessage* msg) { return false; }
