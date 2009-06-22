#include <ResManager/plResManager.h>
#include <ResManager/plFactory.h>
#include <Debug/hsExceptions.h>
#include <Debug/plDebug.h>
#include <PRP/KeyedObject/hsKeyedObject.h>

void doHelp(const char* prgName) {
    fprintf(stderr, "Usage: %s filename.prp action [options]\n\n", prgName);
    fprintf(stderr, "actions:\n");
    fprintf(stderr, "    add filename        Insert an object (.po or .prc) into the PRP\n");
    fprintf(stderr, "    del type:object     Remove an object from the PRP\n");
    fprintf(stderr, "    extract type:object Extract an object (.po) from the PRP\n\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "    -o filename     Specify the output file (extract mode)\n");
    fprintf(stderr, "    --prc           Do PRC decompilation (extract mode)\n");
    fprintf(stderr, "    --help          Display this help message and then exit\n\n");
}

plKey findObject(plResManager* mgr, const plLocation& loc, const plString& name, short type) {
    std::vector<plKey> keys = mgr->getKeys(loc, type);
    for (std::vector<plKey>::iterator it=keys.begin(); it != keys.end(); it++) {
        if ((*it)->getName() == name)
            return *it;
    }
    return plKey();
}

enum {
    kActionUnknown, kActionAdd, kActionDel, kActionExtract,
    kActionMask = 0xFF, kModePRC = 0x100
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        doHelp(argv[0]);
        return 1;
    }

    plString outFile, inFile, prpFile;
    plString objName;
    short objType = -1;
    int action = kActionUnknown;

    for (int i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-o") == 0) {
                if (++i >= argc) {
                    fprintf(stderr, "Missing output filename");
                    return 1;
                }
                outFile = argv[i];
            } else if (strcmp(argv[i], "--prc") == 0) {
                action |= kModePRC;
            } else if (strcmp(argv[i], "--help") == 0) {
                doHelp(argv[0]);
                return 0;
            } else {
                fprintf(stderr, "Unrecognized option: %s\nSee --help for usage details", argv[i]);
                return 1;
            }
        } else {
            if (strcmp(argv[i], "add") == 0) {
                if (++i >= argc) {
                    fprintf(stderr, "Missing input filename");
                    return 1;
                }
                action = (action & ~kActionMask) | kActionAdd;
                inFile = argv[i];
            } else if (strcmp(argv[i], "del") == 0) {
                if (++i >= argc) {
                    fprintf(stderr, "Missing object specifier");
                    return 1;
                }
                action = (action & ~kActionMask) | kActionDel;
                plString objSpec = argv[i];
                plString type = objSpec.beforeFirst(':');
                objType = plFactory::ClassIndex(type);
                if (objType == -1)
                    objType = type.toInt();
                objName = objSpec.afterLast(':');
                if (objName.startsWith('"')) {
                    do {
                        if (++i >= argc) {
                            fprintf(stderr, "Error: Unterminated string");
                            return 1;
                        }
                        objName += plString(" ") + argv[i];
                    } while (!objName.endsWith('"'));
                    objName = objName.mid(1, objName.len() - 2);
                }
            } else if (strcmp(argv[i], "extract") == 0) {
                if (++i >= argc) {
                    fprintf(stderr, "Missing object specifier");
                    return 1;
                }
                action = (action & ~kActionMask) | kActionExtract;
                plString objSpec = argv[i];
                plString type = objSpec.beforeFirst(':');
                objType = plFactory::ClassIndex(type);
                if (objType == -1)
                    objType = type.toInt();
                objName = objSpec.afterLast(':');
                if (objName.startsWith('"')) {
                    do {
                        if (++i >= argc) {
                            fprintf(stderr, "Error: Unterminated string");
                            return 1;
                        }
                        objName += plString(" ") + argv[i];
                    } while (!objName.endsWith('"'));
                    objName = objName.mid(1, objName.len() - 2);
                }
            } else {
                if (prpFile.empty()) {
                    prpFile = argv[i];
                } else {
                    fprintf(stderr, "Unknown action: %s\nSee --help for usage details", argv[i]);
                    return 1;
                }
            }
        }
    }
    if ((action & kActionMask) == kActionUnknown || prpFile.empty()) {
        doHelp(argv[0]);
        return 1;
    }

    plDebug::Init(plDebug::kDLAll);
    plResManager resMgr;
    plPageInfo* page;
    try {
        page = resMgr.ReadPage(prpFile);
    } catch (hsException& e) {
        fprintf(stderr, "%s:%lu: %s\n", e.File(), e.Line(), e.what());
        return 1;
    } catch (std::exception& e) {
        fprintf(stderr, "Caught exception: %s\n", e.what());
        return 1;
    } catch (...) {
        fprintf(stderr, "Undefined error!\n");
        return 1;
    }

    if ((action & kActionMask) == kActionAdd) {
        hsFileStream in;
        plCreatable* cre = NULL;

        if (inFile.endsWith(".prc") || (action & kModePRC) != 0) {
            // Add PRC source
            pfPrcParser prc;
            try {
                in.open(inFile, fmRead);
                prc.read(&in);
                const pfPrcTag* root = prc.getRoot();
                cre = resMgr.prcParseCreatable(root);
            } catch (hsException& e) {
                fprintf(stderr, "%s:%lu: %s\n", e.File(), e.Line(), e.what());
                return 1;
            } catch (std::exception& e) {
                fprintf(stderr, "Caught Exception: %s\n", e.what());
                return 1;
            }
        } else {
            // Add raw object
            try {
                in.setVer(resMgr.getVer());
                in.open(inFile, fmRead);
                cre = resMgr.ReadCreatable(&in);
            } catch (hsException& e) {
                fprintf(stderr, "%s:%lu: %s\n", e.File(), e.Line(), e.what());
                return 1;
            } catch (std::exception& e) {
                fprintf(stderr, "Caught Exception: %s\n", e.what());
                return 1;
            }
        }

        if (cre != NULL) {
            hsKeyedObject* kobj = hsKeyedObject::Convert(cre);
            if (kobj == NULL) {
                fprintf(stderr, "Creatable '%s` is not a keyed object\n",
                        plFactory::ClassName(cre->ClassIndex()));
                return 1;
            }
            resMgr.AddObject(page->getLocation(), kobj);
        } else {
            fprintf(stderr, "Failure parsing %s\n", inFile.cstr());
            return 1;
        }
        resMgr.WritePage(prpFile, page);
    } else if ((action & kActionMask) == kActionDel) {
        plKey key = findObject(&resMgr, page->getLocation(), objName, objType);
        if (!key.Exists() || key->getObj() == NULL) {
            fprintf(stderr, "Could not find %s:%s\n",
                    plFactory::ClassName(objType), objName.cstr());
            return 1;
        }
        resMgr.DelObject(key);
        resMgr.WritePage(prpFile, page);
    } else if ((action & kActionMask) == kActionExtract) {
        plKey key = findObject(&resMgr, page->getLocation(), objName, objType);
        if (!key.Exists() || key->getObj() == NULL) {
            fprintf(stderr, "Could not find %s:%s\n",
                    plFactory::ClassName(objType), objName.cstr());
            return 1;
        }
        if (outFile.empty())
            outFile = plString::Format("[%04X]%s.%s", objType, objName.cstr(),
                                       (action & kModePRC) != 0 ? "prc" : "po");
        hsFileStream out;
        out.setVer(resMgr.getVer());
        out.open(outFile, fmCreate);
        if ((action & kModePRC) != 0) {
            pfPrcHelper prc(&out);
            key->getObj()->prcWrite(&prc);
        } else {
            key->getObj()->write(&out, &resMgr);
        }
        out.close();
    }
}
