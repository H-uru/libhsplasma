#include "plCreatable.h"

plCreatable::plCreatable() { }
plCreatable::~plCreatable() { }

void plCreatable::read(hsStream *S) { }
void plCreatable::write(hsStream *S) { }

const char* plCreatable::getTypeName() { return ""; }
const int plCreatable::getTypeNum() { return -1; }

