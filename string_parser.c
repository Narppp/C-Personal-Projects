// Basic String Parser with strtok()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearBuffer(void){
  int c = 0;
  while((c = getchar()) != '\n' && c != EOF);
}

void get_user_input(char *buffer, size_t buffer_size){
  while(1){
    printf("Enter a sentence: ");
    if(fgets(buffer, buffer_size, stdin) == NULL){
      printf("Reached end of file.\n");
      return;
    }

    if(buffer[strcspn(buffer, "\n")] != '\n'){
      printf("Input exceeded buffer space.\n");
      clearBuffer();
      continue;
    }
    buffer[strcspn(buffer, "\n")] = '\0';

    return;
  }
}
int main(void){
  char buffer[128] = {0};

  get_user_input(buffer, sizeof(buffer));

  int token_num = 1;
  char *str_token = strtok(buffer, " ");

  if(str_token == NULL){
    printf("There is nothing to parse.\n");
    return 0;
  }

  while(str_token != NULL){
    printf("Token %d: %s\n", token_num, str_token);
    str_token = strtok(NULL, " ");
    token_num++;
  }

  printf("Program executed successfully.\n");
  return 0;
}
