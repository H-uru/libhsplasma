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
#include <Debug/hsExceptions.hpp>
#include <Stream/hsStdioStream.h>
#include <Debug/plDebug.h>
#include <PRP/KeyedObject/hsKeyedObject.h>
#include <string_theory/stdio>
#include <cstring>

static void doHelp(const char* exename)
{
    ST::printf("Usage: {} [options] filename\n", exename);
    puts("");
    puts("Options:");
    puts("\t-o file      Write output to `file`");
    puts("\t-v ver       Select input version (prime, pots, moul, eoa, hex, universal)");
    puts("\t             (for use with Creatables; PRP versions are determined automatically)");
    puts("\t-x type:name Decompile a single object from a PRP file");
    puts("\t--novtx      Don't include vertex data");
    puts("\t--notex      Don't include texture data");
    puts("\t--help       Display this help message and then exit");
    puts("");
}

int main(int argc, char* argv[])
{
    ST::string inputFile, outputFile;
    bool exVtx = false, exTex = false;
    PlasmaVer inVer = PlasmaVer::pvUnknown;
    ST::string objName;
    short objType = -1;

    if (argc == 1) {
        doHelp(argv[0]);
        return 0;
    }

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--out") == 0) {
            if (++i >= argc) {
                fputs("Error: expected filename\n", stderr);
                return 1;
            }
            outputFile = argv[i];
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--ver") == 0) {
            if (++i >= argc) {
                fputs("Error: expected version specifier\n", stderr);
                return 1;
            }
            ST::string ver = ST::string(argv[i]).to_lower();
            if (ver == "prime")
                inVer = PlasmaVer::pvPrime;
            else if (ver == "pots")
                inVer = PlasmaVer::pvPots;
            else if (ver == "moul")
                inVer = PlasmaVer::pvMoul;
            else if (ver == "eoa")
                inVer = PlasmaVer::pvEoa;
            else if (ver == "hex")
                inVer = PlasmaVer::pvHex;
            else if (ver == "universal")
                inVer = PlasmaVer::pvUniversal;
            else {
                ST::printf(stderr, "Error: unrecognized version: {}\n", ver);
                return 1;
            }
        } else if (strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "--extract") == 0) {
            if (++i >= argc) {
                fputs("Error: expected object specifier", stderr);
                return 1;
            }
            ST::string objSpec = argv[i];
            ST::string type = objSpec.before_first(':');
            objType = plFactory::ClassIndex(type.c_str());
            if (objType == -1)
                objType = type.to_int();
            objName = objSpec.after_last(':');
            if (objName.starts_with("\"")) {
                do {
                    if (++i >= argc) {
                        fputs("Error: Unterminated string\n", stderr);
                        return 1;
                    }
                    objName += ST_LITERAL(" ") + argv[i];
                } while (!objName.ends_with("\""));
                objName = objName.substr(1, objName.size() - 2);
            }
        } else if (strcmp(argv[i], "--notex") == 0) {
            exTex = true;
            fputs("Warning: omitting texture data; output files wil be incomplete\n", stderr);
        } else if (strcmp(argv[i], "--novtx") == 0) {
            exVtx = true;
            fputs("Warning: omitting vertex data; output files wil be incomplete\n", stderr);
        } else if (strcmp(argv[i], "-?") == 0 || strcmp(argv[i], "--help") == 0) {
            doHelp(argv[0]);
            return 0;
        } else if (argv[i][0] == '-') {
            ST::printf(stderr, "Warning: unrecognized option {}\n", argv[i]);
        } else {
            if (inputFile.empty())
                inputFile = argv[i];
            else
                ST::printf(stderr, "Warning: ignoring extra parameter {}\n", argv[i]);
        }
    }
    if (outputFile.empty())
        outputFile = "out.prc";
    if (!inVer.isValid() && inputFile.after_last('.') != "prp" && inputFile.after_last('.') != "age") {
        fputs("Error: Plasma version must be specified for object decompilation\n", stderr);
        return 1;
    }

    plDebug::Init(plDebug::kDLAll);
    plResManager rm;
    rm.setVer(inVer, true);

    hsFileStream out;
    out.open(outputFile, fmCreate);
    pfPrcHelper prc(&out);
    if (exTex)
        prc.exclude(pfPrcHelper::kExcludeTextureData);
    if (exVtx)
        prc.exclude(pfPrcHelper::kExcludeVertexData);

    try {
        if (inputFile.after_last('.') == "prp") {
            plPageInfo* page = rm.ReadPage(inputFile);
            if (objType == -1) {
                rm.WritePagePrc(&prc, page);
            } else {
                std::vector<plKey> keys = rm.getKeys(page->getLocation(), objType);
                bool found = false;
                for (std::vector<plKey>::iterator it = keys.begin(); it != keys.end(); it++) {
                    if ((*it)->getName() == objName && (*it)->getObj() != nullptr) {
                        (*it)->getObj()->prcWrite(&prc);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    ST::printf(stderr, "Object {}:{} does not exist\n",
                               plFactory::ClassName(objType), objName);
                }
            }
        } else if (inputFile.after_last('.') == "age") {
            plAgeInfo* age = rm.ReadAge(inputFile, false);
            rm.WriteAgePrc(&prc, age);
        } else {
            hsFileStream in;
            if (!in.open(inputFile, fmRead)) {
                fputs("Error opening input file\n", stderr);
                return 1;
            }
            in.setVer(inVer);
            plCreatable* cre = rm.ReadCreatable(&in);
            cre->prcWrite(&prc);
        }
    } catch (hsException& e) {
        ST::printf(stderr, "{}:{}: {}\n", e.File(), e.Line(), e.what());
        return 1;
    } catch (std::exception& e) {
        ST::printf(stderr, "Caught Exception: {}\n", e.what());
        return 1;
    }

    ST::printf("Successfully decompiled {}!\n", inputFile);

    return 0;
}
