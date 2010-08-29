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
#include <Debug/hsExceptions.h>
#include <PRP/plPageInfo.h>
#include <PRP/plCreatable.h>

void doHelp(const char* exename) {
    printf("Usage: %s infile [options]\n\n", exename);
    printf("Options:\n");
    printf("\t-o file  Write output to `file`\n");
    printf("\t-v ver   Select output version (prime, pots, moul, eoa, hex, universal)\n");
    printf("\t--help   Display this help and then exit\n\n");
}

int main(int argc, char* argv[]) {
    plString inputFile, outputFile;
    PlasmaVer outVer = PlasmaVer::pvUnknown;

    if (argc == 1) {
        doHelp(argv[0]);
        return 0;
    }

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--out") == 0) {
            outputFile = argv[++i];
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--ver") == 0) {
            plString ver = plString(argv[++i]).toLower();
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
                fprintf(stderr, "Error: unrecognized version: %s\n", ver.cstr());
                return 1;
            }
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
    if (outVer == PlasmaVer::pvUnknown) {
        fprintf(stderr, "Warning: Unspecified version.  Defaulting to PotS\n");
        outVer = PlasmaVer::pvPots;
    }

    plDebug::Init(plDebug::kDLAll);
    plResManager rm;
    rm.setVer(outVer, true);
    hsFileStream S;
    if (!S.open(inputFile, fmRead)) {
        fprintf(stderr, "Error opening input file\n");
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
            if (cre != NULL) {
                hsFileStream out;
                out.setVer(outVer);
                out.open(outputFile, fmCreate);
                rm.WriteCreatable(&out, cre);
            }
        }
    } catch (hsException& e) {
        fprintf(stderr, "%s:%lu: %s\n", e.File(), e.Line(), e.what());
        return 1;
    } catch (std::exception& e) {
        fprintf(stderr, "Caught Exception: %s\n", e.what());
        return 1;
    }

    printf("Successfully compiled %s!\n", inputFile.cstr());

    return 0;
}
