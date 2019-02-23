//
//  RecursionSumOfArray.cpp
//  
//
//  Created by Prabhat Kadam on 02/02/19.
//

#include <iostream>
using namespace std;
int fun1(int a[])
{
    int index;
    for(int i=0;;i+=2)
    {
        if(a[i]==-1)
        {
            index=i;
            break;
        }
        else if(a[i+1]==-1)
        {
            index=i+1;
            break;
        }
    }
    return index;
}

void fun(int a[],int i,int index)
{
    int j=index-i-1;
    if(i<j)
    {
        
        fun(a,i+1,index);
        a[i]=a[i]+a[j];
        a[j]=a[i];
        //i++;
        //fun(a,i,index);
    }
}

int main()
{
    int a[10];
    int flag=0,i=0;
    for(int i=0;i<10;i++)
        cin>>a[i];

    int index=fun1(a);
    fun(a,0,index);
    for(int i=0;i<index;i++)
    {
        cout<<a[i]<<" ";
    }
}
