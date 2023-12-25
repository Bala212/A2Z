#include <bits/stdc++.h>
using namespace std;

class A
{
public:
    int a;
    int b;

    // A(int a, int b)
    // {
    //     this->a = a;
    //     this->b = b;
    // }

    // A(A &a){
        
    // }

    void fun(){
        cout<<"A\n";
    }
};

class B:public A{
    public:
        void fun(int a){
            cout<<"B\n";
        }
};

// void fun();

int main()
{
    // A a(2, 3);
    // A b = a;

    // int x = 3;
    // int &y = x;

    // cout<<y;

    // fun(); // will give error

    B b;
    b.fun();
}

// void fun(){} 