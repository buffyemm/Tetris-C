#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <ncurses.h>
#include <unistd.h>

#define WIDTH 10
#define HEIGHT 20

typedef struct {
    int x, y;  
    int** figure;  
} TetFigure;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;


GameInfo_t* create_game();
TetFigure* create_figure();
void free_memory(GameInfo_t* game, TetFigure* current_figure);
void print_game(GameInfo_t* game, TetFigure* current_figure);
void next_figure(GameInfo_t* game);
void mv_next_figure(GameInfo_t* game, TetFigure* figure);
UserAction_t get_user_action(int ch);
void move_figure(TetFigure* tet_figure, int dx, int dy);
int check_collision(TetFigure* figure, GameInfo_t* game);
void fix_figure(GameInfo_t* game, TetFigure* tet_figure);
void transpouse(TetFigure* figure);
void clear_line(GameInfo_t* game);
void move_down(TetFigure* temp, GameInfo_t* game);
void update_game(GameInfo_t* game, TetFigure* current_figure, int* game_over);
void handle_user_input(int ch, TetFigure* figure, GameInfo_t* game);
GameInfo_t record_read();
#endif