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
#include <unordered_set>

/* plSDLMgr */
plSDLMgr::~plSDLMgr()
{
    for (auto desc = fDescriptors.begin(); desc != fDescriptors.end(); ++desc)
        delete *desc;
}

void plSDLMgr::ReadDescriptors(const ST::string& filename)
{
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

void plSDLMgr::ReadDescriptors(hsStream* fileStream)
{
    std::unique_ptr<hsTokenStream> tokStream(new hsTokenStream(fileStream));
    tokStream->setDelimiters("{}[]()=,;");
    std::vector<hsTokenStream::Region> commentMarkers;
    commentMarkers.push_back(hsTokenStream::Region("#", "\n"));
    commentMarkers.push_back(hsTokenStream::Region("//", "\n"));
    commentMarkers.push_back(hsTokenStream::Region("/*", "*/"));
    tokStream->setCommentMarkers(commentMarkers);
    std::vector<hsTokenStream::Region> stringMarkers;
    stringMarkers.push_back(hsTokenStream::Region("\"", "\""));
    stringMarkers.push_back(hsTokenStream::Region("'", "'"));
    tokStream->setStringMarkers(stringMarkers);

    ParseState state = kFile;
    std::unique_ptr<plStateDescriptor> curDesc;
    std::unique_ptr<plVarDescriptor> curVar;
    bool reexamine = false;
    ST::string tok;
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
                            ST::format("Unexpected token '{}', expected '{'", tok).c_str());
                }
                state = kUruStateDesc;
            } else if (tok == "struct") {
                curDesc.reset(new plStateDescriptor());
                curDesc->setName(tokStream->next());
                tok = tokStream->next();
                if (tok != "{") {
                    throw plSDLParseException(__FILE__, __LINE__,
                            ST::format("Unexpected token '{}', expected '{'", tok).c_str());
                }
                state = kEoaStateDesc;
            } else {
                throw plSDLParseException(__FILE__, __LINE__,
                        ST::format("Unexpected token '{}', expected 'STATEDESC', 'struct'", tok).c_str());
            }
        } else if (state == kUruStateDesc) {
            if (tok == "VAR") {
                curVar.reset(new plVarDescriptor());
                ST::string typeStr = tokStream->next();
                plVarDescriptor::Type varType = plVarDescriptor::GetTypeFromString(typeStr, false);
                curVar->setType(varType);
                if (varType == plVarDescriptor::kStateDescriptor)
                    curVar->setStateDescType(typeStr.substr(1));
                if (varType == plVarDescriptor::kNone ||
                        (varType == plVarDescriptor::kStateDescriptor && typeStr.size() < 2)) {
                    throw plSDLParseException(__FILE__, __LINE__,
                            ("Invalid var type: " + typeStr).c_str());
                }
                curVar->setName(tokStream->next());
                if (tokStream->peekNext() == "[") {
                    tokStream->next();
                    tok = tokStream->next();
                    if (tok != "]") {
                        curVar->setCount(tok.to_uint());
                        tok = tokStream->next();
                    } else {
                        curVar->setVariableLength(true);
                    }
                    if (tok != "]") {
                        throw plSDLParseException(__FILE__, __LINE__,
                                ST::format("Unexpected token '{}', expected ']'", tok).c_str());
                    }
                }
                state = kUruVarLine;
            } else if (tok == "VERSION") {
                curDesc->setVersion(tokStream->next().to_int());
            } else if (tok == "}") {
                fDescriptors.push_back(curDesc.release());
                state = kFile;
            } else {
                throw plSDLParseException(__FILE__, __LINE__,
                        ST::format("Unexpected token '{}', expected 'VAR', 'VERSION', '}'", tok).c_str());
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
                            ST::format("Unexpected '{}', expected '='", tok).c_str());
                }
                ST::string defStr;
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
                            ST::format("Unexpected '{}', expected '='", tok).c_str());
                }
                tok = tokStream->next();
                if (tok.to_lower() == "vault") {
                    curVar->setAlwaysNew(true);
                } else if (tok.to_lower() == "hidden") {
                    curVar->setInternal(true);
                } else if (tok.to_lower() == "red") {
                    curVar->setDisplay(tok);
                } else {
                    throw plSDLParseException(__FILE__, __LINE__,
                            ST::format("Unexpected DEFAULTOPTION '{}'", tok).c_str());
                }
            } else if (tok == "DISPLAYOPTION") {
                tok = tokStream->next();
                if (tok != "=") {
                    throw plSDLParseException(__FILE__, __LINE__,
                            ST::format("Unexpected '{}', expected '='", tok).c_str());
                }
                tok = tokStream->next();
                curVar->setDisplay(tok);
                if (tok.to_lower() == "hidden")
                    curVar->setInternal(true);
            } else if (tok == "INTERNAL") {
                curVar->setInternal(true);
            } else if (tok == "PHASED") {
                curVar->setAlwaysNew(true);
            } else {
                throw plSDLParseException(__FILE__, __LINE__,
                        ST::format("Unexpected token '{}'", tok).c_str());
            }
        } else if (state == kEoaStateDesc) {
            if (tok == "version") {
                curDesc->setVersion(tokStream->next().to_int());
                tok = tokStream->next();
                if (tok != ";") {
                    throw plSDLParseException(__FILE__, __LINE__,
                            ST::format("Unexpected '{}', expected ';'", tok).c_str());
                }
            } else if (tok == "}") {
                fDescriptors.push_back(curDesc.release());
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
                        curVar->setCount(tok.to_uint());
                        tok = tokStream->next();
                    } else {
                        curVar->setVariableLength(true);
                    }
                    if (tok != "]") {
                        throw plSDLParseException(__FILE__, __LINE__,
                                ST::format("Unexpected token '{}', expected ']'", tok).c_str());
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
                            ST::format("Unexpected '{}', expected '='", tok).c_str());
                }
                int nParens = 0;
                ST::string defStr;
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
                        ST::format("Unexpected token '{}'", tok).c_str());
            }
        }
    }

    if (state != kFile)
        throw plSDLParseException(__FILE__, __LINE__, "Unexpected End of File");
}

void plSDLMgr::ClearDescriptors()
{
    for (size_t i=0; i<fDescriptors.size(); i++)
        delete fDescriptors[i];
    fDescriptors.clear();
}

plStateDescriptor* plSDLMgr::GetDescriptor(const ST::string& name, int version)
{
    plStateDescriptor* desc = nullptr;
    int hiVersion = 0;
    for (size_t i=0; i<fDescriptors.size(); i++) {
        if (fDescriptors[i]->getName().compare_i(name) == 0) {
            if (version == -1 && hiVersion <= fDescriptors[i]->getVersion()) {
                desc = fDescriptors[i];
                hiVersion = desc->getVersion();
            } else if (fDescriptors[i]->getVersion() == version) {
                desc = fDescriptors[i];
            }
        }
    }
    if (desc) {
        for (size_t i=0; i<desc->getNumVars(); i++) {
            if (desc->get(i)->getType() == plVarDescriptor::kStateDescriptor)
                desc->get(i)->setStateDesc(GetDescriptor(desc->get(i)->getStateDescType(),
                                                         desc->get(i)->getStateDescVer()));
        }
    }
    return desc;
}

std::vector<ST::string> plSDLMgr::GetDescriptorNames() const
{
    std::unordered_set<ST::string, ST::hash_i, ST::equal_i> descs;
    for (const auto& it : fDescriptors)
        descs.insert(it->getName());
    return std::vector<ST::string>(descs.begin(), descs.end());
}

void plSDLMgr::read(hsStream* S)
{
    ClearDescriptors();
    fDescriptors.resize(S->readShort());
    for (size_t i=0; i<fDescriptors.size(); i++) {
        fDescriptors[i] = new plStateDescriptor();
        fDescriptors[i]->read(S);
    }

    // Propagate types on SDVars
    for (size_t i=0; i<fDescriptors.size(); i++) {
        plStateDescriptor* desc = fDescriptors[i];
        for (size_t j=0; j<desc->getNumVars(); j++) {
            plVarDescriptor* var = desc->get(j);
            if (var->getType() == plVarDescriptor::kStateDescriptor)
                var->setStateDesc(GetDescriptor(var->getStateDescType(),
                                                var->getStateDescVer()));
        }
    }
}

void plSDLMgr::write(hsStream* S)
{
    S->writeShort(fDescriptors.size());
    for (size_t i=0; i<fDescriptors.size(); i++)
        fDescriptors[i]->write(S);
}
