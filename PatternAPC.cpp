//
//  PatternAPC.cpp
//  
//
//  Created by Prabhat Kadam on 01/02/19.
//

#include <iostream>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int flag=0;
    char ch='A';
    for(int i=0;i<n;i++)
    {
        //cout<<(char)(ch+i);
        for(int j=0;j<n-i;j++)
        {
            cout<<char(ch+j);
        }
        for(int k=1;k<2*i;k++)
        {
            cout<<" ";
        }
        if(flag==0)
        {
            flag=1;
            for(int j=n-2;j>=0;j--)
            {
                cout<<(char)(ch+j);
            }
        }
        else
        {
            for(int j=n-i-1;j>=0;j--)
            {
                cout<<(char)(ch+j);
            }
            //i++;
        }
        cout<<"\n";
    }
    return 0;
}
