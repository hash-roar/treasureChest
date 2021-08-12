#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <class T>

void swamp(T&a,T&b)
{
    T tem = a;
    a= b;
    b= tem;
}



int main()
{
   int a= 12,b=1234;
   swamp(a,b);
   cout<<a<<"______"<<b<<endl;
    return 0;
}