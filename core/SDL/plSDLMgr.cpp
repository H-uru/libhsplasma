#include "plSDLMgr.h"
#include "Stream/hsTokenStream.h"
#include "Stream/plEncryptedStream.h"
#include <stdarg.h>

/* plSDLMgr */
plSDLMgr::plSDLMgr() { }

plSDLMgr::~plSDLMgr() {
    for (size_t i=0; i<fDescriptors.getSize(); i++)
        delete fDescriptors[i];
}

void plSDLMgr::ReadDescriptors(const plString& filename) {
    hsStream* fileStream = NULL;
    if (plEncryptedStream::IsFileEncrypted(filename)) {
        fileStream = new plEncryptedStream();
        ((plEncryptedStream*)fileStream)->open(filename, fmRead, plEncryptedStream::kEncAuto);
    } else {
        fileStream = new hsFileStream();
        ((hsFileStream*)fileStream)->open(filename, fmRead);
    }

    hsTokenStream* tokStream = new hsTokenStream(fileStream);
    tokStream->setDelimiters("{}[]()=,;");
    hsTArray<hsTokenStream::Region> commentMarkers;
    commentMarkers.append(hsTokenStream::Region("#", "\n"));
    commentMarkers.append(hsTokenStream::Region("//", "\n"));
    commentMarkers.append(hsTokenStream::Region("/*", "*/"));
    tokStream->setCommentMarkers(commentMarkers);
    hsTArray<hsTokenStream::Region> stringMarkers;
    stringMarkers.append(hsTokenStream::Region("\"", "\""));
    tokStream->setStringMarkers(stringMarkers);

    ParseState state = kFile;
    plStateDescriptor* curDesc = NULL;
    plVarDescriptor* curVar = NULL;
    bool reexamine = false;
    plString tok;
    while (reexamine || tokStream->hasNext()) {
        if (reexamine)
            reexamine = false;
        else
            tok = tokStream->next();
        if (state == kFile) {
            if (tok == "STATEDESC") {
                curDesc = new plStateDescriptor();
                curDesc->setName(tokStream->next());
                tok = tokStream->next();
                if (tok != "{") {
                    delete curDesc;
                    delete tokStream;
                    delete fileStream;
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected token '%s', expected '{'", tok.cstr());
                }
                state = kUruStateDesc;
            } else if (tok == "struct") {
                curDesc = new plStateDescriptor();
                curDesc->setName(tokStream->next());
                tok = tokStream->next();
                if (tok != "{") {
                    delete tokStream;
                    delete fileStream;
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected token '%s', expected '{'", tok.cstr());
                }
                state = kEoaStateDesc;
            } else {
                delete tokStream;
                delete fileStream;
                throw plSDLParseException(__FILE__, __LINE__,
                        "Unexpected token '%s', expected 'STATEDESC', 'struct'",
                        tok.cstr());
            }
        } else if (state == kUruStateDesc) {
            if (tok == "VAR") {
                curVar = new plVarDescriptor();
                plString typeStr = tokStream->next();
                plVarDescriptor::Type varType = plVarDescriptor::GetTypeFromString(typeStr, false);
                curVar->setType(varType);
                if (varType == plVarDescriptor::kStateDescriptor)
                    curVar->setStateDescType(typeStr.mid(1));
                if (varType == plVarDescriptor::kNone || (varType == plVarDescriptor::kStateDescriptor && typeStr.len() < 2)) {
                    delete curVar;
                    delete curDesc;
                    delete tokStream;
                    delete fileStream;
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Invalid var type: %s", typeStr.cstr());
                }
                curVar->setName(tokStream->next());
                if (tokStream->peekNext() == "[") {
                    tokStream->next();
                    tok = tokStream->next();
                    if (tok != "]") {
                        curVar->setCount(tok.toUint());
                        tok = tokStream->next();
                    } else {
                        curVar->setVariableLength(true);
                    }
                    if (tok != "]") {
                        delete curVar;
                        delete curDesc;
                        delete tokStream;
                        delete fileStream;
                        throw plSDLParseException(__FILE__, __LINE__,
                                "Unexpected token '%s', expected ']'", tok.cstr());
                    }
                }
                state = kUruVarLine;
            } else if (tok == "VERSION") {
                curDesc->setVersion(tokStream->next().toInt());
            } else if (tok == "}") {
                fDescriptors.append(curDesc);
                curDesc = NULL;
                state = kFile;
            } else {
                delete curDesc;
                delete tokStream;
                delete fileStream;
                throw plSDLParseException(__FILE__, __LINE__,
                        "Unexpected token '%s', expected 'VAR', 'VERSION', '}'",
                        tok.cstr());
            }
        } else if (state == kUruVarLine) {
            if (tok == ";") {
                // Skip
            } else if (tok == "VAR" || tok == "VERSION" || tok == "}") {
                curDesc->addVariable(curVar);
                curVar = NULL;
                state = kUruStateDesc;
                reexamine = true;
            } else if (tok == "DEFAULT") {
                tok = tokStream->next();
                if (tok != "=") {
                    delete curVar;
                    delete curDesc;
                    delete tokStream;
                    delete fileStream;
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected '%s', expected '='", tok.cstr());
                }
                int nParens = 0;
                plString defStr;
                do {
                    tok = tokStream->next();
                    if (tok == "(") nParens++;
                    if (tok == ")") nParens--;
                    if (nParens < 0) {
                        delete curVar;
                        delete curDesc;
                        delete tokStream;
                        delete fileStream;
                        throw plSDLParseException(__FILE__, __LINE__, "Unexpected ')'");
                    }
                    defStr += tok;
                } while (nParens > 0);
                curVar->setDefault(defStr);
            } else if (tok == "DEFAULTOPTION") {
                tok = tokStream->next();
                if (tok != "=") {
                    delete curVar;
                    delete curDesc;
                    delete tokStream;
                    delete fileStream;
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected '%s', expected '='", tok.cstr());
                }
                tok = tokStream->next();
                if (tok.toLower() == "vault") {
                    curVar->setAlwaysNew(true);
                } else {
                    delete curVar;
                    delete curDesc;
                    delete tokStream;
                    delete fileStream;
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected DEFAULTOPTION '%s'", tok.cstr());
                }
            } else if (tok == "DISPLAYOPTION") {
                tok = tokStream->next();
                if (tok != "=") {
                    delete curVar;
                    delete curDesc;
                    delete tokStream;
                    delete fileStream;
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected '%s', expected '='", tok.cstr());
                }
                tok = tokStream->next();
                if (tok.toLower() == "hidden") {
                    curVar->setInternal(true);
                }
            } else if (tok == "INTERNAL") {
                curVar->setInternal(true);
            } else if (tok == "PHASED") {
                curVar->setAlwaysNew(true);
            } else {
                delete curVar;
                delete curDesc;
                delete tokStream;
                delete fileStream;
                throw plSDLParseException(__FILE__, __LINE__,
                        "Unexpected token '%s'", tok.cstr());
            }
        } else if (state == kEoaStateDesc) {
            if (tok == "version") {
                curDesc->setVersion(tokStream->next().toInt());
                tok = tokStream->next();
                if (tok != ";") {
                    delete curDesc;
                    delete tokStream;
                    delete fileStream;
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected '%s', expected ';'", tok.cstr());
                }
            } else if (tok == "}") {
                fDescriptors.append(curDesc);
                curDesc = NULL;
                state = kFile;
            } else {
                curVar = new plVarDescriptor();
                plVarDescriptor::Type varType = plVarDescriptor::GetTypeFromString(tok, true);
                curVar->setType(varType);
                if (varType == plVarDescriptor::kStateDescriptor)
                    curVar->setStateDescType(tok);
                curVar->setName(tokStream->next());
                if (tokStream->peekNext() == "[") {
                    tokStream->next();
                    tok = tokStream->next();
                    if (tok != "]") {
                        curVar->setCount(tok.toUint());
                        tok = tokStream->next();
                    } else {
                        curVar->setVariableLength(true);
                    }
                    if (tok != "]") {
                        delete curVar;
                        delete curDesc;
                        delete tokStream;
                        delete fileStream;
                        throw plSDLParseException(__FILE__, __LINE__,
                                "Unexpected token '%s', expected ']'", tok.cstr());
                    }
                }
                state = kEoaVarLine;
            }
        } else if (state == kEoaVarLine) {
            if (tok == ";") {
                curDesc->addVariable(curVar);
                curVar = NULL;
                state = kEoaStateDesc;
            } else if (tok == "}") {
                delete curVar;
                delete curDesc;
                delete tokStream;
                delete fileStream;
                throw plSDLParseException(__FILE__, __LINE__, "Unexpected '}'");
            } else if (tok == "default") {
                tok = tokStream->next();
                if (tok != "=") {
                    delete curVar;
                    delete curDesc;
                    delete tokStream;
                    delete fileStream;
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected '%s', expected '='", tok.cstr());
                }
                int nParens = 0;
                plString defStr;
                do {
                    tok = tokStream->next();
                    if (tok == "(") nParens++;
                    if (tok == ")") nParens--;
                    if (nParens < 0) {
                        delete curVar;
                        delete curDesc;
                        delete tokStream;
                        delete fileStream;
                        throw plSDLParseException(__FILE__, __LINE__, "Unexpected ')'");
                    }
                    defStr += tok;
                } while (nParens > 0);
                curVar->setDefault(defStr);
            } else if (tok == "private") {
                curVar->setInternal(true);
            } else {
                delete curVar;
                delete curDesc;
                delete tokStream;
                delete fileStream;
                throw plSDLParseException(__FILE__, __LINE__,
                        "Unexpected token '%s'", tok.cstr());
            }
        }
    }

    delete tokStream;
    delete fileStream;
    if (state != kFile)
        throw plSDLParseException(__FILE__, __LINE__, "Unexpected End of File");
}

void plSDLMgr::ClearDescriptors() {
    for (size_t i=0; i<fDescriptors.getSize(); i++)
        delete fDescriptors[i];
    fDescriptors.clear();
}

plStateDescriptor* plSDLMgr::GetDescriptor(const plString& name, int version) {
    plStateDescriptor* desc = NULL;
    int hiVersion = 0;
    for (size_t i=0; i<fDescriptors.getSize(); i++) {
        if (fDescriptors[i]->getName() == name) {
            if (version == -1 && hiVersion <= fDescriptors[i]->getVersion()) {
                desc = fDescriptors[i];
                hiVersion = desc->getVersion();
            } else if (fDescriptors[i]->getVersion() == version) {
                desc = fDescriptors[i];
            }
        }
    }
    return desc;
}


/* plSDLParseException */
plSDLParseException::plSDLParseException(const char* file, unsigned long line,
                                         const char* msg, ...) throw()
                   : hsException(file, line) {
    va_list argptr;
    va_start(argptr, msg);
    plString str = plString::FormatV(msg, argptr);
    va_end(argptr);

    if (msg == NULL)
        fWhat = "Unknown SDL Parse Error";
    else
        fWhat = plString("SDL Error: ") + str;
}
