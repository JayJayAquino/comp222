#include <stdio.h>
#include <stdlib.h>

typedef struct Inst {
	int dst;
	int src1;
	int src2;
	int delay;
} Inst;

Inst* sb;
int ic = -1; //instruction count
int d = 0; //delay
char in[8]; //input string

void option1(){
  int i;
  int j;
  do {
    printf("Enter Instruction Count: ");
    scanf("%d", &ic); getchar();  //flush buffer

    if(ic <= 0)
      printf("Invalid Size, please choose a positive integer.\n");
  } while(ic <= 0);

  sb = malloc((ic+1) * sizeof(Inst));
  sb[0] = (Inst) {-1, -1, -1, -1};

  for(i = 1; i < ic+1; ++i) {
    printf("%d) ", i);
    scanf("%s", in); getchar();
    sb[i] = (Inst) {in[1]-'0', in[4]-'0', in[7]-'0', 0};
  }

}

void option2(){
  printf("\n\n");
  int i;
  int j;
  if(ic <= 0) {
    printf("Please enter instructions.");
  } else {
    for(i = 1; i < ic+1; ++i) {
      if(i != 1) {
        if((sb[i].src1 == sb[i-1].dst) || (sb[i].src2 == sb[i-1].dst)) {
          d += 2;
          for(j = i; j < ic+1; ++j)
            sb[j].delay += 2;
        } else if((sb[i].src1 == sb[i-2].dst) || (sb[i].src2 == sb[i-2].dst)) {
          d += sb[i-1].delay > sb[i-2].delay ? 0 : 1;
          for(j = i; j < ic+1; ++j)
            sb[j].delay += sb[i-1].delay > sb[i-2].delay ? 0 : 1;
        }
      }

      printf("%d)", i);

      for(j = 1 - i; j < sb[i].delay; ++j) {
        printf("\t");
      }

      printf("FI\tDI\tCO\tFO\tEI\tWO\n");
    }

    printf("\nTotal Cycles: %d", ic + 5 + d);
  }
  printf("\n\n");
}

// this was done in a hurry, and probably is very spaghetti, but it works
// so please excuse how bad it was written
void option3(){
  //Local Variables
  int i;
  int j;
  int delay = 0;
  int overlap1 = 0;
  int overlap2 = 0;
  int overlap3 = 0;
  int overlap4 = 0;
  int overlap5 = 0;
  int pipe_delay = 1;

  printf("\n\n");


  //for each instruction check for independences (2 to n)
  for(i = 2; i <= ic; i++){

      delay = 0;   //Start assuming the delay is zero
      pipe_delay = 1 - pipe_delay;  //This needs to be oscillated.

      //Check if valid instructions to compare
      if(i >= 5){
          //Check for a RAW (read after write) dependency between instructions i-5) and i)
          if((sb[i-5].dst == sb[i].src1) || (sb[i-5].dst == sb[i].src2)){
              //Check for an overriding overlapping delay
              if((overlap1 == 0) && (overlap2 == 0) && (overlap3 == 0) && (overlap4 == 0)){
                  overlap5 = 1;
                  if(pipe_delay == 1)
                      delay = 0;
                  else
                      delay = 0;   //This is redundant but serves as a template.

                  pipe_delay = 1;  //Force a de-coupling from the previous instruction.
              }
              else{
                  overlap5 = 0;  //Resb overlap5.
              }
          } //End of if there is a raw dependency

          else{
              overlap5 = 0; //Resb overlap5
          }
      }

      //Check if valid instructions to compare
      if(i >= 4){
          //Check for a RAW (read after write) dependency between instructions i-5) and i)
          if((sb[i-4].dst == sb[i].src1) || (sb[i-4].dst == sb[i].src2)){
              //Check for an overriding overlapping delay
              if((overlap1 == 0) && (overlap2 == 0) && (overlap3 == 0)){
                  overlap4 = 1;
                  if(pipe_delay == 1)
                      delay = 1;
                  else
                      delay = 0;   //This is redundant but serves as a template.

                  pipe_delay = 1;  //Force a de-coupling from the previous instruction.
              }
              else{
                  overlap4 = 0;  //Resb overlap5.
              }
          } //End of if there is a raw dependency

          else{
              overlap4 = 0; //Resb overlap5
          }
      }

      //Check if valid instructions to compare
      if(i >= 3){
          //Check for a RAW (read after write) dependency between instructions i-5) and i)
          if((sb[i-3].dst == sb[i].src1) || (sb[i-3].dst == sb[i].src2)){
              //Check for an overriding overlapping delay
              if((overlap1 == 0) && (overlap2 == 0)){
                  overlap3 = 1;
                  if(pipe_delay == 1)
                      delay = 1;
                  else
                      delay = 1;   //This is redundant but serves as a template.

                  pipe_delay = 1;  //Force a de-coupling from the previous instruction.
              }
              else{
                  overlap3 = 0;  //Resb overlap5.
              }
          } //End of if there is a raw dependency

          else{
              overlap3 = 0; //Resb overlap5
          }
      }

      //Check if valid instructions to compare
      if(i >= 2){
          //Check for a RAW (read after write) dependency between instructions i-5) and i)
          if((sb[i-2].dst == sb[i].src1) || (sb[i-2].dst == sb[i].src2)){
              //Check for an overriding overlapping delay
              if((overlap1 == 0)){
                  overlap2 = 1;
                  if(pipe_delay == 1)
                      delay = 2;
                  else
                      delay = 1;   //This is redundant but serves as a template.

                  pipe_delay = 1;  //Force a de-coupling from the previous instruction.
              }
              else{
                  overlap5 = 0;  //Resb overlap5.
              }
          } //End of if there is a raw dependency

          else{
              overlap5 = 0; //Resb overlap5
          }
      }

      //Check if valid instructions to compare
      if(i >= 1){
          //Check for a RAW (read after write) dependency between instructions i-5) and i)
          if((sb[i-1].dst == sb[i].src1) || (sb[i-1].dst == sb[i].src2)){
              //Check for an overriding overlapping delay
              delay = 2;
              pipe_delay = 1;
          } //End of if there is a raw dependency

          else{
              overlap1 = 0; //Resb overlap5
          }
      }

      //finally, sb the delay...
      sb[i].delay = delay + sb[i-1].delay + pipe_delay;

  }

  //get the total_delay
  delay = sb[ic].delay + 6;  //We have to take into consideration that although instr. 1 starts at 0, it must end at 6.
  //Print this out as the total cycles
  printf("Total number of cycles: %d \n\n", delay);

  //Print out the chart
  for(i = 1; i <= ic; i++){
    printf("%d)", i);
      for(j = 0; j < sb[i].delay; j++){
          printf("\t");
      }
      printf("FI\tDI\tCO\tFO\tEI\tWO\n");
  }
  printf("\n\n");
}

int main(void) {
  int choice;
	Inst* sb; //scoreboard
	char in[8]; //input string
	int ic = -1; //instruction count
	int d = 0; //delay
	int i, j; //iterators
  choice = 0;

  while(choice != 4){
    printf("\n\n"
    "Instruction-Level Parallelism\n"
    "------------------------------\n"
    "1) Enter Instructions\n"
    "2) Calculate Cycle Count, 6-Stage Pipeline\n"
    "3) Calculate total cycle count on a 6-stage superscalar architecture\n"
    "4) Quit Program\n"
    "\n"
    "Enter Selection: ");
    scanf("%d", &choice);

    switch(choice){
      case 1: option1();
      break;
      case 2: option2();
      break;
      case 3: option3();
      break;
      case 4: printf("Quitting... \n");
      break;

      default: printf("Invalid Entry \n");
    }
  }
  return 1;
}
