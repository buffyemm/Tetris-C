#include "tetris.h"


GameInfo_t* create_game() {
  GameInfo_t* game = (GameInfo_t*)malloc(sizeof(GameInfo_t));
  game->field = (int**)calloc(HEIGHT, sizeof(int*));
  game->next = (int**)calloc(HEIGHT, sizeof(int*));
  for (int i = 0; i < HEIGHT; i++) {
    game->field[i] = (int*)calloc(WIDTH, sizeof(int));
    game->next[i] = (int*)calloc(WIDTH, sizeof(int));
  }
  game->score = 0;
  game->high_score = 0;
  game->level = 1;
  game->speed = 1;
  game->pause = 0;
  return game;
}

TetFigure* create_figure() {
  TetFigure* figure = (TetFigure*)malloc(sizeof(TetFigure));
  figure->x = WIDTH / 2 - 2;
  figure->y = 0;
  figure->figure = (int**)calloc(4, sizeof(int*));
  for (int i = 0; i < 4; i++) {
    figure->figure[i] = (int*)calloc(4, sizeof(int));
  }
  return figure;
}

void free_memory(GameInfo_t* game, TetFigure* current_figure) {
  for (int i = 0; i < HEIGHT; i++) {
    free(game->field[i]);
    free(game->next[i]);
  }
  free(game->field);
  free(game->next);
  free(game);
  for (int i = 0; i < 4; i++) {
    free(current_figure->figure[i]);
  }
  free(current_figure->figure);
  free(current_figure);
}

void print_game(GameInfo_t* game, TetFigure* current_figure) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      mvaddch(i + 1, j + 1, game->field[i][j] == 1 ? 'X' : '.');
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (current_figure->figure[i][j] == 1) {
        mvaddch(current_figure->y + i + 1, current_figure->x + j + 1, 'X');
      }
      if (game->next[i][j] == 1) {
        mvaddch(7 + i, 18 + j, 'X');
      }
    }
  }
  mvprintw(3, 14, "Score: %d", game->score);
}

void next_figure(GameInfo_t* game) {
  int figures[7][4][4] = {
      {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // I
      {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // J
      {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // L
      {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // T
      {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // S
      {{0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // Z
      {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}   // O
  };

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game->next[i][j] = 0;
    }
  }

  int rnd = rand() % 7;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game->next[i][j] = figures[rnd][i][j];
    }
  }
}

void mv_next_figure(GameInfo_t* game, TetFigure* figure) {
  figure->x = WIDTH / 2 - 2;
  figure->y = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure->figure[i][j] = game->next[i][j];
      game->next[i][j] = 0;
    }
  }
}

UserAction_t get_user_action(int ch) {
  switch (ch) {
    case KEY_LEFT:
      return Left;
    case KEY_RIGHT:
      return Right;
    case KEY_UP:
      return Up;
    case KEY_DOWN:
      return Down;
    case 'p':
      return Pause;
    case ' ':
      return Action;
    default:
      return Terminate;
  }
}

void move_figure(TetFigure* tet_figure, int dx, int dy) {
  tet_figure->x += dx;
  tet_figure->y += dy;
}

int check_collision(TetFigure* figure, GameInfo_t* game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figure->figure[i][j]) {
        int new_x = figure->x + j;
        int new_y = figure->y + i;

        if (new_x < 0 || new_x >= WIDTH || new_y >= HEIGHT) {
          return 1;
        }
        if (new_y >= 0 && game->field[new_y][new_x] != 0) {
          return 1;
        }
      }
    }
  }
  return 0;
}

void fix_figure(GameInfo_t* game, TetFigure* tet_figure) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tet_figure->figure[i][j]) {
        game->field[tet_figure->y + i][tet_figure->x + j] = 1;
      }
    }
  }
}

void transpouse(TetFigure* figure) {
  int temp[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      temp[i][j] = figure->figure[j][4 - 1 - i];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure->figure[i][j] = temp[i][j];
    }
  }
}

void clear_line(GameInfo_t* game) {
  int count_line = 0;
  for (int row = 0; row < HEIGHT; row++) {
    int isFull = 1;
    for (int col = 0; col < WIDTH; col++) {
      if (game->field[row][col] == 0) {
        isFull = 0;
        break;
      }
      if(col == 10)
      count_line++;
    }

    if (isFull) {
      for (int r = row; r > 0; r--) {
        for (int c = 0; c < WIDTH; c++) {
          game->field[r][c] = game->field[r - 1][c];
        }
      }
      for (int c = 0; c < WIDTH; c++) {
        game->field[0][c] = 0;
      }
      row--;
      game->score += 100;
      if (game->high_score < game->score)
      game->high_score = game->score;
      // if(count_line > 1)
      // game->score+= count_line *
    }
  }
}

void move_down(TetFigure* temp, GameInfo_t* game) {
  move_figure(temp, 0, 1);
  if (check_collision(temp, game)) {
    move_figure(temp, 0, -1);
    fix_figure(game, temp);
    clear_line(game);
    mv_next_figure(game, temp);
    next_figure(game);
  }
}

void update_game(GameInfo_t* game, TetFigure* current_figure, int* game_over) {
  move_down(current_figure, game);
  if (check_collision(current_figure, game)) {
    *game_over = 1;
  }
}

void handle_user_input(int ch, TetFigure* figure, GameInfo_t* game) {
  UserAction_t action = get_user_action(ch);
  switch (action) {
    case Down:
      move_figure(figure, 0, 1);
      if (check_collision(figure, game)) {
        move_figure(figure, 0, -1);
        fix_figure(game, figure);
        clear_line(game);
        mv_next_figure(game, figure);
        next_figure(game);
      }
      break;

    case Left:
      move_figure(figure, -1, 0);
      if (check_collision(figure, game)) {
        move_figure(figure, 1, 0);
      }
      break;

    case Right:
      move_figure(figure, 1, 0);
      if (check_collision(figure, game)) {
        move_figure(figure, -1, 0);
      }
      break;

    case Action:
      transpouse(figure);
      while (check_collision(figure, game)) {
        transpouse(figure);
      }
      break;

    default:
      break;
  }
}

GameInfo_t record_read() {
FILE *fp = fopen("record.txt", "r");
GameInfo_t *game = fputc(game->high_score, fp);
fclose(fp);
}