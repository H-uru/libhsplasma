#include <ResManager/plResManager.h>
#include <Debug/hsExceptions.h>
#include <Stream/hsStdioStream.h>
#include <Debug/plDebug.h>
#include <PRP/plCreatable.h>

void doHelp(const char* exename) {
    printf("Usage: %s [options] filename\n\n", exename);
    printf("Options:\n");
    printf("\t-c       Decompile a single creatable, instead of an entire page\n");
    printf("\t-o file  Write output to `file`\n");
    printf("\t-v ver   Select input version (prime, pots, live, eoa, hex)\n");
    printf("\t         (for use with -c; PRP versions are determined automatically)\n");
    printf("\t--novtx  Don't include vertex data\n");
    printf("\t--notex  Don't include texture data\n");
    printf("\t--help   Display this help message and then exit\n\n");
}

int main(int argc, char** argv) {
    plString inputFile, outputFile;
    bool objOnly = false;
    bool exVtx = false, exTex = false;
    PlasmaVer inVer = pvUnknown;

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
            if (ver == "prime")     inVer = pvPrime;
            else if (ver == "pots") inVer = pvPots;
            else if (ver == "live") inVer = pvLive;
            else if (ver == "eoa")  inVer = pvEoa;
            else if (ver == "hex")  inVer = pvHex;
            else {
                fprintf(stderr, "Error: unrecognized version: %s\n", ver.cstr());
                return 1;
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
    if (inVer == pvUnknown && objOnly) {
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
        if (objOnly) {
            hsFileStream in;
            if (!in.open(inputFile, fmRead)) {
                fprintf(stderr, "Error opening input file\n");
                return 1;
            }
            in.setVer(inVer);
            plCreatable* cre = rm.ReadCreatable(&in);
            cre->prcWrite(&prc);
        } else {
            plPageInfo* page = rm.ReadPage(inputFile);
            rm.WritePagePrc(&prc, page);
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
