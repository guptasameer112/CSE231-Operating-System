#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void createDir(char *dirName, int mFlag, int vFlag) {
    long int permission = 0777;

    // Getting the Current Directory Path

    char cwd[1024];
    char *currentDirectory = getcwd(cwd, sizeof(cwd));
    strcat(currentDirectory, "/");
    strcat(currentDirectory, dirName);

    // mFlag: create a directory with a specific permission
    
    if (mFlag == 1 && vFlag == 0) {
        struct stat st = {0};
        printf("Enter the permission for the directory: ");
        permission = scanf("%d", &permission);

        if (permission > 0777 || permission < 00)
        {
            printf("invalid mode: %ld", permission);
            exit(1);
        }

        if (stat(currentDirectory, &st) == -1) {
            mkdir(currentDirectory, permission);
        } else {
            printf("\nDirectory already exists\n");
        }
    } 
    
    // vFlag: verbosly create a new directory

    else if (mFlag == 0 && vFlag == 1) {
        struct stat st = {0};
        if (stat(dirName, &st) == -1) {
            printf("Creating directory: %s", dirName);
            mkdir(dirName, permission);
            printf("\nDirectory Created\n");
        } else {
            printf("Directory already exists\n");
        }
    }

    // mFlag and vFlag: verbosly create a new directory with a specific permission

    else if (mFlag == 1 && vFlag == 1) {
        struct stat st = {0};
        printf("Enter the permission for the directory: ");
        permission = scanf("%d", &permission);

        if (permission > 0777 || permission < 00)
        {
            printf("invalid mode: %ld", permission);
            exit(1);
        }

        if (stat(dirName, &st) == -1) {
            printf("Creating directory: %s", dirName);
            mkdir(dirName, permission);
            printf("Directory Created");
        } else {
            printf("\nDirectory already exists");
        }
    }

    // No flags: create a new directory
    
    else {
        struct stat st = {0};
        if (stat(currentDirectory, &st) == -1) {
            mkdir(currentDirectory, 0700);
        } else {
            printf("\nDirectory already exists\n");
        }
    }
    
}

int main(int argc, char **argv) {

    int mFlag = 0;
    int vFlag = 0;

    /*
        Default: creates a directory
        Two Flags:
            -m: creates a directory with specified permission
            -v: creates a directory verbosly
    */

    if (argc == 0) {
        printf("Please specify a directory name");
    } 
    else 
    {
        for (int i = 0; i < argc; i++) 
        {
            if (argv[i][0] == '-') 
            {
                if (strcmp(argv[i], "-m") == 0) {
                    mFlag = 1;
                }
                else if (strcmp(argv[i], "-v") == 0) {
                    vFlag = 1;
                }
                else if (strcmp(argv[i], "-h") == 0)
                {
                    printf("Usage: mkdir [OPTION]... DIRECTORY...\n");
                    printf("  -m, --mode=MODE   set file mode (as in chmod)\n");
                    printf("  -v, --verbose     print a message for each created directory\n");
                    printf("  -h, --help        display this help and exit\n");
                    exit(0);
                }
                else
                {
                    printf("Invalid option: %s", argv[i]);
                }
            }
        }
    }

    printf("\n");
    return 0;
}

