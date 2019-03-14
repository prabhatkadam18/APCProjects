//
//  SearchEngine.c
//  
//
//  Created by Prabhat Kadam on 07/03/19.
//

#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<string.h>
#include<stdbool.h>

#define BASE_ADDRESS "www.chitkara.edu.in"
#define TEMPFILE "/Users/prabhatkadam/Desktop/temp.txt"
#define MAX_URL 100


FILE *fout;
void testDir(char *dir)
{
    struct stat statbuf;
    if ( stat(dir, &statbuf) == -1 )
    {
        fprintf(stderr, "-----------------\n");
        fprintf(stderr, "Invalid directory\n");
        fprintf(stderr, "-----------------\n");
        exit(1);
    }
    
    //Both check if there's a directory and if it's writable
    if ( !S_ISDIR(statbuf.st_mode) )
    {
        fprintf(stderr, "-----------------------------------------------------\n");
        fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
        fprintf(stderr, "-----------------------------------------------------\n");
        exit(1);
    }
    
    if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR )
    {
        fprintf(stderr, "------------------------------------------\n");
        fprintf(stderr, "Invalid directory entry. It isn't writable\n");
        fprintf(stderr, "------------------------------------------\n");
        exit(1);
    }
}

void getpage(char *url)
{
    int i=0;
    for(i=0;url[i]!='\0';i++);
    int const url_length=i;
    char urlbuffer[url_length+300];
    strcat(urlbuffer, "wget -O ");
    strcat(urlbuffer,TEMPFILE);
    strcat(urlbuffer," ");
    strcat(urlbuffer, url);
    strcat(urlbuffer," >/dev/null 2>&1");
    system(urlbuffer);
    printf("\n------Got Page------\n");
}

int testPage(char *url)
{
    int i;
    for(i=0;url[i]!='\0';i++);
    char urlbuffer[i+200];
    urlbuffer[0]='\0';
    strcat(urlbuffer,"wget --spider ");
    strcat(urlbuffer,url);
    strcat(urlbuffer," >/dev/null 2>&1");
    if(!system(urlbuffer))
    {
        printf("Valid URL");
        return 1;
    }
    else
    {
        printf("Invalid URL");
        return 0;
    }
}

void savePage(char *url,char *depth,char *dir)
{
    int static id=1;         // change to int
    char *buffer=(char*)malloc(300*sizeof(char));
    
    char str_id[5];
    sprintf(str_id,"%d",id);
    strcat(buffer,dir);
    strcat(buffer,str_id);
    strcat(buffer,".txt");
    fout=fopen(buffer,"a");
    printf("----File Created----\n");
    
    fprintf(fout,"%s\n",url);
    printf("----URL Written----\n");
    
   // fprintf(fout,"%s\n\n",depth);//
    
    fseek(fout,0,SEEK_END);
    
    strcpy(buffer,"\0");
    strcat(buffer,"cat>> ");
    strcat(buffer,dir);
    strcat(buffer,str_id);
    strcat(buffer,".txt ");
    strcat(buffer,TEMPFILE);
    system(buffer);
    printf("----File Copied----\n");
    id++;
    
    fclose(fout);
    free(buffer);
}

int fileSize()
{
    struct stat st;
    stat(TEMPFILE,&st);
    return st.st_size;
}

void saveFileData(char *result)
{
    FILE *fin=fopen(TEMPFILE,"r");
    //fgets(result,900,fin);
    char ch=getc(fin);
    int i=0;
    while(ch!=EOF)
    {
        result[i++]=ch;
        ch=getc(fin);
        
    }
    result[i]='\0';
    fclose(fin);
    //printf("%s",result);
}

void removeWhiteSpace(char* html)
{
    int i;
    char *buffer = malloc(strlen(html)+1), *p=malloc (sizeof(char)+1);
    memset(buffer,0,strlen(html)+1);
    for (i=0;html[i];i++)
    {
        if(html[i]>32)
        {
            sprintf(p,"%c",html[i]);
            strcat(buffer,p);
        }
    }
    strcpy(html,buffer);
    free(buffer); free(p);
}


int GetNextURL(char* html, char* urlofthispage, char* result, int pos)
{
    char c;
    int len, i, j;
    char* p1;  //!< pointer pointed to the start of a new-founded URL.
    char* p2;  //!< pointer pointed to the end of a new-founded URL.
    
    // NEW
    // Clean up \n chars
    if(pos == 0) {
        removeWhiteSpace(html);
    }
    // /NEW
    
    // Find the <a> <A> HTML tag.
    while (0 != (c = html[pos]))
    {
        if ((c=='<') &&
            ((html[pos+1] == 'a') || (html[pos+1] == 'A'))) {
            break;
        }
        pos++;
    }
    //! Find the URL it the HTML tag. They usually look like <a href="www.abc.com">
    //! We try to find the quote mark in order to find the URL inside the quote mark.
    if (c)
    {
        // check for equals first... some HTML tags don't have quotes...or use single quotes instead
        p1 = strchr(&(html[pos+1]), '=');
        
        if ((!p1) || (*(p1-1) == 'e') || ((p1 - html - pos) > 10))
        {
            // keep going...
            return GetNextURL(html,urlofthispage,result,pos+1);
        }
        if (*(p1+1) == '\"' || *(p1+1) == '\'')
            p1++;
        
        p1++;
        
        p2 = strpbrk(p1, "\'\">");
        if (!p2)
        {
            // keep going...
            return GetNextURL(html,urlofthispage,result,pos+1);
        }
        if (*p1 == '#')
        { // Why bother returning anything here....recursively keep going...
            
            return GetNextURL(html,urlofthispage,result,pos+1);
        }
        if (!strncmp(p1, "mailto:",7))
            return GetNextURL(html, urlofthispage, result, pos+1);
        if (!strncmp(p1, "http", 4) || !strncmp(p1, "HTTP", 4))
        {
            //! Nice! The URL we found is in absolute path.
            strncpy(result, p1, (p2-p1));
            
            return  (int)(p2 - html + 1);
        } else {
            //! We find a URL. HTML is a terrible standard. So there are many ways to present a URL.
            if (p1[0] == '.') {
                //! Some URLs are like <a href="../../../a.txt"> I cannot handle this.
                // again...probably good to recursively keep going..
                // NEW
                
                return GetNextURL(html,urlofthispage,result,pos+1);
                // /NEW
            }
            if (p1[0] == '/') {
                //! this means the URL is the absolute path
                for (i = 7; i < strlen(urlofthispage); i++)
                    if (urlofthispage[i] == '/')
                        break;
                strcpy(result, urlofthispage);
                
                result[i] = 0;
                strncat(result, p1, (p2 - p1));
                return (int)(p2 - html + 1);
            } else {
                //! the URL is a absolute path.
                len = strlen(urlofthispage);
                for (i = (len - 1); i >= 0; i--)
                    if (urlofthispage[i] == '/')
                        break;
                for (j = (len - 1); j >= 0; j--)
                    if (urlofthispage[j] == '.')
                        break;
                if (i == (len -1)) {
                    //! urlofthis page is like http://www.abc.com/
                    strcpy(result, urlofthispage);
                    
                    result[i + 1] = 0;
                    strncat(result, p1, p2 - p1);
                    return (int)(p2 - html + 1);
                }
                if ((i <= 6)||(i > j)) {
                    //! urlofthis page is like http://www.abc.com/~xyz
                    //! or http://www.abc.com
                    strcpy(result, urlofthispage);
                    
                    result[len] = '/';
                    strncat(result, p1, p2 - p1);
                    return (int)(p2 - html + 1);
                }
                strcpy(result, urlofthispage);
                
                result[i + 1] = 0;
                strncat(result, p1, p2 - p1);
                return (int)(p2 - html + 1);
            }
        }
    }
    return -1;
}

void NormalizeWord(char* word)
{
    int i = 0;
    while (word[i]) {
        // NEW
        if (word[i] < 91 && word[i] > 64) // Bounded below so this funct. can run on all urls
            // /NEW
            word[i] += 32;
        i++;
    }
}

int NormalizeURL(char* URL)
{
    int len = strlen(URL);
    if (len <= 1 )
        return 0;
    //! Normalize all URLs.
    if (URL[len - 1] == '/')
    {
        URL[len - 1] = 0;
        len--;
    }
    int i, j;
    len = strlen(URL);
    //! Safe check.
    if (len < 2)
        return 0;
    //! Locate the URL's suffix.
    for (i = len - 1; i >= 0; i--)
        if (URL[i] =='.')
            break;
    for (j = len - 1; j >= 0; j--)
        if (URL[j] =='/')
            break;
    //! We ignore other file types.
    //! So if a URL link is to a file that are not in the file type of the following
    //! one of four, then we will discard this URL, and it will not be in the URL list.
    if ((j >= 7) && (i > j) && ((i + 2) < len))
    {
        if ((!strncmp((URL + i), ".htm", 4))
            ||(!strncmp((URL + i), ".HTM", 4))
            ||(!strncmp((URL + i), ".php", 4))
            ||(!strncmp((URL + i), ".jsp", 4))
            )
        {
            len = len; // do nothing.
        }
        else
        {
            return 0; // bad type
        }
    }
    return 1;
}

int keyGenerator(char *link)
{
    int count=0;
    for(int i=0;link[i]!='\0';i++)
    {
        count+=(int)link[i];
    }
    count/=8;
    return count;
}


struct Link
{
    char *url;
    int depth;
    bool is_visited;
    int key;
    struct Link *next;
    struct Link *prev;
};

struct Hash
{
    struct Link *node;
}*hash[2000];


int crawler(int argc,char *argv[])
{
    int count_ok=1;      //check for count
    if(argc!=4)
    {
        printf("Count Not as Expected\n");
        count_ok=0;
        return 0;
    }
    else
    {
        printf("Count is Valid\n");
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
        printf("Link Not Same\n");
    }
    else
    {
        printf("Link Same\n");
    }
    
    if(*argv[2]>'0' && *argv[2]<='4')
    {
        printf("Depth Valid\n");
    }
    
    testDir(argv[3]);
    
    int is_page=testPage(argv[1]);    //test if page exists
    
    if(is_page)
    {
        getpage(argv[1]);
        savePage(argv[1],argv[2],argv[3]);
    }
    
    
    //////////////////////////////////
    
    
    
    
    
    //////////////////////////////////
    
    int file_size=fileSize();
    char contents[file_size*sizeof(char)+1];
    
    saveFileData(contents);
    char *links[100000];
    
    int pos=0,flag=0;
    for(int i=0;i<1000;i++)
    {
        links[i]=(char *)malloc(300*sizeof(char));
        
        pos=GetNextURL(contents,argv[1],links[i],pos);
    }
    
    char *final_links[100];
    int k=0;
    for(int i=0;i<1000;i++)
    {
        flag=0;
        final_links[k]=(char *)malloc(300*sizeof(char));
        for(int j=0;j<i;j++)
        {
            if(strcmp(links[j],links[i])==0)
                flag=1;
        }
        if(!flag)
            strcpy(final_links[k++],links[i]);
    }
    
    //    GOT THE LINKS IN FINAL_LINKS
    
   
    
    for(int i=0;i<MAX_URL;i++)
    {
        int key;
        key=keyGenerator(final_links[i]);
        if(hash[key]==NULL)
        {
            hash[key]=(struct Hash*)malloc(sizeof(struct Hash));
            hash[key]->node=(struct Link*)malloc(sizeof(struct Link));
            hash[key]->node->url=(char*)malloc(sizeof(char)*300);
            strcpy(hash[key]->node->url,final_links[i]);
            hash[key]->node->key=key;
            hash[key]->node->next=NULL;
            hash[key]->node->prev=NULL;

        }
        else
        {
            struct Link *ptr;
            ptr=hash[key]->node;
            while(ptr->next!=NULL)
            {
                printf("%s",ptr->url);
                ptr=ptr->next;
            }
            
            struct Link *np=(struct Link*)malloc(sizeof(struct Link));
            np->url=(char*)malloc(sizeof(char)*300);
            strcpy(np->url,final_links[i]);
            np->key=key;
            np->prev=ptr;
            ptr->next=np;
            np->next=NULL;
        }
    }
    
    
    for(int i=0;i<2000;i++)       //PRINT LINKED LIST ON COLLISIONS
    {
        if(hash[i]!=NULL && hash[i]->node->next!=NULL)
        {
            struct Link *ptr=hash[i]->node;
            while(ptr!=NULL)
            {
                printf("%d %s\n",ptr->key,ptr->url);
                ptr=ptr->next;
            }
        }
    }
    
    /////  HASHING FINISHED
    
    
    
    return 0;
}




int main(int argc,char * argv[])
{
    crawler(argc,argv);
    fclose(fout);
    return 0;
}



