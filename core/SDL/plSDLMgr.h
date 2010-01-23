#ifndef _PLSDLMGR_H
#define _PLSDLMGR_H

#include "plStateDescriptor.h"
#include "Debug/hsExceptions.h"
#include "Stream/hsStream.h"

DllClass plSDLMgr {
protected:
    hsTArray<plStateDescriptor*> fDescriptors;

private:
    enum ParseState {
        kFile, kUruStateDesc, kUruVarLine, kEoaStateDesc, kEoaVarLine
    };

public:
    plSDLMgr();
    ~plSDLMgr();

    void ReadDescriptors(const plString& filename);
    void ReadDescriptors(hsStream* S);
    void ClearDescriptors();
    plStateDescriptor* GetDescriptor(const plString& name, int version = -1);

    void read(hsStream* S);
    void write(hsStream* S);
};

DllClass plSDLParseException : public hsException {
public:
    plSDLParseException(const char* file, unsigned long line,
                        const char* msg, ...) throw();
};

#endif
