#include "converter.h"
#include <stdio.h>
#include <ctype.h>

const signed char hexTable[256] = 
{
    ['1'] = 1, ['2'] = 2, ['3'] = 3, ['4'] = 4, ['5'] = 5,    
    ['6'] = 6,  ['7'] = 7, ['8'] =8, ['9'] = 9, ['a'] = 10, ['b'] = 11,    
    ['c'] = 12,  ['d'] = 13, ['e'] = 14, ['f'] = 15, 
    ['A'] = 10, ['B'] = 11, ['C'] = 12,  ['D'] = 13, ['E'] = 14, ['F'] = 15, 
};

int charToHex(unsigned char c)
{
    if (c == '0') return 0;
    return hexTable[c] ? hexTable[c] : -1;
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