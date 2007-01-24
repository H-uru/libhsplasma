#include <stdio.h>
#include "PubUtilLib/plResMgr/plResManager.h"

int main(int argc, char** argv) {
    plResManager rm;

    for (int i=1; i<argc; i++) {
        plAgeSettings* age = rm.ReadPage(argv[i]);
        printf("PageID: %d.%d (%08X)\n", age->pageID.getSeqPrefix(),
                                  age->pageID.getPageNum(),
                                  age->pageID.unparse());
        printf("Page Type: %d\n", age->pageType);
        printf("Age Name: %s\n", age->ageName);
        printf("Page Name: %s\n", age->pageName);
        printf("Plasma Version: %d\n", age->ver);
        printf("Keyring: %d keys\n", rm.keys.countKeys(age->pageID));
        printf("Objects Read: %d\n\n", age->nObjects);
    }

    printf("Done!  Successfully parsed %d files!", argc-1);
    getchar();
    return 0;
}

