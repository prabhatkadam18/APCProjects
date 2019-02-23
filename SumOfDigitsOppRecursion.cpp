//
//  SumOfDigitsOppRecursion.cpp
//  
//
//  Created by Prabhat Kadam on 01/02/19.
//



//    WORKING BUT NOT HOW IT SHOULD



#include <iostream>
using namespace std;

int fun(int n,int x)
{
    if(n/10==0)
    {
        return x+n;
    }
    else
    {
        x=x+n%10;
        x=fun(n/10,x);
        return x;
    }
}

int main()
{
    int a=12134;
    cout<<fun(a,0);
    return 0;
}
