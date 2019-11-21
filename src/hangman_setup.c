/*
** PERSONAL PROJECT, 2019
** hangman
** File description:
** hangman setup
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/my.h"
#include "../include/hangman.h"

int error_dictionary(int id)
{
    if (id == ERROR);
    else if (!id) {
        my_putstr("Error: failed to open the dictionary file.\n"
                "Try './hangman --help' for more information.\n");
        return (ERROR);
    } else
        my_putstr("Error: it appears the dictionary you chose is empty.\n"
                "Try './hangman --help' for more information.\n");
    return (FAILURE);
}

char *get_word_from_dico(char *dictionary_path, uint nth)
{
    FILE *stream = fopen(dictionary_path, "r");
    char *word = NULL;
    size_t buf = 0;

    for (; nth > 0; nth--) {
        if (getline(&word, &buf, stream) == 1) {
            nth++;
            continue;
        }
        for (uint i = 0; i < my_strlen(word); i++)
            if (word[i] == HIDDEN) {
                nth++;
                break;
            }
    }
    fclose(stream);
    return (word);
}

uint choose_n(uint dico_size)
{
    uint n;

    srand(time(0));
    n = rand() % dico_size + 1;
    return (n);
}

static int invalid_word(char *buff)
{
    int n = 0;

    for (uint i = 0; buff[i]; i++)
        if (buff[i] == HIDDEN)
            return (TRUE);
    for (uint i = 0; buff[i]; i++)
        if (my_c_isalpha(buff[i]))
            n++;
    if (!n)
        return (TRUE);
    return (FALSE);
}

int get_dico_size(char *dictionary_path)
{
    FILE *stream = fopen(dictionary_path, "r");
    char *buff = NULL;
    size_t buf = 0;
    int size = 0;

    if (!stream)
        return (error_dictionary(0));
    for (ssize_t ret_v = 0; ret_v != -1;) {
        ret_v = getline(&buff, &buf, stream);
        if (ret_v > 1) {
            size++;
            if (invalid_word(buff))
                size--;
        }
    }
    fclose(stream);
    free(buff);
    return (size);
}
