//
//  SumOfDigitsRecursion.cpp
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
        cout<<endl<<"Sum is: ";
        return 0;
    }
    else
    {
        int sum=n%10;
        cout<<sum<<" ";
        sum+=fun(n/10);
        return sum;
    }
}
int main()
{
    int a=12314;
    cout<<fun(a);
    return 0;
}
