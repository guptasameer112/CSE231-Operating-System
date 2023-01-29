#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

/*
Inbuilt functions:

"cd",
"exit",
"pwd",
"help",
"echo"
*/


void execute(char *command, char *args[10]) 
{

    pid_t pid;

    pid = fork();
    if (pid == 0) 
    {
        if (execv(command, args) < 0) 
        {
            perror("shellinator");
        }
        exit(0);
    } 
    
    else if (pid < 0) 
    {
        perror("shellinator");
    } 
    
    else 
    {
        wait(NULL); 
    }
}

void execute_pthread(char *command, char *args[10]) 
{

    pthread_t thread_id;
    char *fullPath = malloc(100);

    strcpy(fullPath, command);

    for (int i = 1; i < 10; i++)
    {
        if (args[i] != NULL)
        {
            strcat(fullPath, " ");
            strcat(fullPath, args[i]);
        }
        else
        {
            break;
        }
    }

    pthread_create(&thread_id, NULL, (void *)system, fullPath);
    pthread_join(thread_id, NULL);
}

int main(int argc, char **argv)
{
    char *permanentPath = getcwd(NULL, 0);
    while (1) 
    {
        char *username = getenv("USER");
        char *homeDirectory = getenv("HOME");
        char *commands[] = {"exit", "help", "pwd", "cd", "echo", "ls", "cat", "date", "rm", "mkdir"};
        char *path = getcwd(NULL, 0);
        printf("%s@shellinator:%s$ ", username, path);

        char *commands_input = malloc(100 * sizeof(char));
        scanf("%[^\n]%*c", commands_input);

        char *args[100];
        int i = 0;
        char *token = strtok(commands_input, " ");
        while (token != NULL)
        {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        int commandSize = strlen(args[0]);

        char *command = malloc(commandSize * sizeof(char));
        strcpy(command, args[0]);

        int argsSize = 0;
        for (int i = 0; i < 100; i++)
        {
            if (args[i] != NULL)
            {
                argsSize++;
            }
            else
            {
                break;
            }
        }

        if (argsSize > 1)
        {
            for (int i = 0; i < argsSize; i++)
            {
                args[i] = args[i + 1];
            } 
            argsSize -= 1;   
        }

        int pthread_flag = 0;

        if (argsSize >= 1)
        {
            if (strcmp(args[0], "&t") == 0)
            {
                pthread_flag = 1;
            }  
        }
        
        if (strcmp(command, commands[0]) == 0) 
        {
            exit(0);
        } 
        
        else if (strcmp(command, commands[1]) == 0) 
        {
            printf("exit: exits the shell\n");
            printf("help: displays this message\n");
            printf("pwd: prints the current working directory\n");
            printf("cd: changes the current working directory\n");
            printf("echo: prints the arguments\n");
        } 
        
        else if (strcmp(command, commands[2]) == 0) 
        {
            printf("%s", path);
        } 
        
        else if (strcmp(command, commands[3]) == 0) 
        {

            if (strcmp(args[0], "~") == 0) {
                chdir(homeDirectory);
            } else if (strcmp(args[0], "..") == 0) {
                chdir("..");
            } else {
                chdir(args[0]);
            }
        } 
        
        else if (strcmp(command, commands[4]) == 0) 
        {
            printf("%s", args[0]);
        }

        else if (strcmp(command, commands[5]) == 0 || strcmp(command, commands[6]) == 0 || strcmp(command, commands[7]) == 0 || strcmp(command, commands[8]) == 0 || strcmp(command, commands[9]) == 0) 
        {
            
            char *commandPath = malloc(1024 * sizeof(char));
            strcpy(commandPath, permanentPath);
            strcat(commandPath, "/");
            strcat(commandPath, command);
            
            if (pthread_flag == 1)
            {
                execute_pthread(commandPath, args);
            }
            else
            {
                execute(commandPath, args);
            }
        }

        else 
        {
            printf("command not found");
        }
        
        printf("\n");
    }
    return 0;
}