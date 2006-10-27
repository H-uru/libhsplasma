#include <string.h>
#include "plString.h"

plString::plString() {
    str = "";
}

plString::plString(plString * init) {
    int len = strlen(init->str);
    str = new char[len+1];
    strcpy(str, init->str);
}

plString::plString(const char* init) {
    int len = strlen(init);
    str = new char[len+1];
    strcpy(str, init);
}

plString::~plString() { delete str; }

const char* plString::value() { return str; }
void plString::set(const char* value) {
    delete str;
    int len = strlen(value);
    str = new char[len+1];
    strcpy(str, value);
}

int plString::length() { return strlen(str); }

void plString::read(hsStream * S) {
    delete str;
    str = S->readSafeStr();
}

void plString::write(hsStream * S) {
    S->writeSafeStr(str);
}

const char* plString::getTypeName() { return ""; }
const int plString::getTypeNum() { return -1; }

