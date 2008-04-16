#include "hsStdioStream.h"

hsStdioStream::hsStdioStream(bool useStdErr) : hsFileStream(pvUnknown) {
    if (useStdErr)
        setFiles(stdin, stderr);
    else
        setFiles(stdin, stdout);
    fm = fmReadWrite;
}

hsStdioStream::~hsStdioStream() { }

bool hsStdioStream::open(const char* file, FileMode mode) {
    return false;
}

void hsStdioStream::close() { }

hsUint32 hsStdioStream::size() const { return 0; }
hsUint32 hsStdioStream::pos() const { return 0; }
bool hsStdioStream::eof() const { return false; }

void hsStdioStream::seek(hsUint32 pos) {
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void hsStdioStream::skip(hsInt32 count) {
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void hsStdioStream::fastForward() { }
void hsStdioStream::rewind() { }

void hsStdioStream::read(size_t size, void* buf) {
    fread(buf, size, 1, Fin);
}

void hsStdioStream::write(size_t size, const void* buf) {
    fwrite(buf, size, 1, Fout);
}

void hsStdioStream::setFiles(FILE* in, FILE* out) {
    Fin = in;
    Fout = out;
}

FILE* hsStdioStream::getInFile() { return Fin; }
FILE* hsStdioStream::getOutFile() { return Fout; }
