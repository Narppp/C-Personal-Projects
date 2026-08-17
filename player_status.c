// Player Status Checker

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Effects
#define NORMAL_STATE 0
#define HUNGER_EFFECT (1 << 0)
#define WEAKNESS_EFFECT (1 << 1)
#define BLEEDING_EFFECT (1 << 2)
#define DEATH_STATE (1 << 7)

// Default Sizes
#define MAX_ARRAY_SIZE 1024
#define MAX_INPUT_SIZE 5
#define EFFECTS 5

// Errors
#define EOF_ERROR -1
#define BUFFER_ERROR -2
#define NO_VALID_NUM -3
#define INVALID_NUMS -4
#define EXIT_PROGRAM -5

void clearBuffer(void){
  int clear = 0;
  while((clear = getchar()) != '\n' && clear != EOF);
}

int convert_input(char input[], char effects[][MAX_ARRAY_SIZE]){
  long convNum = 0;

  while(1){
    printf("==EFFECT SIMULATOR==\n");
    for(uint8_t idx = 0; idx < EFFECTS; idx++){
      printf("%u. %s\n", idx + 1, effects[idx]);
    }
    printf("Enter the number of the effect you want (or press 'q' to exit the program): ");
    if(fgets(input, MAX_ARRAY_SIZE, stdin) == NULL){
      return EOF_ERROR;
    }

    size_t checkChar = strcspn(input, "\n");

    if(input[checkChar] != '\n'){
      clearBuffer();
      return BUFFER_ERROR;
    }
    input[checkChar] = '\0';

    if(strcmp(input, "q") == 0){
      return EXIT_PROGRAM;
    }

    char *holdChar = NULL;
    convNum = strtol(input, &holdChar, 10);

    if(holdChar == input || *holdChar != '\0'){
      return NO_VALID_NUM;
    }
    if(convNum <= 0 || convNum > EFFECTS){
      return INVALID_NUMS;
    }

    break;
  }
  return convNum;
}

int main(void){
  uint8_t player_status = NORMAL_STATE;
  int player_option = 0;
  char player_input[MAX_INPUT_SIZE] = {0};
  char effects_options[EFFECTS][MAX_ARRAY_SIZE] = {
    "Normal State (clears all effects)",
    "Hunger Effect",
    "Weakness Effect",
    "Bleeding Effect",
    "Death State"
  };

  while(1){
    player_option = convert_input(player_input, effects_options);

    if(player_option < 0 /*Error*/){
      switch(player_option){
        case EOF_ERROR:
          printf("Reached end of file.\n");
          break;
        case BUFFER_ERROR:
          printf("Exceeded character limit.\n");
          break;
        case NO_VALID_NUM:
          printf("Invalid input, no letters allowed.\n");
          break;
        case INVALID_NUMS:
          printf("Number cannot be 0 or greater than %d.\n", EFFECTS);
          break;
        case EXIT_PROGRAM:
          printf("Quitting program...\n");
          return 0;
        default:
          printf("Unknown error, try again.\n");
          break;
      }
      continue;
    }
    else{
      switch (player_option){
        case 1:
          player_status = NORMAL_STATE;
          printf("Cleared all effects.\n");
          break;
        case 2:
          player_status |= HUNGER_EFFECT;
          printf("Player is now hungry.\n");
          break;
        case 3:
          player_status |= WEAKNESS_EFFECT;
          printf("Player is now weak.\n");
          break;
        case 4:
          player_status |= BLEEDING_EFFECT;
          printf("Player is bleeding!\n");
          break;
        case 5:
          player_status = DEATH_STATE;
          printf("Player is dead.\n");
          return 0;
        default:
          printf("Unknown effect.\n");
          break;
      }
      continue;
    }
  }

  return 0;
}
