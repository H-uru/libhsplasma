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
#include "Debug/hsExceptions.hpp"
#include "Debug/plDebug.h"
#include "Stream/hsStdioStream.h"
#include <string_theory/stdio>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

static void doHelp()
{
    puts("Usage: PageList filename.prp");
    puts("");
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        doHelp();
        return 0;
    }

    std::vector<ST::string> files;

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
            files.push_back(argv[i]);
        }
    }

    for (size_t i=0; i<files.size(); i++) {
        try {
            page = rm.ReadPage(files[i], true);
        } catch (hsException& e) {
            ST::printf(stderr, "{}:{}: {}\n", e.File(), e.Line(), e.what());
            return 1;
        } catch (std::exception& e) {
            ST::printf(stderr, "PrcExtract Exception: {}\n", e.what());
            return 1;
        } catch (...) {
            fputs("Undefined error!\n", stderr);
            return 1;
        }

        std::vector<short> types = rm.getTypes(page->getLocation());

        ST::printf("{} :: {}\n", page->getAge(), page->getPage());

        for (size_t f = 0; f < types.size(); f++) {
            ST::printf("|---[{04X}] {}\n", types[f], pdUnifiedTypeMap::ClassName(types[f]));

            std::vector<plKey> mykeys = rm.getKeys(page->getLocation(), types[f]);

            for (size_t ks = 0; ks < mykeys.size(); ks++) {
                printf("|    |--- {}\n", mykeys[ks]->getName());
            }
        }
    }

    return 0;
}
