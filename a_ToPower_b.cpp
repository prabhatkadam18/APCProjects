//
//  ReverseRecursion.cpp
//  
//
//  Created by Prabhat Kadam on 01/02/19.
//

#include <iostream>
using namespace std;
int fun(int a,int b)
{
    if(b==1)
        return a;
    else if(b==0)
        return 1;
    /*else if(b%2==0)
    {
        int p=fun(a,b/2);
        return p*p;
    }*/
    else
    {
        if(b%2!=0)
        {
            return a*fun(a,b-1);
        }
        else
        {
            return fun(a,b/2) * fun(a,b/2);
        }
    }
    /*else
    {
        int p=fun(a,b/2);
        return p*p*a;
    }*/
}

int main()
{
    int a=3,b=5;
    cout<<fun(a,b);
    return 0;
    
}
