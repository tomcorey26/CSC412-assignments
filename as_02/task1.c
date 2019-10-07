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

char *sortString(char *s) {
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
  int letIdx = 0;
  int numIdx = letCount;
  int othIdx = letCount + numCount;
  for (int i = 0; repeatStr[i] != '\0'; i++) {
    if ((repeatStr[i] >= 'a' && repeatStr[i] <= 'z') ||
        (repeatStr[i] >= 'A' && repeatStr[i] <= 'Z')) {
      outStr[letIdx] = repeatStr[i];
      letIdx++;
    } else if (repeatStr[i] <= '9' && repeatStr[i] >= '0') {
      outStr[numIdx] = repeatStr[i];
      numIdx++;
    } else {
      outStr[othIdx] = repeatStr[i];
      othIdx++;
    }
  }
  printf("\"%s\" \n", outStr);
  return s;
}

int main() {
  char in[100];
  // printf() displays the string inside quotation
  while (strcmp(in, "EXIT") != 0) {
    printf("enter an input string:");
    scanf(" %[^\n]", in);
    char *s = sortString(in);
  }
  return 0;
}