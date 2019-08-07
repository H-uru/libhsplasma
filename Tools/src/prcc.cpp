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
#include <Debug/plDebug.h>
#include <Debug/hsExceptions.hpp>
#include <PRP/plPageInfo.h>
#include <PRP/plCreatable.h>
#include <string_theory/stdio>
#include <cstring>

static void doHelp(const char* exename)
{
    ST::printf("Usage: {} infile [options]\n", exename);
    puts("");
    puts("Options:");
    puts("\t-o file  Write output to `file`");
    puts("\t-v ver   Select output version (prime, pots, moul, eoa, hex, universal)");
    puts("\t--help   Display this help and then exit");
    puts("");
}

int main(int argc, char* argv[])
{
    ST::string inputFile, outputFile;
    PlasmaVer outVer = PlasmaVer::pvUnknown;

    if (argc == 1) {
        doHelp(argv[0]);
        return 0;
    }

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--out") == 0) {
            outputFile = argv[++i];
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--ver") == 0) {
            ST::string ver = ST::string(argv[++i]).to_lower();
            if (ver == "prime")
                outVer = PlasmaVer::pvPrime;
            else if (ver == "pots")
                outVer = PlasmaVer::pvPots;
            else if (ver == "moul")
                outVer = PlasmaVer::pvMoul;
            else if (ver == "eoa")
                outVer = PlasmaVer::pvEoa;
            else if (ver == "hex")
                outVer = PlasmaVer::pvHex;
            else if (ver == "universal")
                outVer = PlasmaVer::pvUniversal;
            else {
                ST::printf(stderr, "Error: unrecognized version: {}\n", ver);
                return 1;
            }
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
    if (outVer == PlasmaVer::pvUnknown) {
        fputs("Warning: Unspecified version.  Defaulting to PotS\n", stderr);
        outVer = PlasmaVer::pvPots;
    }

    plDebug::Init(plDebug::kDLAll);
    plResManager rm;
    rm.setVer(outVer, true);
    hsFileStream S;
    if (!S.open(inputFile, fmRead)) {
        fputs("Error opening input file\n", stderr);
        return 1;
    }
    pfPrcParser prc;
    try {
        prc.read(&S);
        const pfPrcTag* root = prc.getRoot();
        if (root->getName() == "Page") {
            if (outputFile.empty())
                outputFile = "out.prp";
            plPageInfo* page = rm.ReadPagePrc(root);
            rm.WritePage(outputFile, page);
        } else if (root->getName() == "Age") {
            if (outputFile.empty())
                outputFile = "out.age";
            plAgeInfo* age = rm.ReadAgePrc(root);
            rm.WriteAge(outputFile, age);
        } else {
            if (outputFile.empty())
                outputFile = "out.po";
            plCreatable* cre = rm.prcParseCreatable(root);
            if (cre) {
                hsFileStream out;
                out.setVer(outVer);
                out.open(outputFile, fmCreate);
                rm.WriteCreatable(&out, cre);
            }
        }
    } catch (hsException& e) {
        ST::printf(stderr, "{}:{}: {}\n", e.File(), e.Line(), e.what());
        return 1;
    } catch (std::exception& e) {
        ST::printf(stderr, "Caught Exception: {}\n", e.what());
        return 1;
    }

    ST::printf("Successfully compiled {}!\n", inputFile);

    return 0;
}
