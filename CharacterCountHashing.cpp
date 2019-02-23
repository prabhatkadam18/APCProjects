//
//  CharacterCountHashing.cpp
//  
//
//  Created by Prabhat Kadam on 17/02/19.
//

#include <iostream>
using namespace std;

int main()
{
    char str[50];
    int ar[256]={0};
    //cin.get(str);
    scanf("%[^\n]s",str);
    for(int i=0;str[i]!='\0';i++)
    {
        ar[(int)str[i]]++;
    }
    for(int i=0;i<256;i++)
    {
        if(ar[i]!=0 && i!=(int)' ')
            cout<<(char)i<<"-"<<ar[i]<<" ";
    }
}
