#include <stdio.h>

int main()
{
  int choice;
  printf("Select an option: ");
  scanf("%o", &choice);

  switch(choice){
    case 1 :
      printf("You chose 1 %d \n", choice);
      break;
    case 2 :
      printf("You chose 2\n");
      break;
    case 3 :
      printf("You chose 3\n");
      break;
    case 4 :
      printf("You Chose 4\n");
  }
}
