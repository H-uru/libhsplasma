#include <stdio.h>
#include "PubUtilLib/plResMgr/plResManager.h"

int main(int argc, char** argv) {
    plResManager rm;

    for (int i=1; i<argc; i++) {
        plPageSettings* page = rm.ReadPage(argv[i]);
        printf("PageID: %s (%08X)\n", page->pageID.toString(), page->pageID.unparse());
        printf("Page Type: %d\n", page->pageType);
        printf("Age Name: %s\n", page->ageName);
        printf("Page Name: %s\n", page->pageName);
        printf("Plasma Version: %d\n", page->ver);
        printf("Keyring: %d keys\n", rm.keys.countKeys(page->pageID));
        printf("Objects Read: %d\n", page->nObjects);
        
        //rm.setVer(pvPots, true);
        char fn[256];
        sprintf(fn, "%s.conv", argv[i]);
        rm.WritePage(fn, page);
        printf("Objects Written: %d\n\n", page->nObjects);
    }

    printf("Done!  Successfully transcoded %d files!", argc-1);
    getchar();
    return 0;
}
