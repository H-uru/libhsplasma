#include "PubUtilLib/plResMgr/plResManager.h"
#include <string.h>
#ifdef WIN32
  #include <windows.h>
  #define SLASH '\\'
#else
  #include <unistd.h>
  #include <dirent.h>
  #define SLASH '/'
#endif
#include <sys/stat.h>

void doHelp() {
    printf("Usage: PrpPack [-x|-r] filename.prp\n");
    printf("       PrpPack [-c] filename.prd\n\n");
    printf("If you're not handy with a hex editor, turn back now!\n\n");
    printf("Options:  -x    Extract a PRP file\n");
    printf("          -r    (Default) Unpacks and repacks the PRP file.  Temp files\n");
    printf("                are automatically deleted after the operation is finished.\n");
    printf("          -c    (Default for .prd files) Create a PRP file from a PRD.\n\n");
    printf("PRD Format\n");
    printf("    [4]   \"PRD\\0\"\n");
    printf("    [2]   Length of Age Name\n");
    printf("    [?]   Age Name\n");
    printf("    [2]   Length of Page Name\n");
    printf("    [?]   Page Name\n");
    printf("    [2:2] Plasma Version [Major:Minor] (Use 0 for EOA)\n");
    printf("    [4]   PageID (actual value)\n");
    printf("    [1]   Location Flags\n\n");
    printf("Objects are read from Age_Page_PRP\\*.po\n\n");
}

typedef enum { kCreate, kExtract, kRepack } eDirection;

const char* filenameConvert(char* filename, eDirection dir) {
    if (dir == kRepack) {
        fprintf(stderr, "Zrax broke me!\n");
        abort();
    }
    char* newName = (char*)malloc(strlen(filename)+5);
    strcpy(newName, filename);
    char* dotLoc = strrchr(newName, '.');
    if (dotLoc == NULL) {
        strcat(newName, dir == kCreate ? ".prp" : ".prd");
    } else if (dir == kCreate) {
        if (strcmp(dotLoc, ".prd") == 0)
            newName[strlen(newName)-1] = 'p';
        else if (strcmp(dotLoc, ".prp") != 0)
            strcat(newName, ".prp");
    } else {
        if (strcmp(dotLoc, ".prp") == 0)
            newName[strlen(newName)-1] = 'd';
        else if (strcmp(dotLoc, ".prd") != 0)
            strcat(newName, ".prd");
    }
    return newName;
}

const char* getOutputDir(char* filename, plPageInfo* page) {
    char* odir = (char*)malloc(strlen(filename) +
                        strlen(page->getAge()) + strlen(page->getPage()) + 7);
    strcpy(odir, filename);
    char* sepLoc = strrchr(odir, SLASH);
    if (sepLoc == NULL) odir[0] = 0;
    else sepLoc[1] = 0;
    sprintf(odir, "%s%s_%s_PRP%c", odir, page->getAge(), page->getPage(), SLASH);
    return odir;
}

#ifndef WIN32
int selPO(const dirent* de) {
    return strcmp(strrchr(de->d_name, '.'), ".po") == 0;
}

int selAll(const dirent* de) {
    return 1;
}
#endif

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
    if (argc < 2 || argc > 3) {
        doHelp();
        return 0;
    }

    eDirection direction = kRepack;
    char* filename = argv[1];
    if (argc == 3) {
        if (strcmp(argv[1], "-c") == 0)
            direction = kCreate;
        else if (strcmp(argv[1], "-x") == 0)
            direction = kExtract;
        else if (strcmp(argv[1], "-r") == 0)
            direction = kRepack;
        else {
            doHelp();
            return 1;
        }
        filename = argv[2];
    } else if (strcmp(strrchr(filename, '.'), ".prd") == 0) {
        direction = kCreate;
    }

    hsStream* S = new hsStream();
    if (!S->open(filename, fmRead)) {
        fprintf(stderr, "Error opening %s for reading!", filename);
        delete S;
        return 1;
    }
    hsStream* OS = new hsStream();
    plPageInfo* page = new plPageInfo();

    int len;
    short maj = 63, min = 11;
    unsigned int i, j;
    char strBuf[256];
    if (direction == kExtract || direction == kRepack) {
        OS->open(filenameConvert(filename, kExtract), fmCreate);
        page->read(S);
        OS->write(4, "PRD");
        len = strlen(page->getAge());
        OS->writeShort(len);
        OS->writeStr(page->getAge(), len);
        len = strlen(page->getPage());
        OS->writeShort(len);
        OS->writeStr(page->getPage(), len);
        if (S->getVer() == pvEoa) maj = min = 0;
        if (S->getVer() == pvPots) min = 12;
        if (S->getVer() == pvLive) {
            maj = 70;
            min = 0;
        }
        OS->writeShort(maj);
        OS->writeShort(min);
        page->getLocation().pageID.write(OS);
        OS->writeByte(page->getLocation().flags);
        OS->close();

        S->seek(page->getIndexStart());
        plKey* keys;
        unsigned int tCount = S->readInt();
      #ifdef WIN32
        CreateDirectory(getOutputDir(filename, page), NULL);
      #else
        mkdir(getOutputDir(filename, page), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
      #endif
        for (i=0; i<tCount; i++) {
            short type = S->readShort();
            if (S->getVer() == pvEoa) {
                S->readInt();
                unsigned char b = S->readByte();
                if (b != 0)
                    printf("NOTICE: Type %04X got flag of %02X\n", type, b);
            }
            unsigned int oCount = S->readInt();
            keys = new plKey[oCount];
            for (j=0; j<oCount; j++)
                keys[j].read(S);
            unsigned int pos = S->pos();
            for (j=0; j<oCount; j++) {
                S->seek(keys[j].fileOff);
                sprintf(strBuf, "%s[%04X]%s.po", getOutputDir(filename, page),
                                type, cleanFileName(keys[j].getName()));
                OS->open(strBuf, fmCreate);
                void* objBuf = malloc(keys[j].objSize);
                S->read(keys[j].objSize, objBuf);
                OS->write(keys[j].objSize, objBuf);
                free(objBuf);
                OS->close();
            }
            S->seek(pos);
            delete[] keys;
        }
    }
    if (direction == kRepack) {
        S->close();
        filename = strdup(filenameConvert(filename, kExtract));
        S->open(filename, fmRead);
    }
    if (direction == kCreate || direction == kRepack) {
        OS->open(filenameConvert(filename, kCreate), fmCreate);
        char sig[4];
        S->read(4, sig);
        if (strcmp(sig, "PRD") != 0) {
            fprintf(stderr, "Error: Invalid input file!\n");
            OS->close();
            S->close();
            delete S;
            delete OS;
            return 1;
        }
        char* ageName = S->readStr(S->readShort());
        char* pageName = S->readStr(S->readShort());
        page->setNames(ageName, pageName);
        maj = S->readShort();
        min = S->readShort();
        OS->setVer(pvPrime);
        if (maj == 0) OS->setVer(pvEoa);
        if (maj >= 70) OS->setVer(pvLive);
        if (min == 12) OS->setVer(pvPots);
        S->setVer(OS->getVer());
        page->getLocation().pageID.read(S);
        page->getLocation().flags = S->readByte();
        page->setReleaseVersion(0);
        page->setFlags(plPageInfo::kBasicChecksum);
        S->close();

        std::vector<char*> inFiles;
        std::vector<short> inClasses;
        hsStream* PS = new hsStream();
        PS->setVer(OS->getVer());
      #ifdef WIN32
        sprintf(strBuf, "%s*.po", getOutputDir(filename, page));
        WIN32_FIND_DATA fd;
        HANDLE fr = FindFirstFile(strBuf, &fd);
        if (fr != NULL) {
            do {
                sprintf(strBuf, "%s%s", getOutputDir(filename, page), fd.cFileName);
                inFiles.push_back(strdup(strBuf));
                PS->open(strBuf, fmRead);
                short classType = PS->readShort();
                PS->close();
                bool haveClass = false;
                for (j=0; j<inClasses.size(); j++)
                    if (inClasses[j] == classType) {
                        haveClass = true;
                }
                if (!haveClass)
                    inClasses.push_back(classType);
            } while (FindNextFile(fr, &fd));
            FindClose(fr);
        }
      #else
        dirent** des;
        unsigned int nEntries = scandir(getOutputDir(filename, page), &des, &selPO, &alphasort);
        for (i=0; i<nEntries; i++) {
            sprintf(strBuf, "%s%s", getOutputDir(filename, page), des[i]->d_name);
            inFiles.push_back(strdup(strBuf));
            PS->open(strBuf, fmRead);
            short classType = PS->readShort();
            PS->close();
            bool haveClass = false;
            for (j=0; j<inClasses.size(); j++)
                if (inClasses[j] == classType) {
                    haveClass = true;
            }
            if (!haveClass)
                inClasses.push_back(classType);
        }
      #endif
        page->setClassList(inClasses);
        page->write(OS);
        page->setDataStart(OS->pos());
        plKeyCollector keys;

        for (i=0; i<inFiles.size(); i++) {
            plKey* key = new plKey();
            PS->open(inFiles[i], fmRead);
            unsigned int poLen = PS->size();
            void* objBuf = malloc(poLen);
            key->fileOff = OS->pos();
            key->objSize = poLen;
            PS->read(poLen, objBuf);
            OS->write(poLen, objBuf);
            free(objBuf);
            PS->seek(2);
            key->readUoid(PS);
            PS->close();
            keys.add(key);
            free(inFiles[i]);
            inFiles[i] = NULL;
        }
        delete PS;

        page->setIndexStart(OS->pos());
        keys.sortKeys(page->getLocation().pageID);
        std::vector<short> types = keys.getTypes(page->getLocation().pageID);
        //if (types != inClasses)
        //    throw "Wtf, mate?";
        OS->writeInt(types.size());
        for (i=0; i<types.size(); i++) {
            std::vector<plKey*> kList = keys.getKeys(page->getLocation().pageID, types[i]);
            OS->writeShort(pdUnifiedTypeMap::MappedToPlasma(types[i], OS->getVer()));
            unsigned int lenPos = OS->pos();
            if (OS->getVer() == pvLive || OS->getVer() == pvEoa) {
                OS->writeInt(0);
                OS->writeByte(0);
            }
            OS->writeInt(kList.size());
            for (j=0; j<kList.size(); j++)
                kList[j]->write(OS);
            if (OS->getVer() == pvEoa || OS->getVer() == pvLive) {
                unsigned int nextPos = OS->pos();
                OS->seek(lenPos);
                OS->writeInt(nextPos - lenPos - 4);
                OS->seek(nextPos);
            }
        }
        if (OS->getVer() == pvEoa)
            page->setChecksum(OS->pos());
        else
            page->setChecksum(OS->pos() - page->getDataStart());
        page->writeSums(OS);
        OS->close();
    }
    
    // Delete temp files with the repack option
    if (direction == kRepack) {
      #ifdef WIN32
        sprintf(strBuf, "%s*.po", getOutputDir(filename, page));
        WIN32_FIND_DATA rfd;
        HANDLE rfr = FindFirstFile(strBuf, &rfd);
        if (rfr != NULL) {
            do {
                sprintf(strBuf, "%s%s", getOutputDir(filename, page), rfd.cFileName);
                DeleteFile(strBuf);
            } while (FindNextFile(rfr, &rfd));
            FindClose(rfr);
        }
        RemoveDirectory(getOutputDir(filename, page));
        DeleteFile(filename);
      #else
        dirent** rdes;
        unsigned int nEntries = scandir(getOutputDir(filename, page), &rdes, &selAll, &alphasort);
        for (i=0; i<nEntries; i++) {
            sprintf(strBuf, "%s%s", getOutputDir(filename, page), rdes[i]->d_name);
            unlink(strBuf);
        }
        rmdir(getOutputDir(filename, page));
        unlink(filename);
      #endif
    }
    
    delete S;
    delete OS;
    return 0;
}

