//
//  Test_CmdLineArgs.cpp
//  SearchEngine
//
//  Created by Prabhat Kadam on 21/02/19.
//  Copyright © 2019 Prabhat Kadam. All rights reserved.
//

#include <iostream>
#define BASE_ADDRESS "www.chitkara.edu.in"


using namespace std;

int crawler(int argc,char *argv[])
{
    int count_ok=1;      //check for count
    if(argc!=4)
    {
        count_ok=0;
    }
    
    char seed_url[70];
    strcpy(seed_url,argv[1]);
    int base_length;
    for(base_length=0;BASE_ADDRESS[base_length]!='\0';base_length++);
    int same=1;
    for(int i=0;i<base_length && same!=0;i++)
    {
        if(BASE_ADDRESS[i]!=seed_url[i])
        {
            same=0;
        }
    }
    if(same==0)
    {
        cout<<"Not Same";
        return -1;
    }
    return 0;
}


int main(int argc,char *argv[])
{
    crawler(argc,argv);
}
