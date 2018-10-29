#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* declare global vars */
int max_length, hamming_parity, num_parity;

/* define hamming string as a dynamic array of characters */
char *hamming_string = NULL;


/***************************************************************/
void set_params()
{
/* prompt for maximum hamming code length and for even/odd parity (even/odd)*/
  printf("Enter the maximum length: ");
  scanf("%d", &max_length);
  printf("Enter the parity (0=even, 1=odd): ");
  scanf("%d", &hamming_parity);
/* allocate memory for hamming string based on maximum length and size of a character element*/
  hamming_string = (char *)malloc(max_length * sizeof(char));

  return;
}

/***************************************************************/
void check_hamming()
{
    /* declare local vars */
    int actual_length, parity_check, hamming_var, i, j, k;
    int error_bit = 0;

    /* prompt for hamming code as a "string"*/
    printf("Enter the Hamming code: ");
    scanf("%s", hamming_string);


    actual_length = strlen(hamming_string);
    num_parity = ceil(log(actual_length) / log(2));

     /* OUTER LOOP: for each parity bit in the Hamming code*/
    for (i = 0; i < num_parity; i++)
    {

        hamming_var = pow(2,i);
        parity_check = hamming_parity;

        /* MIDDLE LOOP: for each starting bit of a sequence */
        for (j = i; j < actual_length; j = j +(2 * hamming_var)) {

            /* INNER LOOP: for each bit to be checked, check value and update parity information for current parity bit*/
            for (k = j; (k < ((2 * j) - 1)) && (k <= actual_length);  k++) {
                parity_check ^= (hamming_string[actual_length - k] - '0');
            } // end k
        } // end j

        error_bit = error_bit + (parity_check * hamming_var);
    } // end i



    if (error_bit == 0) {
        printf("There is no bit error");
    }

    else {
        printf("There is an error in bit: %d\n", error_bit);
        if (hamming_string[actual_length - error_bit] == '0') {
            hamming_string[actual_length - error_bit] = '1';
        }
        else {
            hamming_string[actual_length - error_bit] = '0';

        } // end else
        printf("The corrected Hamming code is: %s\n", hamming_string);

    }

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
      case 1: {set_params();
      break;}
      case 2: {check_hamming();
      break;}
      case 3: {printf("Quitting...\n");
      free_hamming();
      break;}

      default: printf("Invalid Entry\n");
    }
  }
return 1;
}
