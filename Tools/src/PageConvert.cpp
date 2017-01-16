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

#include <stdio.h>
#include <string.h>
#include "ResManager/plResManager.h"
#include "Debug/hsExceptions.hpp"
#include "Debug/plDebug.h"

const char* getSuffix(PlasmaVer pv) {
    switch (pv) {
    case PlasmaVer::pvPrime:       return "prime";
    case PlasmaVer::pvPots:        return "pots";
    case PlasmaVer::pvMoul:        return "moul";
    case PlasmaVer::pvEoa:         return "eoa";
    case PlasmaVer::pvHex:         return "hex";
    case PlasmaVer::pvUniversal:   return "universal";
    default:            return "err";
    }
}

const char* getVerName(PlasmaVer pv) {
    switch (pv) {
    case PlasmaVer::pvPrime:       return "Prime";
    case PlasmaVer::pvPots:        return "PotS";
    case PlasmaVer::pvMoul:        return "MOUL";
    case PlasmaVer::pvEoa:         return "EoA";
    case PlasmaVer::pvHex:         return "HexIsle";
    case PlasmaVer::pvUniversal:   return "Universal";
    default:            return "Unknown";
    }
}

void doHelp() {
    printf("PRP Page Converter 1.0\nBy Michael Hansen\n\n");
    printf("Usage:  PageConvert [-to???] [-help] filename [filename] [...]\n\n");
    printf("  -toprime  Converts to Prime format (63.11) (Default)\n");
    printf("  -topots   Converts to Path of the Shell format (63.12)\n");
    printf("  -tomoul   Converts to Uru Live format\n");
    printf("  -toeoa    Converts to Myst V: End of Ages format\n");
    printf("  -tohex    Converts to Hex Isle format\n");
    printf("  -touniv   Converts to Universal format\n");
    printf("  -help     Displays this screen\n\n");
}

int main(int argc, char** argv) {
    plResManager rm;
    plDebug::Init(plDebug::kDLAll);

    PlasmaVer toVer = PlasmaVer::pvPrime;
    int files = 0;

    if (argc == 1) {
        doHelp();
        return 0;
    }

    for (int i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-') argv[i]++;
            if (strcmp(argv[i], "-toeoa") == 0)
                toVer = PlasmaVer::pvEoa;
            else if (strcmp(argv[i], "-toprime") == 0)
                toVer = PlasmaVer::pvPrime;
            else if (strcmp(argv[i], "-topots") == 0)
                toVer = PlasmaVer::pvPots;
            else if (strcmp(argv[i], "-tomoul") == 0)
                toVer = PlasmaVer::pvMoul;
            else if (strcmp(argv[i], "-tohex") == 0)
                toVer = PlasmaVer::pvHex;
            else if (strcmp(argv[i], "-touniv") == 0)
                toVer = PlasmaVer::pvUniversal;
            else if (strcmp(argv[i], "-help") == 0) {
                doHelp();
                return 0;
            } else {
                plDebug::Error("Error: Unrecognized option {}", argv[i]);
                return 1;
            }
        } else {
            plPageInfo* page;
            try {
                page = rm.ReadPage(argv[i]);
            } catch (const hsException& e) {
                plDebug::Error("{}:{}: {}", e.File(), e.Line(), e.what());
                return 1;
            } catch (const std::exception& e) {
                plDebug::Error("{}", e.what());
                return 1;
            } catch (...) {
                plDebug::Error("Undefined error!");
                return 1;
            }
            printf("PageID: %s (%08X)\n", page->getLocation().toString().c_str(),
                                          page->getLocation().unparse());
            printf("Page Flags: %d\n", page->getLocation().getFlags());
            printf("Age Name: %s\n", page->getAge().c_str());
            printf("Page Name: %s\n", page->getPage().c_str());
            printf("Plasma Version: %s\n", getVerName(rm.getVer()));
            printf("Keyring: %d keys\n", rm.countKeys(page->getLocation()));
            printf("Objects Read: %d\n", page->getNumObjects());

            rm.setVer(toVer, true);
            char fn[256];
            snprintf(fn, 256, "%s.%s", argv[i], getSuffix(toVer));
            rm.WritePage(fn, page);
            printf("Objects Written: %d\n\n", page->getNumObjects());
            files++;
        }
    }

    printf("Done!  Successfully transcoded %d files!\n", files);
    return 0;
}
