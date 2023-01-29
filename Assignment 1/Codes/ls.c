#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void printDir(char *dirName, int aFlag, int lFlag) 
{
    DIR *dir;
    struct dirent *ent;

    // check if the directory exists

    if ((dir = opendir(dirName)) != NULL) 
    {
        while ((ent = readdir(dir)) != NULL) 
        {
            if (aFlag == 0) 
            {
                if (ent->d_name[0] != '.') 
                {
                    printf("%s", ent->d_name);

                    // lFlag: print the type of file

                    if (lFlag == 1) 
                    {
                        
                        if (ent->d_type == DT_DIR)
                        {
                            printf(" (directory)");
                        }

                        else
                        {
                            printf(" (file)");
                        }
                        printf("\n");
                    } 
                    
                    else 
                    {
                        printf(" ");
                    }
                }
            } 
            
            // aFlag: print all files

            else 
            {
                printf("%s", ent->d_name);
                if (lFlag == 1) 
                {
                    printf("\n");
                } 
                
                else 
                {
                    printf("  ");
                }
            }
        }
        closedir(dir);
    } 
    
    else 
    {
        perror("Could not open directory");
    }
}


int main(int argc, char **argv) 
{
    
    int aFlag = 0;
    int lFlag = 0;

    /*
        Default: prints all files in the current directory
        Two Flags:
            -a: displays all files in the directory (including hidden files)
            -l: displays the type of file (file or directory)
    */

    if (argc == 0)
    {
        printf("Please specify a directory to print");
    }

    else
    {
        for (int i = 0; i < argc; i++)
        {
            if (argv[i][0] == '-')
            {
                
                if (strcmp(argv[i], "-a") == 0)
                {
                    aFlag = 1;
                }

                else if (strcmp(argv[i], "-l") == 0)
                {
                    lFlag = 1;
                }

                else if(strcmp(argv[i], "-h") == 0)
                {
                    printf("Usage: ls [OPTION]... [FILE/FOLDER]...\n");
                    printf("  -a  do not ignore entries starting with .\n");
                    printf("  -l  use a long listing format\n");
                    printf("  -h  display this help and exit\n");
                    exit(0);
                }


            }

            else
            {
                printDir(argv[i], aFlag, lFlag);
            }
                    
        }
    }

    printf("\n");
    return 0;
}

