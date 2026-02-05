#include "converter.h"
#include <stdio.h>
#include <ctype.h>
int charToHex(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;

    return -1;
}

int convertHexFileToBin(const char* input, const char* output)
{
    FILE* in = fopen(input, "r");

    if (!in) 
    {
        perror("Err: fopen input");
        return -1;
    }

    FILE* out = fopen(output, "wb");

    if (!out) 
    {
        perror("Err: fopen output");
        fclose(in);
        return -1;
    }

    int high, low;
    int c;

    while ((c = fgetc(in)) != EOF)
    {
        if (isspace(c))
            continue;

        high = charToHex((char)c);
        if (high < 0 || (c = fgetc(in)) == EOF)
            break;

        low = charToHex((char)c);
        if (low < 0)
            break;

        fputc((high << 4) | low, out);
    }
    
    fclose(in);
    fclose(out);
    
    return 0;
}

int convertBinFileToHex(const char* input, const char* output)
{
    FILE* in = fopen(input, "rb");

    if (!in) 
    {
        perror("Err: fopen input");
        return -1;
    }

    FILE* out = fopen(output, "w");

    if (!out) 
    {
        perror("Err: fopen output");
        fclose(in);
        return -1;
    }
    int byte;

    while ((byte = fgetc(in)) != EOF)
        fprintf(out, "%02X", (unsigned char)byte);

    fclose(in);
    fclose(out);
    return 0;
}