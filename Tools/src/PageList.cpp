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

#include "ResManager/plResManager.h"
#include "Debug/hsExceptions.h"
#include "Debug/plDebug.h"
#include "Stream/hsStdioStream.h"
#include <string.h>
#include <time.h>
#include <sys/stat.h>

void doHelp() {
    printf("Usage: PageList filename.prp\n\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        doHelp();
        return 0;
    }

    hsTArray<plString> fFiles;

    plDebug::Init(plDebug::kDLAll);
    plResManager rm;
    plPageInfo* page;
    for (int i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-') argv[i]++;
            if (strcmp(argv[i], "-help") == 0) {
                doHelp();
                return 0;
            }
        } else {
            fFiles.append(argv[i]);
        }
    }

    for (size_t i=0; i<fFiles.getSize(); i++) {
        try {
            page = rm.ReadPage(fFiles[i], true);
        } catch (hsException& e) {
            fprintf(stderr, "%s:%lu: %s\n", e.File(), e.Line(), e.what());
            return 1;
        } catch (std::exception& e) {
            fprintf(stderr, "PrcExtract Exception: %s\n", e.what());
            return 1;
        } catch (...) {
            fprintf(stderr, "Undefined error!\n");
            return 1;
        }

        std::vector<short> types = rm.getTypes(page->getLocation());

        printf("%s :: %s\n", page->getAge().cstr(), page->getPage().cstr());

        for (unsigned int f = 0; f < types.size(); f++) {
            printf("|---[%04X] %s\n", types[f], pdUnifiedTypeMap::ClassName(types[f]));

            std::vector<plKey> mykeys = rm.getKeys(page->getLocation(), types[f]);

            for (unsigned int ks = 0; ks < mykeys.size(); ks++) {
                printf("|    |--- %s\n", mykeys[ks]->getName().cstr());
            }
        }
    }
}
