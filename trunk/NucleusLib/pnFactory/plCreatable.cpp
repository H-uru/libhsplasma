#include "plCreatable.h"

plCreatable::plCreatable() { }
plCreatable::~plCreatable() { }

const char* plCreatable::ClassName() {
    return pdUnifiedTypeMap::ClassName(ClassIndex());
}
