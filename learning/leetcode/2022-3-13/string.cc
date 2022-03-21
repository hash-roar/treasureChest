#include "../include.h"
#include <algorithm>

string repace_space(string const& str)
{
  int str_count=0;
  int str_oldsize = str.size();
  auto result = string{};
  for(int i=0;i<str.size()  ;i++)
  {
    if (str[i]==' ') {
      str_count++;
    }
  }
  result.resize(str.size()+str_count*2);
  int new_size = result.size();
  for(int i=new_size-1,j=str_oldsize-1;j<i;i--)
  {
      if (result[j]!=' ') {
          result[i]=result[j];
      }else {
      result[i]='0';
      result[i-1]='2';
      result[i-2]='%';
      i-=2;
      }
  }
  return result;
}

string reverse_len_string(string &str,int n)
{
    if (str.size()<n-1) {
        return "";
    }
    reverse(str.begin(),str.begin()+n);
    reverse(str.begin()+n,str.end());
    reverse(str.begin(),str.end());
    return str;
}



int main()
{
  return 0;
}



