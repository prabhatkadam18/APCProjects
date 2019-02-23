//
//  LinkedListIntro.cpp
//  
//
//  Created by Prabhat Kadam on 16/02/19.
//

#include <iostream>
using namespace std;

struct Node
{
    int in;
    Node *next;
};

int main()
{
    Node *head=NULL;
    for(int i=0;i<3;i++)
    {
        int val;
        cin>>val;
        if(head==NULL)
        {
            head=new Node;
            head->in=val;
            head->next=NULL;
        }
        else
        {
            Node *ptr=new Node;
            ptr->in=val;
            ptr->next=NULL;
            Node *p=new Node;
            for(p=head;p->next!=NULL;p=p->next);
            p->next=ptr;
        }
        
        
    }
    for(Node *ptr=head;ptr!=NULL;ptr=ptr->next)
    {
        cout<<ptr->in;
    }
}
