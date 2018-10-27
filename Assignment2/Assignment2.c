//John Aquino comp222, Tue/Thur
//Assignment 2

#include <stdio.h>
#include <stdlib.h>

/* declare global var's */
int mm_size, cache_size, block_size, num_of_lines;
/* define structure of dynamic cache and initialize var */

struct node
{
  int tag;
  int *block;
} *cache = NULL;

typedef struct node line;

/* define dynamic array for main memory */
int *mm = NULL;

/****************************************************************/
void enter_params()
{
  /* declare local var's */
  int i;

  /* Prompt for main memory size, cache size, block size */
  printf("Enter main memory size (words): ");
  scanf("%d", &mm_size);
  printf("Enter cache size (words): ");
  scanf("%d", &cache_size);
  printf("Enter block size (words): ");
  scanf("%d", &block_size);

  /* allocate and initialize main memory--value at index i = size of main memory-i*/
  mm = (int *)malloc(mm_size * sizeof(int)); // integers are 4 bytes?

  for(i=0; i < mm_size; i++){
    mm[i] = mm_size - i;
  }
  /* allocate memory for cache based on number of lines in cache*/
  num_of_lines = cache_size/block_size;
  cache = (line *)malloc(num_of_lines*sizeof(line));

  /* initialize each tag to -1 and each block to NULL */
  for(i=0; i < num_of_lines; i++){
    cache[i].tag = -1;
    cache[i].block = NULL;
  }

  return;
}


/****************************************************************/
void access_cache()
{
/* declare local var's */
  int read_write;
  int mm_addr;
  int data;
  int word;
  int tag;
  int block;
  int base;
  int k;
/* Prompt for read/write signal */
  printf("Select read (0) or write (1): ");
  scanf("%d", &read_write);

/* Prompt for main memory address to read/write */
  if(read_write == 0){ //read
    printf("Enter main memory address to read from: ");
    scanf("%d", &mm_addr);
  }else{
    printf("Enter main memory address to write to: ");
    scanf("%d", &mm_addr);
    printf("Enter value to write: ");
    scanf("%d", &data);

  }
/* Translate main mem addr to cache addr fields*/
  base = (mm_addr / block_size) * block_size;
  tag = (mm_addr / cache_size);
  word = (mm_addr % block_size);
  block = ((mm_addr % cache_size) / block_size);

/* Case 1: MISS--BLOCK NOT ALLOCATED */
  if(cache[block].tag == -1){
		/* Allocate cache block based on block size */
    cache[block].block = (int *)malloc(block_size * sizeof(int));
	}

/* Case 2: MISS--NON-MATCHING TAGS */
	if(cache[block].tag != tag){
		/* Print message of Read/Write miss */
    if(read_write == 0){
      printf("Read miss!\n");
    }else{
      printf("Write miss! \n");
    }
		/* Overwrite tag */
    cache[block].tag = tag;
		/* Transfer equivalent block of main memory to cache--one word at a time */
    for (k = 0; k < block_size; k++){
      cache[block].block[k] = mm[base + k];
    }
	}

/* Case 3:HIT DUE TO MATCHING TAGS */
	else if(cache[block].tag == tag){
		/* print message of Read/Write hit*/
    if(read_write == 0){
      printf("Read hit!\n");
    }else{
      printf("Write hit!\n");
    }
	}

/* reference cache word, transfer data to/from cache depending on read/write signal*/
if(read_write == 0){
  data = cache[block].block[word];
}else{
  //reverse above calculation
  cache[block].block[word] = data;
  mm[mm_addr] = data;
}
/* Print message of word, block, tag, data value */

printf("\n-------------------------------------------------------\n");
printf(" Tag: %d | Block: %d | Word: %d | Contents: %d \n", tag, block, word, data);
printf("-------------------------------------------------------\n");

  return;
}


/****************************************************************/
int main()
{
/* declare local var's */
  int choice = 0;
/* until program exits, print menu, select choice via switch statement and call appropriate function*/

  printf("Cache memory allocation and mapping: \n");
  while(choice != 3){
    printf("1) Enter parameters \n");
    printf("2) Access cache for reading/writing and transfer data \n");
    printf("3) Quit\n");
    printf("\n Enter Selection: ");
    scanf("%d", &choice);

    switch(choice){
      case 1: enter_params();
      break;
      case 2: access_cache();
      break;
      case 3: printf("Quitting... \n");
      break;

      default: printf("Invalid Entry \n");
    }
  }
  return 1;
}
