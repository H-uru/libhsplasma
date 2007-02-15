#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CoreLib/plEncryptedStream.h"

typedef enum EncrMethod { emNone, emDecrypt, emTea, emAes, emDroid };

void doHelp() {
    printf("Plasma File Encryption/Decryption Utility 1.0\n"
           "by Michael Hansen\n\n");
    printf("Usage:  PlasmaCrypt decrypt [options] Filename [...]\n"
           "        PlasmaCrypt encrypt method [options] Filename [...]\n\n");
    printf("Methods:  uru     xTea encryption\n"
           "          xtea    \n"
           "          eoa     AES encryption\n"
           "          aes     \n"
           "          live    NTD encryption\n"
           "          droid   \n\n");
    printf("Options:  -replace  Replace the original file instead of creating a new one\n"
           "          -key      Specify the Key to use for decryption, instead of the\n"
           "                    default.  For droid encryption, this must always be\n"
           "                    present.  This should be entered as 32 hex digits, in\n"
           "                    network (big-endian) byte order.\n"
           "          -help     Displays this help screen\n\n");
    printf("Input encryption type is automatically determined.\n\n");
}

const char* getNextOutFile(char* filename) {
    char* fnBuf = (char*)malloc(strlen(filename) + 5);
    sprintf(fnBuf, "%s.out", filename);
    int i = 0;
    while (fopen(fnBuf, "r") != NULL)
        sprintf(fnBuf, "%s.out%d", filename, ++i);
    return fnBuf;
}

unsigned int parseKey(char* buf) {
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
        if (kMap[buf[i]] == -1) {
            printf("Error: Invalid character in key string\n");
            return 0;
        }
    }
    return (kMap[buf[0]] * 0x10000000) + (kMap[buf[1]] * 0x01000000) +
           (kMap[buf[2]] * 0x00100000) + (kMap[buf[3]] * 0x00010000) +
           (kMap[buf[4]] * 0x00001000) + (kMap[buf[5]] * 0x00000100) +
           (kMap[buf[6]] * 0x00000010) + (kMap[buf[7]] * 0x00000001);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        doHelp();
        return 0;
    }

    EncrMethod method = emNone;
    char** realargv; int realargc;
    bool doReplace = false;

    if (strcmp(argv[1], "decrypt") == 0) {
        method = emDecrypt;
        realargv = &argv[2];
        realargc = argc - 2;
    } else if (strcmp(argv[1], "encrypt") == 0) {
        if (argc < 3) {
            doHelp();
            return 0;
        }
        if (strcmp(argv[2], "uru") == 0 || strcmp(argv[2], "xtea") == 0)
            method = emTea;
        else if (strcmp(argv[2], "eoa") == 0 || strcmp(argv[2], "aes") == 0)
            method = emAes;
        else if (strcmp(argv[2], "live") == 0 || strcmp(argv[2], "droid") == 0)
            method = emDroid;
        else {
            printf("Unsupported encryption method.\nSee -help for supported "
                   "encryption methods.\n");
            return 0;
        }
        realargv = &argv[3];
        realargc = argc - 3;
    } else {
        doHelp();
        return 0;
    }

    int nFiles = 0;
    unsigned int droidKey[4];
    bool haveKey = false;
    for (int i=0; i<realargc; i++) {
        if (realargv[i][0] == '-') {
            if (strcmp(realargv[i], "-help") == 0)
                doHelp();
            else if (strcmp(realargv[i], "-replace") == 0)
                doReplace = true;
            else if (strcmp(realargv[i], "-key") == 0) {
                i++;
                if (strlen(realargv[i]) != 32) {
                    printf("Error:  key must be exactly 32 Hex characters, in network byte order.\n");
                    printf("Example:  To use the key { 0x01234567, 0x89ABCDEF, 0x01234567, 0x89ABCDEF } :\n"
                           "    DroidCrypt encrypt droid -key 0123456789ABCDEF0123456789ABCDEF Filename.sdl\n");
                    return 0;
                }
                for (int j=0; j<4; j++)
                    droidKey[j] = parseKey(&realargv[i][j*8]);
                haveKey = true;
            } else {
                printf("Error: Unrecognized option %s\n", realargv[i]);
                printf("See -help for list of accepted options\n");
                return 0;
            }
        } else if (method == emDecrypt) {
            plEncryptedStream SF;
            if (method == emDroid && !haveKey) {
                printf("Error: Droid key not set!\n");
                return 0;
            }
            if (haveKey) SF.setKey(droidKey);
            try {
                SF.open(realargv[i], fmRead);
            } catch (const char* e) {
                printf("Error opening %s: %s\n", realargv[i], e);
                continue;
            } catch (...) {
                printf("Undefined error opening %s\n", realargv[i]);
                continue;
            }
            unsigned int dataSize = SF.size();
            char* buf = (char*)malloc(dataSize);
            SF.read(dataSize, buf);
            SF.close();

            hsStream DF;
            if (doReplace) DF.open(realargv[i], fmCreate);
            else DF.open(getNextOutFile(realargv[i]), fmCreate);
            DF.write(dataSize, buf);
            DF.close();
            free(buf);
            nFiles++;
        } else {
            hsStream SF;
            try {
                SF.open(realargv[i], fmRead);
            } catch (const char* e) {
                printf("Error opening %s: %s\n", realargv[i], e);
                continue;
            } catch (...) {
                printf("Undefined error opening %s\n", realargv[i]);
                continue;
            }
            unsigned int dataSize = SF.size();
            char* buf = (char*)malloc(dataSize);
            SF.read(dataSize, buf);
            SF.close();

            plEncryptedStream DF;
            PlasmaVer dv = pvUnknown;
            if (method == emTea) dv = pvPrime;
            if (method == emAes) dv = pvEoa;
            if (method == emDroid) dv = pvLive;
            DF.setVer(dv);
            if (method == emDroid && !haveKey) {
                printf("Error: Droid key not set!\n");
                return 0;
            }
            if (haveKey) DF.setKey(droidKey);
            if (doReplace) DF.open(realargv[i], fmCreate);
            else DF.open(getNextOutFile(realargv[i]), fmCreate);
            DF.write(dataSize, buf);
            DF.close();
            free(buf);
            nFiles++;
        }
    }

    if (nFiles > 0)
        printf("Successfully %s %d files!\n",
               (method == emDecrypt ? "decrypted" : "encrypted"), nFiles);
    return 0;
}

