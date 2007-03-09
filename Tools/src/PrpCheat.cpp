#include "PubUtilLib/plResMgr/plResManager.h"
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

void doHelp() {
    printf("Usage: PrpCheat filename.prd\n");
    printf("       PrpCheat -x filename.prp\n");
    printf("If you're not handy with a hex editor, turn back now!\n\n");
    printf("Options:  -x    Extract, instead of create, a PRD file\n\n");
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

typedef enum { kCreate, kExtract } eDirection;

const char* filenameConvert(char* filename, eDirection dir) {
    char* newName = (char*)malloc(strlen(filename)+5);
    strcpy(newName, filename);
    char* dotLoc = strrchr(newName, '.');
    if (dotLoc == NULL) {
        strcat(newName, dir == kCreate ? ".prp" : ".prd");
    } else if (dir == kCreate) {
        if (strcmp(dotLoc, ".prd") == 0)
            newName[strlen(newName)-1] = 'p';
        else
            strcat(newName, ".prp");
    } else {
        if (strcmp(dotLoc, ".prp") == 0)
            newName[strlen(newName)-1] = 'd';
        else
            strcat(newName, ".prd");
    }
    return newName;
}

const char* getOutputDir(char* filename, plPageInfo* page) {
    char* odir = (char*)malloc(strlen(filename) +
                        strlen(page->getAge()) + strlen(page->getPage()) + 7);
    strcpy(odir, filename);
    char* sepLoc = strrchr(odir, '/');
    if (sepLoc == NULL) odir[0] = 0;
    else sepLoc[1] = 0;
    sprintf(odir, "%s%s_%s_PRP/", odir, page->getAge(), page->getPage());
    return odir;
}

int selPO(const dirent* de) {
    return strcmp(strrchr(de->d_name, '.'), ".po") == 0;
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        doHelp();
        return 0;
    }

    eDirection direction = kCreate;
    char* filename = argv[1];
    if (strcmp(argv[1], "-x") == 0) {
        direction = kExtract;
        if (argc != 3) {
            doHelp();
            return 0;
        }
        filename = argv[2];
    }

    hsStream* S = new hsStream();
    if (!S->open(filename, fmRead)) {
        fprintf(stderr, "Error opening %s for reading!", filename);
        delete S;
        return 1;
    }
    hsStream* OS = new hsStream();
    OS->open(filenameConvert(filename, direction), fmCreate);
    plPageInfo* page = new plPageInfo();

    int len;
    short maj = 63, min = 11;
    unsigned int i, j;
    char strBuf[256];
    if (direction == kExtract) {
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
        mkdir(getOutputDir(filename, page), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
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
                                type, keys[j].getName());
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
    } else {
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
        dirent** des;
        unsigned int nEntries = scandir(getOutputDir(filename, page), &des, &selPO, &alphasort);
        hsStream* PS = new hsStream();
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

    delete S;
    delete OS;
    return 0;
}

