#include<iostream>
using namespace std;

void add(int a[],int i,int j)
{
  a[i]=a[i]+a[j];
  a[j]=a[i];
}

void fun(int a[],int i,int j)
{
  int static k;
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
    //i=i+1;
    //j=j+2;
    fun(a,i+1,j+2);
    add(a,i,k-i);
  }
}

int main()
{
  int a[]={12,2,4,4,10,5,-1,23};
  fun(a,0,0);
  for(int i=0;i<6;i++)
  cout<<a[i]<<" ";
}
