#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *sortString(char *s) {
    //stores address of malloc allocated memory (first block of memory)
    //allocate memory for sorted string +1 for the null character  
    char *outStr = (char *)malloc(strlen(s) +1);
    
    //set last value to be null value
    outStr[strlen(s)] = '\0';

    int letCount = 0;
    int numCount = 0;
    int othCount = 0;

    //loop through input string and get counts
    for (int i = 0; s[i] != '\0'; i++) {
        printf("%c",s[i]);
        if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')){
            letCount++;
        }
        else if (s[i] <= 9 && s[i] >= 0){
            numCount++;
        } else {
            othCount++;
        }
    }

    for (int i = 0; s[i] != '\0'; i++) {

    }
    return s;
}

int main()
{
    char in[100];
   // printf() displays the string inside quotation
    printf("enter an input string:");
    scanf("%s",in);
    // char *s = sortString(in);
    return 0;
}

