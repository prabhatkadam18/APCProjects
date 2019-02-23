//
//  PrimeFactorsRecursion.cpp
//  
//
//  Created by Prabhat Kadam on 01/02/19.
//

#include <iostream>
using namespace std;

int nextPrime(int n)
{
    int count=0;
    int flag=0;
    int i=n+1;
    while(flag==0)
    {
        count=0;
        for(int j=1;j<i;j++)
        {
            if(i%j==0)
            {
                count++;
            }
            if(count>1)
            {
                i++;
            }
            else
            {
                n=i;
                flag=1;
                break;
                //cout<<i;
                //return i;
            }
        }
    }
    return n;
}

void fun(int n)
{
    int static i=2;
    if(n==1)
    {
       // return 0;
    }
    else
    {
        if(n%i==0)
        {
            cout<<i<<" ";
            fun(n/i);
        }
        else
        {
            i=nextPrime(i);
            fun(n);
        }
    }
}
int main()
{
    fun(24);
    return 0;
}
