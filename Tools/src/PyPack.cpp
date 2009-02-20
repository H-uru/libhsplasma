#include "Stream/plEncryptedStream.h"
#include "Stream/hsRAMStream.h"
#include "Util/hsTArray.hpp"
#include "Debug/plDebug.h"
#include <list>
#include <ctime>

void doHelp() {
    printf("Usage: PyPack -x filename.pak [-o outdir]\n");
    printf("       PyPack -c [options] [source.pyc ...] filename.pak\n");
    printf("       PyPack -a [options] [source.pyc ...] filename.pak\n\n");
    printf("Actions:  -x    Extract a PAK file\n");
    printf("          -c    Create a PAK file and add the .pyc files to it\n");
    printf("          -a    Add .pyc files to an existing PAK file\n");
    printf("          -o    Change the output path (for extracting only)\n\n");
    printf("Options:  -uru  Use Prime/PotS mode\n");
    printf("          -live Use MOUL mode (the encryption key should follow)\n");
    printf("          -eoa  Use Eoa/Hex Isle mode\n");
    printf("          -n    Don't use encryption\n\n");
}

enum Action { kInvalid, kCreate, kExtract, kAdd };

enum PycHeader {
    kPyc22 = 0x0A0DED2D,
    kPyc23 = 0x0A0DF23B,
};

struct PycObject {
    plString fFilename;
    hsUint32 fOffset, fSize;
    hsUbyte* fData;
};

bool parseKey(const char* buf, unsigned int& val) {
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

int main(int argc, char** argv) {
    Action action = kInvalid;
    plString pakfile, outdir;
    std::list<plString> infiles;
    plEncryptedStream::EncryptionType eType = plEncryptedStream::kEncAuto;
    unsigned int uruKey[4];
    
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
                fprintf(stderr, "Error:  key must be exactly 32 Hex characters, in little-endian byte order.\n");
                fprintf(stderr, "Example:  To use the key { 0x01234567, 0x89ABCDEF, 0x01234567, 0x89ABCDEF } :\n"
                                "    PyPack -c -live 0123456789ABCDEF0123456789ABCDEF Filename.pyc Filename.pak\n");
                return 1;
            }
            for (size_t j=0; j<4; j++)
                if (!parseKey(&argv[i][j*8], uruKey[j]))
                    return 1;
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

    hsTArray<PycObject> pakObjects;
    if (action == kCreate) {
        hsUint32 offs = 0, baseOffs = 4;
        pakObjects.setSize(infiles.size());
        std::list<plString>::iterator it = infiles.begin();;
        for (size_t i=0; it!=infiles.end(); i++, it++) {
            plString name = *it;
            if (name.afterLast('.').toLower() != "pyc") {
                plDebug::Error("Unsupported format: %s\n", name.cstr());
                return 1;
            }
            if (name.find(PATHSEP) >= 0)
                name = name.afterLast(PATHSEP).beforeLast('.');
            else
                name = name.beforeLast('.');
            pakObjects[i].fFilename = name + ".py";
            hsFileStream FS;
            if (!FS.open(*it, fmRead)) {
                plDebug::Error("Cannot open file %s\n", (*it).cstr());
                return 1;
            }
            pakObjects[i].fSize = FS.size() - 8;
            pakObjects[i].fData = new hsUbyte[pakObjects[i].fSize];
            FS.seek(8);
            FS.read(pakObjects[i].fSize, pakObjects[i].fData);
            pakObjects[i].fOffset = offs;
            offs += pakObjects[i].fSize + 4;
            baseOffs += pakObjects[i].fFilename.len() + 6;
        }

        if (eType == plEncryptedStream::kEncAuto)
            eType = plEncryptedStream::kEncXtea;
        hsStream* OS;
        if (eType == plEncryptedStream::kEncNone) {
            OS = new hsFileStream();
            ((hsFileStream*)OS)->open(pakfile, fmCreate);
        } else {
            OS = new plEncryptedStream();
            ((plEncryptedStream*)OS)->open(pakfile, fmCreate, eType);
        }
        OS->writeInt(pakObjects.getSize());
        for (size_t i=0; i<pakObjects.getSize(); i++) {
            OS->writeSafeStr(pakObjects[i].fFilename);
            OS->writeInt(baseOffs + pakObjects[i].fOffset);
        }
        for (size_t i=0; i<pakObjects.getSize(); i++) {
            OS->writeInt(pakObjects[i].fSize);
            OS->write(pakObjects[i].fSize, pakObjects[i].fData);
        }
        delete OS;
    } else if (action == kAdd) {
        hsStream* IS;
        hsUint32 offs = 0, baseOffs = 4;
        if (eType == plEncryptedStream::kEncNone || !plEncryptedStream::IsFileEncrypted(pakfile)) {
            IS = new hsFileStream();
            if (!((hsFileStream*)IS)->open(pakfile, fmRead)) {
                plDebug::Error("Cannot open file %s\n", pakfile.cstr());
                return 1;
            }
            eType = plEncryptedStream::kEncNone;
        } else {
            IS = new hsRAMStream();
            plEncryptedStream ES;
            if (!ES.open(pakfile, fmRead, eType)) {
                plDebug::Error("Cannot open file %s\n", pakfile.cstr());
                return 1;
            }
            size_t datLen = ES.size();
            hsUbyte* dat = new hsUbyte[datLen];
            ES.read(datLen, dat);
            ((hsRAMStream*)IS)->copyFrom(dat, datLen);
            delete[] dat;
            eType = ES.getEncType();
        }
        size_t oldObjCount = IS->readInt();
        pakObjects.setSize(oldObjCount + infiles.size());
        for (size_t i=0; i<oldObjCount; i++) {
            pakObjects[i].fFilename = IS->readSafeStr();
            pakObjects[i].fOffset = IS->readInt();
            baseOffs += pakObjects[i].fFilename.len() + 6;
        }
        hsUint32 oldBase = IS->pos();
        for (size_t i=0; i<oldObjCount; i++) {
            IS->seek(pakObjects[i].fOffset);
            pakObjects[i].fSize = IS->readInt();
            pakObjects[i].fData = new hsUbyte[pakObjects[i].fSize];
            IS->read(pakObjects[i].fSize, pakObjects[i].fData);
            pakObjects[i].fOffset -= oldBase;
            offs += pakObjects[i].fSize + 4;
        }
        delete IS;

        std::list<plString>::iterator it = infiles.begin();;
        for (size_t i=oldObjCount; it!=infiles.end(); i++, it++) {
            plString name = *it;
            if (name.afterLast('.').toLower() != "pyc") {
                plDebug::Error("Unsupported format: %s\n", name.cstr());
                return 1;
            }
            if (name.find(PATHSEP) >= 0)
                name = name.afterLast(PATHSEP).beforeLast('.');
            else
                name = name.beforeLast('.');
            pakObjects[i].fFilename = name + ".py";
            hsFileStream FS;
            if (!FS.open(*it, fmRead)) {
                plDebug::Error("Cannot open file %s\n", (*it).cstr());
                return 1;
            }
            pakObjects[i].fSize = FS.size() - 8;
            pakObjects[i].fData = new hsUbyte[pakObjects[i].fSize];
            FS.seek(8);
            FS.read(pakObjects[i].fSize, pakObjects[i].fData);
            pakObjects[i].fOffset = offs;
            offs += pakObjects[i].fSize + 4;
            baseOffs += pakObjects[i].fFilename.len() + 6;
        }
        
        hsStream* OS;
        if (eType == plEncryptedStream::kEncNone) {
            OS = new hsFileStream();
            ((hsFileStream*)OS)->open(pakfile, fmCreate);
        } else {
            OS = new plEncryptedStream();
            ((plEncryptedStream*)OS)->open(pakfile, fmCreate, eType);
        }
        OS->writeInt(pakObjects.getSize());
        for (size_t i=0; i<pakObjects.getSize(); i++) {
            OS->writeSafeStr(pakObjects[i].fFilename);
            OS->writeInt(baseOffs + pakObjects[i].fOffset);
        }
        for (size_t i=0; i<pakObjects.getSize(); i++) {
            OS->writeInt(pakObjects[i].fSize);
            OS->write(pakObjects[i].fSize, pakObjects[i].fData);
        }
        delete OS;
    } else if (action == kExtract) {
        hsStream* IS;
        if (eType == plEncryptedStream::kEncNone || !plEncryptedStream::IsFileEncrypted(pakfile)) {
            IS = new hsFileStream();
            if (!((hsFileStream*)IS)->open(pakfile, fmRead)) {
                plDebug::Error("Cannot open file %s\n", pakfile.cstr());
                return 1;
            }
            eType = plEncryptedStream::kEncNone;
        } else {
            IS = new hsRAMStream();
            plEncryptedStream ES;
            if (!ES.open(pakfile, fmRead, eType)) {
                plDebug::Error("Cannot open file %s\n", pakfile.cstr());
                return 1;
            }
            size_t datLen = ES.size();
            hsUbyte* dat = new hsUbyte[datLen];
            ES.read(datLen, dat);
            ((hsRAMStream*)IS)->copyFrom(dat, datLen);
            delete[] dat;
            eType = ES.getEncType();
        }
        pakObjects.setSize(IS->readInt());
        for (size_t i=0; i<pakObjects.getSize(); i++) {
            pakObjects[i].fFilename = IS->readSafeStr();
            pakObjects[i].fOffset = IS->readInt();
        }
        for (size_t i=0; i<pakObjects.getSize(); i++) {
            IS->seek(pakObjects[i].fOffset);
            pakObjects[i].fSize = IS->readInt();
            pakObjects[i].fData = new hsUbyte[pakObjects[i].fSize];
            IS->read(pakObjects[i].fSize, pakObjects[i].fData);

            hsFileStream FS;
            FS.open(outdir + PATHSEP + pakObjects[i].fFilename + 'c', fmCreate);
            FS.writeInt((eType == plEncryptedStream::kEncXtea || eType == plEncryptedStream::kEncNone)
                        ? kPyc22 : kPyc23);
            time_t ts = time(NULL);
            FS.writeInt(ts);
            FS.write(pakObjects[i].fSize, pakObjects[i].fData);
        }
        delete IS;
    } else {
        doHelp();
        return 1;
    }

    for (size_t i=0; i<pakObjects.getSize(); i++)
        delete[] pakObjects[i].fData;

    return 0;
}
