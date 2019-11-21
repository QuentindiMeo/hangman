/*
** PERSONAL PROJECT, 2019
** hangman
** File description:
** main hangman
*/

#include <stdlib.h>
#include "../include/my.h"
#include "../include/hangman.h"

int error_dictionary(int id);
char *get_word_from_dico(char *dictionary_path, uint nth);
uint choose_n(uint dico_size);
uint get_dico_size(char *dictionary_path);
int hangman(data *game);

static void write_end(data *game, int r_v)
{
    if (r_v == WIN) {
        my_putstr("You found out it was '");
        my_putstr(game->answer);
        if (game->tries == 10)
            my_putstr("' with a perfect!\n");
        else
            my_putstr("'!\n");
    } else if (r_v == LOSE) {
        my_putstr("You couldn't find out it was '");
        my_putstr(game->answer);
        my_putstr("'.\n");
    } else
        my_putstr("?\nYou quit the game.\n");
}

static int game_loop(data *game)
{
    int ret_v = SUCCESS;

    game->history = NULL;
    for (char game_over = FALSE; game_over == FALSE;) {
        ret_v = hangman(game);
        if (ret_v != CONTINUE)
            game_over = TRUE;
        if (ret_v == CTRLD) {
            game_over = TRUE;
            ret_v = QUIT;
        }
    }
    write_end(game, ret_v);
    free(game->history);
    free(game->answer);
    free(game->word);
    free(game);
    return (ret_v != WIN ? WIN : LOSE);
}

static int main_hangman(char *dictionary_path)
{
    int dico_size = get_dico_size(dictionary_path);
    char *word = NULL;
    data *game = NULL;

    if (!dico_size || dico_size == ERROR)
        return (error_dictionary(!dico_size ? 1 : ERROR));
    game = malloc(sizeof(data));
    word = get_word_from_dico(dictionary_path, choose_n(dico_size));
    if (word[my_strlen(word) - 1] == '\n')
        game->answer = my_cut_str(word, 0, my_strlen(word) - 2);
    else
        game->answer = my_strdup(word);
    free(word);
    game->word = my_strdup(game->answer);
    for (uint i = 0; game->word[i]; i++)
        game->word[i] = (!my_c_isalpha(game->answer[i])) ?
                        game->answer[i] : HIDDEN;
    game->tries = 10;
    return (game_loop(game));
}

static int help(void)
{
    my_putstr("\n\tWelcome to the hangman game\n\nUSAGE\n\t./hangman [file]\n"
        "\tThe 'file' you choose contains a set of words put in line.\n\tSee "
        "'DICTIONARY CONTENT SAMPLE' for an example.\n\nDESCRIPTION\n\tThe fil"
        "e you pass as argument contains words that will be parsed and\n\tone "
        " will  be  chosen  in  a  random  manner. If a word contains the\n\t"
        "character used as a mark for a letter that has not been found yet,it"
        "\n\twill be bypassed and never chosen for a game. (def: '_')\n\tThis "
        "game is case insensitive.\n\tA found letter will reveal all of its "
        "occurances in the word.\n\tYou are granted 10 tries until "
        "you die, so choose carefully.\n\tAll non-alphabetical characters are "
        "granted at the very beginning of\n\tthe game, spaces and commas "
        "included.\n\tYou win when all of the characters in the word are found"
        ".\n\tYou can quit the game by pressing CTRL and D simultaneously.\n\n"
        "DICTIONARY CONTENT SAMPLE\n\tkettle\n\tpiNeApPlE\n\tnote-pad\n\t"
        "nucleu$\n\tthis is a sentence\n\theli'copter\n\tEmineM\n\thangman\n\n"
        "RETURN VALUE\n\tThe program returns:\n\t0\tif you won,\n\t1\tif you "
        "lost or quit,\n\t84\tif an error occured regarding the dictionary "
        "(if it's empty,\n\t\tif it failed to open)  or an invalid number "
        "of arguments was\n\t\tpassed to the program.\n\n");
    return (SUCCESS);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        my_putstr("USAGE\n\t./hangman [file]\n");
        return (FAILURE);
    }
    if (my_str_isequal(av[1], "-h") || my_str_isequal(av[1], "--help"))
        return (help());
    return (main_hangman(av[1]));
}
