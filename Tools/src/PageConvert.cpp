#include <stdio.h>
#include <string.h>
#include "ResManager/plResManager.h"
#include "Debug/hsExceptions.h"
#include "Debug/plDebug.h"

const char* PlasmaVerNames[] = { 
    "Unknown",  // pvUnknown
    "Prime",    // pvPrime
    "PotS",     // pvPots
    "EOA",      // pvEoa
    "Live",     // pvLive
    "HexIsle"   // pvHex
};

const char* getSuffix(PlasmaVer pv) {
    switch (pv) {
    case pvPrime:   return "prime";
    case pvPots:    return "pots";
    case pvLive:    return "live";
    case pvEoa:     return "eoa";
    case pvHex:     return "hex";
    default:        return "err";
    }
}

void doHelp() {
    printf("PRP Page Converter 1.0\nBy Michael Hansen\n\n");
    printf("Usage:  PageConvert [-to???] [-help] filename [filename] [...]\n\n");
    printf("  -toprime  Converts to Prime format (63.11) (Default)\n");
    printf("  -topots   Converts to Path of the Shell format (63.12)\n");
    printf("  -tolive   Converts to Uru Live format\n");
    printf("  -toeoa    Converts to Myst V: End of Ages format\n");
    printf("  -tohex    Converts to Hex Isle format\n");
    printf("  -help     Displays this screen\n\n");
}

int main(int argc, char** argv) {
    plResManager rm;
    plDebug::Init(plDebug::kDLAll);

    PlasmaVer toVer = pvPrime;
    int files = 0;

    if (argc == 1) {
        doHelp();
        return 0;
    }

    for (int i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-') argv[i]++;
            if (strcmp(argv[i], "-toeoa") == 0)
                toVer = pvEoa;
            else if (strcmp(argv[i], "-toprime") == 0)
                toVer = pvPrime;
            else if (strcmp(argv[i], "-topots") == 0)
                toVer = pvPots;
            else if (strcmp(argv[i], "-tolive") == 0)
                toVer = pvLive;
            else if (strcmp(argv[i], "-tohex") == 0)
                toVer = pvHex;
            else if (strcmp(argv[i], "-help") == 0) {
                doHelp();
                return 0;
            } else {
                plDebug::Error("Error: Unrecognized option %s", argv[i]);
                return 1;
            }
        } else {
            plPageInfo* page;
            try {
                page = rm.ReadPage(argv[i]);
            } catch (const hsException& e) {
                plDebug::Error("%s:%lu: %s", e.File(), e.Line(), e.what());
                return 1;
            } catch (const std::exception& e) {
                plDebug::Error("%s", e.what());
                return 1;
            } catch (...) {
                plDebug::Error("Undefined error!");
                return 1;
            }
            printf("PageID: %s (%08X)\n", page->getLocation().toString().cstr(),
                                          page->getLocation().getPageID().unparse());
            printf("Page Flags: %d\n", page->getLocation().getFlags());
            printf("Age Name: %s\n", page->getAge().cstr());
            printf("Page Name: %s\n", page->getPage().cstr());
            printf("Plasma Version: %s\n", PlasmaVerNames[rm.getVer()]);
            printf("Keyring: %d keys\n", rm.countKeys(page->getLocation().getPageID()));
            printf("Objects Read: %d\n", page->getNumObjects());
            
            rm.setVer(toVer, true);
            char fn[256];
            sprintf(fn, "%s.%s", argv[i], getSuffix(toVer));
            rm.WritePage(fn, page);
            printf("Objects Written: %d\n\n", page->getNumObjects());
            files++;
        }
    }

    printf("Done!  Successfully transcoded %d files!\n", files);
    return 0;
}
