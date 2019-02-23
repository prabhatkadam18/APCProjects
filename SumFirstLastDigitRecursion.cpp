//
//  SumFirstLastDigitRecursion.cpp
//  
//
//  Created by Prabhat Kadam on 02/02/19.
//

#include <iostream>
using namespace std;

int fun(int n,int flag)
{
    if(flag==0)
    {
        flag=1;
        return n%10+fun(n/10,flag);
    }
    else if(n/10==0)
    {
        return n;
    }
    else
    {
        return fun(n/10,flag);
    }
}
int main()
{
    int num;
    cin>>num;
    cout<<fun(num,0);
    return 0;
}
