#include <Util/plMD5.h>
#include <Stream/plEncryptedStream.h>
#include <list>
#include <vector>
#include <time.h>

/* Sum file structures and operations */
struct SumEntry {
    plString fPath;
    plMD5Hash fHash;
    time_t fTimestamp;
    unsigned int fUnknown;

    SumEntry() : fTimestamp(0), fUnknown(0) { }
};

struct SumFile {
    unsigned int fUnknown;
    std::vector<SumEntry> fEntries;

    SumFile() : fUnknown(0) { }

    void read(hsStream* S) {
        fEntries.resize(S->readInt());
        fUnknown = S->readInt();
        for (size_t i=0; i<fEntries.size(); i++) {
            fEntries[i].fPath = S->readSafeStr();
            fEntries[i].fHash.read(S);
            fEntries[i].fTimestamp = S->readInt();
            fEntries[i].fUnknown = S->readInt();
        }
    }

    void write(hsStream* S) {
        S->writeInt(fEntries.size());
        S->writeInt(fUnknown);
        for (size_t i=0; i<fEntries.size(); i++) {
            S->writeSafeStr(fEntries[i].fPath);
            fEntries[i].fHash.write(S);
            S->writeInt(fEntries[i].fTimestamp);
            S->writeInt(fEntries[i].fUnknown);
        }
    }
};

void PrintFile(const SumEntry& file, char op) {
    char buf[32];
    struct tm* tbuf = localtime(&file.fTimestamp);
    strftime(buf, 32, "%Y/%m/%d %H:%M:%S", tbuf);
    printf("%c %s  %s  %s\n", op,
           file.fHash.toHex().cstr(),
           buf, file.fPath.cstr()); 
}

plString FixSlashes(const plString& src) {
    if (src.empty())
        return plString();

    char* pbuf = strdup(src);
    for (char* pc = pbuf; *pc != 0; pc++) {
        if (*pc == '/' || *pc == '\\')
            *pc = PATHSEP;
    }
    plString dest(pbuf);
    free(pbuf);
    return dest;
}

plString cdUp(plString path) {
    // Check for root paths, we can't go up from there!
#ifdef WIN32
    if (path.mid(1) == ":\\")
        return path;
#else
    if (path == "/")
        return path;
#endif

    // Not very robust, but it works for one level of parent scanning
    if (path.empty())
        return ".." PATHSEPSTR;

    // Strip the ending slash, if necessary, and then go up one dir
    if (path[path.len()-1] == PATHSEP)
        path = path.left(path.len() - 1);
    plString up = path.beforeLast(PATHSEP);
    if (path[0] == PATHSEP) {
        // Absolute path specified -- make sure we keep it that way
        return up + PATHSEP;
    } else {
        // Relative path specified
        return up.empty() ? "" : up + PATHSEP;
    }
}

hsFileStream* FindFilePath(plString path, plString base) {
    if (path.empty())
        return NULL;
    
    // Scan first from the provided path:
    hsFileStream* S = NULL;
    path = FixSlashes(path);
    if (hsFileStream::FileExists(base + path)) {
        S = new hsFileStream();
        S->open(base + path, fmRead);
        return S;
    }

    // If that fails, scan the parent, so we can loop around and find
    // files with explicit locations (sfx/ and dat/ prefixes)
    base = cdUp(base);
    if (hsFileStream::FileExists(base + path)) {
        S = new hsFileStream();
        S->open(base + path, fmRead);
        return S;
    }

    // Otherwise, we can't find the referenced file
    return NULL;
}

static bool s_autoYes = false;
static bool s_createFile = false;
static bool s_oldFormat = false;

plString GetInternalName(const plString& filename) {
    // Different files are stored in different locations; this function
    // will try to guess where to put things based on the file's extension.
    // This is all based on the contents of .sum files included with the
    // games that I examined for this.

    plString split = s_oldFormat ? "/" : "\\";
    plString name = FixSlashes(filename).afterLast(PATHSEP);
    plString ext = name.afterLast('.');
    if (s_oldFormat && ext == "prp")
        return name;
    if (ext == "ogg" || ext == "wav")
        return plString("sfx") + split + name;
    if (ext == "exe" || ext == "dll" || ext == "map" || ext == "pdb")
        return name;
    if (ext == "sdl")
        return plString("SDL") + split + name;
    if (ext == "pak")
        return plString("Python") + split + name;
    if (ext == "fx")
        return plString("fx") + split + name;

    // dat is the default, since so many file types go there...
    // To name a few,
    // prp, age, fni, csv, sub, node, pfp, dat, tron, hex, tga, loc
    return plString("dat") + split + name;
}

bool UpdateSums(const plString& filename) {
    bool isUpdated = false;
    printf("%s:\n", filename.cstr());
    try {
        SumFile sum;
        plEncryptedStream S;
        plEncryptedStream::EncryptionType eType = plEncryptedStream::kEncXtea;
        if (!s_createFile) {
            if (!S.open(filename, fmRead, plEncryptedStream::kEncAuto)) {
                fprintf(stderr, "Could not open file %s\n", filename.cstr());
                return false;
            }
            eType = S.getEncType();
            sum.read(&S);
            S.close();
        }

        std::vector<SumEntry>::iterator it = sum.fEntries.begin();
        while (it != sum.fEntries.end()) {
            hsFileStream* FS = FindFilePath(it->fPath, cdUp(filename));
            if (FS == NULL) {
                if (s_autoYes) {
                    PrintFile(*it, '-');
                    it = sum.fEntries.erase(it);
                    isUpdated = true;
                } else {
                    fprintf(stderr, "File %s not found.  Remove it? [y/N] ",
                            it->fPath.cstr());
                    char buf[256];
                    fgets(buf, 256, stdin);
 
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
            plMD5Hash hash = plMD5::hashStream(FS);
            it->fTimestamp = FS->getModTime();
            if (it->fHash != hash) {
                it->fHash = hash;
                PrintFile(*it, '*');
                isUpdated = true;
            } else {
                PrintFile(*it, ' ');
            }
            if (FS != NULL)
                delete FS;
            ++it;
        }

        if (isUpdated) {
            if (!S.open(filename, fmCreate, eType)) {
                fprintf(stderr, "Error: Could not open %s for writing!\n", filename.cstr());
                return false;
            }
            sum.write(&S);
            S.close();
        }
        printf("\n");
    } catch (hsException& e) {
        fprintf(stderr, "%s:%ld: %s\n", e.File(), e.Line(), e.what());
    } catch (...) {
        fprintf(stderr, "An unknown error occured\n");
    }
    return isUpdated;
}


/* Main program */
void doHelp(const char* progName) {
    printf("Usage: %s [options] sumfile [...]\n\n", progName);
    printf("Options:\n");
    printf("    -L        List the contents of the sumfile\n");
    printf("    -c        Create a new sumfile (or overwrite one if it already exists)\n");
    printf("    -i path   Insert `path` into the sumfile (or re-hash if it exists)\n");
    printf("    -d path   Remove `path` from the sumfile\n");
    printf("    -y        Answer YES to delete prompts\n");
    printf("    -old      Use the older (pre-Path of the Shell) format\n\n");
    printf("If no options are specified, the default is to re-sum the contents\n");
    printf("of `sumfile`\n\n");
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
    std::list<plString> addPaths;
    std::list<plString> delPaths;
    std::list<plString> sumFiles;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-L") == 0) {
                mode = kModeList;
            } else if (strcmp(argv[i], "-i") == 0) {
                mode = kModeManual;
                if (++i >= argc) {
                    fprintf(stderr, "Error: Expected filename\n");
                    return 1;
                }
                addPaths.push_back(argv[i]);
            } else if (strcmp(argv[i], "-d") == 0) {
                mode = kModeManual;
                if (++i >= argc) {
                    fprintf(stderr, "Error: Expected filename\n");
                    return 1;
                }
                delPaths.push_back(argv[i]);
            } else if (strcmp(argv[i], "-c") == 0) {
                s_createFile = true;
            } else if (strcmp(argv[i], "-y") == 0) {
                s_autoYes = true;
            } else if (strcmp(argv[i], "-old") == 0) {
                s_oldFormat = true;
            } else if (strcmp(argv[i], "--help") == 0) {
                doHelp(argv[0]);
                return 0;
            } else {
                fprintf(stderr, "Error: Unrecognized option %s\n", argv[i]);
                return 1;
            }
        } else {
            sumFiles.push_back(argv[i]);
        }
    }

    if (sumFiles.empty()) {
        fprintf(stderr, "Error: No sum files specified\n");
        return 1;
    }
    if (s_createFile && mode == kModeList) {
        fprintf(stderr, "Error: -c and -L options cannot be combined\n");
        return 1;
    }

    switch (mode) {
    case kModeUpdate:
        for (std::list<plString>::iterator fn = sumFiles.begin(); fn != sumFiles.end(); fn++) {
            if (UpdateSums(*fn))
                printf("Successfully updated %s\n", fn->cstr());
        }
        break;
    case kModeList:
        for (std::list<plString>::iterator fn = sumFiles.begin(); fn != sumFiles.end(); fn++) {
            printf("%s:\n", fn->cstr());
            try {
                plEncryptedStream S;
                if (!S.open(*fn, fmRead, plEncryptedStream::kEncAuto)) {
                    fprintf(stderr, "Could not open file %s\n", fn->cstr());
                    continue;
                }
                SumFile sum;
                sum.read(&S);
                S.close();

                std::vector<SumEntry>::iterator it;
                for (it = sum.fEntries.begin(); it != sum.fEntries.end(); it++)
                    PrintFile(*it, ' ');
                printf("\n");
            } catch (hsException& e) {
                fprintf(stderr, "%s:%ld: %s\n", e.File(), e.Line(), e.what());
                return 1;
            } catch (...) {
                fprintf(stderr, "An unknown error occured\n");
                return 1;
            }
        }
        break;
    case kModeManual:
        if (sumFiles.size() != 1) {
            fprintf(stderr, "Error: You must specify exactly ONE sumfile for\n");
            fprintf(stderr, "-i and -d operations\n");
            return 1;
        }
        try {
            bool isUpdated = false;
            SumFile sum;
            plEncryptedStream S;
            plEncryptedStream::EncryptionType eType = plEncryptedStream::kEncXtea;
            if (!s_createFile) {
                if (!S.open(sumFiles.front(), fmRead, plEncryptedStream::kEncAuto)) {
                    fprintf(stderr, "Could not open file %s\n", sumFiles.front().cstr());
                    return 1;
                }
                eType = S.getEncType();
                sum.read(&S);
                S.close();
            } else {
                isUpdated = true;
            }

            std::list<plString>::iterator pi;
            std::vector<SumEntry>::iterator it;
            for (pi = delPaths.begin(); pi != delPaths.end(); pi++) {
                bool found = false;
                it = sum.fEntries.begin();
                while (it != sum.fEntries.end()) {
                    if (it->fPath == *pi) {
                        PrintFile(*it, '-');
                        it = sum.fEntries.erase(it);
                        found = true;
                        isUpdated = true;
                    } else {
                        ++it;
                    }
                }
                if (!found)
                    fprintf(stderr, "Warning: path '%s' not found\n", pi->cstr());
            }

            for (pi = addPaths.begin(); pi != addPaths.end(); pi++) {
                hsFileStream* FS = FindFilePath(*pi, "");
                if (FS == NULL) {
                    fprintf(stderr, "Warning: path '%s' not found\n", pi->cstr());
                    continue;
                }

                SumEntry ent;
                ent.fPath = GetInternalName(*pi);
                ent.fHash = plMD5::hashStream(FS);
                ent.fTimestamp = FS->getModTime();
                bool found = false;
                it = sum.fEntries.begin();
                while (it != sum.fEntries.end()) {
                    if (it->fPath == *pi) {
                        found = true;
                        if (it->fHash != ent.fHash) {
                            PrintFile(*it, '*');
                            it->fHash = ent.fHash;
                            it->fTimestamp = ent.fTimestamp;
                            isUpdated = true;
                        } else {
                            PrintFile(*it, ' ');
                        }
                    }
                    ++it;
                }
                if (!found) {
                    PrintFile(ent, '+');
                    sum.fEntries.push_back(ent);
                    if (FS != NULL)
                        delete FS;
                    isUpdated = true;
                }
            }

            if (isUpdated) {
                if (!S.open(sumFiles.front(), fmWrite, eType)) {
                    fprintf(stderr, "Error: Could not open %s for writing!\n",
                            sumFiles.front().cstr());
                    return 1;
                }
                sum.write(&S);
                S.close();
                printf("Successfully %s %s\n",
                       s_createFile ? "created" : "updated",
                       sumFiles.front().cstr());
            }
        } catch (hsException& e) {
            fprintf(stderr, "%s:%ld: %s\n", e.File(), e.Line(), e.what());
            return 1;
        } catch (...) {
            fprintf(stderr, "An unknown error occured\n");
            return 1;
        }
        break;
    }

    return 0;
}
