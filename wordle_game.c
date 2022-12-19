#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "wordle_game.h"
#define INC 100

// Most of the code that you're going to have to implement goes in here.
// Feel free to add more helper functions if necessary.

// Returns true if the guess is an exact match with the secret word, but
// more importantly, fills in the result with the following:
// - 'x' goes in a slot if the corresponding letter in the guess does not appear
//   anywhere in the secret word
// - 'y' goes in a slot if the corresponding letter in the guess appears in the
//   secret word, but not in the corresponding slot
// - 'g' goes in a slot if the corresponding letter in the guess appears in the
//   corresponding slot in the secret word.
//   You can assume that result points at enough memory for a string of length
//   5. (ie, at least 6 bytes long)

bool inword(char letter, char* word){
  for(size_t i = 0; i < strlen(word); i++){
    if(letter == word[i]){
      return true;
    }
  }
  return false;
}

bool score_guess(char *secret, char *guess, char *result) {
  // TODO(you): finish this function

  for(size_t i = 0; i < strlen(guess); i++){
    if(guess[i] == secret[i]){
      result[i] = 'g';
    }
    else if(inword(guess[i], secret)){
      result[i] = 'y';
    }
    else{
      result[i] = 'x';
    }
  }

  if(strcmp(result, "ggggg") == 0){
    return true;
  }

  return false;
}


// Returns true if the specified guess is one of the strings in the vocabulary,
// and false otherwise. num_words is the length of the vocabulary.
// A simple linear scan over the strings in vocabulary is fine for our purposes,
// but consider: could you do this search more quickly?
bool valid_guess(char *guess, char **vocabulary, size_t num_words) {
  // TODO(you): finish this function
  for(size_t i = 0; i < num_words; i++){
    if(strcmp(vocabulary[i], guess) == 0){
      return true;
    }
  }

  return false;
}

// Returns an array of strings (so, char **), where each string contains a word
// from the specified file. The file is assumed to contain 5-letter words, one
// per line.
// Also, this function sets the value pointed at by *num_words to be the number
// of words read.
// This will need to allocate enough memory to hold all of the char* pointers --
// so you will keep track of the size of your char** array and then use realloc
// to make the array larger over time, so that you have enough space for the
// dynamically-growing array of char *.
// Use fopen to open the input file for reading,
// strdup (or strndup) to make copies of each word read from that file, and
// fclose to close the file when you are done reading from it.
// Each element of the array should be a single five-letter word,
// null-terminated.
char **load_vocabulary(char *filename, size_t *num_words) {
  // TODO(you): finish this function
  *num_words = 0;
  char **out = (char**)malloc(sizeof(char*) * INC);
  char buf[7];

  FILE *infile = fopen(filename, "r");
  while(fgets(buf, 7, infile)){
    int h = strcspn(buf, "\n");
    buf[h] = 0;
    out[*num_words] = strdup(buf);
    (*num_words)++;

    if(*num_words % INC == 0){
      char **temp = realloc(out, (INC + *num_words) * sizeof(char*));
      if(temp != NULL){
        out  = temp;
      }
      else{
        fclose(infile);
        return out;
      }
    }
  }

  fclose(infile);
  return out;
}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **vocabulary, size_t num_words) {
  // TODO(you): finish this function
  for(size_t i = 0; i < num_words; i++){
    free(vocabulary[i]);
  }
  free(vocabulary);
}

