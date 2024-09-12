#ifndef TETRIS_H
#define TETRIS_H

typedef struct TetBlock
{
    int b;
} TetBlock;

typedef struct  TetFigure
{
    int x;
    int y;
    int size;
    TetBlock* blocks;
};

typedef struct TetFiguresT
{
    int count;
    int size;
    TetBlock* blocks;
} TetFiguresT;

typedef struct TetField
{
    int width;
    int height;
    TetBlock* blocks;
} TetField;


typedef struct TetGame
{
    TetField* field;
    TetFigure* figure;
    TetFiguresT* figurest;
} TetGame;

TetGame* createTetGame(int field_width, int field_height, int figures_size, int count,
TetBlock* figures_template);

void calculateTet(TetGame* tetg);

#endif