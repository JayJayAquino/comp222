#include <stdio.h>
#include <stdlib.h>

/* Define page table as dynamic structure containing virtual page and page frame
   and initialize variable as pointer to structure */
struct node{
  int vp;
  int pf;
}*pt = NULL;

typedef struct node entry;

/* Declare global var's */
int mm_size, page_size;
int num_entries;
int policy;


/**************************************************************/
void set_params()
{
  /* Declare local var's */

  /* Prompt for main memory size, page size, and replacement policy */
  printf("Enter main memory size (words): ");
  scanf("%d", &mm_size);
  printf("Enter page size (words/page): ");
  scanf("%d", &page_size);
  printf("Enter replacement policy (0=LRU, 1=FIFO): ");
  scanf("%d", &policy);

  num_entries = mm_size/page_size;

  /* Allocate and initialize page table based on number of entries */
  page_table = (entry*)malloc(num_entries * sizeof(entry));
  //initialize each value with for loop, index's are 0-3
  for(int i = 0; i < 4; i++){
    pt[i].vp = -1;
    pt[i].pf = -1;
  }

return;
}



/***************************************************************/
void mapping()
{
/* Declare local var's */
  int virtual_address, physical_address;
  int offset;
  int temp_pf, temp_vp;
  int i,j,k;
/* Prompt for virtual address */
  printf("Enter virtual memory address to access: ");
  scanf("%d", &virtual_address);
/* Translate virtual mem addr to virtual page and offset*/
  vp = virtual_address/page_size;
  offset = virtual_address % page_size;
/* Check for end of table, unallocated entry, or matched entry in table
 while none of three cases, keep looping */
 while((i < num_entries) && (pt[i].vp != -1) && (pt[i].vp != vp)){
  i++;
}
/* In case of end of table, replace either LRU or FIFO entry (top entry in page table), print message */
  if(i == num_entries){
    temp_pf = pt[0].pf;
    temp_vp = pt[0].vp;
    for(k = 0; k < num_entries - 1; k++){
      pt[k].vp = pt[k+1].vp;
      pt[k].pf = pt[k+1].pf;
    }
    pt[num_entries - 1].vp = vp;
    pt[num_entries - 1].pf = pf;
    printf("Page fault!\n");
  }else if(pt[i].vp == -1){
    pt[i].vp = vp;
    pt[i].pf = i;
    printf("Page fault!\n");
  }
/* In case of unallocated entry, set entry according to virtal page and page frame, print message */

/* In case of hit in page table, calculate physical address and print message, update page table if LRU policy */
  if(pt[i].vp == vp){
    pa = (pt[i].vp * page_size) + offset;
    pf = pt[0].pf;
    if(policy == 0){
      for(k = 0; k <= num_entries - 2; k++){
        if(...){
          break;
        }
        pt[k] = pt[k+1];
      }
      pt[num_entries - 1].vp = vp;
      pt[num_entries - 1].pf = pf;
    } //LRU
    printf("Virtual Address: %d maps to physical address %d",
     virtual_address, physical_address);

  }

return;
}



/***************************************************************/
print_page_table()
{
/* Declare local var's */

/* For each valid entry in page table */
printf("\n-----------------\n");
printf("| VP   | PF   |\n");
printf("-------------------\n");
for (i = 0; i < numPages; i++) {
  if (memory[i].pageFrame != -1 && memory[i].virtualPage != -1) {//To avoid unnecessary printing
    printf("| %d    |", memory[i].virtualPage);
    printf(" %d    |", memory[i].pageFrame);
    printf("\n----------------------\n");
  }
}
	/* print virtual page number and corresponding page frame number */
return;
}



/**************************************************************/
int main()
{
/* Declare local var's */
int choice = 0;
/* until program exits, print menu, select choice via switch statement and call appropriate function*/

printf("Cache memory allocation and mapping: \n");
while(choice != 4){
  printf("1) Enter parameters \n");
  printf("2) Access cache for reading/writing and transfer data \n");
  printf("3) Quit\n");
  printf("\n Enter Selection: ");
  scanf("%d", &choice);

  switch(choice){
    case 1: enter_params();
    break;
    case 2: mapping();
    break;
    case 3: print_page_table();
    break;
    case 4: printf("Quitting... \n");

    default: printf("Invalid Entry \n");
  }
}
return 1;
}
