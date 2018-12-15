#ifndef crawler
#define crawler


#define  maxHashSize 10
#define  maxDepth  3
#define  maxSeedURL 20
#define MAX_URL_PER_PAGE 30
#define MAX_URL_LENGTH 500
#define SET_MEM(start,size) memset(start,0,size)
#define CHECK_MALLOC(s) if((s)==NULL) { \
printf("Memory allocation failed in %s: line %d",__FILE__,__LINE__); \
perror(":"); \
exit(-1); \
}

typedef struct  URL
{
  char url[MAX_URL_LENGTH];
  int depth;
  int isvisited;

}urlList;
 typedef struct Link
{
  struct Link *next;
  struct Link *previous;
  urlList *urlNode;
  int key;

}linkList;

typedef struct hash
{
  linkList *hashtable[maxHashSize];
  linkList *head;
   linkList *last;
}hashTable ;

int hashFunction(char *str)
{
int key =0;

while(*str!='\0')
{
key += *str;
str++;
}

return(key %maxHashSize);
}

char *SEED_URL = "www.uietkuk.org";
#endif
