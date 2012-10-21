/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plSDLMgr.h"
#include "Stream/hsTokenStream.h"
#include "Stream/plEncryptedStream.h"
#include <memory>
#include <stdarg.h>

/* plSDLMgr */
plSDLMgr::~plSDLMgr() {
    for (size_t i=0; i<fDescriptors.getSize(); i++)
        delete fDescriptors[i];
}

void plSDLMgr::ReadDescriptors(const plString& filename) {
    if (plEncryptedStream::IsFileEncrypted(filename)) {
        plEncryptedStream stream;
        stream.open(filename, fmRead, plEncryptedStream::kEncAuto);
        ReadDescriptors(&stream);
    } else {
        hsFileStream stream;
        stream.open(filename, fmRead);
        ReadDescriptors(&stream);
    }
}

void plSDLMgr::ReadDescriptors(hsStream* fileStream) {
    std::auto_ptr<hsTokenStream> tokStream(new hsTokenStream(fileStream));
    tokStream->setDelimiters("{}[]()=,;");
    hsTArray<hsTokenStream::Region> commentMarkers;
    commentMarkers.append(hsTokenStream::Region("#", "\n"));
    commentMarkers.append(hsTokenStream::Region("//", "\n"));
    commentMarkers.append(hsTokenStream::Region("/*", "*/"));
    tokStream->setCommentMarkers(commentMarkers);
    hsTArray<hsTokenStream::Region> stringMarkers;
    stringMarkers.append(hsTokenStream::Region("\"", "\""));
    stringMarkers.append(hsTokenStream::Region("'", "'"));
    tokStream->setStringMarkers(stringMarkers);

    ParseState state = kFile;
    std::auto_ptr<plStateDescriptor> curDesc;
    std::auto_ptr<plVarDescriptor> curVar;
    bool reexamine = false;
    plString tok;
    while (reexamine || tokStream->hasNext()) {
        if (reexamine)
            reexamine = false;
        else
            tok = tokStream->next();
        if (state == kFile) {
            if (tok == "STATEDESC") {
                curDesc.reset(new plStateDescriptor());
                curDesc->setName(tokStream->next());
                tok = tokStream->next();
                if (tok != "{") {
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected token '%s', expected '{'", tok.cstr());
                }
                state = kUruStateDesc;
            } else if (tok == "struct") {
                curDesc.reset(new plStateDescriptor());
                curDesc->setName(tokStream->next());
                tok = tokStream->next();
                if (tok != "{") {
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected token '%s', expected '{'", tok.cstr());
                }
                state = kEoaStateDesc;
            } else {
                throw plSDLParseException(__FILE__, __LINE__,
                        "Unexpected token '%s', expected 'STATEDESC', 'struct'",
                        tok.cstr());
            }
        } else if (state == kUruStateDesc) {
            if (tok == "VAR") {
                curVar.reset(new plVarDescriptor());
                plString typeStr = tokStream->next();
                plVarDescriptor::Type varType = plVarDescriptor::GetTypeFromString(typeStr, false);
                curVar->setType(varType);
                if (varType == plVarDescriptor::kStateDescriptor)
                    curVar->setStateDescType(typeStr.mid(1));
                if (varType == plVarDescriptor::kNone ||
                        (varType == plVarDescriptor::kStateDescriptor && typeStr.len() < 2)) {
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
                        throw plSDLParseException(__FILE__, __LINE__,
                                "Unexpected token '%s', expected ']'", tok.cstr());
                    }
                }
                state = kUruVarLine;
            } else if (tok == "VERSION") {
                curDesc->setVersion(tokStream->next().toInt());
            } else if (tok == "}") {
                fDescriptors.append(curDesc.release());
                state = kFile;
            } else {
                throw plSDLParseException(__FILE__, __LINE__,
                        "Unexpected token '%s', expected 'VAR', 'VERSION', '}'",
                        tok.cstr());
            }
        } else if (state == kUruVarLine) {
            if (tok == ";") {
                // Skip
            } else if (tok == "VAR" || tok == "VERSION" || tok == "}") {
                curDesc->addVariable(curVar.release());
                state = kUruStateDesc;
                reexamine = true;
            } else if (tok == "DEFAULT") {
                tok = tokStream->next();
                if (tok != "=") {
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected '%s', expected '='", tok.cstr());
                }
                plString defStr;
                bool isEnd = false;
                do {
                    tok = tokStream->next();
                    if (tok == "VAR" || tok == "VERSION" || tok == "}" ||
                        tok == "DEFAULT" || tok == "DEFAULTOPTION" ||
                        tok == "DISPLAYOPTION" || tok == "INTERNAL" ||
                        tok == "PHASED") {
                        isEnd = true;
                        reexamine = true;
                    } else {
                        defStr += tok;
                    }
                } while (!isEnd);
                curVar->setDefault(defStr);
            } else if (tok == "DEFAULTOPTION") {
                tok = tokStream->next();
                if (tok != "=") {
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected '%s', expected '='", tok.cstr());
                }
                tok = tokStream->next();
                if (tok.toLower() == "vault") {
                    curVar->setAlwaysNew(true);
                } else if (tok.toLower() == "hidden") {
                    curVar->setInternal(true);
                } else if (tok.toLower() == "red") {
                    curVar->setDisplay(tok);
                } else {
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected DEFAULTOPTION '%s'", tok.cstr());
                }
            } else if (tok == "DISPLAYOPTION") {
                tok = tokStream->next();
                if (tok != "=") {
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected '%s', expected '='", tok.cstr());
                }
                tok = tokStream->next();
                curVar->setDisplay(tok);
                if (tok.toLower() == "hidden")
                    curVar->setInternal(true);
            } else if (tok == "INTERNAL") {
                curVar->setInternal(true);
            } else if (tok == "PHASED") {
                curVar->setAlwaysNew(true);
            } else {
                throw plSDLParseException(__FILE__, __LINE__,
                        "Unexpected token '%s'", tok.cstr());
            }
        } else if (state == kEoaStateDesc) {
            if (tok == "version") {
                curDesc->setVersion(tokStream->next().toInt());
                tok = tokStream->next();
                if (tok != ";") {
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected '%s', expected ';'", tok.cstr());
                }
            } else if (tok == "}") {
                fDescriptors.append(curDesc.release());
                state = kFile;
            } else {
                curVar.reset(new plVarDescriptor());
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
                        throw plSDLParseException(__FILE__, __LINE__,
                                "Unexpected token '%s', expected ']'", tok.cstr());
                    }
                }
                state = kEoaVarLine;
            }
        } else if (state == kEoaVarLine) {
            if (tok == ";") {
                curDesc->addVariable(curVar.release());
                state = kEoaStateDesc;
            } else if (tok == "}") {
                throw plSDLParseException(__FILE__, __LINE__, "Unexpected '}'");
            } else if (tok == "default") {
                tok = tokStream->next();
                if (tok != "=") {
                    throw plSDLParseException(__FILE__, __LINE__,
                            "Unexpected '%s', expected '='", tok.cstr());
                }
                int nParens = 0;
                plString defStr;
                do {
                    tok = tokStream->next();
                    if (tok == "(")
                        nParens++;
                    if (tok == ")")
                        nParens--;
                    if (nParens < 0)
                        throw plSDLParseException(__FILE__, __LINE__, "Unexpected ')'");
                    defStr += tok;
                } while (nParens > 0);
                curVar->setDefault(defStr);
            } else if (tok == "private") {
                curVar->setInternal(true);
            } else {
                throw plSDLParseException(__FILE__, __LINE__,
                        "Unexpected token '%s'", tok.cstr());
            }
        }
    }

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
    if (desc != NULL) {
        for (size_t i=0; i<desc->getNumVars(); i++) {
            if (desc->get(i)->getType() == plVarDescriptor::kStateDescriptor)
                desc->get(i)->setStateDesc(GetDescriptor(desc->get(i)->getStateDescType(),
                                                         desc->get(i)->getStateDescVer()));
        }
    }
    return desc;
}

void plSDLMgr::read(hsStream* S) {
    ClearDescriptors();
    fDescriptors.setSize(S->readShort());
    for (size_t i=0; i<fDescriptors.getSize(); i++) {
        fDescriptors[i] = new plStateDescriptor();
        fDescriptors[i]->read(S);
    }

    // Propagate types on SDVars
    for (size_t i=0; i<fDescriptors.getSize(); i++) {
        plStateDescriptor* desc = fDescriptors[i];
        for (size_t j=0; j<desc->getNumVars(); j++) {
            plVarDescriptor* var = desc->get(j);
            if (var->getType() == plVarDescriptor::kStateDescriptor)
                var->setStateDesc(GetDescriptor(var->getStateDescType(),
                                                var->getStateDescVer()));
        }
    }
}

void plSDLMgr::write(hsStream* S) {
    S->writeShort(fDescriptors.getSize());
    for (size_t i=0; i<fDescriptors.getSize(); i++)
        fDescriptors[i]->write(S);
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
