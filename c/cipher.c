// First Variation on Caesar Cipher Code Wars
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char applyShift(char inChar, int shift)
{
    if (inChar > 64 && inChar < 91) {
        inChar = 65 + (((inChar - 65) + shift) % 26);
    } else if (inChar > 96 && inChar < 123) {
        inChar = 97 + (((inChar - 97) + shift) % 26);
    }
    return inChar;
}

char removeShift(char inChar, int shift)
{
    if (inChar > 64 && inChar < 91) {
        inChar = 90 - (((90 - inChar) + shift) % 26);
    } else if (inChar > 96 && inChar < 123) {
        inChar = 122 - (((122 - inChar) + shift) % 26);
    }
    return inChar;
}

int max(int a, int b)
{
    if (b > a) {
        return b;
    } else {
        return a;
    }
}

int min(int a, int b)
{
    if (b > a) {
        return a;
    } else {
        return b;
    }
}

char** movingShift(char* strng, int shift) {
    int length = 0;
    int copyLen = strlen(strng);
    char *strng2 = calloc((copyLen + 1), sizeof(char));
    strng2 = strncpy(strng2, strng, copyLen);
    strng2[copyLen] = '\0';
    for (int i = 0; strng2[i] != '\0'; ++i) {
        strng2[i] = applyShift(strng2[i], shift);
        ++shift;
        ++length;
    }
    int partLength = ceill(((double)length)/5.0) + 1e-9;
    int lengths[5] = {0};
    for (int i = 0; i != 5; ++i) {
        lengths[i] = min(max(0, length - i * partLength), partLength);
    }
    char **strngs = calloc(5, sizeof(char*));
    int sourceIndex = 0;
    for (int i = 0; i != 5; ++i) {
        strngs[i]= calloc((lengths[i] + 1), sizeof(char));
        memcpy(strngs[i], &strng2[sourceIndex], lengths[i]);
        sourceIndex += lengths[i];
        strngs[i][lengths[i]] = '\0';
    }
    free(strng2);
    strng2 = NULL;
    return strngs;
}

char* demovingShift(char** s, int shift) {
    int copyLen = 0;
    for (int i = 0; i != 5; ++i) {
        copyLen += strlen(s[i]) + 1;
    }
    char *res = calloc(copyLen, sizeof(char));
    res[0] = '\0';
    int resLen = 0;
    for (int i = 0; i != 5; ++i) {
        copyLen = strlen(s[i]);
        strncpy(&res[resLen], s[i], copyLen);
        resLen += copyLen;
        res[resLen] = '\0';
    }
    for (int i = 0; res[i] != '\0'; ++i) {
        res[i] = removeShift(res[i], shift);
        ++shift;
    }
    return res;
}

////////////////////////////////////////////////////////////////////////////////
// Main

int main (int argc, char *argv[])
{
    int shift = strtol(argv[1], NULL, 10);

    int copyLen = strlen(argv[2]);
    char *entry = calloc((copyLen + 1), sizeof(char));
    strncpy(entry, argv[2], strlen(argv[2]));
    entry[copyLen] = '\0';
    char **results = movingShift(entry, shift);
    for (int i = 0; i != 5; ++i) {
        printf("%s", results[i]);
        if (i != 4) {
            printf(" ");
        }
    }
    printf("\n");
    char *undone = demovingShift(results, shift);
    printf("%s\n", undone);
    free (undone);
    undone = NULL;
    free (entry);
    entry = NULL;
    for (int i = 0; i != 5; ++i) {
        free(results[i]);
    }
    free(results);
    results = NULL;

    return 0;
}
