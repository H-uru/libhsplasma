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

#include <ResManager/plResManager.h>
#include <ResManager/plFactory.h>
#include <Debug/hsExceptions.h>
#include <Stream/hsStdioStream.h>
#include <Debug/plDebug.h>
#include <PRP/KeyedObject/hsKeyedObject.h>

void doHelp(const char* exename) {
    printf("Usage: %s [options] filename\n\n", exename);
    printf("Options:\n");
    printf("\t-o file      Write output to `file`\n");
    printf("\t-v ver       Select input version (prime, pots, live, eoa, hex, universal)\n");
    printf("\t             (for use with Creatables; PRP versions are determined automatically)\n");
    printf("\t-x type:name Decompyle a single object from a PRP file\n");
    printf("\t--novtx      Don't include vertex data\n");
    printf("\t--notex      Don't include texture data\n");
    printf("\t--help       Display this help message and then exit\n\n");
}

int main(int argc, char** argv) {
    plString inputFile, outputFile;
    bool exVtx = false, exTex = false;
    PlasmaVer inVer = pvUnknown;
    plString objName;
    short objType = -1;

    if (argc == 1) {
        doHelp(argv[0]);
        return 0;
    }

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--out") == 0) {
            if (++i >= argc) {
                fprintf(stderr, "Error: expected filename\n");
                return 1;
            }
            outputFile = argv[i];
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--ver") == 0) {
            if (++i >= argc) {
                fprintf(stderr, "Error: expected version specifier\n");
                return 1;
            }
            plString ver = plString(argv[i]).toLower();
            if (ver == "prime")
                inVer = pvPrime;
            else if (ver == "pots")
                inVer = pvPots;
            else if (ver == "live")
                inVer = pvLive;
            else if (ver == "eoa")
                inVer = pvEoa;
            else if (ver == "hex")
                inVer = pvHex;
            else if (ver == "universal")
                inVer = pvUniversal;
            else {
                fprintf(stderr, "Error: unrecognized version: %s\n", ver.cstr());
                return 1;
            }
        } else if (strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "--extract") == 0) {
            if (++i >= argc) {
                fprintf(stderr, "Error: expected object specifier");
                return 1;
            }
            plString objSpec = argv[i];
            plString type = objSpec.beforeFirst(':');
            objType = plFactory::ClassIndex(type);
            if (objType == -1)
                objType = type.toInt();
            objName = objSpec.afterLast(':');
            if (objName.startsWith("\"")) {
                do {
                    if (++i >= argc) {
                        fprintf(stderr, "Error: Unterminated string");
                        return 1;
                    }
                    objName += plString(" ") + argv[i];
                } while (!objName.endsWith("\""));
                objName = objName.mid(1, objName.len() - 2);
            }
        } else if (strcmp(argv[i], "--notex") == 0) {
            exTex = true;
            fprintf(stderr, "Warning: omitting texture data; output files wil be incomplete\n");
        } else if (strcmp(argv[i], "--novtx") == 0) {
            exVtx = true;
            fprintf(stderr, "Warning: omitting vertex data; output files wil be incomplete\n");
        } else if (strcmp(argv[i], "-?") == 0 || strcmp(argv[i], "--help") == 0) {
            doHelp(argv[0]);
            return 0;
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "Warning: unrecognized option %s\n", argv[i]);
        } else {
            if (inputFile.empty())
                inputFile = argv[i];
            else
                fprintf(stderr, "Warning: ignoring extra parameter %s\n", argv[i]);
        }
    }
    if (outputFile.empty())
        outputFile = "out.prc";
    if (inVer == pvUnknown && inputFile.afterLast('.') != "prp" && inputFile.afterLast('.') != "age") {
        fprintf(stderr, "Error: Plasma version must be specified for object decompilation\n");
        return 1;
    }

    plDebug::Init(plDebug::kDLAll);
    plResManager rm;
    rm.setVer(inVer, true);

    hsFileStream out;
    out.open(outputFile, fmCreate);
    pfPrcHelper prc(&out);
    if (exTex) prc.exclude(pfPrcHelper::kExcludeTextureData);
    if (exVtx) prc.exclude(pfPrcHelper::kExcludeVertexData);

    try {
        if (inputFile.afterLast('.') == "prp") {
            plPageInfo* page = rm.ReadPage(inputFile);
            if (objType == -1) {
                rm.WritePagePrc(&prc, page);
            } else {
                std::vector<plKey> keys = rm.getKeys(page->getLocation(), objType);
                bool found = false;
                for (std::vector<plKey>::iterator it = keys.begin(); it != keys.end(); it++) {
                    if ((*it)->getName() == objName && (*it)->getObj() != NULL) {
                        (*it)->getObj()->prcWrite(&prc);
                        found = true;
                        break;
                    }
                }
                if (!found)
                    fprintf(stderr, "Object %s:%s does not exist\n",
                                    plFactory::ClassName(objType),
                                    objName.cstr());
            }
        } else if (inputFile.afterLast('.') == "age") {
            plAgeInfo* age = rm.ReadAge(inputFile, false);
            rm.WriteAgePrc(&prc, age);
        } else {
            hsFileStream in;
            if (!in.open(inputFile, fmRead)) {
                fprintf(stderr, "Error opening input file\n");
                return 1;
            }
            in.setVer(inVer);
            plCreatable* cre = rm.ReadCreatable(&in);
            cre->prcWrite(&prc);
        }
    } catch (hsException& e) {
        fprintf(stderr, "%s:%lu: %s\n", e.File(), e.Line(), e.what());
        return 1;
    } catch (std::exception& e) {
        fprintf(stderr, "Caught Exception: %s\n", e.what());
        return 1;
    }
    
    printf("Successfully decompiled %s!\n", inputFile.cstr());

    return 0;
}
