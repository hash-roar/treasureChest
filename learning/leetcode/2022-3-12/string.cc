#include "../include.h"
#include <string.h>

void reverse_string(char* str)
{
  int len = strlen(str);
  for (int i = 0, j = len - 1; i < len / 2; i++, j--) {
    swap_data(str[i], str[j]);
  }
}



int main()
{
  return 0;
}
