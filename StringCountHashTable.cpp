//
//  StringCountHashTable.cpp
//  
//
//  Created by Prabhat Kadam on 16/02/19.
//

#include <iostream>
#include<string>
using namespace std;

struct Word
{
    char str[50];
    int count;
    Word *next;
};

void init(Word *head[])
{
    for(int i=0;i<256;i++)
    {
        head[i]=NULL;
    }
}
void update(Word *head,char s[])
{
    if(head==NULL)
    {
        head=new Word;
        strcpy(head->str,s);
        head->count=1;
        head->next=NULL;
    }
    else
    {
        int flag=0;
        Word *ptr=head;
        for(ptr=head;ptr->next!=NULL;ptr=ptr->next)
        {
            if(strcmp(ptr->str,s)==0)
            {
                ptr->count++;
                flag=1;
            }
        }
        if(flag==0)
        {
            Word *np=new Word;
            np->count=0;
            np->next=NULL;
            strcpy(np->str,s);
            ptr->next=np;
        }
    }
}


void print(Word *head,char *s)
{
    Word *ptr;
    ptr=head;
    for(ptr=head;ptr!=NULL;ptr=ptr->next)
    {
        //if(strcmp(ptr->str,s)==0)
        {
            cout<<ptr->count<<endl;
        }
    }
}

int main()
{
    Word *head[256];
    init(head);
    char str[250];
    scanf("%[^\n]s",str);
    strcat(str," ");    ///////////
    
    int start=0,j=0;
    char tmp[50];
    int i=0;
    for(i=0;str[i]!='\0';i++)       //seperate strings
    {
        if(str[i]==' ' )//|| i==strlen(str))
        {
            tmp[j]='\0';
            update(head[(int)tmp[0]],tmp);
            j=0;
            strcpy(tmp,"\0");
        }
        else
        {
            tmp[j++]=str[i];
        }
        
    }
    
    
    for(int i=0;str[i]!='\0';i++)       //printing
    {
        
        if(str[i]==' ' || i==strlen(str)-1)
        {
            tmp[j]='\0';
            cout<<tmp<<" ";
            print(head[(int)tmp[0]],tmp);
            j=0;
            
            strcpy(tmp,"\0");
        }
        else
        {
            tmp[j++]=str[i];
        }
    }
}
