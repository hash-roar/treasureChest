#include <iostream>
#include<vector>

using namespace std;


int main()
{
    vector<int> vc;
    int k = 0;
    for (int i = 0; i < 15; i++)
    {
        vc.push_back(i+1);
    }
    for (int i = 0; i < vc.size(); i++)
    {
       cout<<vc[i]<<endl;
    }
    
    


    return 0;
}