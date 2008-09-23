#ifndef _HSSTDIOSTREAM_H
#define _HSSTDIOSTREAM_H

#include "hsStream.h"

DllClass hsStdioStream : public hsFileStream {
protected:
    FILE* Fin;
    FILE* Fout;

public:
    explicit hsStdioStream(bool useStdErr = false);
    virtual ~hsStdioStream();

    virtual bool open(const char* file, FileMode mode);
    virtual void close();

    virtual hsUint32 size() const;
    virtual hsUint32 pos() const;
    virtual bool eof() const;
    
    virtual void seek(hsUint32 pos);
    virtual void skip(hsInt32 count);
    virtual void fastForward();
    virtual void rewind();
    virtual void flush();

    virtual size_t read(size_t size, void* buf);
    virtual size_t write(size_t size, const void* buf);

    void setFiles(FILE* in, FILE* out);
    FILE* getInFile();
    FILE* getOutFile();
};

#endif
