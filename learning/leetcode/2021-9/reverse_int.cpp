#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int reverse(int x)
{
    long reverse_x = 0;
    do
    {
        long temp = abs(reverse_x);
        reverse_x = (reverse_x * 10 + x % 10);
        x /= 10;
    } while (x != 0);
    return reverse_x = (int)reverse_x ? reverse_x : 0;
}
bool isPalindrome(int x)
{
    if (x<0) return false;
    int reverse_x = 0;
    do
    {
        reverse_x = reverse_x * 10 + x % 10;
        x /= 10;
    } while (x);
    cout << reverse_x;
    return x-reverse_x ? true : false;
}

int main()
{
    int x = 0;
    while (true)
    {
        cin >> x;
        if (isPalindrome(x))
        {
            cout << "true" << endl;
        }
        else
        {
            cout << "false" << endl;
        }
    }
}