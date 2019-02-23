//
//  RemoveNoise.cpp
//  
//
//  Created by Prabhat Kadam on 07/02/19.
//

#include <iostream>
using namespace std;

void makeZeroColumn(int ar[4][6],int a,int c)
{
    for(int i=0;i<c;i++)
    {
        ar[a][i]=0;
    }
}
void makeZeroRow(int ar[4][6],int r,int a)
{
    for(int i=0;i<r;i++)
    {
        ar[i][a]=0;
    }
}

int main()
{
    int ar[4][6]={{1,1,1,1,1,1},{1,1,1,1,1,0},{1,1,1,0,0,1},{1,1,1,1,0,1}},rowflag=1,colflag=1;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<6;j++)
        {
            if(i==0)
            {
                if(ar[i][j]==0)
                {
                    rowflag=0;
                }
            }
            if(j==0)
            {
                if(ar[i][j]==0)
                {
                    colflag=0;
                }
            }
            if(i!=0 && j!=0)
            if(ar[i][j]==0)
            {
                ar[0][j]=0;
                ar[i][0]=0;
            }
        }
    }
    
    for(int i=1;i<4;i++)
    {
        if(ar[i][0]==0)
            makeZeroColumn(ar,i,6);
    }
    
    for(int j=1;j<6;j++)
    {
        if(ar[0][j]==0)
            makeZeroRow(ar,0,j);
    }
    
    if(rowflag==0)
        makeZeroColumn(ar,0,6);
    if(colflag==0)
        makeZeroRow(ar,4,0);
    
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<6;j++)
            cout<<ar[i][j]<<" ";
        cout<<"\n";
    }
    
    
    return 0;
}
