#include <stdio.h>

/* declare global var's */
int freq_of_machine;
int cycle_total = 0;
int instruction_total = 0;
int num_of_classes;
int cpi_avg;
/*********************************************************/
void enter_params()
{
  /* declare local var's and initialize*/
  int i;
  int cpi_class;
  int instruction_count;

  /* prompt for # instruction classes & frequency of machine */
  printf("Enter Number of instruction classes: ");
  scanf("%d", &num_of_classes);
  printf("Enter the frequency of the machine (MHz): ");
  scanf("%d", &freq_of_machine);

  /* for each instruction class, prompt for CPI of class and instruction count, accumulate cycle total & instruction total */
  for(i = 1; i <= num_of_classes; i++){
    printf("\nEnter CPI of class %d: ", i);
    scanf("%d", &cpi_class);
    printf("Enter instruction count of class %d (millions): ", i);
    scanf("%d", &instruction_count);
    cycle_total += (cpi_class*instruction_count);
    instruction_total += instruction_count;
  }
return;
}

/*********************************************************/
void calc_avg_cpi()
{
  /* declare local var's */
  float average;
  /* calculate CPI average */
  average = (cycle_total/instruction_total)*1.0;
  /* Note: typecast integers to floats via (float)int_var */

  /* Print out result */
  printf("The average CPI of the sequence is: %f\n\n", average);

return;
}

/*********************************************************/
void calc_total_exec_time()
{
  /* declare local var's */

  /* calculate total execution time */

  /* Print out result */

return;
}

/*********************************************************/
void calc_mips()
{
  /* declare local var's */

  /* calculate MIPS */

  /* Print out result */

return;
}

/*********************************************************/
int main()
{
  /* declare local var's */

  /* until user chooses to quit, print menu, select choice via switch statement and call appropriate function*/
  int choice = 0;
  while(choice != 5){
    printf("Welcome to CPI calculator!\n Menu of options: \n-----------------\n");
    printf("1) Enter parameters\n");
    printf("2) Calculate average CPI of a sequence of instructions\n");
    printf("3) Calculate total execution time of a sequence of instructions\n");
    printf("4) Calculate MIPS of a sequence of instructions\n");
    printf("5) Quit\n");
    printf("\nEnter selection: ");
    scanf("%d", &choice);
    switch(choice){
      case 1: enter_params();
      break;
      case 2: calc_avg_cpi();
      break;
      case 3: calc_total_exec_time();
      break;
      case 4: calc_mips();
      break;
      case 5: printf("\nQuitting...Thank you!\n");
      break;
      default: printf("Invalid option\n");
    }
  }
  return 1;
}
