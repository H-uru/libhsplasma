#include "PubUtilLib/plResMgr/plResManager.h"
#include "FeatureLib/pfPRC/pfPrcHelper.h"
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
    printf("Usage: PrcExtract filename.prp\n\n");
    printf("Objects are read from and written to Age_Page_PRP\\filename.prc\n\n");
}

const char* filenameConvert(char* filename) {
    char* newName = (char*)malloc(strlen(filename)+5);
    strcpy(newName, filename);
    char* dotLoc = strrchr(newName, '.');
    if (dotLoc == NULL) {
        strcat(newName, ".prc");
    } else {
        if (strcmp(dotLoc, ".prp") == 0)
            newName[strlen(newName)-1] = 'c';
        else
            strcat(newName, ".prc");
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
    if (argc != 2) {
        doHelp();
        return 0;
    }

    char* filename = argv[1];
    hsStream* IS = new hsStream();
    hsStream* OS = new hsStream();
    if (!IS->open(filename, fmRead)) {
        fprintf(stderr, "Error opening %s for reading!", filename);
        delete IS;
        delete OS;
        return 1;
    }
    OS->open(filenameConvert(filename), fmCreate);
    plPageInfo* page = new plPageInfo();
    pfPrcHelper* prc = new pfPrcHelper();
    page->read(IS);
    prc->startPrc(OS);
    page->prcWrite(OS, prc);
    prc->finalize(OS);
    
    IS->close();
    OS->close();

    /*
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
            maj = 69;
            min = 4;
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
                S->readByte();
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
        if (maj >= 69) OS->setVer(pvLive);
        if (min == 12) OS->setVer(pvPots);
        S->setVer(OS->getVer());
        page->getLocation().pageID.read(S);
        page->getLocation().flags = S->readByte();
        page->setReleaseVersion(0);
        page->setFlags(plPageInfo::kBasicChecksum);
        S->close();

        page->write(OS);
        page->setDataStart(OS->pos());
        plKeyCollector keys;
        hsStream* PS = new hsStream();
      #ifdef WIN32
        sprintf(strBuf, "%s*.po", getOutputDir(filename, page));
        WIN32_FIND_DATA fd;
        HANDLE fr = FindFirstFile(strBuf, &fd);
        if (fr != NULL) {
            do {
                plKey* key = new plKey();
                sprintf(strBuf, "%s%s", getOutputDir(filename, page), fd.cFileName);
                PS->open(strBuf, fmRead);
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
            } while (FindNextFile(fr, &fd));
            FindClose(fr);
        }
      #else
        dirent** des;
        unsigned int nEntries = scandir(getOutputDir(filename, page), &des, &selPO, &alphasort);
        PS->setVer(OS->getVer());
        for (i=0; i<nEntries; i++) {
            plKey* key = new plKey();
            sprintf(strBuf, "%s%s", getOutputDir(filename, page), des[i]->d_name);
            PS->open(strBuf, fmRead);
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
        }
      #endif
        delete PS;
        page->setIndexStart(OS->pos());
        if (OS->getVer() == pvEoa) throw "Not yet supported!";
        std::vector<short> types = keys.getTypes(page->getLocation().pageID);
        OS->writeInt(types.size());
        for (i=0; i<types.size(); i++) {
            std::vector<plKey*> kList = keys.getKeys(page->getLocation().pageID, types[i]);
            OS->writeShort(types[i]);
            OS->writeInt(kList.size());
            for (j=0; j<kList.size(); j++)
                kList[j]->write(OS);
        }
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
    */
    
    delete prc;
    delete IS;
    delete OS;
    return 0;
}

