/*
 ***********************************************************************************************************
 *@file plot.h
 *@author shaokairu
 *@date 2021.5.29
 *@brief This file contains all the functions prototypes for plot library.
 ***********************************************************************************************************
 */
#ifndef __PLOT_H
#define __PLOT_H

#include "sys.h"

void chart_plot(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t* title);
void curve_graph(uint16_t x0, uint16_t y0, uint32_t point[][2], uint16_t num);
void hui_graph(void);
void draw_point_graph(int px, int py,uint16_t cx, uint16_t cy, uint32_t pointColor);

#endif

/******************************************** END OF FILE **************************************************/
