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

#include <ResManager/plResManager.h>
#include <ResManager/plFactory.h>
#include <Debug/hsExceptions.hpp>
#include <Debug/plDebug.h>
#include <PRP/KeyedObject/hsKeyedObject.h>
#include <cstring>

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

plKey findObject(plResManager* mgr, const plLocation& loc, const ST::string& name, short type) {
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

    ST::string outFile, inFile, prpFile;
    ST::string objName;
    short objType = -1;
    int action = kActionUnknown;

    for (int i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-o") == 0) {
                if (++i >= argc) {
                    fprintf(stderr, "Missing output filename\n");
                    return 1;
                }
                outFile = argv[i];
            } else if (strcmp(argv[i], "--prc") == 0) {
                action |= kModePRC;
            } else if (strcmp(argv[i], "--help") == 0) {
                doHelp(argv[0]);
                return 0;
            } else {
                fprintf(stderr, "Unrecognized option: %s\nSee --help for usage details\n", argv[i]);
                return 1;
            }
        } else {
            if (strcmp(argv[i], "add") == 0) {
                if (++i >= argc) {
                    fprintf(stderr, "Missing input filename\n");
                    return 1;
                }
                action = (action & ~kActionMask) | kActionAdd;
                inFile = argv[i];
            } else if (strcmp(argv[i], "del") == 0) {
                if (++i >= argc) {
                    fprintf(stderr, "Missing object specifier\n");
                    return 1;
                }
                action = (action & ~kActionMask) | kActionDel;
                ST::string objSpec = argv[i];
                ST::string type = objSpec.before_first(':');
                objType = plFactory::ClassIndex(type.c_str());
                if (objType == -1)
                    objType = type.to_int();
                objName = objSpec.after_last(':');
                if (objName.starts_with("\"")) {
                    do {
                        if (++i >= argc) {
                            fprintf(stderr, "Error: Unterminated string\n");
                            return 1;
                        }
                        objName += ST::string(" ") + argv[i];
                    } while (!objName.ends_with("\""));
                    objName = objName.substr(1, objName.size() - 2);
                }
            } else if (strcmp(argv[i], "extract") == 0) {
                if (++i >= argc) {
                    fprintf(stderr, "Missing object specifier\n");
                    return 1;
                }
                action = (action & ~kActionMask) | kActionExtract;
                ST::string objSpec = argv[i];
                ST::string type = objSpec.before_first(':');
                objType = plFactory::ClassIndex(type.c_str());
                if (objType == -1)
                    objType = type.to_int();
                objName = objSpec.after_last(':');
                if (objName.starts_with("\"")) {
                    do {
                        if (++i >= argc) {
                            fprintf(stderr, "Error: Unterminated string\n");
                            return 1;
                        }
                        objName += ST::string(" ") + argv[i];
                    } while (!objName.ends_with("\""));
                    objName = objName.substr(1, objName.size() - 2);
                }
            } else {
                if (prpFile.is_empty()) {
                    prpFile = argv[i];
                } else {
                    fprintf(stderr, "Unknown action: %s\nSee --help for usage details\n", argv[i]);
                    return 1;
                }
            }
        }
    }
    if ((action & kActionMask) == kActionUnknown || prpFile.is_empty()) {
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

        if (inFile.ends_with(".prc") || inFile.ends_with(".xml") || (action & kModePRC) != 0) {
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
                fprintf(stderr, "Creatable '%s' is not a keyed object\n",
                        plFactory::ClassName(cre->ClassIndex()));
                delete cre;
                return 1;
            }
            // The key is already registered with the ResManager, but
            // let's make sure it's in the right Location:
            resMgr.MoveKey(kobj->getKey(), page->getLocation());
        } else {
            fprintf(stderr, "Failure parsing %s\n", inFile.c_str());
            return 1;
        }
        resMgr.WritePage(prpFile, page);
    } else if ((action & kActionMask) == kActionDel) {
        plKey key = findObject(&resMgr, page->getLocation(), objName, objType);
        if (!key.Exists() || key->getObj() == NULL) {
            fprintf(stderr, "Could not find %s:%s\n",
                    plFactory::ClassName(objType), objName.c_str());
            return 1;
        }
        resMgr.DelObject(key);
        resMgr.WritePage(prpFile, page);
    } else if ((action & kActionMask) == kActionExtract) {
        plKey key = findObject(&resMgr, page->getLocation(), objName, objType);
        if (!key.Exists() || key->getObj() == NULL) {
            fprintf(stderr, "Could not find %s:%s\n",
                    plFactory::ClassName(objType), objName.c_str());
            return 1;
        }
        if (outFile.is_empty())
            outFile = ST::format("[{_04X}]{}.{}", objType, objName,
                                 (action & kModePRC) != 0 ? "prc" : "po");
        hsFileStream out;
        out.setVer(resMgr.getVer());
        out.open(outFile, fmCreate);
        if ((action & kModePRC) != 0) {
            pfPrcHelper prc(&out);
            key->getObj()->prcWrite(&prc);
        } else {
            resMgr.WriteCreatable(&out, key->getObj());
        }
        out.close();
    }
}
