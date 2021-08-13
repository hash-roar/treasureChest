#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    fstream fd("1.txt",ios::out | ios::binary);
    if(!fd.is_open())
    {
        cout<<"文件打开失败"<<endl;
        return 0 ;
    }
    string buffer;
    while (getline(fd,buffer))
    {
        cout<<buffer<<endl;
    }
    
    
    fd.close();
    return 0;
}