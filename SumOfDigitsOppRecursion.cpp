//
//  SumOfDigitsOppRecursion.cpp
//
//
//  Created by Prabhat Kadam on 01/02/19.
//

#include <iostream>
using namespace std;

int fun(int n)
{
    if(n==0)
    {
        return 0;
    }
    else
    {
        int r=n%10;
        int sum=r+fun(n/10);
        cout<<r<<" ";
        return sum;
    }
}

int main()
{
    int a=12134;
    int sum=fun(a);
    cout<<endl<<"Sum is: "<<sum;
    return 0;
}
