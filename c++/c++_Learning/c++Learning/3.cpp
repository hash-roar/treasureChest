#include <iostream>

using namespace std;

class Person
{
private:
    /* data */
    int a;

public:
    Person();
    Person(int a_out)
    {
        a = a_out;
    }
    Person(const Person &p)
    {
        a = p.a;
        cout << a << "拷贝构造" << endl;
    }
    int getA()
    {
        return a;
    }
    void setA() const{
        
    }
    ~Person();
};

Person::Person(/* args */)
{
    cout << "默认构造" << endl;
}

Person::~Person()
{
}

int main()
{
    
    return 0;
}