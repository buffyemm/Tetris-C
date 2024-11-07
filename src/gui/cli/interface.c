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

void map(GameInfo_t *game, TetFigure* figure){

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
            // if((x)< 11 || (y)<21){
                
            //     mvaddch(y, x, (char)(((int)'0')+ game->field[x-1][y-1]));
               
            // }
            print_game(game, figure);
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

// FILE *fp = fopen("r.txt", "w");
//  for (int i = 0; i < 10; i++) {
//         for (int j = 0; j < 20; j++) {
//             fprintf(fp, "%d ", game->field[i][j]); // Записываем элемент массива
//         }
//         fprintf(fp, "\n");
//  }
//  fclose(fp);
refresh();
    
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
int i = 0;
srand(time(NULL));    
   // tablo();
    mvprintw(1, 11, "HIGHT SCORE:1999888");
    mvprintw(3, 14, "SCORE:9999888");
    mvprintw(5, 12, "NEXT:");
    mvprintw(11, 14, "LEVEL:21");
    mvprintw(12, 14, "SPEED:4");
    mvprintw(14, 14, "PAUSE: P");
    mvprintw(19, 14, "TIME:21:01");
    GameInfo_t* game = create_game();
    TetFigure* figure = create_figure();
    keypad(stdscr, TRUE);
    //test_move(game, 2,0);
    while (1)
    {
    next_figure(game, figure);
    //generate_matrix();
       
       
    // print_game(game, figure);
    map(game, figure);
    
     int ch = getch();
        UserAction_t action = get_user_action(ch);

        switch (action)
        {
        case Down:
        if (!collision(figure, game, 0, 1)) 
                    move_figure(figure, 0, 1); 
        
            //igure->y++;
            break;
        
        case Left:
        if (!collision(figure, game, -1, 0)) {
                    move_figure(figure, -1, 0); 
                }
            //igure->x--;
            break;
        case Right:
        if (!collision(figure, game, 1, 0)) {
                    move_figure(figure, 1, 0); 
                }
            //figure->x++;
            break;
        // case Up:
        //     figure->y--;
        //     break;
        default:
            break;
        }
    
    //collision(figure,game);
    //if (collision(figure,game)) {
            
            //break;
       // }
    }
    
    
    
    endwin();
    return 0;
}
