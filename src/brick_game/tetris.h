#ifndef TETRIS_H
#define TETRIS_H
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

// typedef struct TetBlock
// {
//     int b;
// } TetBlock;

// typedef struct  TetFigure
// {
//     int x;
//     int y;
//     int size;
//     TetBlock* blocks;
// };

// typedef struct TetFiguresT
// {
//     int count;
//     int size;
//     TetBlock* blocks;
// } TetFiguresT;

// typedef struct TetField
// {
//     int width;
//     int height;
//     TetBlock* blocks;
// } TetField;


// typedef struct TetGame
// {
//     TetField* field;
//     TetFigure* figure;
//     TetFiguresT* figurest;
// } TetGame;

// TetGame* createTetGame(int field_width, int field_height, int figures_size, int count,
// TetBlock* figures_template);

// void calculateTet(TetGame* tetg);
typedef struct {
    int x, y;  
    int tick;  
    int** figure;  
} TetFigure;

typedef struct {
    // bool is_place;
    int **field;
    int **next;
    // int pos_x;
    // int pos_y;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
    // TetFigure current_figure;
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


TetFigure* create_figure();
void test();
GameInfo_t* create_game();
void next_figure(GameInfo_t* temp, TetFigure* figure);
 GameInfo_t* generate_matrix();
void print_game(GameInfo_t* game, TetFigure* current_figure);
UserAction_t get_user_action(int ch);
int collision(TetFigure* figure, GameInfo_t* game, int dx, int dy);
//int check_collision(TetFigure* figure, GameInfo_t* game);
void move_figure(TetFigure* tet_figure, int dx, int dy);
// void createGame();
// void spawn();
// void moving();
// void shifting();
// void reached();
// void colliped();

#endif