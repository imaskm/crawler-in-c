#include<stdio.h>
#include<stdlib.h>
#include"crawler.h"
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include"html.h"
#include"html.c"
char *url_list[MAX_URL_PER_PAGE+2];
static int currentdepth = 0;
static int htmlnum=0;
int checkURL(int , char*);
int isPresent( char *URL ,int hashvalue);
linkList *listnode;
urlList *newnode;
hashTable *hash;
void createList()
{
   int i;
 
  
   for(i=0;url_list[i] != NULL;i++)
   {
        //puts("\n---------create List starts -------------------");
       
      newnode= malloc(sizeof(urlList));
    
      strcpy(newnode->url,url_list[i]);
      newnode->depth=currentdepth;
      newnode->isvisited =0;
      
      listnode = malloc(sizeof(linkList));
      listnode->next =NULL;
      listnode->previous=NULL;
    //  puts("2---------");
      listnode->urlNode = newnode;
      listnode->key=hashFunction(url_list[i]);
      //printf("\n%d",listnode->key);
     // hash = malloc(sizeof(hashTable));
     //puts("3---------");
     
      if(!(hash->hashtable[listnode->key]))
         {
         
      //     puts("4---------");
            
            (hash->last)->next=listnode;
            listnode->previous=hash->last;
          hash->last=listnode;
          (hash->last)->next = NULL;
          
          hash->hashtable[listnode->key] = listnode;
         }
      
      else
      {
       if(!(isPresent(url_list[i],listnode->key )))
       {
      puts("aa gaya");
      
      linkList *ptr = hash->hashtable[listnode->key];
      linkList *temp=ptr;
      while( ptr != NULL  && ptr->key == listnode->key)
      {
              temp = ptr;
              puts(temp->urlNode->url);
              ptr=ptr->next;   
      
      }  
       puts("loop ke baad");
         puts(hash->last->urlNode->url);
            
         puts(listnode->urlNode->url);
            puts(temp->urlNode->url);
           temp->next = listnode;
           listnode->previous =temp;
           listnode->next = ptr;
       
      if(ptr!=NULL)
        {
              puts(ptr->urlNode->url);
           ptr->previous = listnode;
         }  
       else
       {
          hash->last = listnode;
       }  
      
      }         
   
   
   }
    
    }


}
int isPresent( char *URL ,int hashvalue)
{   
   
    //puts("Check");
    //int hashvalue = hashFunction( URL );
    linkList *tempptr= hash->hashtable[hashvalue];
  
 // puts((tempptr->urlNode)->url);
  
    while( tempptr!=NULL && tempptr->key == hashvalue  )
    {
    
             
         if(!( strcmp((tempptr->urlNode)->url, URL ) ))
         {
           //puts("Is Present");
            return 1;
         }
      tempptr=tempptr->next;
    }
    puts(URL);
    puts("End of IS Present"); 
   return 0; 
   
}





char* getPage(char *url ,int depth ,char *dir )
{

     if(!NormalizeURL(url))
     {
     
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Please enter URL again \n");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);
   } 
    puts("-****In Get Page****"); 
     puts(url);
      
     char *urlbuffer=(char *)malloc(500*sizeof(char));
     CHECK_MALLOC(urlbuffer);
   
     strcpy(urlbuffer, "wget -e use_proxy=on -e http_proxy=10.0.0.220:3128 --proxy-user=user1 --proxy-password=user1 ");
     strcat(urlbuffer, url);
     strcat(urlbuffer," -O /home/imaskm/temp/temp.txt"); 
    // puts(urlbuffer);
  /*   strcpy(urlbuffer,"wget -e use_proxy=on -e http_proxy=10.0.0.220:3128 -O ");
//strcat(urlbuffer,argv[3]); //TARGET DIRECTORY ARGUMENT
 strcat(urlbuffer,"/home/imaskm ");
strcat(urlbuffer,url); //SEED URL ARGUMENT
strcat(urlbuffer,"--proxy-user=user1 --proxy-password=user1"); */
     
     if(system(urlbuffer))
     {
       printf("..................WgetPage............Error\n");
       free(urlbuffer);
       return NULL;
        
     }
     else{
           puts("-----------------Okay---------------------------");
           free(urlbuffer);
     }
     
  
    char* pathname = "/home/imaskm/temp/temp.txt";
      
     
     struct stat st;
     stat(pathname, &st);
     int numbytes = st.st_size;     
    
   
     char *filebuffer = (char *)malloc( (numbytes+1) * sizeof(char ));
     CHECK_MALLOC(filebuffer);
     
     FILE *fp;
     fp = fopen( "/home/imaskm/temp/temp.txt","r" );
     
     int c = fgetc(fp);
     
     int i;
     for(i=0;c!=EOF;i++)
     {
       filebuffer[i]=c;
       c=fgetc(fp);
     }
     
     
     //puts(pathname);
    
     
     filebuffer[i] = '\0';
      
      char *filenum=malloc(6);
      CHECK_MALLOC(filenum);
      char* newpath = (char *)malloc( (sizeof(dir)+20)*sizeof(char));
     CHECK_MALLOC(newpath);
     strcpy(newpath,dir);
     strcat(newpath,"/");
     sprintf(filenum,"%d",htmlnum);
     strcat(newpath,filenum);
     strcat(newpath,".html");
    
     //puts(newpath); 
     
     FILE *newfp;
     newfp = fopen(newpath,"w");
     
    if( newfp == NULL )
    {
       printf("----Error---fp---");
       exit(1);
    }
    
    fprintf(newfp,"%s",url);
    
    fprintf(newfp,"%s","\n");
    fprintf(newfp,"%d",depth);
    fprintf(newfp,"%s","\n");
    fprintf(newfp,"%s",filebuffer);
   
        
    
    
     fclose(fp);
     fclose(newfp);
     free(newpath);
      htmlnum++;
     puts("End of Get Page");
     return filebuffer;
    
        
      
}

void extractURL(char* pagebuffer,char * currentURL)
{
   int i;
   int count=0;
   
  for(i=0; i<MAX_URL_PER_PAGE+2 ; i++)
   {
    
     //count++;
     //printf("Freeeeeeee-----------%d-------\n",count);
     //puts(url_list[i]);
     free(url_list[i]);
     url_list[i]=NULL;
    
   } 
   
  
     char result[MAX_URL_LENGTH];
   puts("extracting..............URL.......................    ");
   puts(currentURL);
   int currentpos=0;
   int numextracted=0;
  
   while(numextracted < MAX_URL_PER_PAGE && currentpos>=0)
   {
         
        SET_MEM(result,MAX_URL_LENGTH);
        // puts(pagebuffer);
         //puts(currentURL);
       //puts(result);
        currentpos = GetNextURL(pagebuffer,currentURL,result,currentpos);
        
        if(currentpos != -1)
        {
        char* resultcopy=(char*)malloc(MAX_URL_LENGTH * sizeof(char));
        strcpy(resultcopy, result);
        
        if(checkURL(numextracted,resultcopy))
        {
            
           url_list[numextracted++]=resultcopy; 
           
           //printf("\n%d  %s\n\n",numextracted , url_list[numextracted-1]);
        }
        
   }
   }
   url_list[numextracted] =  NULL;
  
   
   puts("Extract URL ends") ;
   


}


int checkURL(int numextracted, char* resulttemp)
{

   
        int i;
         
        if(!NormalizeURL(resulttemp))
        return 0;
        
        for(i=0;i<numextracted;i++)
        {
             if(!strcmp(url_list[i],resulttemp))
             return 0;
        }
        
        if( strncmp(resulttemp,"www.uietkuk.org",15))
        {
                return 0;
        }
        
        return 1;
        
        
        
}

void testDirectory(char *dir)
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


int main(int argc , char* argv[])
{
// checking number of arguments

puts(argv[1]);// = directory
puts(argv[2]);// = SeedUrl
puts(argv[3]);// = depth
if( argc != 4 )
{
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Invalid number of Arguments\n");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);
  
  
}

//argv[1] is target directory..check if it exist;
char *path =argv[1];
testDirectory(path);

//Valiadting Depth

if(atoi(argv[3]) > 3 && atoi(argv[3]) <0)
{
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Enter a value between 1 & 3 (Both inclusive)\n");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);

}

//validating URL

if(strcmp( SEED_URL , argv[2] ) != 0)
{
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, " Enter SEED URL correctly ");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);
}


//fetching pages from URL

char urlbuffer[maxSeedURL + 300] ={0};

strcat(urlbuffer,"wget --spider -e use_proxy=on -e http_proxy=10.0.0.220:3128 --proxy-user=user1 --proxy-password=user1 -q ");
strcat(urlbuffer,argv[2] );


if( system( urlbuffer ))
{
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Seed URL doesn't exist  ");
    fprintf(stderr, "------------------------------------------\n");
     exit(1);
}
else
{
  printf("Seed-OK");
}

newnode=malloc(sizeof(urlList)) ;

strcpy(newnode->url,argv[2]);
newnode->depth= currentdepth;
newnode->isvisited = 0;

int hashvalue = hashFunction(argv[2]);


listnode = malloc(sizeof(linkList));
listnode->next = NULL;
listnode->previous = NULL;
listnode->urlNode = newnode;
listnode->key = hashvalue;
printf("\n\n\n%d\n\n\n",listnode->key);
hash = malloc(sizeof(hashTable));
hash->hashtable[hashvalue] = listnode;
hash->head = hash->last = listnode;





linkList *point;
 int flag ;
do
{ 
    
    point = (hash->head);
     flag =0;
    char *url = malloc(MAX_URL_LENGTH*sizeof(char));
     CHECK_MALLOC(url);
     SET_MEM(url,MAX_URL_LENGTH);
    
   while( point != NULL && point->urlNode->isvisited == 1 )
   {
     point = point->next;
     
     //puts("is ---Visited--------------check--------------------");
   } 
   
  if(point != NULL  && point->urlNode->depth <= atoi(argv[3] ) )
  {  
   puts("yaha b aa ra");
   flag=1;
   strcpy(url,(point->urlNode)->url); 
   point->urlNode->isvisited =1;  
  char *page = getPage(url,currentdepth,path);
if(page == NULL)
{
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "New page not created  ");
    fprintf(stderr, "------------------------------------------\n");
     free (page);
     }
else
{
puts("After get Page");

extractURL(page,url);

free(page);

puts("after extract URL");
currentdepth++;
createList();
}
//puts("\n\n\nLInk List \n\n");
/*linkList *ptr=hash->head;
while( ptr != NULL )
{
  puts(((ptr)->urlNode)->url );
  ptr = ptr->next;
  }
*/
puts("After create List");
point = point->next;

}
//printf("*******************%d-------------------",flag);
}while( point !=NULL && flag);


puts("After cList");

linkList *ptr=hash->head;
while( ptr != NULL )
{
  printf("%d",((ptr)->urlNode)->depth );
  puts("   ");
  puts(((ptr)->urlNode)->url );
  ptr = ptr->next;
  }
puts("end");
return 0;

}


