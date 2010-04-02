#include "hsStdioStream.h"

hsStdioStream::hsStdioStream(bool useStdErr) : hsFileStream(pvUnknown) {
    if (useStdErr)
        setFiles(stdin, stderr);
    else
        setFiles(stdin, stdout);
    fm = fmReadWrite;
}

void hsStdioStream::seek(hsUint32 pos) {
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void hsStdioStream::skip(hsInt32 count) {
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void hsStdioStream::flush() {
    fflush(Fin);
    fflush(Fout);
}

size_t hsStdioStream::read(size_t size, void* buf) {
    return fread(buf, size, 1, Fin);
}

size_t hsStdioStream::write(size_t size, const void* buf) {
    return fwrite(buf, size, 1, Fout);
}
