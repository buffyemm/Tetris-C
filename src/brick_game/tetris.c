#include "tetris.h"
#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 20

  static GameInfo_t* temp = NULL;
  static int ** old_massive;
  static int ** new_massive;




// typedef struct
// {
//     int x,y;
//     int tick;
//      int** figure;  
// } TetFigure;


TetFigure* create_figure() {
    TetFigure* figure = (TetFigure*)malloc(sizeof(TetFigure));
    figure->x = WIDTH / 2 - 2;  
    figure->y = 1;               
    figure->tick = 30;
    figure->figure = (int**)calloc(4, sizeof(int*));
    for (int i = 0; i < 4; i++) {
        figure->figure[i] = (int*)calloc(4, sizeof(int));
    }
    return figure;
}


GameInfo_t *create_game() {
    temp = (GameInfo_t*)malloc(sizeof(GameInfo_t));
    temp->field = (int**)calloc(HEIGHT,sizeof(int*));
    temp->next = (int**)calloc(HEIGHT,sizeof(int*));
     old_massive =  (int**)calloc(HEIGHT,sizeof(int*));
    new_massive = (int**)calloc(HEIGHT,sizeof(int*));
    for(int i = 0; i < HEIGHT; i++){
        temp->field[i] = (int*)calloc(WIDTH,sizeof(int));
        temp->next[i] = (int*)calloc(WIDTH,sizeof(int));
        old_massive[i]= (int*)calloc(WIDTH,sizeof(int));
        new_massive[i] = (int*)calloc(WIDTH,sizeof(int));
    }
    // temp->is_place = true;
    temp->score = 0;
    temp->level = 1;
    temp->speed = 1;
    temp->pause = 0;
    // temp->pos_x = 0;
    // temp->pos_y = 0;
    return temp;
}

void next_figure(GameInfo_t* temp, TetFigure* figure){
        int figures[7][4][4] = {
        {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
        {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}
    };
    
  


    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp->field[i][j] = 0;
        }
    }
    static  int rnd = 0;
    static int flag = 1;
      if (flag == 1) {
        rnd = rand() % 7;
        flag = 0;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            figure->figure[i][j] = figures[rnd][i][j];
        }
    }
//      for (int i = 0; i < ; i++) {
//         for (int j = 0; j < 20; j++) {
//             temp->field[i+temp->pos_x][j+temp->pos_y] = temp->next[i][j];
//         }
//     }
 }
            // if (temp->field[i-temp->pos_x] > 0 &&  temp->field[j-temp->pos_y] > 0) {
            //     temp->field[i-temp->pos_x][j-temp->pos_y] = 0;
            // }

// GameInfo_t* generate_matrix() {
//             int figures[7][4][4] = {
//         {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//         {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//         {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//         {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//         {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//         {{0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//         {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}
//     };
//     static int rnd = 0;
//     if(temp->is_place == true){
//     rnd = rand() % 7;
//     temp->is_place = false;
//     }
//   int start_y = temp->pos_y;
//   int start_x = temp->pos_x;
//   for (int i = 0; i < 20; i++) {
//     for (int j = 0; j < 10; j++) {
//       if (start_y <= i && i < (start_y + 4) && start_x <= j &&
//           j < (start_x + 4)) {
//         if (figures[rnd][i - start_y][j - start_x] == 1) {

//           new_massive[j][i] = 1;
//           // game->tmp->figure_rsrc[i - start_y][j - start_x];
//         } else {
//           new_massive[j][i] = 0;
//         }
//       } else {
//         new_massive[j][i] = 0;
//       }
//     }
//   }

//   for (int i = 0; i < 10; i++) {
//     for (int j = 0; j < 20; j++) {
//       temp->field[j][i] =
//           old_massive[j][i] == 1 || new_massive[j][i] == 1;
//     }
//   }
// //   FILE *fp = fopen("r.txt", "w");
// //  for (int i = 0; i < 10; i++) {
// //         for (int j = 0; j < 20; j++) {
// //             fprintf(fp, "%d ", old_massive->field[i][j]); // Записываем элемент массива
// //         }
// //         fprintf(fp, "\n");
// //  }
// //  fclose(fp);
//   return temp;
// }


void print_game(GameInfo_t* game, TetFigure* current_figure) {    
    
    for (int i = 1; i < HEIGHT; i++) {
        for (int j = 1; j < WIDTH; j++) {
            if (game->field[i][j] == 1) {
                mvaddch(i, j, 'X'); 
            } else {
                mvaddch(i, j, ' '); 
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (current_figure->figure[i][j] == 1) {
                mvaddch(current_figure->y + i, current_figure->x + j, 'X'); 
            }
        }
    }
}

UserAction_t get_user_action(int ch) {

  switch (ch)
  {
  case KEY_LEFT: return Left;

  case KEY_RIGHT: return Right;

  case KEY_UP: return Up;

  case KEY_DOWN: return Down;

  case 'p': return Pause;

  case ' ': return Action;

  default:
    break;
  }
}

int collision(TetFigure* figure, GameInfo_t* game, int dx, int dy){

  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(figure->figure[i][j]){
        int new_x = figure->x + i + dx;
        int new_y = figure->y + j + dy;
        if(new_x < 0 || new_x >= WIDTH || new_y >= HEIGHT ||
            new_y >= 0 && game->field[new_x][new_y]){
            return 1;
          }
      }
    }
  }
  return 0;
}

void move_figure(TetFigure* tet_figure, int dx, int dy) {
   tet_figure->x = tet_figure->x + dx;
    tet_figure->y = tet_figure->y + dy;
}

int check_collision(TetFigure* figure, GameInfo_t* game) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (figure->figure[i][j]) {
                int new_x = figure->x + j;
                int new_y = figure->y + i;
                // Проверка границ и столкновений с другими фигурами
                if (new_x < 0 || new_x >= WIDTH || new_y >= HEIGHT || 
                    (new_y >= 0 && game->field[new_y][new_x])) {
                    return 1; // столкновение
                }
            }
        }
    }
    return 0; // нет столкновения
}













// void moving(GameInfo_t *){

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
