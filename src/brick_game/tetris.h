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
    int **field;
    int **next;
    int pos_x;
    int pos_y;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

void test();
GameInfo_t* create_game();
void next_figure(GameInfo_t* temp);
//void test_move(int x, int y, GameInfo_t* temp);
void test_move(GameInfo_t* game, int dx, int dy);
bool can_move(GameInfo_t* game, int dx, int dy);
#endif