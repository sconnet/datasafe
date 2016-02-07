//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : Screen.h
// Author           : Steve Connet
//
// File Overview    : Handle the screen GUI
//
//*****************************************************************************

#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "docwindow.h"

class Screen
{
public:

    Screen();
    ~Screen();

    inline operator WINDOW *() const
    {
        return win;
    }

    void paint();
    void resize();

    void nextWin();
    void prevWin();

    DocWindow::DOCTYPE activeWin() const
    {
        return active.wintype;
    }
    Window *getActive() const
    {
        return active.win;
    }

private:

    // keep track of the active window
    struct Active
    {
        Active() : win(NULL), count(0) {}

        Window *win;
        DocWindow::DOCTYPE wintype;
        unsigned int count;
    };

    Active active;
    void switchWin();

    WINDOW *win; // ncurses window struct

    DocWindow *winBook;
    DocWindow *winPage;
    DocWindow *winText;

    int height;
    int width;
    int half_width;
    int half_height;

    std::string menu;
    std::string status;
};

#endif // _SCREEN_H_
