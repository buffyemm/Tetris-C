#include "tetris.h"
#include <stdlib.h>



#ifndef TETRIS_C
#define TETRIS_C
#define WIDTH 10
#define HEIGHT 20



// void test() {
// initscr();
// for(int j=0; j<3; j++){
//     for (int i = 1; i < 7; i++) {
//         if(j==0){
//             mvprintw(i, 1, "DONIL");
//             refresh();
//             clear();
//             napms(500);
//         }
//         if(j==1){
//             mvprintw(7, 1, "DONIL");
//             mvprintw(i, 8, "POPY");
//             refresh();
//             clear();
//             napms(500);
//         }
//          if(j==2){
//             mvprintw(7, 8, "POPY");
//             mvprintw(7, 1, "DONIL");
//             mvprintw(i, 11, "MbIL?");

//             refresh();
//             clear();
//             napms(500);
//         }

//     }
// }
// endwin();
// }

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


typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;


TetFigure* create_figure(){
    TetFigure* figure = (TetFigure*)malloc(sizeof(TetFigure));
    figure->x = WIDTH / 2 -2;
    figure->y = 0;
    figure->tick = 30;
    figure->figure = (int**)calloc(4,sizeof(int));
}


void transpouse(matrix_t* figure){
matrix_t temp;

for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp.matrix[i][j] = figure->matrix[j][4 - 1 - i];
        }
    }
    // Копируем обратно в оригинальную матрицу
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            figure->matrix[i][j] = temp.matrix[i][j];
        }
    }
 }


void print(matrix_t figure, int x, int y){
    initscr();

//       matrix_t polosa = {
// .matrix = {
//             {0, 0, 0, 0},
//             {1, 1, 1, 1},
//             {0, 0, 0, 0},
//             {0, 0, 0, 0}
//         }
//     };
 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (figure.matrix[i][j] == 1) { 
                mvprintw(i + x , j + y, "%d", figure.matrix[i][j]);
            }
        }
        refresh(); 
        //napms(100); 
    }

    getch(); 
    clear();
    endwin(); 
}

// void testm1(){ 
// initscr();
// for(int k = 0; k < 8; k++){
// fig(1, k);
// refresh();
// napms(500);
// //map();
// //tablo_map();
// clear(); 
// }
// endwin();
// }

// void move(int x, int y){
//     for(int i = 0; i < 4;i++){
//         for(int j = 0; j < 4;j++){
//             if(figure[i][j] == 1){
//             mvprintw(i+y, j+x, "%d", figure[i][j]);
//             }
//         }
//     } 
// }

int main(){

     matrix_t polosa = {
.matrix = {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    };

 matrix_t ugol = {
.matrix = {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 0}
        }
    };

matrix_t FIGURES[2] = {
polosa, ugol
};
matrix_t result = FIGURES[1];
int i = 0;
//scanf("%d", &i);
//while(i>0){
transpouse(&result);
    //print(result, 1, 1);
//i--;
//}


//fizik();
//test();
//map();
//tablo_map();
//testm1();
return 0;
}


#endif