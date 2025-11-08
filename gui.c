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
    printw("Apasa tasta 'q' pentru a iesi din joc");
}

int main(void)
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); 

    char tabla[3][3];

    int max_y, max_x; 
    
    int cursor_y = 0;
    int cursor_x = 0;
    
    char jucator_curent = 'X';

    for(int i = 0; i < 3;i ++)
        for(int j = 0; j < 3; j++)
            tabla[i][j] = ' ';
    
    int ch;

    while( (ch = getch()) != 'q' )
    {
        switch(ch) 
        {
            case KEY_UP:
                if (cursor_y > 0) cursor_y--;
                break;
            case KEY_DOWN:
                if (cursor_y < 2) cursor_y++;
                break;
            case KEY_LEFT:
                if (cursor_x > 0) cursor_x--;
                break;
            case KEY_RIGHT:
                if (cursor_x < 2) cursor_x++;
                break;
            
            case ' ':
                if (tabla[cursor_y][cursor_x] == ' ') 
                {
                    tabla[cursor_y][cursor_x] = jucator_curent;
    
                    if(jucator_curent == 'X')
                        jucator_curent = '0';
                    else
                        jucator_curent = 'X';
                }
                break;
        }
        
        //simulam efectul de miscare
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

    endwin();
    return 0;
}