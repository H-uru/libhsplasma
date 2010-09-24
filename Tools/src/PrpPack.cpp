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

#include "ResManager/plResManager.h"
#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Sys/Platform.h"
#include <string.h>
#ifdef WIN32
  #include <windows.h>
#else
  #include <unistd.h>
  #include <dirent.h>
#endif
#include <sys/stat.h>

#ifdef MACOSX
  #define DIRENT dirent*
#else
  #define DIRENT const dirent*
#endif

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
    printf("    [2]   Location Flags\n\n");
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
                        page->getAge().len() + page->getPage().len() + 7);
    strcpy(odir, filename);
    char* sepLoc = strrchr(odir, PATHSEP);
    if (sepLoc == NULL) odir[0] = 0;
    else sepLoc[1] = 0;
    sprintf(odir, "%s%s_%s_PRP%c", odir, page->getAge().cstr(), page->getPage().cstr(), PATHSEP);
    return odir;
}

#ifndef WIN32
int selPO(DIRENT de) {
    return strcmp(strrchr(de->d_name, '.'), ".po") == 0;
}

int selAll(DIRENT de) {
    return 1;
}
#endif

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
    } else if (strrchr(filename, '.') && strcmp(strrchr(filename, '.'), ".prd") == 0) {
        direction = kCreate;
    }

    plResManager rm;
    hsFileStream* S = new hsFileStream();
    if (!S->open(filename, fmRead)) {
        fprintf(stderr, "Error opening %s for reading!", filename);
        delete S;
        return 1;
    }
    hsFileStream* OS = new hsFileStream();
    plPageInfo* page = new plPageInfo();

    //int len;
    short maj = 63, min = 11;
    unsigned int i, j;
    char strBuf[256];
    if (direction == kExtract || direction == kRepack) {
        S->close();
        delete S;
        S = NULL;
        delete page;
        page = rm.ReadPage(filename, true);
        OS->open(filenameConvert(filename, kExtract), fmCreate);
        OS->write(4, "PRD");
        OS->writeShort(strlen(page->getAge()));
        OS->writeStr(page->getAge());
        OS->writeShort(strlen(page->getPage()));
        OS->writeStr(page->getPage());
        if (rm.getVer().isUniversal()) {
            maj = 0x7FFF;
            min = 0x7FFF;
        } else  if (rm.getVer().isEoa()) {
            maj = -1;
            min = 1;
        } else if (rm.getVer().isHexIsle()) {
            maj = -1;
            min = 2;
        } else {
            maj = rm.getVer().revMajor();
            min = rm.getVer().revMinor();
        }
        OS->writeShort(maj);
        OS->writeShort(min);
        plLocation loc = page->getLocation();
        loc.write(OS);
        OS->close();

        std::vector<short> types = rm.getTypes(loc);
      #ifdef WIN32
        CreateDirectory(getOutputDir(filename, page), NULL);
      #else
        mkdir(getOutputDir(filename, page), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
      #endif
        for (i=0; i<types.size(); i++) {
            std::vector<plKey> objs = rm.getKeys(loc, types[i]);
            for (j=0; j<objs.size(); j++) {
                sprintf(strBuf, "%s[%04hX]%s.po", getOutputDir(filename, page),
                                types[i], CleanFileName(objs[j]->getName()).cstr());
                OS->open(strBuf, fmCreate);
                rm.WriteCreatable(OS, objs[j]->getObj());
                OS->close();
            }
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
        plString ageName = S->readStr(S->readShort());
        plString pageName = S->readStr(S->readShort());
        page->setAge(ageName);
        page->setPage(pageName);
        maj = S->readShort();
        min = S->readShort();
        if (maj == 0x7FFF) {
            OS->setVer(PlasmaVer::pvUniversal);
        } else if (maj == -1) {
            if (min == 1)
                OS->setVer(PlasmaVer::pvEoa);
            else if (min == 2)
                OS->setVer(PlasmaVer::pvHex);
        } else if (maj == 70) {
            OS->setVer(PlasmaVer::pvMoul);
        } else if (maj == 63) {
            if (min == 11)
                OS->setVer(PlasmaVer::pvPrime);
            if (min == 12)
                OS->setVer(PlasmaVer::pvPots);
        } else {
            fprintf(stderr, "Error: Invalid Plasma version: %hd.%hd\n", maj, min);
            OS->close();
            S->close();
            delete S;
            delete OS;
            return 1;
        }
        S->setVer(OS->getVer());
        plLocation loc;
        loc.read(S);
        page->setLocation(loc);
        page->setReleaseVersion(0);
        page->setFlags(plPageInfo::kBasicChecksum);
        S->close();

        std::vector<char*> inFiles;
        std::vector<short> inClasses;
        hsFileStream* PS = new hsFileStream();
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
            plKey key = new plKeyData();
            PS->open(inFiles[i], fmRead);
            unsigned int poLen = PS->size();
            void* objBuf = malloc(poLen);
            key->setFileOff(OS->pos());
            key->setObjSize(poLen);
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
        keys.sortKeys(page->getLocation());
        std::vector<short> types = keys.getTypes(page->getLocation());
        //if (types != inClasses)
        //    throw "Wtf, mate?";
        OS->writeInt(types.size());
        for (i=0; i<types.size(); i++) {
            std::vector<plKey> kList = keys.getKeys(page->getLocation(), types[i]);
            OS->writeShort(pdUnifiedTypeMap::MappedToPlasma(types[i], OS->getVer()));
            unsigned int lenPos = OS->pos();
            if (!OS->getVer().isUruSP() && !OS->getVer().isUniversal()) {
                OS->writeInt(0);
                OS->writeByte(0);
            }
            OS->writeInt(kList.size());
            for (j=0; j<kList.size(); j++)
                kList[j]->write(OS);
            if (!OS->getVer().isUruSP() && !OS->getVer().isUniversal()) {
                unsigned int nextPos = OS->pos();
                OS->seek(lenPos);
                OS->writeInt(nextPos - lenPos - 4);
                OS->seek(nextPos);
            }
        }
        if (OS->getVer().isNewPlasma())
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
