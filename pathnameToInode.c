//CS 3377 
//Ira Garrett


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 64

int i;
char pathname[LEN];
char input[LEN];

//implicit declarations


//tokenize
struct tokenizedStringStruct
{
char **tokenizedStringArray;
int numberOfWords;
};


struct tokenizedStringStruct inputStruct; //declare inputStruct as 
void tokenize (char *pathname, char *delimiter)
{ 
        printf("\033[95mCHECK AT TOKENIZE: test1\033[0m\n");
        //variables
        char *tokenizedString;
        i = 0;    
        inputStruct.numberOfWords = 0;

        printf("\033[95mCHECK AT TOKENIZE: test2\033[0m\n");
        tokenizedString = strtok(pathname, delimiter);
           
        //iterate through each term in the string to determine pathname
        while( tokenizedString != NULL ) 
        {
                inputStruct.numberOfWords++;
                printf("\033[95mCHECK AT TOKENIZE: # of terms in input: %ld: \"%s\"\twith token %s\033[0m\n", strlen(tokenizedString),tokenizedString, delimiter);
                
                printf("++++++++++++++++++++++");
                inputStruct.tokenizedStringArray[i++] = tokenizedString;
                printf("____________________");
                tokenizedString = strtok(NULL, delimiter);
        }
        
        
        printf("\033[93mCHECK AT TOKENIZE input: \"%s\" \tdelimiter: \'%c\' \033[0m\n",pathname, *delimiter);
        //return tokenizedStringArray,numberOfWords;
}

int main()
{
        //variable declarations
        char *pathname;
        char *delimiter;
        pathname = "/a/b/c/d";
        delimiter = "/";
                       
        //get user input for a location
        printf("\033[94mPlease enter the pathname to the file (DEFAULT: %s):\n\t \033[0m",pathname);

        //get user input
        fgets(input, LEN, stdin);
        input[strlen(input) -1] = 0;  //kill "\n" at the end of the stirng      
        printf("\033[94mCHECK AT MAIN \"input\": \"%s\" \033[0m\n",input);        
        
        //overwrite the default value for pathname if user input is detected
        if(strcmp(input, ""))
        {
                printf("\033[94mCHECK AT MAIN user input detected \033[0m\n");
                pathname = input;

        }
        else
        {
                //no user input was detected
                printf("\033[94mCHECK AT MAIN \033[93m no\033[94m user input detected \033[0m\n");
        }
        

        printf("\033[94mCHECK AT MAIN pathname: \"%s\" \033[0m\n",pathname);
        
        //tokenize the input string
        tokenize(pathname, delimiter);
        printf("\033[94mCHECK AT MAIN pathname/input string tokenized. \033[0m\n");
        
        for(i = 0; i < inputStruct.numberOfWords; i++)
        {
                printf("\033[94mCHECK AT MAIN%s \033[0m\n",inputStruct.tokenizedStringArray[i]);
        }
        
}
