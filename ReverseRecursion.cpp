//
//  ReverseRecursion.cpp
//  
//
//  Created by Prabhat Kadam on 01/02/19.
//

#include <iostream>
using namespace std;

int fun(int n,int x)
{
    if(n/10==0)
    {
        return x*10+n;
    }
    else
    {
        x=x*10+n%10;
        x=fun(n/10,x);
        return x;
    }
    
}

int main()
{
    int a=1234;
    cout<<fun(a,0);
    return 0;
}
