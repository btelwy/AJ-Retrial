#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "aj-text2code.h"

boolean includeHeader = FALSE; //determines whether to do the extra step of adding the header
int sectionCount = 0; //global variable to count number of sections
int sectionOffsets[500]; //global array to hold offsets of sections, of arbitrary size
int offsetIndex = 0; //index to keep track of position in array

int main() {
    FILE *fptrRead;
    FILE *fptrWrite;

    fptrRead = fopen("C:\\Users\\ben\\Desktop\\AJ-Retrial\\Helper programs\\aj-text2code\\Unfinished\\credits.txt","r");
    //open script.txt for reading from

    int bufferSize = 100; //default value
    char readBuffer[300]; //the array of chars used to store what's read from the file each line

    fptrWrite = fopen("C:\\Users\\ben\\Desktop\\AJ-Retrial\\Helper programs\\aj-text2code\\code.bin","wb+"); 
    //open code.txt for writing to

    int lineCount = countLines(fptrRead);

    int charCount[lineCount - 1];
    int *charCountPtr = lineCharCount(fptrRead, lineCount - 1);

    for (int i = 0; i < lineCount; i++)
    {
        charCount[i] = *(charCountPtr + i);
    }


    int lineStart = 0; //offset in file of line start


    if(fptrRead != NULL) //if file can be read
    {
        for(int i = 0; i < lineCount; i++) //read one line of the file at a time until EOF
        {
            fseek(fptrRead, lineStart, SEEK_SET);
            fgets(readBuffer, charCount[i] + 1, fptrRead);

            printf("%s", readBuffer); //print line to terminal

            convertLine(readBuffer, charCount[i], fptrWrite);

            lineStart = 0;
            for (int j = 0; j <= i; j++)
                lineStart += charCount[j] + 2;
        }
    }

    else
        printf("\nFile to be read couldn't be opened.");
    
    if (includeHeader)
    {
        addHeader(fptrWrite);
    }

    fclose(fptrRead);
    fclose(fptrWrite);

    printf("\nEverything finished.");
    return 0;
}

int countLines(FILE* pointer)
{
    char c;
    int count = 1; //defaults to 1, though could be entirely blank

    for (c = getc(pointer); c != EOF; c = getc(pointer))
    {
        if (c == '\n')
            count++;
    }

    fseek(pointer, 0, SEEK_SET);
    return count;
}

int* lineCharCount(FILE* pointer, int length)
{
    char c;
    int count = 0;
    static int countArr[1000];

    for (int i = 0; i <= length; i++)
    {
        for (c = getc(pointer); c != '\n' && c != EOF; c = getc(pointer))
            count++;
        
        countArr[i] = count;
        count = 0; //reset to 0 for next line, although probably not necessary
    }
    
    fseek(pointer, 0, SEEK_SET);

    int* arrayPointer = &countArr[0];
    return arrayPointer;
}

void convertLine(char line[], int arrLength, FILE* pointer)
    {
        int writeBuffer = 0;

        for (int i = 0; i < arrLength; i++)
        {
            switch(line[i])
            {
                case '0':
                writeBuffer = 0x0090;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '1':
                writeBuffer = 0x0091;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '2':
                writeBuffer = 0x0092;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '3':
                writeBuffer = 0x0093;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '4':
                writeBuffer = 0x0094;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '5':
                writeBuffer = 0x0095;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '6':
                writeBuffer = 0x0096;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '7':
                writeBuffer = 0x0097;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '8':
                writeBuffer = 0x0098;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '9':
                writeBuffer = 0x0099;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;
                
                case 'A':
                writeBuffer = 0x009A;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'B':
                writeBuffer = 0x009B;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'C':
                writeBuffer = 0x009C;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'D':
                writeBuffer = 0x009D;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'E':
                writeBuffer = 0x009E;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'F':
                writeBuffer = 0x009F;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'G':
                writeBuffer = 0x00A0;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'H':
                writeBuffer = 0x00A1;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'I':
                writeBuffer = 0x00A2;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'J':
                writeBuffer = 0x00A3;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'K':
                writeBuffer = 0x00A4;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'L':
                writeBuffer = 0x00A5;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'M':
                writeBuffer = 0x00A6;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'N': 
                writeBuffer = 0x00A7;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'O':
                writeBuffer = 0x00A8;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'P':
                writeBuffer = 0x00A9;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'Q':
                writeBuffer = 0x00AA;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'R':
                writeBuffer = 0x00AB;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'S':
                writeBuffer = 0x00AC;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'T':
                writeBuffer = 0x00AD;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'U':
                writeBuffer = 0x00AE;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'V': 
                writeBuffer = 0x00AF;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'W':
                writeBuffer = 0x00B0;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'X':
                writeBuffer = 0x00B1;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;
                
                case 'Y':
                writeBuffer = 0x00B2;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'Z':
                writeBuffer = 0x00B3;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'a':
                writeBuffer = 0x00B4;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'b':
                writeBuffer = 0x00B5;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'c':
                writeBuffer = 0x00B6;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'd':
                writeBuffer = 0x00B7;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'e':
                writeBuffer = 0x00B8;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'f':
                writeBuffer = 0x00B9;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'g':
                writeBuffer = 0x00BA;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'h':
                writeBuffer = 0x00BB;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'i':
                writeBuffer = 0x00BC;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'j':
                writeBuffer = 0x00BD;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'k':
                writeBuffer = 0x00BE;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'l':
                writeBuffer = 0x00BF;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'm':
                writeBuffer = 0x00C0;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'n':
                writeBuffer = 0x00C1;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'o':
                writeBuffer = 0x00C2;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'p':
                writeBuffer = 0x00C3;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'q':
                writeBuffer = 0x00C4;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'r':
                writeBuffer = 0x00C5;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 's':
                writeBuffer = 0x00C6;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 't':
                writeBuffer = 0x00C7;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'u':
                writeBuffer = 0x00C8;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'v':
                writeBuffer = 0x00C9;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'w':
                writeBuffer = 0x00CA;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'x':
                writeBuffer = 0x00CB;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'y':
                writeBuffer = 0x00CC;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case 'z':
                writeBuffer = 0x00CD;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                //add support for numbers

                case ' ':
                writeBuffer = 0x018F;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '.':
                writeBuffer = 0x0171;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '?':
                writeBuffer = 0x00CF;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '!':
                writeBuffer = 0x00CE;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case ',':
                writeBuffer = 0x017F;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '\'':
                writeBuffer = 0x0183;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '"':
                writeBuffer = 0x0191;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '-':
                writeBuffer = 0x0184;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '&':
                writeBuffer = 0x018C;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '*':
                writeBuffer = 0x0182;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case ':':
                writeBuffer = 0x017D;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                //find semicolon

                case '(':
                writeBuffer = 0x0175;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case ')':
                writeBuffer = 0x0176;
                fwrite(&writeBuffer, 2, 1, pointer);
                break;

                case '{':
                //the function would also increase i so it's on the closing brace, then the for loop
                //will increment it past it
                //there won't be spaces between commands
                i = readCommand(line, arrLength, i, pointer);
                break;

                default: //if no match
                break;
            }

            if (i == -1)
                break;
        }
    }



    int readCommand(char line[], int arrLength, int index, FILE* pointer)
    {
        int writeBuffer = 0;
        int startIndex = index + 1; //location right after opening brace
        
        //find closing brace; since this function is called upon reading an opening brace
        while (line[index] != '}' && index < arrLength && line[index] != EOF)
            index++;
        
        //index is now set to location of closing brace, startIndex to opening
        char command[index - startIndex + 1]; //excludes both braces
        command[index - startIndex] = '\0';

        for (int i = startIndex; i < index; i++)
            command[i - startIndex] = line[i]; //make command a substring of line that holds the command between the braces

        int paramCount = 0; //number of paramters in the command, from 0 to probably 2
        int colonLoc = 0; //index of first colon in command string, if present

        //check how many colons are in the command string, since colons indicate parameters
        for (int i = 0; i < index - startIndex - 1; i++)
        {
            if (command[i] == ':')
            {
                paramCount++;
                colonLoc = i;
                break; //if there are two colons, only find the first one
            }
        }

        int paramLength = index - colonLoc;
        char param[paramLength + 1]; //string for parameter, with room for terminating zero

        if (paramCount == 1)
        {
            for (int i = colonLoc + 1; i < index; i++) //from the colon to the end of the command
                param[i - (colonLoc + 1)] = command[i]; //fill param string
            
            param[paramLength] = '\0'; //add terminating zero
        }

        char shortCommand[colonLoc + 1];

        if (colonLoc != 0)
        {
            for (int i = 0; i < colonLoc; i++)
                shortCommand[i] = command[i];
            
            shortCommand[colonLoc] = '\0';
        }
        

        //for commands that take a parameter, make a function and pass it the command and parameter strings
        if(strcmp(command, "sectionStart") == 0)
        {
            if (includeHeader) //if header will be added at end, collect data for it
            {
                //pointer refers to the writing file, but it's the same result as the reading file would be
                
                if (pointer == NULL)
                {
                    printf("oops");
                }

                sectionOffsets[offsetIndex] = ftello(pointer);
                offsetIndex++;
                sectionCount++;
            }

            writeBuffer = 0x0000;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
    
        else if(strcmp(command, "sectionEnd") == 0)
        {
            writeBuffer = 0x000D;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        else if(strcmp(command, "newLine") == 0)
        {
            writeBuffer = 0x0001;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        else if(strcmp(command, "textboxEnd") == 0)
        {
            writeBuffer = 0x002D;
            fwrite(&writeBuffer, 2, 1, pointer); //check difference with 0200
        }

        else if(strcmp(command, "textboxEndForced") == 0)
        {
            writeBuffer = 0x002E;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        else if(strcmp(command, "spriteVanish") == 0)  //doesn't seem to work
        {
            writeBuffer = 0x0031;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        else if(strcmp(command, "reset") == 0) //technically the "beat game" command, unlocks all episodes and returns to title screen
        {
            //620004000F00 before 49001500 prevents a softlock on real hardware
            
            writeBuffer = 0x0062;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x000F0004;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x00150049;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if(strcmp(command, "guiltyReset") == 0) //courtroom doors close, returns to title screen
        {
            //adding this first part just because it works for the other reset and is harmless anyway
            writeBuffer = 0x0062;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x000F0004;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x0024;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        else if(strcmp(command, "musicResume") == 0)
        {
            long writeBuffer = 0x00000023;
            fwrite(&writeBuffer, 4, 1, pointer);

            //FF probably stands for the previously playing song
            music("previous", pointer);
        }

        else if(strcmp(command, "typewriter") == 0) //only applies to the next textbox
        {
            writeBuffer = 0x00020030;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if(strcmp(command, "hideBox") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        else if(strcmp(command, "halt") == 0)
        {
            writeBuffer = 0x0015;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        else if(strcmp(command, "saveScreen") == 0)
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        else if(strcmp(command, "initialize") == 0) //to be used after section start
        {
            //print 620004000100740002000000
            //the game softlocks without these two commands, for some reason
            //or at least without one of them, but both doesn't hurt
            writeBuffer = 0x00040062;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x00740001;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x00000002;
            fwrite(&writeBuffer, 4, 1, pointer);
        } 

        else if (strcmp(shortCommand, "textColor") == 0)
            textColor(param, pointer);
        
        else if (strcmp(shortCommand, "wait") == 0)
            wait(param, pointer);

        else if (strcmp(shortCommand, "waitNoAnim") == 0)
            waitNoAnim(param, pointer);
        
        else if (strcmp(shortCommand, "textSpeed") == 0)
            textSpeed(param, pointer);
        
        else if (strcmp(shortCommand, "twoChoices") == 0)
            twoChoices(param, pointer);

        else if (strcmp(shortCommand, "threeChoices") == 0)
            threeChoices(param, pointer);

        else if (strcmp(shortCommand, "spriteFade") == 0)
            spriteFade(param, pointer);

        else if (strcmp(shortCommand, "name") == 0)
            name(param, pointer);
        
        else if (strcmp(shortCommand, "charAnimation") == 0)
            charAnimation(param, pointer);

        else if (strcmp(shortCommand, "centerText") == 0)
            centerText(param, pointer);
        
        else if (strcmp(shortCommand, "textbox") == 0)
            textbox(param, pointer);

        else if (strcmp(shortCommand, "courtRecordButton") == 0)
            courtRecordButton(param, pointer);
        
        else if (strcmp(shortCommand, "music") == 0)
            music(param, pointer);

        else if (strcmp(shortCommand, "sound") == 0)
            sound(param, pointer);

        else if (strcmp(shortCommand, "flash") == 0)
            flash(param, pointer);
        
        else if (strcmp(shortCommand, "shake") == 0)
            shake(param, pointer);

        else if (strcmp(shortCommand, "voiceSFX") == 0)
            voiceSFX(param, pointer);

        else if (strcmp(shortCommand, "musicFade") == 0)
            musicFade(param, pointer);
        
        else if (strcmp(shortCommand, "background") == 0)
            background(param, pointer);

        else if (strcmp(shortCommand, "setFlag") == 0)
            setFlag(param, pointer);

        else if (strcmp(shortCommand, "screenFade") == 0)
            screenFade(param, pointer);

        else if (strcmp(shortCommand, "jump") == 0)
            jump(param, pointer);

        else if (strcmp(shortCommand, "monochrome") == 0)
            monochrome(param, pointer);

        else if (strcmp(shortCommand, "showBox") == 0)
            showBox(param, pointer);

        else if (strcmp(shortCommand, "psycheLocks") == 0)
            psycheLocks(param, pointer);

        if (line[index] != EOF)
        {
            return index; //update i in for loop of convertLine function
        }
        else
        {
            return -1;
        }
    }


    void textColor(char parameter[], FILE* pointer)
    {
        long writeBuffer = 0;

        if (strcmp(parameter, "white") == 0)
        {
            writeBuffer = 0x00000003;
            fwrite(&writeBuffer, 4, 1, pointer);
        }
        else if (strcmp(parameter, "red") == 0)
        {
            writeBuffer = 0x00010003;
            fwrite(&writeBuffer, 4, 1, pointer);
        }
        else if (strcmp(parameter, "blue") == 0)
        {
            writeBuffer = 0x00020003;
            fwrite(&writeBuffer, 4, 1, pointer);
        }
        else if (strcmp(parameter, "green") == 0)
        {
            writeBuffer = 0x00030003;
            fwrite(&writeBuffer, 4, 1, pointer);
        }
    }

    void wait(char parameter[], FILE* pointer)
    {
        //the parameter will be a hex number, but as a string
        //it might also be "short" for a comma wait, and "normal" for a period wait

        long writeBuffer = 0x000C;
        fwrite(&writeBuffer, 2, 1, pointer);

        if (strcmp(parameter, "short") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "normal") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        
        //if the parameter is a number; must be two digits
        else
        {
            char *ptr;
            writeBuffer = strtol(parameter, &ptr, 16);
            fwrite(&writeBuffer, 2, 1, pointer);
        }
    }


    void waitNoAnim(char parameter[], FILE* pointer)
    {
        //same as wait, but no character animation while waiting

        long writeBuffer = 0x004E;
        fwrite(&writeBuffer, 2, 1, pointer);

        char *ptr;
        writeBuffer = strtol(parameter, &ptr, 16);
        fwrite(&writeBuffer, 2, 1, pointer);
    }


    void textSpeed(char parameter[], FILE* pointer)
    {
        long writeBuffer = 0x000B;
        fwrite(&writeBuffer, 2, 1, pointer);

        //add normal, slow, and fast later
        //if (strcmp(parameter, "normal") == 0)
        
        //if (strcmp(parameter, "slow") == 0)

        //if (strcmp(parameter, "fast") == 0)


        //else if parameter is just a hex number; must be two digits
        char *ptr;
        writeBuffer = strtol(parameter, &ptr, 16);
        fwrite(&writeBuffer, 2, 1, pointer);       
    }



void spriteFade(char parameter[], FILE* pointer)
{
    int writeBuffer = 0x0031;
    fwrite(&writeBuffer, 2, 1, pointer);

    if (strcmp(parameter, "in") == 0)
    {
        writeBuffer = 0x00020003;
        fwrite(&writeBuffer, 4, 1, pointer);
    }
    else if (strcmp(parameter, "out") == 0)
    {
        writeBuffer = 0x00010004;
        fwrite(&writeBuffer, 4, 1, pointer);
    }
}


void flash(char parameter[], FILE* pointer)
{
    int writeBuffer = 0x0012;
    fwrite(&writeBuffer, 2, 1, pointer);

    if (strcmp(parameter, "black") == 0)
    {
        writeBuffer = 0x00010204;
        fwrite(&writeBuffer, 4, 1, pointer);
        writeBuffer = 0x001F;
        fwrite(&writeBuffer, 2, 1, pointer);
        writeBuffer = 0x0019000C; //followed by wait 19
        fwrite(&writeBuffer, 4, 1, pointer);
    }

    if (strcmp(parameter, "white") == 0)
    {
        writeBuffer = 0x00080901;
        fwrite(&writeBuffer, 4, 1, pointer);
        writeBuffer = 0x001F;
        fwrite(&writeBuffer, 2, 1, pointer);
        writeBuffer = 0x0000001C;
        fwrite(&writeBuffer, 4, 1, pointer);
    }

}

//------------------------------------------------------------------------------------------------------------------

    void name(char parameter[], FILE* pointer)
    {
        //parameter will be a character's name in lowercase, like apollo
        long writeBuffer = 0x000E;
        fwrite(&writeBuffer, 2, 1, pointer);

        if (strcmp(parameter, "noneMale") == 0)
        {
            writeBuffer = 0x0000;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        else if (strcmp(parameter, "noneFemale") == 0)
        {
            writeBuffer = 0x0100;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        else if (strcmp(parameter, "???Male") == 0)
        {
            writeBuffer = 0x0200;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        else if (strcmp(parameter, "???Female") == 0)
        {
            writeBuffer = 0x0300;
            fwrite(&writeBuffer, 2, 1, pointer);
        }

        if (strcmp(parameter, "apollo") == 0)
        {
            writeBuffer = 0x0400;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "trucy") == 0)
        {
            writeBuffer = 0x0500;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        //originally a Kristoph name
        else if (strcmp(parameter, "edgeworth") == 0)
        {
            writeBuffer = 0x0600;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "phoenix") == 0)
        {
            writeBuffer = 0x0700;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "kristoph") == 0)
        {
            writeBuffer = 0x0800;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "ema") == 0)
        {
            writeBuffer = 0x0900;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "judge") == 0)
        {
            writeBuffer = 0x0A00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "payne") == 0)
        {
            writeBuffer = 0x0B00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "orly") == 0)
        {
            writeBuffer = 0x0C00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "alita") == 0)
        {
            writeBuffer = 0x0D00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "wocky") == 0)
        {
            writeBuffer = 0x0E00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "eldoon") == 0)
        {
            writeBuffer = 0x0F00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "plum") == 0)
        {
            writeBuffer = 0x1000;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "bigWins") == 0)
        {
            writeBuffer = 0x1100;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "hickfield") == 0)
        {
            writeBuffer = 0x1200;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "vera") == 0)
        {
            writeBuffer = 0x1300;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "brushel") == 0)
        {
            writeBuffer = 0x1400;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "phoenix2") == 0)
        {
            writeBuffer = 0x1500;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "gumshoe") == 0)
        {
            writeBuffer = 0x1600;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        //originally a Kristoph name
        else if (strcmp(parameter, "clay") == 0)
        {
            writeBuffer = 0x1700;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "maya") == 0)
        {
            writeBuffer = 0x1800;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "valant") == 0)
        {
            writeBuffer = 0x1900;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "drew") == 0)
        {
            writeBuffer = 0x1A00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "childTrucy") == 0)
        {
            writeBuffer = 0x1B00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "childVera") == 0)
        {
            writeBuffer = 0x1C00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "meekins") == 0)
        {
            writeBuffer = 0x1D00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "stickler") == 0)
        {
            writeBuffer = 0x1E00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "zak") == 0)
        {
            writeBuffer = 0x1F00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "smith") == 0)
        {
            writeBuffer = 0x2000;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "valant2") == 0)
        {
            writeBuffer = 0x2100;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "lamiroir") == 0)
        {
            writeBuffer = 0x2200;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "machi") == 0)
        {
            writeBuffer = 0x2300;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "letouse") == 0)
        {
            writeBuffer = 0x2400;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "daryan") == 0)
        {
            writeBuffer = 0x2500;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        //all the values in between 25 and 2B are dummy values
        else if (strcmp(parameter, "bailiff") == 0)
        {
            writeBuffer = 0x2B00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "officer") == 0)
        {
            writeBuffer = 0x2C00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "announcer") == 0)
        {
            writeBuffer = 0x2D00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "mrhat") == 0)
        {
            writeBuffer = 0x2E00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "meraktis") == 0)
        {
            writeBuffer = 0x2F00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "enigmar") == 0)
        {
            writeBuffer = 0x3000;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "public") == 0)
        {
            writeBuffer = 0x3100;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "magnifi") == 0)
        {
            writeBuffer = 0x3200;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "no6") == 0)
        {
            writeBuffer = 0x3300;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "guard") == 0)
        {
            writeBuffer = 0x3400;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "klavier") == 0)
        {
            writeBuffer = 0x3500;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "thalassa") == 0)
        {
            writeBuffer = 0x3600;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "staff") == 0)
        {
            writeBuffer = 0x3700;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "oldLady") == 0)
        {
            writeBuffer = 0x3800;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "kristoph3") == 0)
        {
            writeBuffer = 0x3900;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
        else if (strcmp(parameter, "tv") == 0)
        {
            writeBuffer = 0x3A00;
            fwrite(&writeBuffer, 2, 1, pointer);
        }
    }

//--------------------------------------------------------------------------------

    void charAnimation(char parameter[], FILE* pointer)
    {
        long writeBuffer = 0x001E;

        //Valant's shocked animation uses a completely different command
        //with no 1E
        if (strcmp(parameter, "valantShocked") == 0)
        {
            writeBuffer = 0x00E4002F;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x0001;
            fwrite(&writeBuffer, 2, 1, pointer);

            //things that go along with the animation
            flash("white", pointer);
            sound("damage", pointer);
            shake("1", pointer);

            return;
            //don't get to the rest of the function
            //which will write a 1E
        }

        fwrite(&writeBuffer, 2, 1, pointer);

        if (strcmp(parameter, "phoenixNormalS") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00B100B1;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        if (strcmp(parameter, "phoenixNormal") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00B100B2;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixSideLookS") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00B700B7;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixSideLook") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00B700B8;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixHeadDownS") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00BB00BB;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixHeadDown") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00BB00BC;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixStraightLookS") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00B500B5;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixStraightLook") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00B500B6;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixSmilingS") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00BD00BD;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixSmiling") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00BD00BE;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixWideEyedS") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00B300B3;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixWideEyed") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00B300B4;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixGlaringS") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00B900B9;
            fwrite(&writeBuffer, 4, 1, pointer);
        }
        
        else if (strcmp(parameter, "phoenixGlaring") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00B900BA;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "phoenixLaughing") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00BE00BF;
            fwrite(&writeBuffer, 4, 1, pointer);
        }
        
        else if (strcmp(parameter, "phoenixLaughingS") == 0)
        {
            writeBuffer = 0x0007;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00BF00BF;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "apolloNormal") == 0)
        {
            writeBuffer = 0x0004;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00240025;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "apolloDrooping") == 0)
        {
            writeBuffer = 0x0004;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x003D003D;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "apolloDetermined") == 0)
        {
            writeBuffer = 0x0004;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x003A003A;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "apolloThinking") == 0)
        {
            writeBuffer = 0x0004;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x002A002B;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "apolloReading") == 0)
        {
            writeBuffer = 0x0004;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00280029;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "apolloPointWindup") == 0)
        {
            writeBuffer = 0x0004;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00410040;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "apolloConfident") == 0)
        {
            writeBuffer = 0x0004;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x002F0030;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "apolloNod") == 0)
        {
            writeBuffer = 0x0004;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00260026;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0046000C;
            fwrite(&writeBuffer, 4, 1, pointer);
            //followed by wait 46
        }

        else if (strcmp(parameter, "kristophBadgeNormalS") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00C900C9;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophBadgeNormal") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00C900CA;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophBadgeSmilingS") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00CB00CB;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophBadgeSmiling") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00CB00CC;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophBadgeArrogantS") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00CD00CD;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophBadgeArrogant") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00CD00CE;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophBadgeScowlingS") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00CF00CF;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophBadgeScowling") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00CF00D0;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophBadgeHeadShake") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00D100D1;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00B4000C;
            fwrite(&writeBuffer, 4, 1, pointer);
            //usually followed by wait B4
        }

        else if (strcmp(parameter, "kristophBadgeAngryS") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00D200D2;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophBadgeAngry") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00D200D3;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophNormal") == 0) //note: Kristoph sprites are badgeless
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02120213;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophNormalS") == 0) //S versions are the non-talking animations
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02120212;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophSmilingS") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02150215;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophSmiling") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02150216;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophScowlingS") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x022F022F;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophScowling") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x022F0230;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophHandOverMouth") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02290229;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophArrogant") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02310231;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophArrogant") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02310232;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophAngryS") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x021D021D;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophAngry") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x021D021E;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophHeadShake") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x021C021C;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00B4000C;
            fwrite(&writeBuffer, 4, 1, pointer);
            //usually followed by wait B4
        }

        else if (strcmp(parameter, "kristophCocounselNormal") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00DB00DC;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophCocounselStraight") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00DF00E0;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "kristophCocounselSmiling") == 0)
        {
            writeBuffer = 0x0008;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00DD00DE;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "klavierNormal") == 0)
        {
            writeBuffer = 0x0006;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00850086;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "klavierSideSmile") == 0)
        {
            writeBuffer = 0x0006;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x008B008C;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "klavierSerious") == 0)
        {
            writeBuffer = 0x0006;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00870088;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "klavierSeriousS") == 0)
        {
            writeBuffer = 0x0006;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00870087;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyNormal") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00430044;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyNormalS") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00430043;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucySmiling") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00450048;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucySmilingS") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00450045;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyGrinning") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00460046;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucySmilingEyesShut") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00470047;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyDetermined") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x005F0060;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyDeterminedS") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x005F005F;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyPosing") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x0049004A;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyPosingS") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00490049;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucySerious") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00550056;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucySeriousS") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00550055;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucySurprised") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00510052;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucySurprisedS") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00510051;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyThinking") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x004B004C;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyThinkingS") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x004B004B;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyAnnoyed") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x005A005B;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyAnnoyedS") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x005A005A;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucySad") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x005C005D;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucySadS") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x005C005C;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyWorried") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00530054;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyWorriedS") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x00530053;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "trucyBonk") == 0)
        {
            writeBuffer = 0x0005;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x005E005E;
            fwrite(&writeBuffer, 4, 1, pointer);

            wait("10", pointer);
        }



        //add other Trucy animations and variations

        else if (strcmp(parameter, "judgeNormal") == 0)
        {
            writeBuffer = 0x000A;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01020103;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "judgeNormalS") == 0)
        {
            writeBuffer = 0x000A;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01020102;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "judgeStern") == 0)
        {
            writeBuffer = 0x000A;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01060107;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "judgeSurprised") == 0)
        {
            writeBuffer = 0x000A;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01080109;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "judgeHeadShake") == 0)
        {
            writeBuffer = 0x000A;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01050105;
            fwrite(&writeBuffer, 4, 1, pointer);

            wait("46", pointer);
        }

        else if (strcmp(parameter, "brushelNormal") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01C101C2;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelNormalS") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01C101C1;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelGrinning") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01C301C4;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelGrinningS") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01C301C3;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelNose") == 0) //not sure there's a talking variant
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01C501C6;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelNoseS") == 0) //not sure there's a talking variant
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01C501C5;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelThinking") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01C801C9;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelThinkingS") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01C801C8;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelSurprised") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01CB01CC;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelSurprisedS") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01CB01CB;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelWriting") == 0) //not sure this one is a thing
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01CD01CE;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelWritingS") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01CD01CD;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelConfident") == 0)
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01CF01D0;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "brushelConfidentS") == 0) //not sure this exists
        {
            writeBuffer = 0x0014;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01CF01CF;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeNormalS") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01EB01EB;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeNormal") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01EB01EC;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeSadS") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01F701F7;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeSad") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01F701F8;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeAngryS") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01F501F5;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeAngry") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01F501F6;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeSmilingS") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01F901F9;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeSmiling") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01F901FA;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeThinkingS") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01ED01ED;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeThinking") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01ED01EE;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeLaughingS") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01EF01EF;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeLaughing") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01EF01F0;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeConfidentS") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01F101F1;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeConfident") == 0) //not sure this exists
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01F101F2;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeSideLookS") == 0)
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01F301F3;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "gumshoeSideLook") == 0)
        {
            writeBuffer = 0x0016;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01F301F4;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "olgaNormalS") == 0)
        {
            writeBuffer = 0x000C;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01140114;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "olgaNormal") == 0)
        {
            writeBuffer = 0x000C;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01140115;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "olgaSnap") == 0)
        {
            writeBuffer = 0x000C;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01170116;
            fwrite(&writeBuffer, 4, 1, pointer);

            //unknown what the 63 command does
            //but the screen stays white forever after the flash without it
            writeBuffer = 0x0063;
            fwrite(&writeBuffer, 2, 1, pointer);

            //sound effect
            writeBuffer = 0x0006;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x0001002D;
            fwrite(&writeBuffer, 4, 1, pointer);

            //and then there's 27001E000100, but not sure what it's for
            //another time 6300
        }

        else if (strcmp(parameter, "olgaCameraS") == 0)
        {
            writeBuffer = 0x000C;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01170117;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "olgaCamera") == 0)
        {
            writeBuffer = 0x000C;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01170118;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "olgaWorriedS") == 0)
        {
            writeBuffer = 0x000C;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x01190119;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "olgaWorried") == 0)
        {
            writeBuffer = 0x000C;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x0119011A;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "olgaCoweringS") == 0)
        {
            writeBuffer = 0x000C;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x011B011B;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "olgaCowering") == 0)
        {
            writeBuffer = 0x000C;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x011B011C;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "childTrucyNormalS") == 0)
        {
            writeBuffer = 0x001B;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x025F025F;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "childTrucyNormal") == 0)
        {
            writeBuffer = 0x001B;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x025F0260;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "childTrucySmilingS") == 0)
        {
            writeBuffer = 0x001B;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02650265;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "childTrucySmiling") == 0)
        {
            writeBuffer = 0x001B;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02650266;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "childTrucyThinkingS") == 0)
        {
            writeBuffer = 0x0005; //I think it's 05, not 1B?
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02630263;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "childTrucyThinking") == 0)
        {
            writeBuffer = 0x0005; //I think it's 05, not 1B?
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02630264;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "childTrucySadS") == 0)
        {
            writeBuffer = 0x001B;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02610261;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "childTrucySad") == 0)
        {
            writeBuffer = 0x001B;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02610262;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "childTrucyMrHat") == 0)
        {
            //Getting him to appear:
            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0006026B;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x000100BA;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0063;
            fwrite(&writeBuffer, 2, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0063026C;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0063026D;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0063026E;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0063026F;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630270;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630271;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630272;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630273;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630276;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630277;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630278;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630279;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0063027A;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0063027B;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0063027C;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0063027D;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0063027E;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0063027F;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630280;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630281;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630282;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630283;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B008E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x00630269;
            fwrite(&writeBuffer, 4, 1, pointer);

            writeBuffer = 0x001B001E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x0267026A;
            fwrite(&writeBuffer, 4, 1, pointer);

            //8E001B00 6B020600.
            //BA000100 6300.
            //8E001B00 6C026300.
            //8E001B00 6D026300.
            //8E001B00 6E026300.
            //8E001B00 6F026300.
            //8E001B00 70026300.
            //8E001B00 71026300.
            //8E001B00 72026300.
            //8E001B00 73026300.
            //8E001B00 76026300.
            //8E001B00 77026300.
            //8E001B00 78026300.
            //8E001B00 79026300.
            //8E001B00 7A026300.
            //8E001B00 7B026300.
            //8E001B00 7C026300.
            //8E001B00 7D026300.
            //8E001B00 7E026300.
            //8E001B00 7F026300.
            //8E001B00 80026300.
            //8E001B00 81026300.
            //8E001B00 82026300.
            //88E01B00 83026300.
            //8E001B00 69026300.
            //1E001B00 6A026702.
            //1200 01090800 1F0042000000
            
            //uses text speed 4
        }

        else if (strcmp(parameter, "valantNormalS") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02D302D3;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "valantNormal") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02D302D4;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "valantLaughing") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02D302D9;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "valantSurprisedS") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02D702D7;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "valantSurprised") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02D702D8;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "valantThinkingS") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02DC02DC;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "valantThinking") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02DC02DD;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "valantPointingS") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02D502D5;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "valantPointing") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02D502D6;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "valantWorriedS") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02DA02DA;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "valantWorried") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x02DA02DB;
            fwrite(&writeBuffer, 4, 1, pointer);
        }

        else if (strcmp(parameter, "valantStaffTwirl") == 0)
        {
            writeBuffer = 0x0021;
            fwrite(&writeBuffer, 2, 1, pointer);
            writeBuffer = 0x2D302D3;
            fwrite(&writeBuffer, 4, 1, pointer);

            sound("staffTwirl", pointer);
            wait("A", pointer);

            writeBuffer = 0x0021001E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x2D302E2;
            fwrite(&writeBuffer, 4, 1, pointer);
            
            wait("F", pointer);

            writeBuffer = 0x0021001E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x2D302E2;
            fwrite(&writeBuffer, 4, 1, pointer);

            wait("4", pointer);

            writeBuffer = 0x0021001E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x2D302E8;
            fwrite(&writeBuffer, 4, 1, pointer);
        
            wait("2", pointer);

            writeBuffer = 0x0021001E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x2D302E3;
            fwrite(&writeBuffer, 4, 1, pointer);
            
            wait("6", pointer);

            writeBuffer = 0x0021001E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x2D302E4;
            fwrite(&writeBuffer, 4, 1, pointer);
            
            wait("7", pointer);

            writeBuffer = 0x0021001E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x2D302E5;
            fwrite(&writeBuffer, 4, 1, pointer);
            
            wait("7", pointer);

            writeBuffer = 0x0021001E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x2D302E6;
            fwrite(&writeBuffer, 4, 1, pointer);
            
            wait("3", pointer);

            writeBuffer = 0x0021001E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x2D302E7;
            fwrite(&writeBuffer, 4, 1, pointer);
            
            wait("4", pointer);

            writeBuffer = 0x0021001E;
            fwrite(&writeBuffer, 4, 1, pointer);
            writeBuffer = 0x2D302E8;
            fwrite(&writeBuffer, 4, 1, pointer);
            
            wait("1E", pointer);

            charAnimation("valantNormalS", pointer);
        }
    }

//------------------------------------------------------------------------------------------------

void centerText(char parameter[], FILE* pointer)
{
    int writeBuffer = 0x005D;
    fwrite(&writeBuffer, 2, 1, pointer);

    if (strcmp(parameter, "on") == 0)
    {
        writeBuffer = 0x0001;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    else if (strcmp(parameter, "off") == 0)
    {
        writeBuffer = 0x0000;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
}


void shake(char parameter[], FILE* pointer)
{
    long writeBuffer = 0x001E0027; //code is 27, and first argument always 1E
    fwrite(&writeBuffer, 4, 1, pointer);

    char* ptr;

    writeBuffer = strtol(parameter, &ptr, 16); //not sure what it does, but second argument varies from 0 to about 2
    fwrite(&writeBuffer, 2, 1, pointer);
}


void textbox(char parameter[], FILE* pointer)
{
    int writeBuffer = 0x001C;
    fwrite(&writeBuffer, 2, 1, pointer);

    if (strcmp(parameter, "show") == 0)
    {
        writeBuffer = 0x0000;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    else if (strcmp(parameter, "hide") == 0)
    {
        writeBuffer = 0x0001;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
}

void courtRecordButton(char parameter[], FILE* pointer)
{
    int writeBuffer = 0x0026;
    fwrite(&writeBuffer, 2, 1, pointer);

    if (strcmp(parameter, "show") == 0)
    {
        writeBuffer = 0x0000;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    else if (strcmp(parameter, "hide") == 0)
    {
        writeBuffer = 0x0001;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
}


void screenFade(char parameter[], FILE* pointer)
{
    //standard form:
    //12 00 01 02 00 00 1F 00 0C 00 01 00 0C 00 28 00
    //change background using 1B command
    //12 00 04 01 01 00 1F 00 0C 00 19 00 0C 00 3C 00

    //the string argument is the background to fade in to from black

    long writeBuffer = 0x0012;
    fwrite(&writeBuffer, 2, 1, pointer);

    writeBuffer = 0x00000201;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x001F;
    fwrite(&writeBuffer, 2, 1, pointer);

    wait("1", pointer);
    wait("3C", pointer);

    //now change the background
    background(parameter, pointer);

    //now write the rest of the flashes
    writeBuffer = 0x0012;
    fwrite(&writeBuffer, 2, 1, pointer);

    writeBuffer = 0x00010104;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x001F;
    fwrite(&writeBuffer, 2, 1, pointer);

    wait("19", pointer);
    wait("3C", pointer);
}


void jump(char parameter[], FILE* pointer)
{
    //jumps to the start of a section within the same text file
    //note: there needs to be a sectionEnd() right after for it to work

    char* ptr;
    
    //the section to jump to, displayed as signed hex
    int sectionNum = strtol(parameter, &ptr, 16) + 0x80;

    int writeBuffer = 0x002C;
    fwrite(&writeBuffer, 2, 1, pointer);

    writeBuffer = sectionNum;
    fwrite(&writeBuffer, 2, 1, pointer);
}


void twoChoices(char parameter[], FILE* pointer)
{
    //requires four parameters separated with commas like 80,7F,2,3
    //the first two numbers the option buttons to choose
    //the second two the script sections each option jumps to

    long paramList[4] = {0, 0, 0, 0};
    int commas = 0;
    int arrayLength = strlen(parameter);
    int previousComma = -1; //if there were a hypothetical 0th comma, it'd be at -1
    char* ptr;
    char substring1[2];
    char substring2[3];
    char substring3[4];

    //not sure if the three-digit parameter functionality works, but also not sure it's needed

    for (int count = 0; count < 3; count++) //once for each comma
    {
        for (int i = 0; i < arrayLength; i++) //iterate through array length
        {
            if (parameter[i] == ',')
            {
                commas++;

                if (commas == count + 1) //plus one since comma count can't be 0
                {
                    if (i - 1 - previousComma == 3) //if the value is three digits long
                    {
                        strncpy(substring3, parameter+i-3, 3);
                        paramList[count] = strtol(substring3, &ptr, 16);
                    }
                    else if (i - 1 - previousComma == 2) //if the value is two digits digits long
                    {
                        strncpy(substring2, parameter+i-2, 2);
                        paramList[count] = strtol(substring2, &ptr, 16);
                    }
                    else //if it's one digit long
                    {
                        strncpy(substring1, parameter+i-1, 1);
                        paramList[count] = strtol(substring1, &ptr, 16);
                    }

                    if (count == 2 && commas == 3) //if it's the third comma, last parameter must also be stored in addition to third one
                    {
                        if (arrayLength - 1 - i == 3) //if it's three digits long
                        {
                            strncpy(substring3, parameter+i+1, 3);
                            paramList[3] = strtol(substring3, &ptr, 16);
                        }
                        else if (arrayLength - 1 - i == 2) //if it's two digits long
                        {
                            strncpy(substring2, parameter+i+1, 2);
                            paramList[3] = strtol(substring2, &ptr, 16);
                        }
                        else //if it's one digit long
                        {
                            strncpy(substring1, parameter+i+1, 1);
                            paramList[3] = strtol(substring1, &ptr, 16);
                        }
                    }

                    previousComma = i;
                }
            }
        }
        commas = 0;
    }

    long writeBuffer = 0x0001000C;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x0000006B;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x00000001;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x00620069;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x00070165;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x0050;
    fwrite(&writeBuffer, 2, 1, pointer);

    //that's the 50 command, so next comes the two parameters for options to display
    writeBuffer = paramList[0];
    fwrite(&writeBuffer, 1, 1, pointer);
    writeBuffer = 0x00;
    fwrite(&writeBuffer, 1, 1, pointer);

    writeBuffer = paramList[1];
    fwrite(&writeBuffer, 1, 1, pointer);
    writeBuffer = 0x00;
    fwrite(&writeBuffer, 1, 1, pointer);

    writeBuffer = 0x0001FFFF;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x0008;
    fwrite(&writeBuffer, 2, 1, pointer);

    writeBuffer = 0x80 + paramList[2]; //for some reason, the section number is added to 0x80
    fwrite(&writeBuffer, 1, 1, pointer);
    writeBuffer = 0x00;
    fwrite(&writeBuffer, 1, 1, pointer);

    writeBuffer = 0x80 + paramList[3];
    fwrite(&writeBuffer, 1, 1, pointer);
    writeBuffer = 0x00;
    fwrite(&writeBuffer, 1, 1, pointer);
}


void threeChoices(char parameter[], FILE* pointer)
{
    //requires six parameters separated with five commas like 15,16,17,2,3,4
    //the first three numbers the option buttons to choose
    //the second three the script sections each option jumps to

    long paramList[6] = {0, 0, 0, 0, 0, 0};
    int commas = 0;
    int arrayLength = strlen(parameter);
    int previousComma = -1; //if there were a hypothetical 0th comma, it'd be at -1
    char* ptr;
    char substring1[2];
    char substring2[3];
    char substring3[4];

    //not sure if the three-digit parameter functionality works, but also not sure it's needed

    for (int count = 0; count < 5; count++) //once for each comma
    {
        for (int i = 0; i < arrayLength; i++) //iterate through array length
        {
            if (parameter[i] == ',')
            {
                commas++;

                if (commas == count + 1) //plus one since comma count can't be 0
                {
                    if (i - 1 - previousComma == 3) //if the value is three digits long
                    {
                        strncpy(substring3, parameter+i-3, 3);
                        paramList[count] = strtol(substring3, &ptr, 16);
                    }
                    else if (i - 1 - previousComma == 2) //if the value is two digits long
                    {
                        strncpy(substring2, parameter+i-2, 2);
                        paramList[count] = strtol(substring2, &ptr, 16);
                    }
                    else //if it's one digit long
                    {
                        strncpy(substring1, parameter+i-1, 1);
                        paramList[count] = strtol(substring1, &ptr, 16);
                    }

                    if (count == 4 && commas == 5) //if it's the fifth comma, last parameter must also be stored in addition to fifth one
                    {
                        if (arrayLength - 1 - i == 3) //if it's three digits long
                        {
                            strncpy(substring3, parameter+i+1, 3);
                            paramList[5] = strtol(substring3, &ptr, 16);
                        }
                        else if (arrayLength - 1 - i == 2) //if it's two digits long
                        {
                            strncpy(substring2, parameter+i+1, 2);
                            paramList[5] = strtol(substring2, &ptr, 16);
                        }
                        else //if it's one digit long
                        {
                            strncpy(substring1, parameter+i+1, 1);
                            paramList[5] = strtol(substring1, &ptr, 16);
                        }
                    }

                    previousComma = i;
                }
            }
        }
        commas = 0;
    }

    long writeBuffer = 0x0001000C;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x0000006B;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x00000001;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x00620069;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x00070165;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x0050;
    fwrite(&writeBuffer, 2, 1, pointer);

    //that's the 50 command, so next comes the two parameters for options to display
    writeBuffer = paramList[0];
    fwrite(&writeBuffer, 1, 1, pointer);
    writeBuffer = 0x00;
    fwrite(&writeBuffer, 1, 1, pointer);

    writeBuffer = paramList[1];
    fwrite(&writeBuffer, 1, 1, pointer);
    writeBuffer = 0x00;
    fwrite(&writeBuffer, 1, 1, pointer);

    writeBuffer = paramList[2];
    fwrite(&writeBuffer, 1, 1, pointer);
    writeBuffer = 0x00;
    fwrite(&writeBuffer, 1, 1, pointer);

    writeBuffer = 0x00010001;
    fwrite(&writeBuffer, 4, 1, pointer);

    writeBuffer = 0x0009;
    fwrite(&writeBuffer, 2, 1, pointer);

    writeBuffer = 0x80 + paramList[3]; //for some reason, the section number is added to 0x80
    fwrite(&writeBuffer, 1, 1, pointer);
    writeBuffer = 0x00;
    fwrite(&writeBuffer, 1, 1, pointer);

    writeBuffer = 0x80 + paramList[4];
    fwrite(&writeBuffer, 1, 1, pointer);
    writeBuffer = 0x00;
    fwrite(&writeBuffer, 1, 1, pointer);

    writeBuffer = 0x80 + paramList[5];
    fwrite(&writeBuffer, 1, 1, pointer);
    writeBuffer = 0x00;
    fwrite(&writeBuffer, 1, 1, pointer);
}

void setFlag(char parameter[], FILE* pointer)
{
    //an example is that 10 00 02 80 sets the four bit (the third one)
    //not sure what the 35 does, and it can change, but I'll just leave it
    //the parameter is the bit number, like "1" is setting the second-lowest bit

    long writeBuffer = 0x0010;
    fwrite(&writeBuffer, 2, 1, pointer);

    if (strcmp(parameter, "0") == 0)
    {
        writeBuffer = 0x8000;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    else if (strcmp(parameter, "1") == 0)
    {
        writeBuffer = 0x8001;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    else if (strcmp(parameter, "2") == 0)
    {
        writeBuffer = 0x8002;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    else if (strcmp(parameter, "3") == 0)
    {
        writeBuffer = 0x8003;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    else if (strcmp(parameter, "4") == 0)
    {
        writeBuffer = 0x8004;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    else if (strcmp(parameter, "5") == 0)
    {
        writeBuffer = 0x8005;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    else if (strcmp(parameter, "6") == 0)
    {
        writeBuffer = 0x8006;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    else if (strcmp(parameter, "7") == 0)
    {
        writeBuffer = 0x8007;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
}

void music(char parameter[], FILE* pointer)
{
    long writeBuffer = 0x0005;
    fwrite(&writeBuffer, 2, 1, pointer);

    if (strcmp(parameter, "courtBegins2007") == 0)
    {
        writeBuffer = 0x0001;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "moderato2007") == 0)
    {
        writeBuffer = 0x0002;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "allegro2007") == 0)
    {
        writeBuffer = 0x0003;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "tranceLogic") == 0)
    {
        writeBuffer = 0x0004;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "objection2007") == 0)
    {
        writeBuffer = 0x0005;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "prelude2007") == 0)
    {
        writeBuffer = 0x0006;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "pursuit2007") == 0)
    {
        writeBuffer = 0x0007;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "pursuitVariation2007") == 0)
    {
        writeBuffer = 0x0008;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "tellTheTruth2007") == 0)
    {
        writeBuffer = 0x0009;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "perceive") == 0)
    {
        writeBuffer = 0x000A;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "4-1Intro") == 0)
    {
        writeBuffer = 0x000B;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "4-2Intro") == 0)
    {
        writeBuffer = 0x000C;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "guiltyLoveRingtone") == 0)
    {
        writeBuffer = 0x000F;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    //add others

    else if (strcmp(parameter, "childOfMagic") == 0)
    {
        writeBuffer = 0x0010;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "detentionCenter2007") == 0)
    {
        writeBuffer = 0x0011;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "suspense") == 0)
    {
        writeBuffer = 0x0012;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "guiltyLove") == 0)
    {
        writeBuffer = 0x0013;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "kitakiFamily") == 0)
    {
        writeBuffer = 0x0014;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "troupeGramarye") == 0)
    {
        writeBuffer = 0x0016;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "jingle") == 0)
    {
        writeBuffer = 0x0017;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "4-4Intro2") == 0)
    {
        writeBuffer = 0x0018;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "drewStudio") == 0)
    {
        writeBuffer = 0x0019;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "guiltyLoveMuted") == 0)
    {
        writeBuffer = 0x001A;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "darkness") == 0)
    {
        writeBuffer = 0x001B;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "hurtFox") == 0)
    {
        writeBuffer = 0x001C;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "fateSmeared") == 0)
    {
        writeBuffer = 0x001D;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    //add others

    else if (strcmp(parameter, "investigationCore") == 0)
    {
        writeBuffer = 0x0021;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "forgottenLegend") == 0)
    {
        writeBuffer = 0x0022;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "thrill") == 0)
    {
        writeBuffer = 0x0023;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "victory2007") == 0)
    {
        writeBuffer = 0x0024;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "ending") == 0)
    {
        writeBuffer = 0x0025;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "eccentricPeople") == 0)
    {
        writeBuffer = 0x0026;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "scientificDetective") == 0)
    {
        writeBuffer = 0x0029;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    //add others

    else if (strcmp(parameter, "objection2001") == 0)
    {
        writeBuffer = 0x0036;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "birdsChirping") == 0)
    {
        writeBuffer = 0x0038;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "detentionCenter2001") == 0)
    {
        writeBuffer = 0x0039;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "newCredits") == 0)
    {
        writeBuffer = 0x0058;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "serenadeRingtone") == 0) //streamed, added
    {
        writeBuffer = 0x0059;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "previous") == 0)
    {
        writeBuffer = 0x00FF;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "greatRevival") == 0)
    {
        writeBuffer = 0x005D;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "turnaboutSisters") == 0)
    {
        writeBuffer = 0x005E;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "jingle2001") == 0)
    {
        writeBuffer = 0x005F;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else
    {
    //else, if the parameter is just a number and not a track name, write that number
    char* ptr;
    writeBuffer = strtol(parameter, &ptr, 16);
    fwrite(&writeBuffer, 2, 1, pointer);
    }

    writeBuffer = 0x0000;
    fwrite(&writeBuffer, 2, 1, pointer);

    //write the number of frames of fade-in (not customizable, yet)
    //seems to usually be 00
}

void sound(char parameter[], FILE* pointer)
{
    int writeBuffer = 0x0006;
    fwrite(&writeBuffer, 2, 1, pointer);

    if (strcmp(parameter, "truth") == 0)
    {
        writeBuffer = 0x001A;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "outburst") == 0)
    {
        writeBuffer = 0x001B;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    
    else if (strcmp(parameter, "objection") == 0)
    {
        writeBuffer = 0x0020;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "damage") == 0)
    {
        writeBuffer = 0x002C;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "shock") == 0)
    {
        writeBuffer = 0x002D;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "POVChange") == 0)
    {
        writeBuffer = 0x0030;
        fwrite(&writeBuffer, 2, 1, pointer);
        //when you cycle around perspectives in the courtroom, culminating in argument sound for final one
    }

    else if (strcmp(parameter, "flashTransition") == 0)
    {
        writeBuffer = 0x0031;
        fwrite(&writeBuffer, 2, 1, pointer);
        //when you cycle around perspectives in the courtroom, culminating in argument sound for final one
    }
    
    else if (strcmp(parameter, "argument") == 0)
    {
        writeBuffer = 0x0032;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "ding") == 0)
    {
        writeBuffer = 0x0033;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "realization") == 0)
    {
        writeBuffer = 0x0034;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "punctuate") == 0)
    {
        writeBuffer = 0x0035;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "door") == 0)
    {
        writeBuffer = 0x003A;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "phoneBeep") == 0)
    {
        writeBuffer = 0x00C2;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "glassShattering") == 0)
    {
        writeBuffer = 0x0052;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "barking") == 0)
    {
        writeBuffer = 0x005E;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "rain") == 0)
    {
        writeBuffer = 0x005F;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "gulp") == 0)
    {
        writeBuffer = 0x0061;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "staffTwirl") == 0)
    {
        writeBuffer = 0x0093;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    writeBuffer = 0x0001;
    fwrite(&writeBuffer, 2, 1, pointer);
}


void voiceSFX(char parameter[], FILE* pointer)
{
    int writeBuffer = 0x0042;
    fwrite(&writeBuffer, 2, 1, pointer);

    if (strcmp(parameter, "on") == 0)
    {
        writeBuffer = 0x0000;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
    if (strcmp(parameter, "off") == 0)
    {
        writeBuffer = 0x0001;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
}


void musicFade(char parameter[], FILE* pointer)
{
    long writeBuffer = 0x0022;
    fwrite(&writeBuffer, 2, 1, pointer);

    char* ptr;

    writeBuffer = strtol(parameter, &ptr, 16); //3C is a standard fade length argument
    fwrite(&writeBuffer, 2, 1, pointer);
}


void background(char parameter[], FILE* pointer)
{
    int writeBuffer = 0x001B;
    fwrite(&writeBuffer, 2, 1, pointer);

    if (strcmp(parameter, "black") == 0)
    {
        writeBuffer = 0x0FFF;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "waa") == 0)
    {
        writeBuffer = 0x00F3;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "courtZoomedOut") == 0)
    {
        writeBuffer = 0x0018;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "judgeGavel") == 0)
    {
        writeBuffer = 0x0009;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "judgePOV") == 0)
    {
        writeBuffer = 0x001D;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "prosecutorPOV") == 0)
    {
        writeBuffer = 0x001A;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "cocounselPOV") == 0)
    {
        writeBuffer = 0x001C;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "witnessPOV") == 0) //has a visual glitch?
    {
        writeBuffer = 0x001B;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "courtLobby") == 0) //has a visual glitch?
    {
        writeBuffer = 0x001E;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "wright&Co") == 0) //has a visual glitch?
    {
        writeBuffer = 0x0028;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "hickfieldClinic") == 0) //has a visual glitch?
    {
        writeBuffer = 0x00E2;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "solitaryConfinement") == 0) //has a visual glitch?
    {
        writeBuffer = 0x00EC;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "backstageHallway") == 0) //has a visual glitch?
    {
        writeBuffer = 0x00F7;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "borschtBowlClub") == 0) //has a visual glitch?
    {
        writeBuffer = 0x0114;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "lanaScene") == 0)
    {
        writeBuffer = 0x012A;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else if (strcmp(parameter, "edgeworthOffice") == 0)
    {
        writeBuffer = 0x012B;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    //add more
}

void showBox(char parameter[], FILE* pointer)
{
    //parameter is written like "magatama,left"

    int writeBuffer = 0x0013;
    fwrite(&writeBuffer, 2, 1, pointer);

    char* ptr;
    writeBuffer = strtol(parameter, &ptr, 16); //param is one-byte ID
    fwrite(&writeBuffer, 2, 1, pointer);

    //think about "left" and "right" later
}

void psycheLocks(char parameter[], FILE* pointer)
{
    //the parameter, written as "1" through "5", is the number of locks to appear
    //it can also be "hide"
    //note that the Psyche-Lock command seems to hide the textbox automatically

    int writeBuffer;

    if (strcmp(parameter, "hide") == 0)
    {
        writeBuffer = 0x0089;
        fwrite(&writeBuffer, 2, 1, pointer);
    }

    else
    {
        writeBuffer = 0x0088;
        fwrite(&writeBuffer, 2, 1, pointer);

        char* ptr;
        long numLocks = strtol(parameter, &ptr, 10);

        writeBuffer = numLocks;
        fwrite(&writeBuffer, 2, 1, pointer);
    }
}

void monochrome(char parameter[], FILE* pointer)
{
    long writeBuffer = 0x005F;
    fwrite(&writeBuffer, 2, 1, pointer);

    if (strcmp(parameter, "on") == 0)
    {
        writeBuffer = 0x00010003;
        fwrite(&writeBuffer, 4, 1, pointer);
    }

    else if (strcmp(parameter, "off") == 0)
    {
        writeBuffer = 0x001F0004;
        fwrite(&writeBuffer, 4, 1, pointer);
    }

    //5F00 03000100 (might be a 02 at the end instead?)
    //5F00 04001F00
}

void addHeader(FILE* fptrOriginal)
{
    //the number of bytes to append to the start of the file
    int headerNumBytes = (sectionCount + 1) * 4;

    //the file that will contain the final result of the header plus the code
    FILE* fptrMerge = fopen("C:\\Users\\ben\\Desktop\\AJ-Retrial\\Helper programs\\aj-text2code\\codeHeader.bin","wb"); 

    fseek(fptrMerge, 0, SEEK_SET);

    long writeBuffer = sectionCount;
    fwrite(&writeBuffer, 4, 1, fptrMerge); //currently only works if section count < 255, i.e., is one byte

    int currentOffset;
    //now write the rest of the header, with the section offsets
    for (int i = 0; i < sectionCount; i++)
    {
        //the size of the header needs to be added to the offset, since it's absolute, not relative
        currentOffset = sectionOffsets[i] + headerNumBytes;

        writeBuffer = currentOffset;
        fwrite(&writeBuffer, 4, 1, fptrMerge);
    }
    
    //then write all of the original .bin file into this one after the header
    char* fileBuffer[200000]; //buffer of arbitrary large size; if too large, seg faults
    
    fseek(fptrOriginal, 0, SEEK_SET); //return to beginning of file

    //read all of the original file into a buffer; stops when EOF is reached
    fread(fileBuffer, sizeof(fileBuffer), 1, fptrOriginal);

    //then write the original .bin file from the buffer to the new one
    fwrite(fileBuffer, ftell(fptrOriginal), 1, fptrMerge);

    printf("\nAdded header.");
    fclose(fptrMerge);
}