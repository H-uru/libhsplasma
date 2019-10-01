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
#include <string_theory/stdio>
#include <string.h>
#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
  #include <dirent.h>
#endif
#include <sys/stat.h>

#ifdef DIRENT_IS_CONST
  #define DIRENT const dirent*
#else
  #define DIRENT dirent*
#endif

static void doHelp()
{
    puts("Usage: PrpPack [-x|-r] filename.prp");
    puts("       PrpPack [-c] filename.prd");
    puts("");
    puts("If you're not handy with a hex editor, turn back now!");
    puts("");
    puts("Options:  -x    Extract a PRP file");
    puts("          -r    (Default) Unpacks and repacks the PRP file.  Temp files");
    puts("                are automatically deleted after the operation is finished.");
    puts("          -c    (Default for .prd files) Create a PRP file from a PRD.");
    puts("");
    puts("PRD Format");
    puts("    [4]   \"PRD\\0\"");
    puts("    [2]   Length of Age Name");
    puts("    [?]   Age Name");
    puts("    [2]   Length of Page Name");
    puts("    [?]   Page Name");
    puts("    [2:2] Plasma Version [Major:Minor] (Use 0 for EOA)");
    puts("    [4]   PageID (actual value)");
    puts("    [2]   Location Flags");
    puts("");
    puts("Objects are read from Age_Page_PRP\\*.po");
    puts("");
}

typedef enum { kCreate, kExtract, kRepack } eDirection;

static ST::string filenameConvert(const ST::string& filename, eDirection dir)
{
    if (dir == kRepack) {
        fputs("Zrax broke me!\n", stderr);
        abort();
    }
    ST::string newName = filename;
    ST_ssize_t dotLoc = newName.find_last('.');
    if (dotLoc < 0) {
        newName += (dir == kCreate) ? ".prp" : ".prd";
    } else if (dir == kCreate) {
        ST::string ext = newName.substr(dotLoc);
        if (ext == ".prd")
            newName.replace(".prd", ".prp");
        else if (ext != ".prp")
            newName += ".prp";
    } else {
        ST::string ext = newName.substr(dotLoc);
        if (ext == ".prp")
            newName.replace(".prp", ".prd");
        else if (ext != ".prd")
            newName += ".prd";
    }
    return newName;
}

static ST::string getOutputDir(const ST::string& filename, plPageInfo* page)
{
    ST::string odir = filename;
    ST_ssize_t sepLoc = odir.find_last(PATHSEP);
    if (sepLoc < 0)
        odir = ST::string();
    else
        odir = odir.left(sepLoc + 1);
    return odir + ST::format("{}_{}_PRP" PATHSEPSTR, page->getAge(), page->getPage());
}

static ST::string CleanFileName(const ST::string& fname)
{
    ST::char_buffer result = fname.to_utf8();
    for (char* bp = result.data(); *bp; bp++) {
        if (*bp == '?' || *bp == '*' || *bp == '<' || *bp == '>' ||
            *bp == '"' || *bp == '|' || *bp < (char)0x20)
            *bp = '_';
        if (*bp == '/' || *bp == '\\' || *bp == ':')
            *bp = '_';
    }
    return result;
}

#ifndef _WIN32
static int selPO(DIRENT de)
{
    return strcmp(strrchr(de->d_name, '.'), ".po") == 0;
}

static int selAll(DIRENT de)
{
    return 1;
}
#endif

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3) {
        doHelp();
        return 0;
    }

    eDirection direction = kRepack;
    ST::string filename = argv[1];
    ST_ssize_t dotLoc = filename.find_last('.');
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
    } else if (dotLoc >= 0 && filename.substr(dotLoc) == ".prd") {
        direction = kCreate;
    }

    plResManager rm;
    hsFileStream S, OS;
    if (!S.open(filename, fmRead)) {
        ST::printf(stderr, "Error opening {} for reading!", filename);
        return 1;
    }
    plPageInfo* page = new plPageInfo();

    //int len;
    short maj = 63, min = 11;
    unsigned int i, j;
    if (direction == kExtract || direction == kRepack) {
        S.close();
        delete page;
        page = rm.ReadPage(filename, true);
        OS.open(filenameConvert(filename, kExtract), fmCreate);
        OS.write(4, "PRD");
        OS.writeShort(page->getAge().size());
        OS.writeStr(page->getAge());
        OS.writeShort(page->getPage().size());
        OS.writeStr(page->getPage());
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
        OS.writeShort(maj);
        OS.writeShort(min);
        plLocation loc = page->getLocation();
        loc.write(&OS);
        OS.close();

        std::vector<short> types = rm.getTypes(loc);
      #ifdef _WIN32
        CreateDirectoryW(getOutputDir(filename, page).to_wchar().data(), nullptr);
      #else
        mkdir(getOutputDir(filename, page).c_str(), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
      #endif
        for (i=0; i<types.size(); i++) {
            std::vector<plKey> objs = rm.getKeys(loc, types[i]);
            for (j=0; j<objs.size(); j++) {
                ST::string po_file = ST::format("{}[{04X}]{}.po", getOutputDir(filename, page),
                                                types[i], CleanFileName(objs[j]->getName()));
                OS.open(po_file, fmCreate);
                OS.setVer(rm.getVer());
                rm.WriteCreatable(&OS, objs[j]->getObj());
                OS.close();
            }
        }
    }
    if (direction == kRepack) {
        filename = filenameConvert(filename, kExtract);
        S.open(filename, fmRead);
    }
    if (direction == kCreate || direction == kRepack) {
        OS.open(filenameConvert(filename, kCreate), fmCreate);
        char sig[4];
        S.read(4, sig);
        if (strncmp(sig, "PRD", sizeof(sig)) != 0) {
            fputs("Error: Invalid input file!\n", stderr);
            OS.close();
            S.close();
            return 1;
        }
        ST::string ageName = S.readStr(S.readShort());
        ST::string pageName = S.readStr(S.readShort());
        page->setAge(ageName);
        page->setPage(pageName);
        maj = S.readShort();
        min = S.readShort();
        if (maj == 0x7FFF) {
            OS.setVer(PlasmaVer::pvUniversal);
        } else if (maj == -1) {
            if (min == 1)
                OS.setVer(PlasmaVer::pvEoa);
            else if (min == 2)
                OS.setVer(PlasmaVer::pvHex);
        } else if (maj == 70) {
            OS.setVer(PlasmaVer::pvMoul);
        } else if (maj == 63) {
            if (min == 11)
                OS.setVer(PlasmaVer::pvPrime);
            if (min == 12)
                OS.setVer(PlasmaVer::pvPots);
        } else {
            ST::printf(stderr, "Error: Invalid Plasma version: {}.{}\n", maj, min);
            OS.close();
            S.close();
            return 1;
        }
        S.setVer(OS.getVer());
        plLocation loc;
        loc.read(&S);
        page->setLocation(loc);
        page->setReleaseVersion(0);
        page->setFlags(plPageInfo::kBasicChecksum);
        S.close();

        std::vector<ST::string> inFiles;
        std::vector<short> inClasses;
        hsFileStream PS;
        PS.setVer(OS.getVer());
      #ifdef _WIN32
        ST::string pattern = ST::format("{}*.po", getOutputDir(filename, page));
        WIN32_FIND_DATAW fd;
        HANDLE fr = FindFirstFileW(pattern.to_wchar().data(), &fd);
        if (fr != INVALID_HANDLE_VALUE) {
            do {
                ST::string po_file = getOutputDir(filename, page) + fd.cFileName;
                inFiles.push_back(po_file);
                PS.open(po_file, fmRead);
                short classType = PS.readShort();
                PS.close();
                bool haveClass = false;
                for (j=0; j<inClasses.size(); j++)
                    if (inClasses[j] == classType) {
                        haveClass = true;
                }
                if (!haveClass)
                    inClasses.push_back(classType);
            } while (FindNextFileW(fr, &fd));
            FindClose(fr);
        }
      #else
        dirent** des;
        unsigned int nEntries = scandir(getOutputDir(filename, page).c_str(), &des, &selPO, &alphasort);
        for (i=0; i<nEntries; i++) {
            ST::string po_file = getOutputDir(filename, page) + des[i]->d_name;
            inFiles.push_back(po_file);
            PS.open(po_file, fmRead);
            short classType = PS.readShort();
            PS.close();
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
        page->write(&OS);
        page->setDataStart(OS.pos());
        plKeyCollector keys;

        for (i=0; i<inFiles.size(); i++) {
            plKey key = new plKeyData();
            PS.open(inFiles[i], fmRead);
            PS.setVer(S.getVer());
            unsigned int poLen = PS.size();
            uint8_t* objBuf = new uint8_t[poLen];
            key->setFileOff(OS.pos());
            key->setObjSize(poLen);
            PS.read(poLen, objBuf);
            OS.write(poLen, objBuf);
            delete[] objBuf;
            PS.seek(2);
            key->readUoid(&PS);
            PS.close();
            keys.add(key);
        }

        page->setIndexStart(OS.pos());
        keys.sortKeys(page->getLocation());
        std::vector<short> types = keys.getTypes(page->getLocation());
        //if (types != inClasses)
        //    throw "Wtf, mate?";
        OS.writeInt(types.size());
        for (i=0; i<types.size(); i++) {
            std::vector<plKey> kList = keys.getKeys(page->getLocation(), types[i]);
            OS.writeShort(pdUnifiedTypeMap::MappedToPlasma(types[i], OS.getVer()));
            unsigned int lenPos = OS.pos();
            if (!OS.getVer().isUruSP() && !OS.getVer().isUniversal()) {
                OS.writeInt(0);
                OS.writeByte(0);
            }
            OS.writeInt(kList.size());
            for (j=0; j<kList.size(); j++)
                kList[j]->write(&OS);
            if (!OS.getVer().isUruSP() && !OS.getVer().isUniversal()) {
                unsigned int nextPos = OS.pos();
                OS.seek(lenPos);
                OS.writeInt(nextPos - lenPos - 4);
                OS.seek(nextPos);
            }
        }
        if (OS.getVer().isNewPlasma())
            page->setChecksum(OS.pos());
        else
            page->setChecksum(OS.pos() - page->getDataStart());
        page->writeSums(&OS);
        OS.close();
    }

    // Delete temp files with the repack option
    if (direction == kRepack) {
      #ifdef _WIN32
        ST::string pattern = ST::format("{}*.po", getOutputDir(filename, page));
        WIN32_FIND_DATAW rfd;
        HANDLE rfr = FindFirstFileW(pattern.to_wchar().data(), &rfd);
        if (rfr) {
            do {
                ST::string po_file = getOutputDir(filename, page) + rfd.cFileName;
                DeleteFileW(po_file.to_wchar().data());
            } while (FindNextFileW(rfr, &rfd));
            FindClose(rfr);
        }
        RemoveDirectoryW(getOutputDir(filename, page).to_wchar().data());
        DeleteFileW(filename.to_wchar().data());
      #else
        dirent** rdes;
        unsigned int nEntries = scandir(getOutputDir(filename, page).c_str(), &rdes, &selAll, &alphasort);
        for (i=0; i<nEntries; i++) {
            ST::string po_file = getOutputDir(filename, page) + rdes[i]->d_name;
            unlink(po_file.c_str());
        }
        rmdir(getOutputDir(filename, page).c_str());
        unlink(filename.c_str());
      #endif
    }

    return 0;
}
