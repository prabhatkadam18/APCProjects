//
//  StringCountHashTable2.cpp
//  
//
//  Created by Prabhat Kadam on 22/02/19.
//

#include <iostream>
using namespace std;

struct Word
{
    char str[50];
    int count;
    Word *next;
}*np;

void init(Word *head[])
{
    for(int i=0;i<256;i++)
    {
        head[i]=NULL;
    }
}

void clear(char* s,int j)
{
    for(int i=0;i<j;i++)
    {
        s[i]='\0';
    }
}

Word* createNode(int c,char* s)
{
    np=new Word;
    np->count=c;
    strcpy(np->str,s);
    np->next=NULL;
    return np;
}

void update(Word* head,char* s)
{
    Word *ptr=new Word;
    if(head==NULL)
    {
        head=createNode(0, s);
    }
    else
    {
        Word *p=head;
        int flag=0;
        for(p=head;p->next!=NULL;p=p->next)
        {
            if(strcmp(p->str,s)==0)
            {
                p->count++;
                flag=1;
            }
        }
        if(flag==0)
        {
            Word *np=createNode(0, s);
            p->next=np;
        }
        
    }
}

int main()
{
    Word *head[256];
    init(head);
    
    char str[250]={"My Mame is Prabhat"};
    //scanf("%[^\n]s",str);
    strcat(str," ");
    
    char tmp[50]={""};
    int j=0;
    for(int i=0;str[i]!='\0';i++)       //seperate strings
    {
        if(str[i]==' ')
        {
            //tmp[j]='\0';
            update(head[(int)tmp[0]],tmp);
            clear(tmp,j);
            j=0;
        }
        else
        {
            tmp[j++]=str[i];
        }
        
    }
    
    return 0;
}
