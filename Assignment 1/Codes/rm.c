#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


void deleteDir(char *dirName, int fFlag, int vFlag) 
{

    // vFlag: verbosly delete a directory

    if (vFlag == 1 && fFlag == 0) 
    {
        struct stat st = {0};
        if (stat(dirName, &st) == -1) 
        {
            printf("Directory does not exist");
        } 
        
        else 
        {
            printf("Deleting directory: %s", dirName);
            rmdir(dirName);
            printf("\nDirectory Deleted");
        }
    }

    // fFlag: delete a file

    else if (vFlag == 0 && fFlag == 1) 
    {
        struct stat st = {0};
        
        if (stat(dirName, &st) == -1) 
        {
            printf("File does not exist");
        } 
        
        else 
        {
            remove(dirName);
        }
    }

    // vFlag and fFlag: verbosly delete the file

    else if (vFlag == 1 && fFlag == 1) 
    {
        struct stat st = {0};
        if (stat(dirName, &st) == -1) 
        {
            printf("File does not exist");
        } 
        
        else 
        {
            printf("Deleting file: %s", dirName);
            remove(dirName);
            printf("\nFile Deleted");
        }
    }

    // Default: Delete the directory

    else 
    {
        struct stat st = {0};
        if (stat(dirName, &st) == -1) 
        {
            printf("Directory does not exist");
        } 
        
        else 
        {
            rmdir(dirName);
        }
    }
}


int main(int argc, char **argv) {

    int fFlag = 0;
    int vFlag = 0;

    /*
        Default: delete the directory
        Two Flags:
            -f: deletes a file
            -v: display verbose output (explain what is being deleted)
    */

    if (argc == 0) 
    {
        printf("Please specify a directory name");
    } 

    else
    {
        for (int i = 0; i < argc; i++)
        {
            if (argv[i][0] == '-')
            {
                
                if (strcmp(argv[i], "-f") == 0)
                {
                    fFlag = 1;
                }

                else if (strcmp(argv[i], "-v") == 0)
                {
                    vFlag = 1;
                }

                else if (strcmp(argv[i], "-h") == 0)
                {
                    printf("Usage: rm [OPTION]... DIRECTORY...\n");
                    printf("  -f: delete files\n");
                    printf("  -v: explain what is being done\n");
                    printf("  -h: display this help and exit\n");
                    exit(0);
                }

            }

            else
            {
                deleteDir(argv[i], fFlag, vFlag);
            }
            
        }
    }

    printf("\n");
    return 0;
}

