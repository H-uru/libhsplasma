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
#include <Debug/hsExceptions.hpp>
#include <Stream/hsStdioStream.h>
#include <Debug/plDebug.h>
#include <string_theory/stdio>
#include <cstring>
#include <time.h>
#ifdef _WIN32
  #include <windows.h>
  #define SLASH '\\'
  #define SLASH_S "\\"
#else
  #include <unistd.h>
  #define SLASH '/'
  #define  SLASH_S "/"
#endif
#include <sys/stat.h>

static void doHelp()
{
    puts("Usage: PrcExtract [options] filename.prp");
    puts("");
    puts("Objects are written to Age_PRC\\filename.prc");
    puts("");
    puts("options:");
    puts("    -vtx   include vertex data");
    puts("    -tex   include texture data");
    puts("    -help  display this help message");
    puts("");
}

static ST::string filenameConvert(const ST::string& filename)
{
    ST::string name = filename;
    if (name.find_last('.') >= 0)
        name = name.left(name.find_last('.')) + ".prc";
    else
        name += ".prc";
    if (name.find_last(SLASH) >= 0)
        return name.substr(name.find_last(SLASH) + 1);
    else
        return name;
}

static ST::string getOutputDir(const ST::string& filename, plPageInfo* page)
{
    ST::string name = filename;
    if (name.find_last(SLASH) >= 0)
        name = name.left(name.find_last(SLASH) + 1);
    else
        name = "";
    return name + page->getAge() + "_PRC" SLASH_S;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        doHelp();
        return 0;
    }

    std::vector<ST::string> fFiles;

    plDebug::Init(plDebug::kDLAll);
    plResManager rm;
    plPageInfo* page;
    ST::string outDir, outFile;
    bool exVtx = true, exTex = true, noHdr = false;
    for (int i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-')
                argv[i]++;
            if (strcmp(argv[i], "-help") == 0) {
                doHelp();
                return 0;
            } else if (strcmp(argv[i], "-vtx") == 0) {
                exVtx = false;
                fputs("Warning: Including Vertex data\n", stderr);
            } else if (strcmp(argv[i], "-tex") == 0) {
                exTex = false;
                fputs("Note: Texture data unsupported. -tex will "
                      "be ignored for this export\n", stderr);
            } else if (strcmp(argv[i], "-nohdr") == 0) {
                noHdr = true;
            } else {
                ST::printf(stderr, "Error: Unrecognized option %s\n", argv[i]);
                return 1;
            }
        } else {
            fFiles.push_back(argv[i]);
        }
    }

    for (size_t i=0; i<fFiles.size(); i++) {
        try {
            page = rm.ReadPage(fFiles[i]);
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
        outDir = getOutputDir(fFiles[i], page);
        outFile = outDir + filenameConvert(fFiles[i]);
      #ifdef _WIN32
        CreateDirectoryW(outDir.to_wchar().data(), nullptr);
      #else
        mkdir(outDir.c_str(), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
      #endif

        ST::printf("Writing {}\n", outFile);
        hsFileStream S;
        if (!S.open(outFile, fmWrite)) {
            ST::printf(stderr, "Error opening {} for writing!\n", outFile);
            return 1;
        }
        S.setVer(rm.getVer());
        pfPrcHelper prc(&S);
        if (exVtx)
            prc.exclude(pfPrcHelper::kExcludeVertexData);
        if (exTex)
            prc.exclude(pfPrcHelper::kExcludeTextureData);
        if (!noHdr) {
            prc.writeComment("Generator: PrcExtract");
            prc.writeComment(("Source: " + fFiles[i]).c_str());
            time_t ts = time(nullptr);
            char buf[256];
            strftime(buf, 256, "Created: %Y/%m/%d %H:%M:%S", localtime(&ts));
            prc.writeComment(buf);
            S.writeStr("\n");
        }
        try {
            rm.WritePagePrc(&prc, page);
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

        S.close();
    }

    return 0;
}
