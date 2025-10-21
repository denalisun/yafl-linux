#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    char *playPath = NULL;
    size_t allTweaksSize = 1;
    size_t allTweaksUsed = 0;
    char **allTweaks = (char**)calloc(allTweaksSize, sizeof(char*));
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--play") == 0) {
            playPath = argv[i+1];
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-tweak") == 0) {
            if (allTweaksUsed == allTweaksSize) {
                allTweaksSize++;
                allTweaks = realloc(allTweaks, sizeof(char*) * allTweaksSize);
            }
            allTweaks[allTweaksUsed] = argv[i+1];
            allTweaksUsed++;
        }
    }

    if (playPath != NULL) {
        printf("%s\n", playPath);
    }
    for (int i = 0; i < allTweaksUsed; i++) {
        printf("%d  \"%s\"\n", i, allTweaks[i]);
    }
    return 0;
}
