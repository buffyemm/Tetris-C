#include <ncurses.h> //подключаем библиотеку ncurses

// int main(int argc,char *argv[])
// {
//   // инициализация (должна быть выполнена 
//   // перед использованием ncurses)
//   initscr();

//   // Измеряем размер экрана в рядах и колонках
//   //int row, col;
//   int x, y;
//   //getmaxyx(stdscr, row, col);
  
//   // перемещение курсора в стандартном экране
//   //move(10 , 10);
//    for (int i = 0; i < 20; i++){
//     for (int j = 0; j < 10; j++)
//     {
//       mvprintw(i, j, "-");
//    //printw("-"); // вывод строки
//     }
    
//    } 
//   // for(int i = 0; i < 20; i++){
//   //   for(int j = 0; j < 10; j++)
//   //     mvprintw(row, col + i, "-");
//   // }
//   refresh(); // обновить экран
//   getch(); // ждём нажатия символа
  
//   endwin(); // завершение работы с ncurses
// }




/////////////////////////


// int main() {
//     initscr(); // Инициализация ncurses
//     cbreak();  // Включение режима немедленного ввода
//     noecho();  // Отключение отображения вводимых символов

//     // Создание окна размером 10 на 20, начиная с позиции (1, 1)
//     WINDOW *win = newwin(10, 20, 1, 1);

//     // Задание символов для рамки
//     char top_left = '+';
//     char top_right = '+';
//     char bottom_left = '+';
//     char bottom_right = '+';
//     char horizontal = '-';
//     char vertical = '|';

//     // Рисуем рамку вручную
//     for (int x = 1; x < 19; x++) {
//         mvwaddch(win, 0, x, horizontal); // Верхняя граница
//         mvwaddch(win, 9, x, horizontal); // Нижняя граница
//     }
//     for (int y = 0; y < 10; y++) {
//         mvwaddch(win, y, 0, vertical); // Левая граница
//         mvwaddch(win, y, 19, vertical); // Правая граница
//     }
//     mvwaddch(win, 0, 0, top_left); // Верхний левый угол
//     mvwaddch(win, 0, 19, top_right); // Верхний правый угол
//     mvwaddch(win, 9, 0, bottom_left); // Нижний левый угол
//     mvwaddch(win, 9, 19, bottom_right); // Нижний правый угол

//     // Обновление окна для отображения изменений
//     wrefresh(win);

//     getch(); // Ожидание нажатия клавиши
//     delwin(win); // Удаление окна
//     endwin(); // Завершение работы с ncurses

//     return 0;
// }




/////////////////////////

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>


void fizik() {
for(int j=0; j<3; j++){
    for (int i = 1; i < 7; i++) {
        if(j==0){
            mvprintw(i, 1, "DARINA");
            refresh();
            clear();
            sleep(1);
        }
        if(j==1){
            mvprintw(7, 1, "DARINA");
            mvprintw(i, 8, "YA");
            refresh();
            clear();
            sleep(1);
        }
         if(j==2){
            mvprintw(7, 8, "YA");
            mvprintw(7, 1, "DARINA");
            mvprintw(i, 11, "CHUT_Zanat");

            refresh();
            clear();
            sleep(1);
        }

    }
}
}


void map(){

initscr();
//int row, col;
// getmaxyx(stdscr, row, col);
mvaddch(0,0, ACS_ULCORNER);
mvaddch(0,10, ACS_TTEE);
mvaddch(20,0, ACS_LLCORNER);
mvaddch(20,10, ACS_BTEE);
for(int y = 1; y < 20; y++){
    for(int x = 1; x < 10; x++){
        if(y == 1){
            mvaddch(0, x, ACS_HLINE);
            mvaddch(20, x, ACS_HLINE);
        }
            mvaddch(y, 0, ACS_VLINE);
            mvaddch(y, 10, ACS_VLINE);
  refresh();
    }
}
    //getch();
    //endwin();
}


void tablo_map(){
initscr();
mvaddch(0,30, ACS_URCORNER);
mvaddch(20,30, ACS_LRCORNER);
for(int x = 11 ; x < 30; x++){
    for (int y = 1; y < 20; y++)
    {
        mvaddch(y, 30, ACS_VLINE);
    }
    
mvaddch(0,x, ACS_HLINE);
mvaddch(20,x, ACS_HLINE);
}
//map();
 getch();
refresh();
endwin();
}


int main(){
map();
tablo_map();
return 0;
}