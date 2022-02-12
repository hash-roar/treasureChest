#include <array>
#include <iostream>
#include <chrono>
#include <ostream>
#include <string>

using namespace std::chrono;
using namespace std;

int main()
{
    
    cout<<system_clock::now().time_since_epoch().count()<<endl;
    cout<<system_clock::now().time_since_epoch().count()<<endl;
    return 0;
}
