/*
 *Given the pathname of a file, e.g. /a/b/c/d, write a C program to find the file and prints its information, such as the file type, owner id, size, date of creation and data block numbers, including indirect and double indirect blocks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <fcntl.h>
#include   <time.h>
#include   <sys/types.h>
#include   <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include   "ext2_fs.h"

//getFileType
char *getFileType(int mode )
{
    char *type = NULL;

    if(S_ISREG(mode))type = "Regular";
    else if(S_ISDIR(mode))type = "Directory";
    else if(S_ISCHR(mode))type = "Character Device";
    else if(S_ISBLK(mode))type = "Block Device";
    else if(S_ISFIFO(mode))type = "Pipe";
    else if(S_ISLNK(mode))type = "Symbolic link";
    else if(S_ISSOCK(mode))type = "Socket";
    else type = "Unknown";
    return type;
}


//getFileInfo
int getFileInfo(const char *FILEName)
{
    //variable definitions
    struct stat fileStat;
    int fd=0;
    char *StatFields[10] = {
            "inode ",
            "protection",
            "hard links",
            "user id",
            "group ID",
            "size",
            "last accessed",
            "last status change",
            "File Type" };
    const char *filename = FILEName;

    //printf("(getFileInfo) File to read data of: %s\n", FILEName);

    //exit if there is an error in opening the file
    if ( ( fd = open (filename , O_RDONLY) ) == -1){
        printf("Error: could not open file \"%s\" is it a directory?\n", filename);
        exit (1) ;
    }

    //
    if(fstat(fd, &fileStat)<0) return 1;

    //print the file information
    printf("Information for file \"%s\"\n",filename);

    for(int i = 0; StatFields[i] != NULL; i++)
    {
        //printf("(getFileInfo) StatFields[%d]: %s\n",i,StatFields[i]);
        printf("\n%s:\t\t", StatFields[i]);
        switch(i)
        {
            //inode number
            case 0:
                printf("%ld",fileStat.st_ino);
                break;

            //protection
            case 1:
                printf("%d",fileStat.st_mode);
                break;

            //number of hard links
            case 2:
                printf("%ld",fileStat.st_nlink);
                break;

            //user id of owner
            case 3:
                printf("%d",fileStat.st_uid);
                break;

            //group id of owner
            case 4:
                printf("%d",fileStat.st_gid);
                break;

            //size
            case 5:
                printf("%ld",fileStat.st_size);
                break;

            //time last accessed
            case 6:
                printf("%ld",fileStat.st_atime);
                break;

            //time of last status change
            case 7:
                printf("%ld",fileStat.st_ctime);
                break;

            //file type
            case 8:
                printf("%s\n",getFileType(fileStat.st_mode));
                break;

        }
    }


    /*printf("mode: %d\n",fileStat.st_mode);
    printf("File Size: \t\t%ld bytes\n",fileStat.st_size);
    printf("Number of Links: \t%ld\n",fileStat.st_nlink);
    printf("File inode: \t\t%ld\n",fileStat.st_ino);
     */

}

//printArray
void printArray(const char **array);
void printArray(const char **array)
{
    for (int i = 0; array[i] != NULL; i++)
    {
        printf("(printArray) '%s' has length %ld\n", array[i], strlen(array[i]));
    }
}

//changeDirectory
int changeDirectory(const char *PATH)
{
    char buf[256];
    char *cwd = getcwd(buf, 256);
    int fd = 0;

    //printf("(changeDirectory) file %s is a Directory\n", PATH);

    //call chdir on the file
    int cd = chdir(PATH);

    //printf("(changeDirectory) cd: %d\n",cd);
    //printf("(changeDirectory) cwd: %s\n", cwd);

    //print that there was an error if file is not found
    if (cd) printf("error: directory \"%s\" in directory \"%s\" not found\n", PATH, cwd);

    return cd;
}
void changeDirectoryForArrayPath(const char **PATH)
{
    //define variables
    int failure;
    char buf[255];

    //print the array being passed
    //printArray(PATH);

    //cd to the root ("/") directory
    //changeDirectory("/");
    chdir("/");

    //iterate through each of the tokenized strings in the filepath
    for(int i = 0; PATH[i] != NULL; i++)
    {
        //call the i(th) element of PATH and call it to changeDirectory
        //if(PATH[i+1] != NULL)
        failure = changeDirectory(PATH[i]); //failure is going to be 0 if the directory is properly changed, -1 if there is an error

        //the last element in PATH is the device
        if(PATH[i+1] == NULL)
        {
            //printf("(changeDirectoryForArrayPath) last element is %s\n",PATH[i]);
            getFileInfo(PATH[i]);
        }


        //if there is an error in changing the directory
        if(failure) break;
    }
}

//getPATHNAME
char *getPATHNAME(int argc, char *argv[])
{
    //variable definition
    char *PATHNAME = malloc(sizeof(char) * 255);

    //exit the program if there is no path supplied
    if(argc < 2)
    {
        printf("Error: no pathname provided in code execution\n");
        exit(3);
    }

        //if too many arguments are provided on code execution
    else if(argc > 2)
    {
        printf("Error: too many values provided\n");
        exit(2);
    }

        //if only one argument is provided
    else
    {
        strcpy(PATHNAME, argv[1]);
        //printf("PATHNAME: %s \n", PATHNAME);
    }

    return PATHNAME;
}

//tokenizePATHNAME
const char **TokenizePATHNAME(char *PATHNAME, const char *KEY);
const char **TokenizePATHNAME(char *PATHNAME, const char *KEY)
{
    //initial variables
    int i;
    char s [256];

    //allocate space for the array of strings for the path
    const char **TokenizedPATH = malloc(sizeof(char) * 255);

    //tokenize the string PATHNAME based on the key KEY
    strcpy(s, PATHNAME);
    char* token = strtok(s, KEY);
    i = 0;

    //while there are still characters left
    while (token != NULL)
    {

        TokenizedPATH[i++] = token;
        //printf("token: %s\n", token);
        token = strtok(NULL, KEY);
    }

    //ensure that the TokenizedPATH is null-terminated
    TokenizedPATH[sizeof(TokenizedPATH)] = NULL;

    //printf all the tokenized strings of the path
    /*
     * for(int i = 0; TokenizedPATH[i] != NULL; i++)
    {
        printf("(TokenizePATHNAME) Term %d of TokenizedPATH (which has size %ld): %s \n",i,sizeof(TokenizedPATH[i]),TokenizedPATH[i]);
    }
     */

    //print the array TokenizedPATH
    //printArray(TokenizedPATH);

    //change directory to TokenizedPATH
    changeDirectoryForArrayPath(TokenizedPATH);

    return TokenizedPATH;
}

//main
int main(int argc, char *argv[]) {

    //define variables
    char *KEY;
    int i;

    char *PATHNAME;

    //define PATHNAME to be the first argument provided by the user
    PATHNAME = getPATHNAME(argc, argv);

    //call tokenize PATHNAME with '/' as the key
    KEY = "/";
    TokenizePATHNAME(PATHNAME, KEY);



    return 1;

}
