#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isReapeat(char *str, char let) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (let == str[i])
      return 1;
  }
  return 0;
}

char *sortByAsc(char *str) {
  for (int i = 0; i < strlen(str); i++) {
    for (int j = 0; j < strlen(str); j++) {
      if (str[j] > str[i]) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
      }
    }
  }
  return str;
}

void sortString(char *s) {
  // stores address of malloc allocated memory (first block of memory)
  // allocate memory for sorted string +1 for the null character
  char *outStr = (char *)malloc(strlen(s) + 1);
  char *repeatStr = (char *)malloc(strlen(s) + 1);

  // set last value to be null value
  outStr[strlen(s)] = '\0';

  int letCount = 0;
  int numCount = 0;
  int othCount = 0;
  int currIdx = 0;
  // loop through input string and get counts
  for (int i = 0; s[i] != '\0'; i++) {
    if (!isReapeat(repeatStr, s[i])) {
      // add to non repeat string
      repeatStr[currIdx] = s[i];
      currIdx++;

      if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
        letCount++;
      } else if (s[i] <= '9' && s[i] >= '0') {
        numCount++;
      } else {
        othCount++;
      }
    }
  }
  char *letterStr = (char *)malloc(letCount + 1);
  char *numStr = (char *)malloc(numCount + 1);
  char *othStr = (char *)malloc(othCount + 1);

  for (int i = 0; repeatStr[i] != '\0'; i++) {
    if ((repeatStr[i] >= 'a' && repeatStr[i] <= 'z') ||
        (repeatStr[i] >= 'A' && repeatStr[i] <= 'Z')) {
      // add to letter string
      letterStr[letCount - 1] = repeatStr[i];
      letCount--;
    } else if (repeatStr[i] <= '9' && repeatStr[i] >= '0') {
      // ad to num string
      numStr[numCount - 1] = repeatStr[i];
      numCount--;
    } else {
      // add to oth string
      othStr[othCount - 1] = repeatStr[i];
      othCount--;
    }
  }
  letterStr = sortByAsc(letterStr);
  numStr = sortByAsc(numStr);
  othStr = sortByAsc(othStr);

  // print
  printf("\"%s", letterStr);
  printf("%s", numStr);
  printf("%s\"\n", othStr);
  return;
}

int main() {
  char in[100];
  // printf() displays the string inside quotation
  while (strcmp(in, "EXIT") != 0) {
    printf("enter an input string:");
    scanf(" %[^\n]", in);
    sortString(in);
  }
  return 0;
}
