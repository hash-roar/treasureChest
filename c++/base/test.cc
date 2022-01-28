#include <iostream>
#include <chrono>
#include <ostream>

using namespace std::chrono;
using namespace std;

int main()
{
    
    cout<<system_clock::now().time_since_epoch().count()<<endl;
    return 0;
}
