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

#include "Stream/plEncryptedStream.h"
#include "Stream/hsRAMStream.h"
#include "Debug/plDebug.h"
#include <list>
#include <ctime>
#include <cstring>

static void doHelp()
{
    puts("Usage: PyPack -x filename.pak [-o outdir]");
    puts("       PyPack -c [options] [source.pyc ...] filename.pak");
    puts("       PyPack -a [options] [source.pyc ...] filename.pak");
    puts("");
    puts("Actions:  -x    Extract a PAK file");
    puts("          -c    Create a PAK file and add the .pyc files to it");
    puts("          -a    Add .pyc files to an existing PAK file");
    puts("          -o    Change the output path (for extracting only)");
    puts("");
    puts("Options:  -uru  Use Prime/PotS mode");
    puts("          -live Use MOUL mode (the encryption key should follow)");
    puts("          -eoa  Use Eoa/Hex Isle mode");
    puts("          -n    Don't use encryption");
    puts("");
}

enum Action { kInvalid, kCreate, kExtract, kAdd };

enum PycHeader
{
    kPyc22 = 0x0A0DED2D,
    kPyc23 = 0x0A0DF23B,
};

struct PycObject
{
    ST::string fFilename;
    uint32_t fOffset, fSize;
    uint8_t* fData;
};

static bool parseKey(const char* buf, unsigned int& val)
{
    char kMap[256];
    memset(kMap, -1, 256);
    int i;
    for (i='0'; i<='9'; i++)
        kMap[i] = i - '0';
    for (i='A'; i<='F'; i++)
        kMap[i] = (i - 'A') + 10;
    for (i='a'; i<='f'; i++)
        kMap[i] = (i - 'a') + 10;
    for (i=0; i<8; i++) {
        if (kMap[(size_t)buf[i]] == -1) {
            fprintf(stderr, "Error: Invalid character in key string\n");
            return false;
        }
    }
#ifdef LEKEY
    val = (kMap[(size_t)buf[0]] * 0x00000010) + (kMap[(size_t)buf[1]] * 0x00000001) +
          (kMap[(size_t)buf[2]] * 0x00001000) + (kMap[(size_t)buf[3]] * 0x00000100) +
          (kMap[(size_t)buf[4]] * 0x00100000) + (kMap[(size_t)buf[5]] * 0x00010000) +
          (kMap[(size_t)buf[6]] * 0x10000000) + (kMap[(size_t)buf[7]] * 0x01000000);
#else
    val = (kMap[(size_t)buf[0]] * 0x10000000) + (kMap[(size_t)buf[1]] * 0x01000000) +
          (kMap[(size_t)buf[2]] * 0x00100000) + (kMap[(size_t)buf[3]] * 0x00010000) +
          (kMap[(size_t)buf[4]] * 0x00001000) + (kMap[(size_t)buf[5]] * 0x00000100) +
          (kMap[(size_t)buf[6]] * 0x00000010) + (kMap[(size_t)buf[7]] * 0x00000001);
#endif
    return true;
}

int main(int argc, char* argv[])
{
    Action action = kInvalid;
    ST::string pakfile, outdir;
    std::list<ST::string> infiles;
    plEncryptedStream::EncryptionType eType = plEncryptedStream::kEncAuto;
    unsigned int uruKey[4];
    memcpy(uruKey, plEncryptedStream::DefaultKey(), sizeof(uruKey));

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "-x") == 0) {
            action = kExtract;
        } else if (strcmp(argv[i], "-c") == 0) {
            action = kCreate;
        } else if (strcmp(argv[i], "-a") == 0) {
            action = kAdd;
        } else if (strcmp(argv[i], "-o") == 0) {
            outdir = argv[++i];
        } else if (strcmp(argv[i], "-?") == 0 || strcmp(argv[i], "--help") == 0) {
            doHelp();
            return 0;
        } else if (strcmp(argv[i], "-n") == 0) {
            eType = plEncryptedStream::kEncNone;
        } else if (strcmp(argv[i], "-uru") == 0) {
            eType = plEncryptedStream::kEncXtea;
        } else if (strcmp(argv[i], "-live") == 0) {
            eType = plEncryptedStream::kEncDroid;
            i++;
            if (strlen(argv[i]) != 32) {
                fputs("Error:  key must be exactly 32 Hex characters, in little-endian byte order.\n", stderr);
                fputs("Example:  To use the key { 0x01234567, 0x89ABCDEF, 0x01234567, 0x89ABCDEF } :\n", stderr);
                fputs("    PyPack -c -live 0123456789ABCDEF0123456789ABCDEF Filename.pyc Filename.pak\n", stderr);
                return 1;
            }
            for (size_t j=0; j<4; j++) {
                if (!parseKey(&argv[i][j*8], uruKey[j]))
                    return 1;
            }
        } else if (strcmp(argv[i], "-eoa") == 0) {
            eType = plEncryptedStream::kEncAES;
        } else {
            if (!pakfile.empty())
                infiles.push_back(pakfile);
            pakfile = argv[i];
        }
    }

    if (pakfile.empty()) {
        doHelp();
        return 1;
    }

    std::vector<PycObject> pakObjects;
    if (action == kCreate) {
        uint32_t offs = 0, baseOffs = 4;
        pakObjects.resize(infiles.size());
        std::list<ST::string>::iterator it = infiles.begin();
        for (size_t i=0; it!=infiles.end(); i++, it++) {
            ST::string name = *it;
            if (name.after_last('.').to_lower() != "pyc") {
                plDebug::Error("Unsupported format: {}", name);
                return 1;
            }
            if (name.find(PATHSEP) >= 0)
                name = name.after_last(PATHSEP).before_last('.');
            else
                name = name.before_last('.');
            pakObjects[i].fFilename = name + ".py";
            hsFileStream S;
            if (!S.open(*it, fmRead)) {
                plDebug::Error("Cannot open file {}", *it);
                return 1;
            }
            pakObjects[i].fSize = S.size() - 8;
            pakObjects[i].fData = new uint8_t[pakObjects[i].fSize];
            S.seek(8);
            S.read(pakObjects[i].fSize, pakObjects[i].fData);
            pakObjects[i].fOffset = offs;
            offs += pakObjects[i].fSize + 4;
            baseOffs += pakObjects[i].fFilename.size() + 6;
        }

        PlasmaVer ver = PlasmaVer::pvPrime;
        if (eType == plEncryptedStream::kEncAuto)
            eType = plEncryptedStream::kEncXtea;
        else if (eType == plEncryptedStream::kEncAES)
            ver = PlasmaVer::pvEoa;
        hsStream* OS;
        if (eType == plEncryptedStream::kEncNone) {
            OS = new hsFileStream(ver);
            ((hsFileStream*)OS)->open(pakfile, fmCreate);
        } else {
            OS = new plEncryptedStream(ver);
            ((plEncryptedStream*)OS)->open(pakfile, fmCreate, eType);
            ((plEncryptedStream*)OS)->setKey(uruKey);
        }
        OS->writeInt(pakObjects.size());
        for (size_t i=0; i<pakObjects.size(); i++) {
            OS->writeSafeStr(pakObjects[i].fFilename);
            OS->writeInt(baseOffs + pakObjects[i].fOffset);
        }
        for (size_t i=0; i<pakObjects.size(); i++) {
            OS->writeInt(pakObjects[i].fSize);
            OS->write(pakObjects[i].fSize, pakObjects[i].fData);
        }
        delete OS;
    } else if (action == kAdd) {
        hsStream* IS;
        uint32_t offs = 0, baseOffs = 4;
        if (eType == plEncryptedStream::kEncNone || !plEncryptedStream::IsFileEncrypted(pakfile)) {
            IS = new hsFileStream(PlasmaVer::pvPrime);
            if (!((hsFileStream*)IS)->open(pakfile, fmRead)) {
                plDebug::Error("Cannot open file {}", pakfile);
                return 1;
            }
            eType = plEncryptedStream::kEncNone;
        } else {
            IS = new plEncryptedStream(PlasmaVer::pvPrime);
            if (!((plEncryptedStream*)IS)->open(pakfile, fmRead, eType)) {
                plDebug::Error("Cannot open file {}", pakfile);
                return 1;
            }
            ((plEncryptedStream*)IS)->setKey(uruKey);
            eType = ((plEncryptedStream*)IS)->getEncType();

            if (eType == plEncryptedStream::kEncAES)
                IS->setVer(PlasmaVer::pvEoa);
        }
        PlasmaVer oldVer = IS->getVer();

        size_t oldObjCount = IS->readInt();
        pakObjects.resize(oldObjCount + infiles.size());
        for (size_t i=0; i<oldObjCount; i++) {
            pakObjects[i].fFilename = IS->readSafeStr();
            pakObjects[i].fOffset = IS->readInt();
            baseOffs += pakObjects[i].fFilename.size() + 6;
        }
        uint32_t oldBase = IS->pos();
        for (size_t i=0; i<oldObjCount; i++) {
            IS->seek(pakObjects[i].fOffset);
            pakObjects[i].fSize = IS->readInt();
            if (IS->pos() + pakObjects[i].fSize > IS->size()) {
                plDebug::Warning("Warning: Truncating last entry");
                pakObjects[i].fSize = IS->size() - IS->pos();
            }
            pakObjects[i].fData = new uint8_t[pakObjects[i].fSize];
            IS->read(pakObjects[i].fSize, pakObjects[i].fData);
            pakObjects[i].fOffset -= oldBase;
            offs += pakObjects[i].fSize + 4;
        }
        delete IS;

        std::list<ST::string>::iterator it = infiles.begin();;
        for (size_t i=oldObjCount; it!=infiles.end(); i++, it++) {
            ST::string name = *it;
            if (name.after_last('.').to_lower() != "pyc") {
                plDebug::Error("Unsupported format: {}", name);
                return 1;
            }
            if (name.find(PATHSEP) >= 0)
                name = name.after_last(PATHSEP).before_last('.');
            else
                name = name.before_last('.');
            pakObjects[i].fFilename = name + ".py";
            hsFileStream S;
            if (!S.open(*it, fmRead)) {
                plDebug::Error("Cannot open file {}", *it);
                return 1;
            }
            pakObjects[i].fSize = S.size() - 8;
            pakObjects[i].fData = new uint8_t[pakObjects[i].fSize];
            S.seek(8);
            S.read(pakObjects[i].fSize, pakObjects[i].fData);
            pakObjects[i].fOffset = offs;
            offs += pakObjects[i].fSize + 4;
            baseOffs += pakObjects[i].fFilename.size() + 6;
        }

        hsStream* OS;
        if (eType == plEncryptedStream::kEncNone) {
            OS = new hsFileStream(oldVer);
            ((hsFileStream*)OS)->open(pakfile, fmCreate);
        } else {
            OS = new plEncryptedStream(oldVer);
            ((plEncryptedStream*)OS)->open(pakfile, fmCreate, eType);
            ((plEncryptedStream*)OS)->setKey(uruKey);
        }
        OS->writeInt(pakObjects.size());
        for (size_t i=0; i<pakObjects.size(); i++) {
            OS->writeSafeStr(pakObjects[i].fFilename);
            OS->writeInt(baseOffs + pakObjects[i].fOffset);
        }
        for (size_t i=0; i<pakObjects.size(); i++) {
            OS->writeInt(pakObjects[i].fSize);
            OS->write(pakObjects[i].fSize, pakObjects[i].fData);
        }
        delete OS;
    } else if (action == kExtract) {
        hsStream* IS;
        if (eType == plEncryptedStream::kEncNone || !plEncryptedStream::IsFileEncrypted(pakfile)) {
            IS = new hsFileStream(PlasmaVer::pvPrime);
            if (!((hsFileStream*)IS)->open(pakfile, fmRead)) {
                plDebug::Error("Cannot open file {}", pakfile);
                return 1;
            }
            eType = plEncryptedStream::kEncNone;
        } else {
            IS = new plEncryptedStream(PlasmaVer::pvPrime);
            if (!((plEncryptedStream*)IS)->open(pakfile, fmRead, eType)) {
                plDebug::Error("Cannot open file {}", pakfile);
                return 1;
            }
            ((plEncryptedStream*)IS)->setKey(uruKey);
            eType = ((plEncryptedStream*)IS)->getEncType();

            if (eType == plEncryptedStream::kEncAES)
                IS->setVer(PlasmaVer::pvEoa);
        }

        pakObjects.resize(IS->readInt());
        for (size_t i=0; i<pakObjects.size(); i++) {
            pakObjects[i].fFilename = IS->readSafeStr();
            pakObjects[i].fOffset = IS->readInt();
        }

        for (size_t i=0; i<pakObjects.size(); i++) {
            if (pakObjects[i].fOffset != IS->pos())
                IS->seek(pakObjects[i].fOffset);
            pakObjects[i].fSize = IS->readInt();
            if (IS->pos() + pakObjects[i].fSize > IS->size()) {
                plDebug::Warning("Warning: Truncating last entry");
                pakObjects[i].fSize = IS->size() - IS->pos();
            }
            pakObjects[i].fData = new uint8_t[pakObjects[i].fSize];
            IS->read(pakObjects[i].fSize, pakObjects[i].fData);

            hsFileStream S;
            if (!outdir.empty())
                outdir += PATHSEPSTR;
            S.open(outdir + pakObjects[i].fFilename + "c", fmCreate);
            S.writeInt((eType == plEncryptedStream::kEncXtea || eType == plEncryptedStream::kEncNone)
                        ? kPyc22 : kPyc23);
            time_t ts = time(nullptr);
            S.writeInt(ts);
            S.write(pakObjects[i].fSize, pakObjects[i].fData);
        }
        delete IS;
    } else {
        doHelp();
        return 1;
    }

    for (size_t i=0; i<pakObjects.size(); i++)
        delete[] pakObjects[i].fData;

    return 0;
}
