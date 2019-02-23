//
//  RobotCleaning.cpp
//  
//
//  Created by Prabhat Kadam on 07/02/19.
//

#include <iostream>
using namespace std;

void fun(int r,int c,int ar[4][5],int i,int j)
{
    if( i<0 || i>=r || j<0 || j>=c || ar[i][j]==-1 || ar[i][j]==0 )
    {
        
    }
    
    else
    {
        cout<<ar[i][j]<<" ";
        ar[i][j]=0;
        fun(4,5,ar,i,j-1);
        fun(4,5,ar,i-1,j);
        fun(4,5,ar,i,j+1);
        fun(4,5,ar,i+1,j);
    }
}

int main()
{
    int ar[4][5]={{1,2,-1,6,4},{3,-1,6,4,-1},{2,4,7,6,5},{7,-1,6,9,-1}};
    fun(4,5,ar,1,2);
    return 0;
}
