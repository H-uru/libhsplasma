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
};

struct SumFile {
    unsigned int fUnknown;
    std::vector<SumEntry> fEntries;

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

void UpdateSums(const plString& filename) {
    printf("%s:\n", filename.cstr());
    try {
        plEncryptedStream S;
        if (!S.open(filename, fmRead, plEncryptedStream::kEncAuto)) {
            fprintf(stderr, "Could not open file %s\n", filename.cstr());
            return;
        }
        plEncryptedStream::EncryptionType eType = S.getEncType();
        SumFile sum;
        sum.read(&S);
        S.close();

        for (size_t i=0; i<sum.fEntries.size(); i++) {
            hsFileStream* FS = FindFilePath(sum.fEntries[i].fPath, cdUp(filename));
            if (FS == NULL) {
                if (s_autoYes) {
                    PrintFile(sum.fEntries[i], '-');
                    sum.fEntries.erase(sum.fEntries.begin() + i);
                    --i;
                } else {
                    fprintf(stderr, "File %s not found.  Remove it? [y/N] ",
                            sum.fEntries[i].fPath.cstr());
                    char buf[256];
                    fgets(buf, 256, stdin);
 
                    if (strcmp(buf, "y\n") == 0 || strcmp(buf, "Y\n") == 0) {
                        PrintFile(sum.fEntries[i], '-');
                        sum.fEntries.erase(sum.fEntries.begin() + i);
                        --i;
                    } else {
                        PrintFile(sum.fEntries[i], '!');
                    }
                }
                continue;
            }
            plMD5Hash hash = plMD5::hashStream(FS);
            sum.fEntries[i].fTimestamp = FS->getModTime();
            if (sum.fEntries[i].fHash != hash) {
                sum.fEntries[i].fHash = hash;
                PrintFile(sum.fEntries[i], '*');
            } else {
                PrintFile(sum.fEntries[i], ' ');
            }
            delete FS;
        }

        S.open(filename, fmWrite, eType);
        sum.write(&S);
        S.close();
        printf("\n");
    } catch (hsException& e) {
        fprintf(stderr, "%s:%ld: %s\n", e.File(), e.Line(), e.what());
    } catch (...) {
        fprintf(stderr, "An unknown error occured\n");
    }
}


/* Main program */
void doHelp(const char* progName) {
    printf("Usage: %s [options] sumfile [...]\n\n", progName);
    printf("Options:\n");
    printf("    -L        List the contents of the sumfile\n");
    printf("    -i path   Insert `path` into the sumfile\n");
    printf("    -d path   Remove `path` from the sumfile\n");
    printf("    -y        Answer YES to delete prompts\n\n");
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
            } else if (strcmp(argv[i], "-y") == 0) {
                s_autoYes = true;
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

    switch (mode) {
    case kModeUpdate:
        if (sumFiles.empty()) {
            fprintf(stderr, "Error: No files specified\n");
            return 1;
        }
        for (std::list<plString>::iterator fn = sumFiles.begin(); fn != sumFiles.end(); fn++)
            UpdateSums(*fn);
        break;
    case kModeList:
        for (std::list<plString>::iterator fn = sumFiles.begin(); fn != sumFiles.end(); fn++) {
            printf("%s:\n", fn->cstr());
            try {
                plEncryptedStream S;
                S.open(*fn, fmRead, plEncryptedStream::kEncAuto);
                SumFile sum;
                sum.read(&S);
                S.close();

                for (size_t i=0; i<sum.fEntries.size(); i++)
                    PrintFile(sum.fEntries[i], ' ');
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
            plEncryptedStream S;
            S.open(sumFiles.front(), fmRead, plEncryptedStream::kEncAuto);
            plEncryptedStream::EncryptionType eType = S.getEncType();
            SumFile sum;
            sum.read(&S);
            S.close();

            for (std::list<plString>::iterator pi = delPaths.begin(); pi != delPaths.end(); pi++) {
                bool found = false;
                for (size_t i=0; i<sum.fEntries.size(); i++) {
                    if (sum.fEntries[i].fPath == *pi) {
                        sum.fEntries.erase(sum.fEntries.begin() + i);
                        --i;
                        found = true;
                    }
                }
                if (!found)
                    fprintf(stderr, "Warning: path '%s' not found\n", pi->cstr());
            }

            for (std::list<plString>::iterator pi = addPaths.begin(); pi != addPaths.end(); pi++) {
                hsFileStream* FS = FindFilePath(*pi, "");
                if (FS == NULL) {
                    fprintf(stderr, "Warning: path '%s' not found\n", pi->cstr());
                    continue;
                }

                SumEntry ent;
                ent.fPath = *pi;
                ent.fHash = plMD5::hashStream(FS);
                ent.fTimestamp = FS->getModTime();
                ent.fUnknown = 0;
                sum.fEntries.push_back(ent);
                delete FS;
            }

            S.open(sumFiles.front(), fmWrite, eType);
            sum.write(&S);
            S.close();
            printf("Successfully updated %s\n", sumFiles.front().cstr());
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
