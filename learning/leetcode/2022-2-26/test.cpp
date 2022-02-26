
#include <iostream>

using namespace std;

template <typename T>
void swap_data(T& a, T& b)
{
  auto temp = a;
  a = b;
  b = a;
}

int main()
{
  int intarr[] ={1,2,3,4};
  swap_data(intarr[0],intarr[1]);
  cout<<intarr[0]<<endl;
  return 0;
}
