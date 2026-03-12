#include <ncurses.h>
#include "gui.h"
#include <string.h>
#include "tic_tac_toe.h"
int main(void)
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); 

    char tabla[3][3];

    int max_y = 0, max_x = 0; 
    
    int cursor_y = 0;
    int cursor_x = 0;
    
    char jucator_curent = 'X';

    for(int i = 0; i < 3;i ++)
        for(int j = 0; j < 3; j++)
            tabla[i][j] = ' ';
    
    int ch;

    bool joc_terminat = 0; 

    init_game(cursor_x, cursor_y, max_x, max_y, tabla, jucator_curent);

    while(!joc_terminat && (ch = getch()) != 'q' )
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
                    if(game_check(tabla, jucator_curent)==true){
                        clear();
                        getmaxyx(stdscr, max_y, max_x);
                        desenare_tabla(tabla);
                        move(max_y/4+17, max_x/2-13);
                        printw("Jucatorul %c a castigat!", jucator_curent);
                        move(max_y/4+18, max_x/2-18);
                        printw("Apasati enter sau 'Q' pentru iesire");
                        refresh();
                        int ch2;
                        do {
                            ch2 = getch();
                        } while (ch2 != 'q' && ch2 != '\n'); // asteapta Enter// asteapta Q inainte de iesire
                        joc_terminat = 1;
                        break; 
                    }
    
                    if(jucator_curent == 'X')
                        jucator_curent = '0';
                    else
                        jucator_curent = 'X';
                }
                break;
        }
        if(joc_terminat)break;
        //simulam efectul de miscare
        init_game(cursor_x, cursor_y, max_x, max_y, tabla, jucator_curent);

    } 

    endwin();
    return 0;
}