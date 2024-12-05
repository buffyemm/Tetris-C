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

void map() {
  mvaddch(0, 0, ACS_ULCORNER);
  mvaddch(0, 11, ACS_TTEE);
  mvaddch(21, 0, ACS_LLCORNER);
  mvaddch(21, 11, ACS_BTEE);
  mvaddch(0, 31, ACS_URCORNER);
  mvaddch(21, 31, ACS_LRCORNER);
  for (int y = 1; y < 21; y++) {
    for (int x = 1; x < 11; x++) {
      if (y == 1) {
        mvaddch(0, x, ACS_HLINE);
        mvaddch(21, x, ACS_HLINE);
      }
      mvaddch(y, 0, ACS_VLINE);
      mvaddch(y, 11, ACS_VLINE);
      refresh();
    }
  }
  for (int x = 12; x < 31; x++) {
    for (int y = 1; y < 21; y++) {
      mvaddch(y, 31, ACS_VLINE);
    }

    mvaddch(0, x, ACS_HLINE);
    mvaddch(21, x, ACS_HLINE);
  }

  // FILE *fp = fopen("r.txt", "w");
  //  for (int i = 0; i < 10; i++) {
  //         for (int j = 0; j < 20; j++) {
  //             fprintf(fp, "%d ", game->field[i][j]); // Записываем элемент
  //             массива
  //         }
  //         fprintf(fp, "\n");
  //  }
  //  fclose(fp);
  //refresh();

  // endwin();
}

int main() {
  initscr();
  curs_set(0);
  srand(time(NULL));
  keypad(stdscr, TRUE);
  // tablo();
  mvprintw(1, 12, "HIGHT SCORE:1999888");
  mvprintw(3, 14, "SCORE:9999888");
  mvprintw(5, 12, "NEXT:");
  mvprintw(11, 14, "LEVEL:21");
  mvprintw(12, 14, "SPEED:4");
  mvprintw(14, 14, "PAUSE: P");
  mvprintw(19, 14, "TIME:21:01");
  TetFigure* figure = create_figure();
  GameInfo_t* game = create_game();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  next_figure(game);
  mv_next_figure(game, figure);
  next_figure(game);

  int game_over = 0;
  int drop_interval = 500;
  int last_drop_time = 0;
  struct timespec start_time, current_time;

  clock_gettime(CLOCK_MONOTONIC, &start_time);

  while (!game_over) {
    print_game(game, figure);
    map();

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    int elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000 +
                       (current_time.tv_nsec - start_time.tv_nsec) / 1000000;

    if (elapsed_time - last_drop_time > drop_interval) {
      last_drop_time = elapsed_time;
      move_down(figure, game);
      if (check_collision(figure, game)) {
        game_over = 1;
      }
      if (game->score / 500 > (last_drop_time / drop_interval)) {
        drop_interval =
            drop_interval > 100 ? drop_interval - 50 : drop_interval;
      }
    }

    int ch = getch();
    if (ch != ERR) {
      handle_user_input(ch, figure, game);
    }

    refresh();
    clear();
  }

  mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "Game Over!");
  refresh();

  napms(2000);
  record_read;
  free_memory(game, figure);
  endwin();
  return 0;
}
