/*
** EPITECH PROJECT, 2018
** hangman
** File description:
** hangman headers
*/

#ifndef HANGMAN_H_
#define HANGMAN_H_

struct data {
    char *answer;
    char *word;
    int tries;
    char *history;
};
typedef struct data data;

typedef enum {
    HIDDEN = '_',
    QUIT = -1,
    LOSE = 0,
    WIN = 1,
    CONTINUE = 2,
} return_values_hangman_t;

void freer(data *, int);
data *mallocator(int);

#endif
