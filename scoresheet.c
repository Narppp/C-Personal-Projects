// Scoresheet in C
/* TODO: Create an array of student names and scores then print them out. */

/* things to keep in mind:
1. when passing 2d arrays in a function, you MUST include the size
of every array except the first one so the compiler knows how much
bytes in needs to jump on the array to access your other values in that array. */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARR_SIZE 20
#define MAX_INPUT_SIZE 40

void clearBuffer(void){
  int findN = 0;
  while((findN = getchar()) != '\n' && findN != EOF);
}

bool list_students(char studentArr[][MAX_INPUT_SIZE], size_t *idx){
  while(*idx < MAX_ARR_SIZE){
    printf("Enter the name of the student (or press 'q' to quit): ");
    if(fgets(studentArr[*idx], sizeof(studentArr[*idx]), stdin) == NULL){
      printf("Reached end of file.\n");
      return false;
    }

    size_t replace = strcspn(studentArr[*idx], "\n");

    if(studentArr[*idx][replace] != '\n'){
      printf("Buffer overflowed.\n");
      clearBuffer(); // Clear buffer when no newline is found.
      continue;
    }

    studentArr[*idx][replace] = '\0';

    if(strcmp(studentArr[*idx], "q") == 0){
      if(*idx <=  0){
        printf("Student list is empty.\n");
        continue;
      }
      break;
    }

    (*idx)++;
  }

  return true;
}

bool list_scores(char inputScore[], char studentArr[][MAX_INPUT_SIZE], int scoreArr[], size_t *count){
  size_t itemCount = 0;
  size_t student_number = 1;

  while(itemCount < *count){
    printf("Enter the score of %zu. %s: ", student_number, studentArr[itemCount]);
    if(fgets(inputScore, MAX_INPUT_SIZE, stdin) == NULL){
      printf("Reached end of file.\n");
      return false;
    }

    int findChar = strcspn(inputScore, "\n");

    if(inputScore[findChar] != '\n'){
      printf("Buffer overflowed.\n");
      clearBuffer();
      continue;
    }
    inputScore[findChar] = '\0';

    char *holdChar = NULL;
    long converted_num = strtol(inputScore, &holdChar, 10);

    if(holdChar == inputScore){
      printf("No numbers found.\n");
      continue;
    }
    if(*holdChar != '\0'){
      printf("Letters found on input.\n");
      continue;
    }

    scoreArr[itemCount] = converted_num;

    student_number++;
    itemCount++;
  }

  return true;
}

int main(void){
  char student_names[MAX_ARR_SIZE][MAX_INPUT_SIZE] = {0};
  char score_input[MAX_INPUT_SIZE] = {0};
  int student_scores[MAX_ARR_SIZE] = {0};
  size_t count = 0;

  bool executed1 = list_students(student_names, &count);

  if(!executed1){
    printf("Program failed to execute.\n");
    return 0;
  }

  bool executed2 = list_scores(score_input, student_names, student_scores, &count);

   if(!executed2){
    printf("Program failed to execute.\n");
    return 0;
  }

  size_t student_num = 1;

  for(size_t idx = 0; idx < count; idx++){
    printf("Student %zu: %s | Score: %d\n", student_num, student_names[idx], student_scores[idx]);
    student_num++;
  }

  return 0;
}
