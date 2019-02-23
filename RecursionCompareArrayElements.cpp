#include<iostream>
using namespace std;

int equal(int a[],int i,int j)
{
  if(a[i]==a[j])
    return 1;
  else
    return 0;
}

int fun(int a[],int i,int j)
{
  int static r=1,k;
  if(r==0)
    return 0;
  else
  {
    if(a[j]==-1)
    {
      j--;i--;k=j;
    }
    else if(a[j+1]==-1)
    {
      k=j;
    }
    else
    {
      r=fun(a,i+1,j+2);
      int p=equal(a,i,k-i);
      return p;
    }
  }
  return r;
}

int main()
{
  int a[]={12,2,3,3,2,12,-1,23};
  cout<<fun(a,0,0);
  //for(int i=0;i<6;i++)
  //cout<<a[i]<<" ";
}
