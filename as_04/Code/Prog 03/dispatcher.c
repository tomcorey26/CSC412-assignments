#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void appendSlash(char *s)
{
    int length = strlen(s);
    s[length] = '/';
    s[length + 1] = '\0';
}

int main(int argc, char *argv[])
{
    //grab in and out path
    char *inputDirectory = argv[1];
    char *outputDirectory = argv[2];

    //loop thru command line
    for (int i = 3; i < argc; i++)
    {
        //arg list
        char **commandArgs;
        if (!strcmp(argv[i], "split"))
        {
            char inPath[50];
            strcpy(inPath, inputDirectory);
            appendSlash(inPath);
            strcat(inPath, argv[i + 1]);
            //allocate array of arguements
            commandArgs = calloc(4, sizeof(char *));
            commandArgs[0] = "./split";
            commandArgs[1] = inPath;
            commandArgs[2] = outputDirectory;
            commandArgs[3] = NULL;

            i += 1;
        }
        else if (!strcmp(argv[i], "rotate"))
        {
            char inPath[50];
            strcpy(inPath, inputDirectory);
            appendSlash(inPath);
            strcat(inPath, argv[i + 2]);
            commandArgs = calloc(5, sizeof(char *));
            commandArgs[0] = "./rotate";
            commandArgs[1] = argv[i + 1];
            commandArgs[2] = inPath;
            commandArgs[3] = outputDirectory;
            commandArgs[4] = NULL;
            i += 2;
        }
        else if (!strcmp(argv[i], "crop"))
        {
            char inPath[50];
            strcpy(inPath, inputDirectory);
            appendSlash(inPath);
            strcat(inPath, argv[i + 5]);

            commandArgs = calloc(8, sizeof(char *));

            commandArgs[0] = "./crop";
            commandArgs[1] = inPath;
            commandArgs[2] = outputDirectory;
            commandArgs[3] = argv[i + 1];
            commandArgs[4] = argv[i + 2];
            commandArgs[5] = argv[i + 3];
            commandArgs[6] = argv[i + 4];
            commandArgs[7] = NULL;

            i += 5;
        }

        int p = fork();

        if (p == 0)
        {
            execvp(commandArgs[0], commandArgs);
            exit(0);
        }
        else if (p > 0)
        {
        }
    }

    return 0;
}
