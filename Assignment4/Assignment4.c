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
  pt = (entry*)malloc(num_entries * sizeof(entry));
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
  int VMAddress;//From user
	int realAddress;//Generated
	int vp;
	int offset;


	printf("Enter virtual memory address to access: ");
	scanf("%d", &VMAddress);

	//Calculate offset and virtual page
	offset = VMAddress % page_size;
	vp = VMAddress / page_size;

	int i;
	for (i = 0; i < num_entries; i++) {
		//if there is a hit (page in pt)
		if (pt[i].vp == vp) {
			realAddress = (pt[i].pf * page_size) + offset;
			//LRU
			if (policy == 0) {
				int pfHolder;//placeholder for pf
				int vpHolder;//placeholder for vp
				int g;
				for (g = i; g < num_entries - 1; g++) {
					//Shift page table at index of hit
					pfHolder = pt[g].pf;
					vpHolder = pt[g].vp;
					pt[g] = pt[g + 1];
					pt[g + 1].pf = pfHolder;
					pt[g + 1].vp = vpHolder;
				}
			}
			printf("Virtual Address: %d maps to physical address %d", VMAddress,realAddress);
			i = num_entries-1;
		}
		//if theres a blank space
		else if (pt[i].vp == -1) {
			//map virtual page to generated virtual page
			pt[i].vp = vp;
			//map pf to current index
			pt[i].pf = i;
			printf("Page fault!\n");
			//set index to last element
			i = num_entries - 1;
		}
		else if (i == num_entries - 1) {//condition for last element
			pt[0].vp = vp;
			int pfHolder;//placeholder for pf
			int vpHolder;//placeholder for vp
			int h;
			for (h = 0; h < num_entries - 1; h++) {
				//shift page table from beginning
				pfHolder = pt[h].pf;
				vpHolder = pt[h].vp;
				pt[h] = pt[h + 1];
				pt[h + 1].pf = pfHolder;
				pt[h + 1].vp = vpHolder;
			}
			printf("Page Fault! \n");
		}

	}

return;
}



/***************************************************************/
void print_page_table()
{
/* Declare local var's */
  int i;
/* For each valid entry in page table */
printf("\n-----------------\n");
printf("| VP   | PF   |\n");
printf("-------------------\n");
for (i = 0; i < num_entries; i++) {
  if (pt[i].pf != -1 && pt[i].vp != -1) {//To avoid unnecessary printing
    printf("| %d    |", pt[i].vp);
    printf(" %d    |", pt[i].pf);
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
  printf("\n1) Enter parameters \n");
  printf("2) Access cache for reading/writing and transfer data \n");
  printf("3) Print page table\n");
  printf("4) Quit\n");
  printf("\n Enter Selection: ");
  scanf("%d", &choice);

  switch(choice){
    case 1: set_params();
    break;
    case 2: mapping();
    break;
    case 3: print_page_table();
    break;
    case 4: printf("Quitting... \n");
    break;

    default: printf("Invalid Entry \n");
  }
}
return 1;
}
