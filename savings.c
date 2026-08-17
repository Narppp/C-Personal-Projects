// Savings tracker in C
// TODO: Make a savings system with a goal that needs to be met in 31 days


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void clearBuffer(void){
  int c = 0;
  while((c = getchar()) != '\n' && c != EOF);
}

size_t validate_and_convert(char input[], size_t inputSize, int moneyArr[], size_t mArrSize){
  size_t loop = 0;

  while(loop < mArrSize){
    printf("Enter the amount of money you saved this week (Day %zu): ", loop + 1);
    if(fgets(input, inputSize, stdin) == NULL){
      printf("Reached end of file.\n");
      return -1;
    }
 
    int len = strcspn(input, "\n");

    if(input[len] != '\n'){
      printf("You have exceeded the number limit (only 10 numbers allowed).\n");
      clearBuffer();
      continue;
    }
    input[len] = '\0';

    if(strcmp(input, "q") == 0){
      printf("Exiting program...\n");
      break;
    }

    // Number conversion
    char *charptr = NULL;
    long convNum = strtol(input, &charptr, 10);

    if(charptr == input){
      printf("No numbers found.\n");
      continue;
    }
    if(*charptr != '\0'){
      printf("Letters found in input.\n");
      continue;
    }

    if(convNum <= 0){
      printf("Zero and negative numbers are not allowed.\n");
      continue;
    }
    if(convNum > 4294967296){
      printf("Exceeded 32 bit number limit.\n");
      continue;
    }

    moneyArr[loop] = convNum;
    loop++;
  }
  return loop;
}

void calculate_result(const int moneyArr[], size_t *count, const int GOAL){
  float total = 0.0f;
  for(size_t idx = 0; idx < *count; idx++){
    total += moneyArr[idx];
  }

  printf("Money earned in %zu days: $%.2f\n", *count, total);
  
  if(total < GOAL){
    printf("Goal of $10,000 is not reached.\n");
    return;
  }
  printf("Reached goal in %zu days, congratulations!\n", *count);

  return;
}

int main(void){
  const int SAVINGS_GOAL = 10000;
  char money_input[11] = {0};
  int money_per_week[31] = {0};
  size_t moneyArrSize = sizeof(money_per_week) / sizeof(money_per_week[0]);
  size_t moneyInputSize = sizeof(money_input) / sizeof(money_input[0]);

  size_t itemCount = validate_and_convert(money_input, moneyInputSize, money_per_week, moneyArrSize);

  if(itemCount == -1){
    printf("Program failed.\n");
    return 0;
  }
  
  calculate_result(money_per_week, &itemCount, SAVINGS_GOAL);

  printf("Program executed.\n");

  return 0;
}
