#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv) {
    char volName[256];
    DWORD serialNum, maxComponentLen, FSFlags;
    char FSName[256];
    char DriveName[4];
    
    DWORD Drives = GetLogicalDrives();
    Drives &= (Drives << 2);
    printf("Drive Mask: %x\n\n", Drives);
    
    printf("Drive\tS/N      MCL      Flags      Name (Type)\n");
    printf("--------------------------------------------------\n");
    for (char D='A'; D<='Z'; D++) {
        sprintf(DriveName, "%c:\\", D);
        if (GetVolumeInformation(DriveName, volName, 255,
                            &serialNum, &maxComponentLen, &FSFlags,
                            FSName, 255))
            printf("%c:\t%08x %08x %08x : %s (%s)\n", D,
                   serialNum, maxComponentLen, FSFlags, volName, FSName);
    }
    printf("\n");
    
    return 0;
}
