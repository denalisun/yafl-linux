#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* convert_path_to_windows(char* path) {
    char* newPath = (char*)malloc(strlen(path)+3);
    sprintf(newPath, "Z:%s", path);
    for (int i = 0; i < strlen(newPath); i++) {
        if (newPath[i] == '/') newPath[i] = '\\';
    }
    return newPath;
}

char* create_args(char *playPath, char **allTweaks, size_t allTweaksUsed, bool bIsServer, char* redirectPath) {
    size_t len = strlen(playPath) + 7 + 1;
    char* r = (char*)calloc(len, sizeof(char)); 
    sprintf(r, "-p \"%s\" ", convert_path_to_windows(playPath));
    if (redirectPath != NULL) {
        char* redirectArg = (char*)calloc(strlen(redirectPath) + 15, sizeof(char));
        sprintf(redirectArg, "--redirect \"%s\" ", redirectPath);
        r = realloc(r, len + strlen(redirectArg)+1);
        len += strlen(redirectArg)+1;
        strcat(r, redirectArg);
    }
    for (size_t i = 0; i < allTweaksUsed; i++) {
        size_t tweakLen = strlen(allTweaks[i]) + 6 + 1;
        char* tweakArg = (char*)calloc(tweakLen, sizeof(char));
        sprintf(tweakArg, "-t \"%s\" ", convert_path_to_windows(allTweaks[i]));
        r = realloc(r, len + tweakLen);
        len += tweakLen;
        strcat(r, tweakArg);
    }
    if (bIsServer) {
        size_t serverLen = 3;
        r = realloc(r, len + serverLen);
        strcat(r, "-s");
    }
    return r;
}

int main(int argc, char **argv) {
    char *playPath = NULL;
    char *redirectPath = NULL;
    size_t allTweaksSize = 1;
    size_t allTweaksUsed = 0;
    char **allTweaks = (char**)calloc(allTweaksSize, sizeof(char*));
    bool bIsServer = false;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--play") == 0) {
            playPath = argv[i+1];
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--tweak") == 0) {
            if (allTweaksUsed == allTweaksSize) {
                allTweaksSize++;
                allTweaks = realloc(allTweaks, sizeof(char*) * allTweaksSize);
            }
            allTweaks[allTweaksUsed] = argv[i+1];
            allTweaksUsed++;
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--server") == 0) {
            bIsServer = true;
        } else if (strcmp(argv[i], "--redirect") == 0) {
            redirectPath = argv[i+1];
        }
    }

    char* usedArgs = create_args(playPath, allTweaks, allTweaksUsed, bIsServer, redirectPath);
    printf("%s\n", usedArgs);
    size_t len = 17 + (strlen(usedArgs) + 1);
    char* wineCmd = (char*)calloc(len, sizeof(char));
    sprintf(wineCmd, "wine ./yafl.exe %s", usedArgs);
    
    system(wineCmd);

    return 0;
}
