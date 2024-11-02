#include "tetris.h"
#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 20
#define ROWS 10
#define COLS 20


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

typedef struct matrix_struct {
  int matrix[4][4];
  
} matrix_t;

typedef struct
{
    int x,y;
    int tick;
     int** figure;  
} TetFigure;


    static GameInfo_t* temp = NULL;
    static int ** old_massive;
    static int ** new_massive;

void logick(int ** matrix){
    

}



TetFigure* create_figure(){
    TetFigure* figure = (TetFigure*)malloc(sizeof(TetFigure));
    figure->x = WIDTH / 2 -2;
    figure->y = 0;
    figure->tick = 30;
    figure->figure = (int**)calloc(4,sizeof(int*));
    for(int i = 0; i < 4; i++) {
        figure->figure[i] = (int*)calloc(4,sizeof(int));
    }
    return figure;
}

GameInfo_t* create_game() {
    GameInfo_t* game = (GameInfo_t*)malloc(sizeof(GameInfo_t));
    game->field = (int**)calloc(HEIGHT,sizeof(int*));
     old_massive =  (int**)calloc(HEIGHT,sizeof(int*));
    new_massive = (int**)calloc(HEIGHT,sizeof(int*));
    for(int i = 0; i < HEIGHT; i++){
        game->field[i] = (int*)calloc(WIDTH,sizeof(int));
        old_massive[i]= (int*)calloc(WIDTH,sizeof(int));
        new_massive[i] = (int*)calloc(WIDTH,sizeof(int));
    }
    game->score = 0;
    game->level = 1;
    game->speed = 1;
    game->pause = 0;
    game->pos_x = 0;
    game->pos_y = 0;
    return game;
}

void next_figure(GameInfo_t* temp){
        int figures[7][4][4] = {
        {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}
    };

    int rnd = rand() % 7;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp->field[i][j] = figures[rnd][i][j];
        }
    }
}

// void test_move(int x, int y, GameInfo_t* temp){
// for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 4; j++) {
//             temp->field[i+x][j+y];
//         }
//     }
// }

bool can_move(GameInfo_t* game, int dx, int dy) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (game->field[i][j] != 0) {
                int new_x = game->pos_x + j + dx; // Новая позиция по X
                int new_y = game->pos_y + i + dy; // Новая позиция по Y

                // Проверка границ поля
                if (new_x < 0 || new_x >= COLS || new_y < 0 || new_y >= ROWS) {
                    return false; // Невозможно переместить фигуру за границы
                }

                // Проверка на занятую ячейку
                if (new_y >= 0 && game->field[new_y][new_x] != 0) {
                    return false; // Невозможно переместить фигуру на занятое место
                }
            }
        }
    }
    return true; // Перемещение возможно
}


void test_move(GameInfo_t* game, int dx, int dy) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i+dy >= 0 && i+dy < ROWS || j+dx >= 0 && j+dx < COLS){
                temp->field[i][j] = game->field[i+dy][j+dx];
            } 
            //else temp->field[i][j] = game->field[i-dy][j-dx];
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            game->field[i][j] = temp->field[i][j];
        }
    }
}



//     for (int i = 0; i < ROWS; i++) {
//         for (int j = 0; j < COLS; j++) {
//             int new_i = i + dy; // Новая позиция по y
//             int new_j = j + dx; // Новая позиция по x

//             // Проверяем, не выходит ли за границы массива
//             if (new_i >= 0 && new_i < ROWS && new_j >= 0 && new_j < COLS) {
//                 new_array[new_i][new_j] = array[i][j];
//             }
//             // Если выходит за границы, можно оставить значение на месте или установить в 0
//             // else {
//             //     new_array[i][j] = array[i][j]; // Оставить на месте
//             //     // или
//             //     // new_array[i][j] = 0; // Установить в 0
//             // }
//         }
//     }

//     // Копируем новый массив обратно в оригинальный
//     for (int i = 0; i < ROWS; i++) {
//         for (int j = 0; j < COLS; j++) {
//             array[i][j] = new_array[i][j];
//         }
//     }
// }

// void test_move(GameInfo_t* game, int dx, int dy) {
//     // Проверяем, можем ли мы переместить фигуру
//     if (can_move(game, dx, dy)) {
//         // Обновляем позицию фигуры
//         game->pos_x += dx;
//         game->pos_y += dy;
//     }
// }



// void print(matrix_t figure, int x, int y){
//     initscr();

//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 4; j++) {
//             if (figure.matrix[i][j] == 1) { 
//                 mvprintw(i + x , j + y, "%d", figure.matrix[i][j]);
//             }
//         }
//         refresh(); 
//         //napms(100); 
//     }

//     getch(); 
//     clear();
//     endwin(); 
// }

// void transpouse(matrix_t* figure){
// matrix_t temp;

// for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 4; j++) {
//             temp.matrix[i][j] = figure->matrix[j][4 - 1 - i];
//         }
//     }
//     // Копируем обратно в оригинальную матрицу
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 4; j++) {
//             figure->matrix[i][j] = temp.matrix[i][j];
//         }
//     }
//  }
