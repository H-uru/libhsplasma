#include "hsExceptions.h"

// hsException //
hsException::hsException(const char* file, unsigned long line) throw()
    : fWhat("Undefined Plasma Exception"), fFile(file), fLine(line) { }
hsException::hsException(const hsException& e) throw()
    : std::exception(e), fWhat(e.fWhat), fFile(e.fFile), fLine(e.fLine) { }
hsException::hsException(const plString& w, const char* file,
    unsigned long line) throw() : fWhat(w), fFile(file), fLine(line) { }

hsException::~hsException() throw() { }

hsException& hsException::operator=(const hsException& other) throw() {
    fWhat = other.fWhat;
    return *this;
}

const char* hsException::what() const throw() { return fWhat; }
const char* hsException::File() const throw() { return fFile; }
unsigned long hsException::Line() const throw() { return fLine; }


// hsNotImplementedException //
hsNotImplementedException::hsNotImplementedException(const char* file,
                           unsigned long line, const char* feature) throw()
                         : hsException(file, line) {
    if (feature == NULL)
        fWhat = "Not implemented";
    else
        fWhat = plString("`") + feature + "' not implemented";
}


// hsBadParamException //
hsBadParamException::hsBadParamException(const char* file,
                     unsigned long line) throw()
                   : hsException(file, line) {
    fWhat = "Bad parameter";
}


// hsOutOfBoundsException //
hsOutOfBoundsException::hsOutOfBoundsException(const char* file,
                        unsigned long line) throw()
                      : hsException(file, line) {
    fWhat = "Out of bounds";
}


// hsBadVersionException //
hsBadVersionException::hsBadVersionException(const char* file,
                       unsigned long line) throw()
                     : hsException(file, line) {
    fWhat = "Unknown Plasma version";
}
