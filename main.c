#include <stdio.h>
#include <string.h>
#include "converter.h"

typedef enum
{
    ConvertNone = 0,
    ConvertHexToBin,
    ConvertBinToHex,
    Help,
} Mode;

#define MAX_LEN 1024
Mode parseMode(const char* arg);
int buildOutputFilename(char *out, int size, const char *input, Mode mode);
void showHelpInfo();

int main(int argc, char *argv[])
{
    Mode mod = parseMode(argv[1]);
    char outputName[MAX_LEN];

    switch (mod)
    {
    case ConvertHexToBin:    
        if (!buildOutputFilename(outputName, sizeof(outputName), argv[2], mod))
            return -1;
        
        return convertHexFileToBin(argv[2], outputName);
            
        break;
    case ConvertBinToHex:    
            if (!buildOutputFilename(outputName, sizeof(outputName), argv[2], mod))
                return -1;
        
        return convertBinFileToHex(argv[2], outputName);        
        break;
    case Help:
        showHelpInfo();
        break;
    default:
        printf("error: unknown parameter\n");
        break;
    }

    return 0;
}

void showHelpInfo()
{
    printf("HEX To BIN converter\n");
    printf("-a Convert ACII HEX to BIN\n");
    printf("-b Convert BIN to ACII HEX\n");
    printf("-h show this help info\n");
}

Mode parseMode(const char* arg)
{
    if (strcmp(arg, "-a") == 0)
        return ConvertHexToBin;

    if (strcmp(arg, "-b") == 0)
        return ConvertBinToHex;
    
    if (strcmp(arg, "-h") == 0)
        return Help;
    
    return ConvertNone;
}       

int buildOutputFilename(char* out, int size, const char* input, Mode mode)
{
    const char *suffix = (mode == ConvertHexToBin) ? ".bin" : ".hex";
    /*const char *dot = strrchr(input, '.');
    int len = (int)strlen(dot);
    
    memcpy(out, input, len);
    out[len] = '\0';
    strcat(out, suffix);

    return 1;
    */
    return snprintf(out, size, "%s%s", input, suffix) < (int)size;
}