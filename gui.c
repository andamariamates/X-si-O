#include <ncurses.h>
#include <string.h>

void desenare_tabla(char tabla[3][3])
{
    int row, col;
    getmaxyx(stdscr, row, col);
    move(row / 4 + 1, (col / 2) - 7);
    printw("+---+---+---+");
    move(row / 4 + 2, (col / 2) - 7);
    printw("| %c | %c | %c |", tabla[0][0], tabla[0][1], tabla[0][2]);
    move(row / 4 + 3, (col / 2) - 7);
    printw("+---+---+---+");
    move(row / 4 + 4, (col / 2) - 7);
    printw("| %c | %c | %c |", tabla[1][0], tabla[1][1], tabla[1][2]);
    move(row / 4 + 5, (col / 2) - 7);
    printw("+---+---+---+");
    move(row / 4 + 6, (col / 2) - 7);
    printw("| %c | %c | %c |", tabla[2][0], tabla[2][1], tabla[2][2]);
    move(row / 4 + 7, (col / 2) - 7);
    printw("+---+---+---+\n");

    move(row / 4 + 10, (col / 2) - 20);
    printw("Apasa tasta 'Space' pentru a selecta casuta");
    move(row / 4 + 11, (col / 2) - 17);
    printw("Apasa tasta 'Q' pentru a iesi din joc");
}

void init_game(int cursor_x, int cursor_y, int max_x, int max_y, char tabla[3][3], char jucator_curent){
    clear();
        
    getmaxyx(stdscr, max_y, max_x); 

    char titlu[] = "X si 0";
    int len = strlen(titlu);
    move(max_y / 4 - 3, (max_x / 2) - (len / 2));
    printw("%s\n", titlu);

    move(max_y / 4 - 1, (max_x / 2) - 9);
    printw("Este randul lui: %c ", jucator_curent);
        
    desenare_tabla(tabla);

    int pune_cursor_y = (max_y / 4 + 2) + (cursor_y * 2);
    int pune_cursor_x = ((max_x / 2) - 7) + 2 + (cursor_x * 4);
    move(pune_cursor_y, pune_cursor_x);
        
    refresh();
}