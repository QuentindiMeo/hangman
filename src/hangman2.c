/*
** PERSONAL PROJECT, 2019
** hangman
** File description:
** hangman 2
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/hangman.h"

static void display_history(data *game, char letter)
{
    char *tmp = NULL;

    if (!game->history) {
        game->history = malloc(sizeof(char) * 2);
        game->history[0] = letter;
        game->history[1] = '\0';
    } else if (!my_c_isinstr(game->history, letter)) {
        tmp = malloc(sizeof(char) * (my_strlen(game->history) + 2));
        tmp[my_strlen(game->history) + 1] = '\0';
        my_strcpy(tmp, game->history);
        my_charcat(tmp, letter);
        free(game->history);
        game->history = my_strdup(tmp);
        free(tmp);
    }
    my_putstr("not in the word: ");
    my_putstr(game->history);
    my_putstr("\n\n");
}

static int try_letter(char c1, char c2)
{
    if (c2 < 94 && c1 > 94)
        c1 -= 32;
    else if (c1 < 94 && c2 > 94)
        c1 += 32;
    if (c1 == c2)
        return (TRUE);
    return (FALSE);
}

static int play_letter(data *game, char letter)
{
    uint found = 0;

    if (letter == CTRLD)
        return (CTRLD);
    for (uint i = 0; i < my_strlen(game->answer); i++)
        if (try_letter(letter, game->answer[i])) {
            game->word[i] = game->answer[i];
            found++;
        }
    if (!found) {
        my_putchar(letter);
        my_putstr(" is not in the word.\n");
        display_history(game, letter);
        return (1);
    }
    my_putchar('\n');
    return (0);
}

static int ctrld(char *to_be_freed)
{
    free(to_be_freed);
    return (CTRLD);
}

static int get_entry(void)
{
    char letter = 0;
    char *entry = NULL;
    size_t buff = 0;
    int ret_v;

    my_putstr("\nYour letter: ");
    for (; !letter; letter = *entry) {
        ret_v = getline(&entry, &buff, stdin);
        if (ret_v == EOF)
            return (ctrld(entry));
        if (my_strlen(entry) != 2 ||
            (my_strlen(entry) == 2 && !my_c_isalpha(*entry))) {
                my_putstr(my_strlen(entry) == 0 ? "\0" :
                        "Error: please only enter one correct letter.");
            free(entry);
            return (get_entry());
        }
    }
    free(entry);
    return (letter);
}

int hangman(data *game)
{
    int ret_v;

    my_putstr(game->word);
    my_putstr("\nTries: ");
    my_putnbr(game->tries);
    ret_v = play_letter(game, get_entry());
    if (ret_v == CTRLD)
        return (QUIT);
    game->tries -= ret_v;
    if (!game->tries)
        return (LOSE);
    for (uint i = 0; i < my_strlen(game->answer); i++)
        if (game->word[i] == HIDDEN)
            return (CONTINUE);
    return (WIN);
}
