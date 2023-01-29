#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



void printFile(char *fileName, int nFlag, int bFlag) 
{
    // Reading the File

    FILE *file;
    file = fopen(fileName, "r");

    if (file == NULL) 
    {
        perror("Could not open file");
    } 
    
    else 
    {
        char c;
        
        // nFlag: print line numbers

        if (nFlag == 1 && bFlag == 0) 
        {
            int lineNum = 1;
            printf("%d. ", lineNum);
            while ((c = fgetc(file)) != EOF) 
            {
                printf("%c", c);
                
                if (c == '\n') 
                {
                    lineNum++;
                    printf("%d. ", lineNum);
                }
            }
        }

        // bFlag: print only non-blank lines


        else if (bFlag == 1 && nFlag == 0)  
        {
            while ((c = fgetc(file)) != EOF) 
            {
                if (c != '\n') 
                {
                    printf("%c", c);
                }
            }
        }

        // bFlag and nFlag: print only non-blank lines with line numbers

        else if (nFlag == 1 && bFlag == 1) 
        {
            char *line = NULL;
            ssize_t lineread;
            size_t length = 0;
            int lineNum = 1;
            while (lineread = getline(&line, &length, file) != -1)
            {
                if (strcmp(line, "\n") == 0)
                {
                    continue;
                }
                else
                {
                    printf("%d. ", lineNum);
                    printf("%s", line);
                    lineNum++;
                }
            }
        }

        else 
        {
            while ((c = fgetc(file)) != EOF) 
            {
                printf("%c", c);
            }
        }
        
        fclose(file);
    }
}


int main(int argc, char **argv) 
{
    int nFlag = 0;
    int bFlag = 0;

    if (argc == 0) 
    {
        printf("Please specify a file to print");
    } 
    
    else 
    {
        for (int i = 0; i < argc; i++) 
        {

            /*
                Default: prints the contents of the file
                Two Flags:
                    -n: displays the line numbers
                    -b: displays the unique lines only
            */

            if (argv[i][0] == '-') 
            {
                if (strcmp(argv[i], "-n") == 0) 
                {
                    nFlag = 1;
                } 
                
                else if (strcmp(argv[i], "-b") == 0) 
                {
                    bFlag = 1;
                }

                else if (strcmp(argv[i], "-h") == 0) 
                {
                    printf("Usage: cat [-n] [-b] [file]\n");
                    printf(" -n: displays the line numbers\n");
                    printf(" -b: displays the unique lines only\n");
                    printf(" -h: displays the help menu\n");
                    exit(0);
                }

            } 

            else 
            {
                printFile(argv[i], nFlag, bFlag);
                printf("\n");
            }
        }
    }

    printf("\n");
    return 0;
}

