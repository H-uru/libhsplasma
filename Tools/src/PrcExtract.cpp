#include "PubUtilLib/plResMgr/plResManager.h"
#include "CoreLib/plString.h"
#include <string.h>
#include <time.h>
#ifdef WIN32
  #include <windows.h>
  #define SLASH '\\'
#else
  #include <unistd.h>
  #define SLASH '/'
#endif
#include <sys/stat.h>

void doHelp() {
    printf("Usage: PrcExtract filename.prp\n\n");
    printf("Objects are written to Age_PRC\\filename.prc\n");
    printf("Binary data is written to Age_PRC\\filename.ext\n\n");
}

plString filenameConvert(const char* filename) {
    plString name = filename;
    if (name.rfind('.') >= 0)
        name = name.left(name.rfind('.')) + ".prc";
    else
        name += ".prc";
    if (name.rfind(SLASH) >= 0)
        return name.mid(name.rfind(SLASH) + 1);
    else
        return name;
}

plString getOutputDir(const char* filename, plPageInfo* page) {
    plString name = filename;
    if (name.rfind(SLASH) >= 0)
        name = name.left(name.rfind(SLASH) + 1);
    else
        name = "";
    return name + page->getAge() + "_PRC" + SLASH;
}

plString cleanFileName(const char* filename) {
    char* cName = strdup(filename);
    for (char* c=cName; *c != 0; c++) {
        if (*c < 0x20 || *c > 0x7E || *c == '\\' || *c == '/' ||
            *c == '*' || *c == ':' || *c == '?' || *c == '"' ||
            *c == '<' || *c == '>' || *c == '|' || *c == '\'')
            *c = '_';
    }
    plString sName = cName;
    free(cName);
    return sName;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        doHelp();
        return 0;
    }

    plResManager rm;
    plPageInfo* page;
    plString outDir, outFile;
    for (int i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-') argv[i]++;
            if (strcmp(argv[i], "-help") == 0) {
                doHelp();
                return 0;
            } else {
                fprintf(stderr, "Error: Unrecognized option %s\n", argv[i]);
                return 1;
            }
        } else {
            try {
                page = rm.ReadPage(argv[i]);
            } catch (const char* e) {
                fprintf(stderr, "%s\n", e);
                return 1;
            } catch (...) {
                fprintf(stderr, "Undefined error!\n");
                return 1;
            }
            outDir = getOutputDir(argv[i], page);
            outFile = outDir + filenameConvert(argv[i]);
          #ifdef WIN32
            CreateDirectory(outDir.cstr(), NULL);
          #else
            mkdir(outDir.cstr(), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
          #endif

            hsStream* S = new hsStream();
            if (!S->open(outFile, fmWrite)) {
                fprintf(stderr, "Error opening %s for writing!\n", outFile.cstr());
                delete S;
                return 1;
            }
            S->setVer(rm.getVer());
            pfPrcHelper* prc = new pfPrcHelper(S);
            prc->writeComment("Generator: PrcExtract");
            prc->writeComment(plString("Source: ") + argv[i]);
            time_t ts = time(NULL);
            char buf[256];
            strftime(buf, 256, "Created: %Y/%m/%d %H:%M:%S", localtime(&ts));
            prc->writeComment(buf);
            S->writeStr("\n");
            rm.WritePrc(prc, page);

            delete prc;
            S->close();
            delete S;
        }
    }

    return 0;
}

