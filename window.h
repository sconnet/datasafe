//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : window.h
// Author           : Steve Connet
//
// File Overview    : An ncurses window
//
//*****************************************************************************

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <ncurses.h>

class Window
{
public:

    Window(int height, int width, int starty, int startx);
    virtual ~Window();

    virtual void paint();

    enum DIRECTION { UP, DOWN, RIGHT, LEFT };
    virtual void cursorMove(DIRECTION dir);

    inline operator WINDOW *() const
    {
        return win;
    }

protected:

    WINDOW *win;

    int height;
    int width;
    int starty;
    int startx;

    int ycur;
    int xcur;

private:

    Window();
};

#endif // _WINDOW_H_
