#include<iostream>
#include <pthread.h>
#include <unistd.h>
using namespace  std;

int main(int arg_count,char * arg[])
{
    cout<<"son:"<<getpid()<<endl;
    cout<<"arg_count"<<arg_count<<"   arg:"<<arg[1]<<endl;

    return 0;
}
