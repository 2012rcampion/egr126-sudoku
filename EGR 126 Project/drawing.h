#ifndef DRAWING_H
#define DRAWING_H

void draw_board();

void draw_time(int seconds);

void draw_cell(char c, int row, int col, bool emphasize = false);

void highlight_cell(int row, int col, bool highlight);

void draw_cursor(int row, int col);

#endif
