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

#include <cstring>
#include <cstdlib>
#include <exception>
#include <vector>
#include <memory>
#include <string_theory/format>
#include <string_theory/stdio>
#include "Stream/plEncryptedStream.h"

enum EncrMethod { emNone, emDecrypt, emTea, emAes, emDroid };

static void doHelp()
{
    puts("Plasma File Encryption/Decryption Utility 1.0");
    puts("by Michael Hansen");
    puts("");
    puts("Usage:  PlasmaCrypt action [options] Filename [...]");
    puts("");
    puts("Actions:  decrypt Decrypt the source file(s)");
    puts("          xtea    Encrypt with xTea (Uru) encryption");
    puts("          aes     Encrypt with AES (Myst V) encryption");
    puts("          droid   Encrypt with NTD (Uru Live) encryption");
    puts("");
    puts("Note: Decryption method is automatically determined.");
    puts("");
    puts("Options:  -noreplace  Store output in a different file instead of replacing");
    puts("                      the original.");
    puts("          -key        Specify the Key to use for decryption, instead of the");
    puts("                      default.  For droid encryption, this must always be");
    puts("                      present.  This should be entered as 32 hex digits, in");
    puts("                      network (big-endian) byte order.");
    puts("                      NOTE:  This option is not available for AES encryption.");
    puts("          -verbose    Give more output chatter.");
    puts("          -quiet      Give less output chatter.");
    puts("          -help       Displays this help screen");
    puts("");
}

static ST::string getNextOutFile(const ST::string& filename)
{
    ST::string fn = ST::format("{}.out", filename);
    int i = 0;
    FILE* outFile;
    while ((outFile = fopen(fn.c_str(), "r")) != nullptr) {
        fclose(outFile);
        fn = ST::format("{}.out{}", filename, ++i);
    }
    return fn;
}

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
    if (argc < 2) {
        doHelp();
        return 1;
    }

    EncrMethod method = emNone;
    bool doReplace = true;

    if (strcmp(argv[1], "decrypt") == 0)
        method = emDecrypt;
    else if (strcmp(argv[1], "xtea") == 0)
        method = emTea;
    else if (strcmp(argv[1], "aes") == 0)
        method = emAes;
    else if (strcmp(argv[1], "droid") == 0)
        method = emDroid;
    else if (strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "--help") == 0) {
        doHelp();
        return 0;
    } else {
        fputs("Unrecognized action.\n", stderr);
        fputs("See -help for available options and encryption methods.\n", stderr);
        return 1;
    }

    unsigned int uruKey[4];
    bool haveKey = false;
    int verbosity = 0;
    std::vector<ST::string> files;
    for (int i=2; i<argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-')
                argv[i]++;
            if (strcmp(argv[i], "-help") == 0) {
                doHelp();
                return 0;
            } else if (strcmp(argv[i], "-noreplace") == 0)
                doReplace = false;
            else if (strcmp(argv[i], "-verbose") == 0)
                verbosity++;
            else if (strcmp(argv[i], "-quiet") == 0)
                verbosity--;
            else if (strcmp(argv[i], "-key") == 0) {
                i++;
                if (strlen(argv[i]) != 32) {
                    fputs("Error:  key must be exactly 32 Hex characters, in network byte order.\n", stderr);
                    fputs("Example:  To use the key { 0x01234567, 0x89ABCDEF, 0x01234567, 0x89ABCDEF } :\n", stderr);
                    fputs("    PlasmaCrypt encrypt droid -key 0123456789ABCDEF0123456789ABCDEF Filename.sdl\n", stderr);
                    return 1;
                }
                for (size_t j=0; j<4; j++) {
                    if (!parseKey(&argv[i][j*8], uruKey[j]))
                        return 1;
                }
                haveKey = true;
            } else {
                ST::printf(stderr, "Error: Unrecognized option {}\n", argv[i]);
                fputs("See -help for list of accepted options\n", stderr);
                return 1;
            }
        } else {
            files.push_back(argv[i]);
        }
    }

    unsigned int nFiles = 0;
    ST::string outFileName;
    for (size_t i=0; i<files.size(); i++) {
        if (method == emDecrypt) {
            plEncryptedStream SF;
            if (haveKey)
                SF.setKey(uruKey);
            try {
                if (!plEncryptedStream::IsFileEncrypted(files[i])) {
                    if (verbosity >= 0)
                        ST::printf("File {} not encrypted -- skipping!\n", files[i]);
                    continue;
                } else {
                    SF.open(files[i], fmRead, plEncryptedStream::kEncAuto);
                    if (SF.getEncType() == plEncryptedStream::kEncDroid && !haveKey) {
                        fputs("Error: Droid key not set!\n", stderr);
                        SF.close();
                        return 1;
                    }
                    if (SF.getEncType() == plEncryptedStream::kEncAES && haveKey && verbosity >= 0)
                        fputs("Warning: Ignoring key for AES decryption\n", stderr);
                }
            } catch (std::exception& e) {
                if (verbosity >= 0)
                    ST::printf(stderr, "Error opening {}: {}\n", files[i], e.what());
                continue;
            } catch (...) {
                if (verbosity >= 0)
                    ST::printf(stderr, "Undefined error opening {}\n", files[i]);
                continue;
            }
            uint32_t dataSize = SF.size();
            std::unique_ptr<uint8_t[]> buf(new uint8_t[dataSize]);
            SF.read(dataSize, buf.get());
            SF.close();

            hsFileStream DF;
            outFileName = doReplace ? files[i] : getNextOutFile(files[i]);
            if (verbosity >= 1)
                ST::printf("Decrypting {}...\n", outFileName);
            DF.open(outFileName, fmCreate);
            DF.write(dataSize, buf.get());
            DF.close();
            nFiles++;
        } else {
            hsFileStream SF;
            try {
                if (plEncryptedStream::IsFileEncrypted(files[i])) {
                    if (verbosity >= 0)
                        ST::printf("File {} already encrypted -- skipping!\n", files[i]);
                    continue;
                } else {
                    SF.open(files[i], fmRead);
                }
            } catch (std::exception& e) {
                if (verbosity >= 0)
                    ST::printf(stderr, "Error opening {}: {}\n", files[i], e.what());
                continue;
            } catch (...) {
                if (verbosity >= 0)
                    ST::printf(stderr, "Undefined error opening {}\n", files[i]);
                continue;
            }
            uint32_t dataSize = SF.size();
            std::unique_ptr<uint8_t[]> buf(new uint8_t[dataSize]);
            SF.read(dataSize, buf.get());
            SF.close();

            plEncryptedStream DF;
            plEncryptedStream::EncryptionType eType = plEncryptedStream::kEncAuto;
            if (method == emTea)
                eType = plEncryptedStream::kEncXtea;
            if (method == emAes)
                eType = plEncryptedStream::kEncAES;
            if (method == emDroid)
                eType = plEncryptedStream::kEncDroid;
            if (method == emDroid && !haveKey) {
                fputs("Error: Droid key not set!\n", stderr);
                return 1;
            }
            if (method == emAes && haveKey && verbosity >= 0)
                fputs("Warning: Ignoring key for AES encryption\n", stderr);
            if (haveKey)
                DF.setKey(uruKey);
            outFileName = doReplace ? files[i] : getNextOutFile(files[i]);
            if (verbosity >= 1)
                ST::printf("Encrypting {}...\n", outFileName);
            DF.open(outFileName, fmCreate, eType);
            DF.write(dataSize, buf.get());
            DF.close();
            nFiles++;
        }
    }

    if (nFiles > 0) {
        if (verbosity >= 0) {
            ST::printf("Successfully {} {} files!\n",
                       (method == emDecrypt ? "decrypted" : "encrypted"), nFiles);
        }
    }
    return 0;
}
