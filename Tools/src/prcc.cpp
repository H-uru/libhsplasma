#include <ResManager/plResManager.h>
#include <Debug/plDebug.h>
#include <Debug/hsExceptions.h>
#include <PRP/plPageInfo.h>
#include <PRP/plCreatable.h>

void doHelp(const char* exename) {
    printf("Usage: %s infile [options]\n\n", exename);
    printf("Options:\n");
    printf("\t-c       Compile a single creatable, instead of an entire page\n");
    printf("\t-o file  Write output to `file`\n");
    printf("\t-v ver   Select output version (prime, pots, live, eoa, hex)\n");
    printf("\t--help   Display this help and then exit\n\n");
}

int main(int argc, char* argv[]) {
    plString inputFile, outputFile;
    bool objOnly = false;
    PlasmaVer outVer = pvUnknown;

    if (argc == 1) {
        doHelp(argv[0]);
        return 0;
    }

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--creatable") == 0) {
            objOnly = true;
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--out") == 0) {
            outputFile = argv[++i];
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--ver") == 0) {
            plString ver = argv[++i];
            ver.toLower();
            if (ver == "prime")     outVer = pvPrime;
            else if (ver == "pots") outVer = pvPots;
            else if (ver == "live") outVer = pvLive;
            else if (ver == "eoa")  outVer = pvEoa;
            else if (ver == "hex")  outVer = pvHex;
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
    if (outputFile.empty())
        outputFile = objOnly ? "a.po" : "a.prp";
    if (outVer == pvUnknown) {
        fprintf(stderr, "Warning: Unspecified version.  Defaulting to PotS\n");
        outVer = pvPots;
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
        if (objOnly) {
            plCreatable* cre = rm.prcParseCreatable(root);
            if (cre != NULL) {
                hsFileStream out;
                out.setVer(outVer);
                out.open(outputFile, fmCreate);
                rm.WriteCreatable(&out, cre);
            }
        } else {
            plPageInfo* page = rm.ReadPagePrc(root);
            rm.WritePage(outputFile, page);
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
