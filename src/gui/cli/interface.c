#include "interface.h"

// void tablo_map(){
// //initscr();
// mvaddch(0,30, ACS_URCORNER);
// mvaddch(20,30, ACS_LRCORNER);
// for(int x = 11 ; x < 30; x++){
//     for (int y = 1; y < 20; y++)
//     {
//         mvaddch(y, 30, ACS_VLINE);
//     }
    
// mvaddch(0,x, ACS_HLINE);
// mvaddch(20,x, ACS_HLINE);
// }
// //map();
// refresh();
// //getch();
// //endwin();
// }

void map(GameInfo_t *game){

mvaddch(0,0, ACS_ULCORNER);
mvaddch(0,11, ACS_TTEE);
mvaddch(21,0, ACS_LLCORNER);
mvaddch(21,11, ACS_BTEE);
mvaddch(0,31, ACS_URCORNER);
mvaddch(21,31, ACS_LRCORNER);
for(int y = 1; y < 21; y++){
    for(int x = 1; x < 11; x++){
        if(y == 1){
            mvaddch(0, x, ACS_HLINE);
            mvaddch(21, x, ACS_HLINE);
        }
            if((x)< 11 || (y)<21){
                mvaddch(y, x, (char)(((int)'0')+ game->field[x-1][y-1]));
            }
           //if(massiv[y][x] == 1) mvaddch(x+1,y+1, (char)(((int)'X')+ massiv[x-1][y-1]));
            mvaddch(y, 0, ACS_VLINE);
            mvaddch(y, 11, ACS_VLINE);
  refresh();
    }
}
for(int x = 12 ; x < 31; x++){
    for (int y = 1; y < 21; y++)
    {
        mvaddch(y, 31, ACS_VLINE);
    }
    
mvaddch(0,x, ACS_HLINE);
mvaddch(21,x, ACS_HLINE);
}
refresh();
    getch();
    //endwin();
}

void tablo(){
// mvaddch(1, 12 , ACS_VLINE);
// mvaddch(1, 28 , ACS_VLINE);
// mvaddch(3, 12 , ACS_VLINE);
// mvaddch(3, 28 , ACS_VLINE);
refresh();
}

int main(){
initscr();
srand(time(NULL));    
   // tablo();
    // mvprintw(1, 11, "HIGHT SCORE:1999888");
    // mvprintw(3, 14, "SCORE:9999888");
    // mvprintw(5, 11, "NEXT:");
    //mvprintw(11, 14, "LEVEL:21");
    // mvprintw(12, 14, "SPEED:4");
    // mvprintw(14, 14, "PAUSE: P");
    // mvprintw(19, 14, "TIME:21:01");
    GameInfo_t* game = create_game();
    // game->field[4][1] = 1;
    // game->field[5][1] = 1;
    // game->field[6][1] = 1;
    // game->field[7][1] = 1;
    next_figure(game);
    test_move(game, 1,1);
    map(game);
    endwin();
    return 0;
}