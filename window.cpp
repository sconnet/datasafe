//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : window.h
// Author           : Steve Connet
//
// File Overview    : Handle the various windows on the screen
//
//*****************************************************************************

#include "window.h"
#include "document.h"

Window::Window(int height, int width, int starty, int startx) :
    ycur(0), xcur(0)
{
    win = newwin(height, width, starty, startx);
    //  win = subwin(stdscr, height, width, starty, startx);
    scrollok(win, TRUE);
    leaveok(win, FALSE);

    this->height = height;
    this->width = width;
    this->starty = starty;
    this->startx = startx;
}

Window::~Window()
{
    wclear(win);
    delwin(win);
}

void Window::paint()
{
    wattron(win, COLOR_PAIR(5));
    mvwprintw(win, height / 2, width / 2, "%dX%d %d %d",
              width, height, ycur, xcur);
    wattroff(win, COLOR_PAIR(5));

    wmove(win, ycur, xcur);
    //  touchwin(stdscr);
    wnoutrefresh(win);
}

void Window::cursorMove(DIRECTION dir)
{
    getyx(win, ycur, xcur);

    switch(dir)
    {
        case UP:
            if(ycur > 0)
            {
                --ycur;
            }
            break;

        case DOWN:
            if(ycur < height - 1)
            {
                ++ycur;
            }
            break;

        case RIGHT:
            if(xcur < width - 1)
            {
                ++xcur;
            }
            break;

        case LEFT:
            if(xcur > 0)
            {
                --xcur;
            }
            break;
    }
}
