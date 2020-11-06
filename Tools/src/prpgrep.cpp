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
#include <ResManager/pdUnifiedTypeMap.h>
#include <Stream/pfPrcHelper.h>
#include <Stream/hsRAMStream.h>
#include <PRP/KeyedObject/hsKeyedObject.h>
#include <string_theory/stdio>
#include <list>

static char lnbuf[4096];
static char* lnbuf_ptr = &lnbuf[4096];

static ST::string GetLine(hsStream* S)
{
    if (lnbuf_ptr >= &lnbuf[4096]) {
        size_t len = S->size() - S->pos();
        if (len > 4096)
            len = 4096;
        S->read(len, lnbuf);
        if (len < 4096)
            lnbuf[len] = 0;
        lnbuf_ptr = lnbuf;
    }

    char* bp = lnbuf_ptr;
    while (true) {
        if (bp >= &lnbuf[4096]) {
            ST::string prefix(lnbuf_ptr, bp - lnbuf_ptr);
            lnbuf_ptr = &lnbuf[4096];
            return prefix + GetLine(S);
        } else if (*bp == '\n' || *bp == 0) {
            ST::string ln(lnbuf_ptr, bp - lnbuf_ptr);
            lnbuf_ptr = bp + 1;
            return ln;
        }
        bp++;
    }

    // Should never get here...
    return ST::string();
}

static void DoSearch(hsStream* S, const ST::string& pattern,
                     const ST::string& filename, const plKey& key)
{
    unsigned int ln = 1;
    lnbuf_ptr = &lnbuf[4096];
    while (!S->eof()) {
        ST::string text = GetLine(S);
        if (text.find(pattern) >= 0) {
            // Strip initial whitespace
            const char* txtout = text.c_str();
            while (*txtout == ' ' || *txtout == '\t')
                txtout++;
            ST::printf("{}:[{}]{}:{}: {}\n", filename,
                       pdUnifiedTypeMap::ClassName(key->getType()),
                       key->getName(), ln, txtout);
        }
        ln++;
    }
}

static void doHelp(const char* progname)
{
    ST::printf("Usage: {} pattern file1 [file2 [...]]\n\n", progname);
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        doHelp(argv[0]);
        return 1;
    }

    const char* pattern = argv[1];
    std::list<ST::string> files;
    for (int i=2; i<argc; i++)
        files.push_back(argv[i]);

    plResManager mgr;
    std::list<ST::string>::iterator it;
    for (it = files.begin(); it != files.end(); it++) {
        plPageInfo* page;
        try {
            page = mgr.ReadPage(*it);
        } catch (hsException& ex) {
            ST::printf(stderr, "Error reading {}: {}\n", *it, ex.what());
            continue;
        } catch (...) {
            ST::printf(stderr, "Undefined error reading {}\n", *it);
            continue;
        }

        std::vector<short> types = mgr.getTypes(page->getLocation());
        std::vector<short>::iterator ti;
        for (ti = types.begin(); ti != types.end(); ti++) {
            std::vector<plKey> keys = mgr.getKeys(page->getLocation(), *ti);
            std::vector<plKey>::iterator ki;
            for (ki = keys.begin(); ki != keys.end(); ki++) {
                hsRAMStream prcOut;
                pfPrcHelper prc(&prcOut);
                prc.exclude(pfPrcHelper::kExcludeTextureData);
                prc.exclude(pfPrcHelper::kExcludeVertexData);
                hsKeyedObject* obj = GET_KEY_OBJECT((*ki), hsKeyedObject);
                if (obj == nullptr)
                    continue;
                obj->prcWrite(&prc);
                prcOut.rewind();
                DoSearch(&prcOut, pattern, *it, *ki);
            }
        }
        mgr.UnloadPage(page->getLocation());
    }

    return 0;
}
