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
    int tick;  
    int** figure;  
} TetFigure;

typedef struct {
    int** field;  
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

TetFigure* create_figure() {
    TetFigure* figure = (TetFigure*)malloc(sizeof(TetFigure));
    figure->x = WIDTH / 2 - 2;  
    figure->y = 0;               
    figure->tick = 30;
    figure->figure = (int**)calloc(4, sizeof(int*));
    for (int i = 0; i < 4; i++) {
        figure->figure[i] = (int*)calloc(4, sizeof(int));
    }
    return figure;
}

GameInfo_t* create_game() {
    GameInfo_t* game = (GameInfo_t*)malloc(sizeof(GameInfo_t));
    game->field = (int**)calloc(HEIGHT, sizeof(int*));
    for (int i = 0; i < HEIGHT; i++) {
        game->field[i] = (int*)calloc(WIDTH, sizeof(int));
    }
    game->score = 0;
    game->high_score = 0;
    game->level = 1;
    game->speed = 1;
    game->pause = 0;
    return game;
}

void init_next_figure(GameInfo_t* game, TetFigure* current_figure) {
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
            current_figure->figure[i][j] = figures[rnd][i][j];
        }
    }
}

int can_move(GameInfo_t* game, TetFigure* tet_figure, int dx, int dy) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tet_figure->figure[i][j]) {
                int new_x = tet_figure->x + j + dx;
                int new_y = tet_figure->y + i + dy;
                if (new_x < 0 || new_x >= WIDTH || new_y >= HEIGHT ||
                 (new_y >= 0 && game->field[new_y][new_x])) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void move_figure(TetFigure* tet_figure, int dx, int dy) {
    tet_figure->x += dx;
    tet_figure->y += dy;
}

void rotate_figure(TetFigure* tet_figure) {
    int temp[4][4] = {0}; // Временный массив для вращаемой фигуры

    // Вращение
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j][3 - i] = tet_figure->figure[i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tet_figure->figure[i][j] = temp[i][j];
        }
    }
}

void fix_figure(GameInfo_t* game, TetFigure* tet_figure) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tet_figure->figure[i][j]) {
                int y = tet_figure->y + i;
                int x = tet_figure->x + j;
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
                    game->field[y][x] = 1;
                }
            }
        }
    }
}

void print_game(GameInfo_t* game, TetFigure* current_figure) {
    clear();
    
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
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

    refresh(); 
}

void update_game(GameInfo_t* game, TetFigure* current_figure, int* game_over) {
    if (can_move(game, current_figure, 0, 1)) {
        move_figure(current_figure, 0, 1);
    } else {
        fix_figure(game, current_figure); // Фиксируем фигуру
        current_figure->y = 0; 
        current_figure->x = WIDTH / 2 - 2; 
        init_next_figure(game, current_figure); // Инициализируем новую фигуру
        if (!can_move(game, current_figure, 0, 0)) {
            *game_over = 1; // Игра окончена
        }
    }
}

void game_tact(GameInfo_t* game, TetFigure* current_figure, int* game_over) {
    update_game(game, current_figure, game_over); // Обновляем состояние игры
}

void free_memory(GameInfo_t* game, TetFigure* current_figure) {
    for (int i = 0; i < HEIGHT; i++) {
        free(game->field[i]);
    }
    free(game->field);
    free(game);
    for (int i = 0; i < 4; i++) {
        free(current_figure->figure[i]);
    }
    free(current_figure->figure);
    free(current_figure);
}

UserAction_t get_user_action(int ch) {
    switch (ch) {
        case KEY_LEFT: return Left;
        case KEY_RIGHT: return Right;
        case KEY_UP: return Up;
        case KEY_DOWN: return Down;
        case 'p': return Pause; 
        case ' ': return Action; // вращение
        default: break; 
    }
}

int main() {
    srand(time(NULL)); 
    setlocale(LC_ALL, "");
    initscr();    
    nodelay(stdscr, TRUE);
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    GameInfo_t* game = create_game();
   
    TetFigure* current_figure = create_figure();
    init_next_figure(game, current_figure);

    int game_over = 0;
    int paused = 0;

    while (!game_over) {
        int ch = getch();
        UserAction_t action = get_user_action(ch);

        switch (action) {
            case Left:
                if (!paused && can_move(game, current_figure, -1, 0)) {
                    move_figure(current_figure, -1, 0); 
                }
                break;
            case Right:
                if (!paused && can_move(game, current_figure, 1, 0)) {
                    move_figure(current_figure, 1, 0); 
                }
                break;
            case Down:
                if (!paused && can_move(game, current_figure, 0, 1)) {
                    move_figure(current_figure, 0, 1); 
                }
                break;
            case Action:
                if(!paused){
                    rotate_figure(current_figure);
                }
                break;
            case Pause:
                paused = !paused;
                break;
            case Terminate:
                game_over = 1; 
                break;
            default:
                break; 
        }

        if(!paused){
            game_tact(game, current_figure, &game_over);        
            print_game(game, current_figure); 
            usleep(300000 / game->speed); 
        }else{
            attron(COLOR_PAIR(1));
            mvprintw(8, 4, "PAUSE");
            attroff(COLOR_PAIR(1));
        }
    }

    free_memory(game, current_figure);
    endwin();
    return 0;
}