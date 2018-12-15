#include<stdio.h>
#include<stdlib.h>
#include"crawler.h"
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>

int currentdepth = 0;
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
// End Directory Function
//Get Page Function 

/*char* getPage(char *url ,int depth ,char *dir )
{
     if(!NormalizeURL(url))
     {
     
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Please enter URL again \n");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);
   
     char *dirbuffer = (char *)malloc( (strlen(dir) +15) * sizeof(char)  );
     CHECK_MALLOC(dirbuffer);
     SET_MEM(dirbuffer,sizeof(dirbuffer));
     
     strcat(dirbuffer ,dir);
     strcat(dirbuffer , "\\temp");
     
    if( ! system(dirbuffer) )
     {
      fprintf(stderr, "------------------------------------------\n");
      fprintf(stderr, "Error creating folder \n");
      fprintf(stderr, "------------------------------------------\n");
      exit(1);  
     } 
     
     struct stat st;
     stat(pathname, &st);
     int numbytes = st.st_size;  
     
   
           
     }
      
}*/

int main(int argc , char* argv[])
{
// checking number of arguments
printf("\nHLO 1\n");
//argv[1] = directory
//argv[2] = url
//argv[3] = depth
if( argc != 4 )
{
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Invalid number of Arguments\n");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);
  
  
}

printf("\nHLO 2\n");
//argv[1] is target directory..check if it exist;
char *path =argv[1];
testDirectory(path);

//Valiadting Depth
printf("\nHLO 3\n");
if(atoi(argv[3]) > 3 && atoi(argv[3]) <0)
{
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Enter a value between 1 & 3 (Both inclusive)\n");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);

}

//validating URL
printf("\nHLO 4\n");
if(strcmp( SEED_URL , argv[2] ) != 0)
{
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, " Enter SEED URL correctly ");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);
}

printf("\nHLO 5\n");
//fetching pages from URL

char urlbuffer[maxSeedURL + 300] ={0};

strcat(urlbuffer,wget --spider -e use_proxy=on -e http_proxy=10.0.0.220:3128 --proxy-user=user1 --proxy-password=user1 -q );
strcat(urlbuffer,argv[2] );
/*
strcat(urlbuffer,"wget -e use_proxy=on -e http_proxy=10.0.0.220:3128 -O ");
strcat(urlbuffer,argv[3]); //TARGET DIRECTORY ARGUMENT
// OR strcat(urlbuffer,"TARGET DIRECTORY PATH");
strcat(urlbuffer,argv[1]); //SEED URL ARGUMENT
strcat(urlbuffer,"--proxy-user=user1 --proxy-password=user1"); */



if( system( urlbuffer ) )
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

//int key_Seed = hashFunction(argv[2]);
//struct hashTbale hashtable;


//char *page = getPage(argv[2],currentdepth,path)



  














 

}
