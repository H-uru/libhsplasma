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
#include <string_theory/stdio>
#include <cstring>

static void doHelp(const char* prgName)
{
    ST::printf("Usage: {} filename.prp action [options]\n", prgName);
    puts("");
    puts("actions:");
    puts("    add filename        Insert an object (.po or .prc) into the PRP");
    puts("    del type:object     Remove an object from the PRP");
    puts("    extract type:object Extract an object (.po) from the PRP");
    puts("");
    puts("options:");
    puts("    -o filename     Specify the output file (extract mode)");
    puts("    --prc           Do PRC decompilation (extract mode)");
    puts("    --help          Display this help message and then exit");
    puts("");
}

static plKey findObject(plResManager* mgr, const plLocation& loc,
                        const ST::string& name, short type)
{
    std::vector<plKey> keys = mgr->getKeys(loc, type);
    for (std::vector<plKey>::iterator it=keys.begin(); it != keys.end(); it++) {
        if ((*it)->getName() == name)
            return *it;
    }
    return plKey();
}

enum
{
    kActionUnknown, kActionAdd, kActionDel, kActionExtract,
    kActionMask = 0xFF, kModePRC = 0x100
};

int main(int argc, char* argv[])
{
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
                    fputs("Missing output filename\n", stderr);
                    return 1;
                }
                outFile = argv[i];
            } else if (strcmp(argv[i], "--prc") == 0) {
                action |= kModePRC;
            } else if (strcmp(argv[i], "--help") == 0) {
                doHelp(argv[0]);
                return 0;
            } else {
                ST::printf(stderr, "Unrecognized option: {}\n"
                                   "See --help for usage details\n", argv[i]);
                return 1;
            }
        } else {
            if (strcmp(argv[i], "add") == 0) {
                if (++i >= argc) {
                    fputs("Missing input filename\n", stderr);
                    return 1;
                }
                action = (action & ~kActionMask) | kActionAdd;
                inFile = argv[i];
            } else if (strcmp(argv[i], "del") == 0) {
                if (++i >= argc) {
                    fputs("Missing object specifier\n", stderr);
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
                            fputs("Error: Unterminated string\n", stderr);
                            return 1;
                        }
                        objName += ST::string(" ") + argv[i];
                    } while (!objName.ends_with("\""));
                    objName = objName.substr(1, objName.size() - 2);
                }
            } else if (strcmp(argv[i], "extract") == 0) {
                if (++i >= argc) {
                    fputs("Missing object specifier\n", stderr);
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
                            fputs("Error: Unterminated string\n", stderr);
                            return 1;
                        }
                        objName += ST::string(" ") + argv[i];
                    } while (!objName.ends_with("\""));
                    objName = objName.substr(1, objName.size() - 2);
                }
            } else {
                if (prpFile.empty()) {
                    prpFile = argv[i];
                } else {
                    ST::printf(stderr, "Unknown action: {}\n"
                                       "See --help for usage details\n", argv[i]);
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
        ST::printf(stderr, "{}:{}: {}\n", e.File(), e.Line(), e.what());
        return 1;
    } catch (std::exception& e) {
        ST::printf(stderr, "Caught exception: {}\n", e.what());
        return 1;
    } catch (...) {
        fputs("Undefined error!\n", stderr);
        return 1;
    }

    if ((action & kActionMask) == kActionAdd) {
        hsFileStream in;
        plCreatable* cre = nullptr;

        if (inFile.ends_with(".prc") || inFile.ends_with(".xml") || (action & kModePRC) != 0) {
            // Add PRC source
            pfPrcParser prc;
            try {
                in.open(inFile, fmRead);
                prc.read(&in);
                const pfPrcTag* root = prc.getRoot();
                cre = resMgr.prcParseCreatable(root);
            } catch (hsException& e) {
                ST::printf(stderr, "{}:{}: {}\n", e.File(), e.Line(), e.what());
                return 1;
            } catch (std::exception& e) {
                ST::printf(stderr, "Caught Exception: {}\n", e.what());
                return 1;
            }
        } else {
            // Add raw object
            try {
                in.setVer(resMgr.getVer());
                in.open(inFile, fmRead);
                cre = resMgr.ReadCreatable(&in);
            } catch (hsException& e) {
                ST::printf(stderr, "{}:{}: {}\n", e.File(), e.Line(), e.what());
                return 1;
            } catch (std::exception& e) {
                ST::printf(stderr, "Caught Exception: {}\n", e.what());
                return 1;
            }
        }

        if (cre) {
            hsKeyedObject* kobj = hsKeyedObject::Convert(cre);
            if (kobj == nullptr) {
                ST::printf(stderr, "Creatable '{}' is not a keyed object\n",
                           plFactory::ClassName(cre->ClassIndex()));
                delete cre;
                return 1;
            }
            // The key is already registered with the ResManager, but
            // let's make sure it's in the right Location:
            resMgr.MoveKey(kobj->getKey(), page->getLocation());
        } else {
            ST::printf(stderr, "Failure parsing {}\n", inFile);
            return 1;
        }
        resMgr.WritePage(prpFile, page);
    } else if ((action & kActionMask) == kActionDel) {
        plKey key = findObject(&resMgr, page->getLocation(), objName, objType);
        if (!key.Exists() || key->getObj() == nullptr) {
            ST::printf(stderr, "Could not find {}:{}\n",
                       plFactory::ClassName(objType), objName);
            return 1;
        }
        resMgr.DelObject(key);
        resMgr.WritePage(prpFile, page);
    } else if ((action & kActionMask) == kActionExtract) {
        plKey key = findObject(&resMgr, page->getLocation(), objName, objType);
        if (!key.Exists() || key->getObj() == nullptr) {
            ST::printf(stderr, "Could not find {}:{}\n",
                       plFactory::ClassName(objType), objName);
            return 1;
        }
        if (outFile.empty())
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

    return 0;
}
