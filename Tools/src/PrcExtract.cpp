#include "PubUtilLib/plResMgr/plResManager.h"
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
    printf("Objects are read from and written to Age_Page_PRP\\filename.prc\n\n");
}

const char* filenameConvert(const char* filename) {
    char* newName = new char[256];
    strcpy(newName, filename);
    char* find = strrchr(newName, '.');
    if (find != NULL)
        *find = '\0';
    find = strrchr(newName, SLASH);
    if (find == NULL)
        find = &newName[0];
    strcat(find, ".prc");
    char* ret = strdup(find);
    delete[] newName;
    return ret;
}

const char* getOutputDir(const char* filename, plPageInfo* page) {
    char* odir = (char*)malloc(strlen(filename) +
                        strlen(page->getAge()) + strlen(page->getPage()) + 7);
    strcpy(odir, filename);
    char* sepLoc = strrchr(odir, SLASH);
    if (sepLoc == NULL) odir[0] = 0;
    else sepLoc[1] = 0;
    sprintf(odir, "%s%s_PRC%c", odir, page->getAge(), SLASH);
    return odir;
}

const char* cleanFileName(const char* filename) {
    char* cName = strdup(filename);
    for (char* c=cName; *c != 0; c++) {
        if (*c < 0x20 || *c > 0x7E || *c == '\\' || *c == '/' ||
            *c == '*' || *c == ':' || *c == '?' || *c == '"' ||
            *c == '<' || *c == '>' || *c == '|' || *c == '\'')
            *c = '_';
    }
    return cName;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        doHelp();
        return 0;
    }

    plResManager rm;
    plPageInfo* page;
    char outfile[256];
    for (int i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            // Switches...  None for now...
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
          #ifdef WIN32
            CreateDirectory(getOutputDir(argv[i], page), NULL);
          #else
            mkdir(getOutputDir(argv[i], page), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
          #endif
            sprintf(outfile, "%s%s", getOutputDir(argv[i], page), filenameConvert(argv[i]));

            hsStream* S = new hsStream();
            if (!S->open(outfile, fmWrite)) {
                fprintf(stderr, "Error opening %s for writing!\n", outfile);
                delete S;
                return 1;
            }
            S->setVer(rm.getVer());
            char buf[256];
            pfPrcHelper* prc = new pfPrcHelper(S);
            prc->writeComment("Generator: PrcExtract");
            sprintf(buf, "Source: %s", argv[i]);
            prc->writeComment(buf);
            time_t ts = time(NULL);
            strftime(buf, 256, "Created: %y/%m/%d %H:%M:%S", localtime(&ts));
            prc->writeComment(buf);
            S->writeStr("\n");
            rm.WritePrc(S, prc, page);

            delete prc;
            S->close();
            delete S;
        }
    }

    return 0;
}

