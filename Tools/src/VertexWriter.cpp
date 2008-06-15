#include <stdio.h>
#include <string.h>
#include "ResManager/plResManager.h"
#include "PRP/Object/plSceneObject.h"
#include "Debug/hsExceptions.h"
#include "Debug/plDebug.h"

void doHelp() {
    printf("Usage: VertexWriter filename.prp objectname\n\n");
}

const char* filenameConvert(char* filename) {
    char* newName = (char*)malloc(strlen(filename)+5);
    strcpy(newName, filename);
    strcat(newName, ".obj");
    return newName;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        doHelp();
        return 0;
    }
    plDebug::Init(plDebug::kDLAll);

    char* filename = argv[1];
    char* fObj = argv[2];

    plResManager rm;
    plPageInfo* page;
    try {
        page = rm.ReadPage(filename);
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

    hsFileStream* OS = new hsFileStream();
    if (!OS->open(filenameConvert(fObj), fmCreate)) {
        fprintf(stderr, "Error opening %s.obj for writing!\n", fObj);
        delete OS;
        return 1;
    }

    OS->writeStr(plString::Format("#Written by libPlasma\n"));

    std::vector<plKey> SObjs = rm.getKeys(page->getLocation(), 0x0001);
    for(size_t i = 0; i < SObjs.size(); i++)
    {
        if(strcmp(SObjs[i]->getName(), fObj) == 0)
        {
            ((plSceneObject*)rm.getObject(SObjs[i]))->VertexWrite(OS);
        }
    }
}

