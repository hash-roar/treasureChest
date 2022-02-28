
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  
  vector<char> char_arr{};
  for(int i=0;i<26;i++)
  {
    char_arr.push_back(static_cast<char>('a'+i));
  }
  char_arr.push_back('\0');
  const char* str = &char_arr[0];
  cout<<str<<endl;
    return 0;
}
