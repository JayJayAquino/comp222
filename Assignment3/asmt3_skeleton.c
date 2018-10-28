#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* declare global vars */
int max_length, hamming_parity;

/* define hamming string as a dynamic array of characters */
char *hamming_string = NULL;


/***************************************************************/
void set_params()
{
/* prompt for maximum hamming code length and for even/odd parity (even/odd)*/
  //prinf
  //scanf
/* allocate memory for hamming string based on maximum length and size of a character element*/
  hamming_string = (char *)malloc(max_length * sizeof(char));

  return;
}

/***************************************************************/
void hamming_code()
{
/* declare local vars */
  int actual_length;
  int i; // parity bits
  int j; //starting bit of a sequence of consecutive bits
  int k; //each bit in a consecutive sequence
  int parity_check;

/* prompt for hamming code as a "string"*/
  //printf
  scanf("%s", hamming_string);
/* Determine actual Hamming code length & number of parity bits*/
  actual_length = strlen(hamming_string);
  //this line is optional
  num_parity = ceil(log(actual_length) / log(2));
/* OUTER LOOP: for each parity bit in the Hamming code*/

 /* BEGIN OF OUTER LOOP */
  for(i = 1; i < actual_length; i = i*2){

	/* initialize appropriate local variables */
  parity_check = hamming_parity;

   	/* MIDDLE LOOP: for each starting bit of a sequence */
    for(j = i; j < actual_length; j = j + (i*2)){

        	/* INNER LOOP: for each bit to be checked, check value and update parity information for current parity bit*/
          for(k = j; k < (j+i) && k < (actual_length); k++){
            parity_check ^= (int)(hamming_string[actual_length - k] - '0');
          }//k
				/* update parity checking by including result for parity bit checked in total */
        // error_bit = error_bit...;
			}//i
} /* END OF OUTER LOOP

/* report error in hamming code based on result from parity bits or report no error if none */
// ...hamming_string[actual_length - error_bit]...


/* correct hamming code by flipping error bit (if necessary)*/
//above variable = ('1' + '0') - that variable

  return;
}
//optional
void free_hamming()
{
  if(hamming_string != NULL){
    free(hamming_string);
  }
  return;
}
/***************************************************************/
//REMEMBER TO RUN LIKE GCC .C -lm
int main()
{
  int choice = 0;
/* print out menu, prompt for choice, and call appropriate procedure until user quits */
  while(choice != 3){
    printf("Error detection/correction:\n");
    printf("1) Enter Paramters\n");
    printf("2) Check Hamming Code\n");
    printf("3) Quit\n");
    printf("\nEnter Selection: ");
    scanf("%d", &choice);

    switch(choice){
      case 1: enter_params();
      break;
      case 2: hamming_code();
      break;
      case 3: printf("Quitting...\n");
      free_haming();
      break;

      default: printf("Invalid Entry\n");
    }
  }
return 1;
}
