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

#include <string_theory/stdio>
#include <list>
#include <vector>
#include <cstring>
#include <time.h>
#include <memory>

#include "Util/plMD5.h"
#include "Stream/plEncryptedStream.h"

/* Sum file structures and operations */
struct SumEntry {
    ST::string fPath;
    plMD5Hash fHash;
    time_t fTimestamp;
    unsigned int fUnknown;

    SumEntry() : fTimestamp(0), fUnknown(0) { }
};

struct SumFile {
    unsigned int fUnknown;
    std::vector<SumEntry> fEntries;

    SumFile() : fUnknown() { }

    void read(hsStream* S) {
        fEntries.resize(S->readInt());
        fUnknown = S->readInt();
        for (size_t i = 0; i < fEntries.size(); ++i) {
            fEntries[i].fPath = S->readSafeStr();
            fEntries[i].fHash.read(S);
            fEntries[i].fTimestamp = S->readInt();
            fEntries[i].fUnknown = S->readInt();
        }
    }

    void write(hsStream* S) const {
        S->writeInt(fEntries.size());
        S->writeInt(fUnknown);
        for (const SumEntry& entry : fEntries) {
            S->writeSafeStr(entry.fPath);
            entry.fHash.write(S);
            S->writeInt(entry.fTimestamp);
            S->writeInt(entry.fUnknown);
        }
    }
};

static void PrintFile(const SumEntry& file, char op) {
    char buf[32];
    struct tm* tbuf = localtime(&file.fTimestamp);
    strftime(buf, hsArraySize(buf), "%Y/%m/%d %H:%M:%S", tbuf);
    ST::printf("{c} {}  {}  {}\n", op, file.fHash.toHex(), buf, file.fPath);
}

static ST::string FixSlashes(const ST::string& src) {
    if (src.is_empty())
        return src;

    ST::char_buffer dest;
    dest.allocate(src.size());
    memcpy(dest.data(), src.c_str(), src.size());
    for (auto pc = dest.begin(); pc != dest.end(); ++pc) {
        if (*pc == '/' || *pc == '\\')
            *pc = PATHSEP;
    }
    return dest;
}

static ST::string cdUp(ST::string path) {
    // Check for root paths, we can't go up from there!
#ifdef _WIN32
    if (path.substr(1) == ":\\")
        return path;
#else
    if (path == "/")
        return path;
#endif

    // Not very robust, but it works for one level of parent scanning
    if (path.is_empty())
        return ST_LITERAL(".." PATHSEPSTR);

    // Strip the ending slash, if necessary, and then go up one dir
    if (path.back() == PATHSEP)
        path = path.left(path.size() - 1);
    ST::string up = path.before_last(PATHSEP);
    if (path.front() == PATHSEP) {
        // Absolute path specified -- make sure we keep it that way
        return up + PATHSEPSTR;
    } else {
        // Relative path specified
        return up.is_empty() ? ST::null : up + PATHSEPSTR;
    }
}

static std::unique_ptr<hsFileStream> FindFilePath(ST::string path, ST::string base) {
    if (path.is_empty())
        return nullptr;

    // Scan first from the provided path:
    std::unique_ptr<hsFileStream> S;
    path = FixSlashes(path);
    if (hsFileStream::FileExists(base + path)) {
        S = std::make_unique<hsFileStream>();
        S->open(base + path, fmRead);
        return S;
    }

    // If that fails, scan the parent, so we can loop around and find
    // files with explicit locations (sfx/ and dat/ prefixes)
    base = cdUp(base);
    if (hsFileStream::FileExists(base + path)) {
        S = std::make_unique<hsFileStream>();
        S->open(base + path, fmRead);
        return S;
    }

    // Otherwise, we can't find the referenced file
    return nullptr;
}

static bool s_autoYes = false;
static bool s_createFile = false;
static bool s_oldFormat = false;

static ST::string GetInternalName(const ST::string& filename) {
    // Different files are stored in different locations; this function
    // will try to guess where to put things based on the file's extension.
    // This is all based on the contents of .sum files included with the
    // games that I examined for this.

    ST::string split = s_oldFormat ? "/" : "\\";
    ST::string name = FixSlashes(filename).after_last(PATHSEP);
    ST::string ext = name.after_last('.');
    if (s_oldFormat && ext == "prp")
        return name;
    if (ext == "ogg" || ext == "wav")
        return ST_LITERAL("sfx") + split + name;
    if (ext == "exe" || ext == "dll" || ext == "map" || ext == "pdb")
        return name;
    if (ext == "sdl")
        return ST_LITERAL("SDL") + split + name;
    if (ext == "pak")
        return ST_LITERAL("Python") + split + name;
    if (ext == "fx")
        return ST_LITERAL("fx") + split + name;

    // dat is the default, since so many file types go there...
    // To name a few,
    // prp, age, fni, csv, sub, node, pfp, dat, tron, hex, tga, loc
    return ST_LITERAL("dat") + split + name;
}

static bool UpdateSums(const ST::string& filename) {
    bool isUpdated = false;
    ST::printf("{}:\n", filename);
    try {
        SumFile sum;
        plEncryptedStream S;
        plEncryptedStream::EncryptionType eType = plEncryptedStream::kEncXtea;
        if (!S.open(filename, fmRead, plEncryptedStream::kEncAuto)) {
            ST::printf(stderr, "Could not open file {}\n", filename);
            return false;
        }
        eType = S.getEncType();
        sum.read(&S);
        S.close();

        auto it = sum.fEntries.begin();
        while (it != sum.fEntries.end()) {
            std::unique_ptr<hsFileStream> IS = FindFilePath(it->fPath, cdUp(filename));
            if (!IS) {
                if (s_autoYes) {
                    PrintFile(*it, '-');
                    it = sum.fEntries.erase(it);
                    isUpdated = true;
                } else {
                    ST::printf(stderr, "File {} not found.  Remove it? [y/N] ",
                               it->fPath);
                    char buf[256];
                    fgets(buf, hsArraySize(buf), stdin);

                    if (strcmp(buf, "y\n") == 0 || strcmp(buf, "Y\n") == 0) {
                        PrintFile(*it, '-');
                        it = sum.fEntries.erase(it);
                        isUpdated = true;
                    } else {
                        PrintFile(*it, '!');
                        ++it;
                    }
                }
                continue;
            }
            plMD5Hash hash = plMD5::hashStream(IS.get());
            it->fTimestamp = IS->getModTime();
            if (it->fHash != hash) {
                it->fHash = hash;
                PrintFile(*it, '*');
                isUpdated = true;
            } else {
                PrintFile(*it, ' ');
            }
            ++it;
        }

        if (isUpdated) {
            if (!S.open(filename, fmCreate, eType)) {
                ST::printf(stderr, "Error: Could not open {} for writing!\n", filename);
                return false;
            }
            sum.write(&S);
            S.close();
        }
        puts("");
    } catch (const hsException& e) {
        ST::printf(stderr, "{}:{}: {}\n", e.File(), e.Line(), e.what());
    } catch (...) {
        fputs("An unknown error occured\n", stderr);
    }
    return isUpdated;
}


/* Main program */
static void doHelp(const char* progName) {
    ST::printf("Usage: {} [options] sumfile [...]\n", progName);
    puts("");
    puts("Options:");
    puts("    -L        List the contents of the sumfile");
    puts("    -c        Create a new sumfile (or overwrite one if it already exists)");
    puts("    -i path   Insert `path` into the sumfile (or re-hash if it exists)");
    puts("    -d path   Remove `path` from the sumfile");
    puts("    -y        Answer YES to delete prompts");
    puts("    -old      Use the older (pre-Path of the Shell) format");
    puts("");
    puts("If no options are specified, the default is to re-sum the contents");
    puts("of `sumfile`");
    puts("");
}

enum OperationMode {
    kModeUpdate, kModeList, kModeManual
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        doHelp(argv[0]);
        return 1;
    }

    OperationMode mode = kModeUpdate;
    std::list<ST::string> addPaths;
    std::list<ST::string> delPaths;
    std::list<ST::string> sumFiles;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-L") == 0) {
                mode = kModeList;
            } else if (strcmp(argv[i], "-i") == 0) {
                mode = kModeManual;
                if (++i >= argc) {
                    fputs("Error: Expected filename\n", stderr);
                    return 1;
                }
                addPaths.emplace_back(argv[i]);
            } else if (strcmp(argv[i], "-d") == 0) {
                mode = kModeManual;
                if (++i >= argc) {
                    fputs("Error: Expected filename\n", stderr);
                    return 1;
                }
                delPaths.emplace_back(argv[i]);
            } else if (strcmp(argv[i], "-c") == 0) {
                mode = kModeManual;
                s_createFile = true;
            } else if (strcmp(argv[i], "-y") == 0) {
                s_autoYes = true;
            } else if (strcmp(argv[i], "-old") == 0) {
                s_oldFormat = true;
            } else if (strcmp(argv[i], "--help") == 0) {
                doHelp(argv[0]);
                return 0;
            } else {
                ST::printf(stderr, "Error: Unrecognized option {}\n", argv[i]);
                return 1;
            }
        } else {
            sumFiles.emplace_back(argv[i]);
        }
    }

    if (sumFiles.empty()) {
        fputs("Error: No sum files specified\n", stderr);
        return 1;
    }
    if (s_createFile && mode == kModeList) {
        fputs("Error: -c and -L options cannot be combined\n", stderr);
        return 1;
    }

    switch (mode) {
    case kModeUpdate:
        for (const ST::string& fn : sumFiles) {
            if (UpdateSums(fn))
                ST::printf("Successfully updated {}\n", fn);
        }
        break;
    case kModeList:
        for (const ST::string& fn : sumFiles) {
            ST::printf("{}:\n", fn);
            try {
                plEncryptedStream S;
                if (!S.open(fn, fmRead, plEncryptedStream::kEncAuto)) {
                    ST::printf(stderr, "Could not open file {}\n", fn);
                    continue;
                }
                SumFile sum;
                sum.read(&S);
                S.close();

                for (const SumEntry& entry : sum.fEntries)
                    PrintFile(entry, ' ');
                printf("\n");
            } catch (const hsException& e) {
                ST::printf(stderr, "{}:{}: {}\n", e.File(), e.Line(), e.what());
                return 1;
            } catch (...) {
                fputs("An unknown error occurred\n", stderr);
                return 1;
            }
        }
        break;
    case kModeManual:
        if (sumFiles.size() != 1) {
            fputs("Error: You must specify exactly ONE sumfile for\n", stderr);
            fputs("-i, -d, -c operations\n", stderr);
            return 1;
        }
        const ST::string sumFile = sumFiles.front();
        try {
            bool isUpdated = false;
            SumFile sum;
            plEncryptedStream S;
            plEncryptedStream::EncryptionType eType = plEncryptedStream::kEncXtea;
            if (!s_createFile) {
                if (!S.open(sumFile, fmRead, plEncryptedStream::kEncAuto)) {
                    ST::printf(stderr, "Could not open file {}\n", sumFile);
                    return 1;
                }
                eType = S.getEncType();
                sum.read(&S);
                S.close();
            } else {
                isUpdated = true;
            }

            for (const ST::string& path : delPaths) {
                bool found = false;
                auto it = sum.fEntries.begin();
                while (it != sum.fEntries.end()) {
                    if (it->fPath == path) {
                        PrintFile(*it, '-');
                        it = sum.fEntries.erase(it);
                        found = true;
                        isUpdated = true;
                    } else {
                        ++it;
                    }
                }
                if (!found)
                    ST::printf(stderr, "Warning: path '{}' not found\n", path);
            }

            for (const ST::string& path : addPaths) {
                std::unique_ptr<hsFileStream> IS = FindFilePath(path, ST::null);
                if (!IS) {
                    ST::printf(stderr, "Warning: path '{}' not found\n", path);
                    continue;
                }

                SumEntry newEntry;
                newEntry.fPath = GetInternalName(path);
                newEntry.fHash = plMD5::hashStream(IS.get());
                newEntry.fTimestamp = IS->getModTime();
                bool found = false;
                for (SumEntry& entry : sum.fEntries) {
                    if (entry.fPath == path) {
                        found = true;
                        if (entry.fHash != newEntry.fHash) {
                            PrintFile(entry, '*');
                            entry.fHash = newEntry.fHash;
                            entry.fTimestamp = newEntry.fTimestamp;
                            isUpdated = true;
                        } else {
                            PrintFile(entry, ' ');
                        }
                    }
                }
                if (!found) {
                    PrintFile(newEntry, '+');
                    sum.fEntries.push_back(newEntry);
                    isUpdated = true;
                }
            }

            if (isUpdated) {
                if (!S.open(sumFile, fmWrite, eType)) {
                    ST::printf(stderr, "Error: Could not open {} for writing!\n",
                               sumFile);
                    return 1;
                }
                sum.write(&S);
                S.close();
                ST::printf("Successfully {} {}\n", s_createFile ? "created" : "updated",
                           sumFile);
            }
        } catch (const hsException& e) {
            ST::printf(stderr, "{}:{}: {}\n", e.File(), e.Line(), e.what());
            return 1;
        } catch (...) {
            fputs("An unknown error occurred\n", stderr);
            return 1;
        }
        break;
    }

    return 0;
}
