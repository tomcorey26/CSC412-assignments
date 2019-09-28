#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Category
{
  int index;
  char name[50];
  char ranges[20][2];
};
struct Categorys
{
  int categoryAmount;
  struct Category categorys[];
};

int isReapeat(char *str, char let)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (let == str[i])
      return 1;
  }
  return 0;
}

char *sortByAsc(char *str)
{
  for (int i = 0; i < strlen(str); i++)
  {
    for (int j = 0; j < strlen(str); j++)
    {
      if (str[j] > str[i])
      {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
      }
    }
  }
  return str;
}

int isInRange(char currStr, char *range)
{
  if (currStr >= range[0] && currStr <= range[1])
  {
    return 1;
  }
  return 0;
}

void sortString(char *s)
{
  struct Category letter =
      {
          1,
          "letter",
          {{'a', 'z'}, {'A', 'Z'}}};

  struct Category number =
      {
          2,
          "number",
          {{'0', '9'}}};

  // stores address of malloc allocated memory (first block of memory)
  // allocate memory for sorted string +1 for the null character
  char *repeatStr = (char *)malloc(strlen(s) + 1);

  // initialize count variables
  int letCount = 0;
  int numCount = 0;
  int othCount = 0;
  int currIdx = 0;

  // loop through input string and get counts
  for (int i = 0; s[i] != '\0'; i++)
  {
    if (!isReapeat(repeatStr, s[i]))
    {
      // add to non repeat string
      repeatStr[currIdx] = s[i];
      currIdx++;

      if ((isInRange(s[i], letter.ranges[0])) ||
          (isInRange(s[i], letter.ranges[1])))
      {
        letCount++;
      }
      else if (isInRange(s[i], number.ranges[0]))
      {
        numCount++;
      }
      else
      {
        othCount++;
      }
    }
  }
  char *letterStr = (char *)malloc(letCount + 1);
  char *numStr = (char *)malloc(numCount + 1);
  char *othStr = (char *)malloc(othCount + 1);

  for (int i = 0; repeatStr[i] != '\0'; i++)
  {
    if (isInRange(repeatStr[i], letter.ranges[0]) ||
        isInRange(repeatStr[i], letter.ranges[1]))
    {
      // add to letter string
      letterStr[letCount - 1] = repeatStr[i];
      letCount--;
    }
    else if (isInRange(repeatStr[i], number.ranges[0]))
    {
      // ad to num string
      numStr[numCount - 1] = repeatStr[i];
      numCount--;
    }
    else
    {
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
int main()
{
  char in[100];
  // printf() displays the string inside quotation
  while (strcmp(in, "EXIT") != 0)
  {
    printf("enter an input string:");
    scanf(" %[^\n]", in);
    sortString(in);
  }
  return 0;
}
