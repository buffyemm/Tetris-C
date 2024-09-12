#include "tetris.h"
#include <stdlib.h>



#ifndef TETRIS_C
#define TETRIS_C

Tet

TetGame* createTetGame(int field_width, int field_height, int figures_size, int count,
TetBlock* figures_template){

TetGame* tetg = (TetGame*)malloc(sizeof(TetGame));
tetg->field = createTetField(field_width, field_height);
tetg->figurest = createTetFiguresT(count, figures_size, figures_template);

return tetg;
};

void calculateTet(TetGame* tetg);


#endif