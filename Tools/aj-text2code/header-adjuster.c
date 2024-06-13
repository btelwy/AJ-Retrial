#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header-adjuster.h"

int main()
{
    FILE* fptrOriginal = fopen("C:\\Users\\ben\\Desktop\\AJ-Retrial\\Helper programs\\aj-text2code\\header.bin","rb");
    FILE* fptrNew = fopen("C:\\Users\\ben\\Desktop\\AJ-Retrial\\Helper programs\\aj-text2code\\adjustedHeader.bin","wb");

    int delta = 0x4; //the amount to add to each offset in the header; change this value

    char* first4Bytes[5]; //only four bytes needed, but a fifth for the terminating zero

    fseek(fptrOriginal, 0, SEEK_SET);
    fread(first4Bytes, 4, 1, fptrOriginal); //read the first four bytes into numSections
    fwrite(first4Bytes, 4, 1, fptrNew); //copy them over to the new header

    char* ptr;
    long numOffsets = strtol(first4Bytes, &ptr, 16); //convert those four bytes into a long


    //now read all the offsets from the original file
    char* offsets[1000][5]; //2D array to hold the offsets, arbitrary large number
    int* intOffsets[1000]; //array to hold the offsets as ints, plus the delta
    for (int i = 0; i < numOffsets * 4; i += 4)
    {
        fseek(fptrOriginal, i + 4, SEEK_SET); //make sure the marker is at the proper position
        fread(offsets[i/4], 4, 1, fptrOriginal); //i/4 is the correct array to put the next four bytes in
        intOffsets[i/4] = strtol(offsets[i/4], &ptr, 16) + delta; //convert those four bytes to an int, add delta
    }

    //now write the rest of the new header
    for (int i = 0; i < numOffsets * 4; i += 4)
    {
        fseek(fptrNew, i + 4, SEEK_SET); //make sure the marker is at the proper position
        fwrite(intOffsets[i/4], 4, 1, fptrNew); //i/4 is the correct array to put the next four bytes in
    }

    fclose(fptrOriginal);
    fclose(fptrNew);

    return 0;
}