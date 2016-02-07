//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : screen.cpp
// Author           : Steve Connet
//
// File Overview    : Handle the screen GUI using ncurses library
//
//*****************************************************************************

#include "datasafe.h"
#include "screen.h"
#include "document.h"
#include <stdlib.h>
#include <errno.h>

Screen::Screen()
{
    win = initscr();

    leaveok(win, TRUE);
    scrollok(win, FALSE);

    // get size
    getmaxyx(win, height, width);

    // make room for the status and menu lines
    height -= 2;

    // this makes things easier to split the screen
    half_width = width / 2;
    half_height = height / 2;

    menu = "q:quit  SPACE:add  DEL:delete  TAB:next  STAB:prev  ENTER:edit  UP:up  DOWN:down  ?:help";
    if((int)menu.length() < width)
    {
        menu += std::string(width - menu.length(), ' ');
    }
    else
    {
        menu.erase(width);
    }

    status = "Datasafe v1.0 (c) Steve Connet  book_title  page_title";
    if((int)status.length() < width)
    {
        status += std::string(width - status.length(), ' ');
    }
    else
    {
        status.erase(width);
    }

    if(has_colors())
    {
        start_color();

        // leave background the way it is
        use_default_colors();

        // clear the screen
        //attron(COLOR_PAIR(0));
        wclear(win);
        wrefresh(win);

        // -1 default background color
        init_pair(1, COLOR_YELLOW,  COLOR_BLUE);
        init_pair(2, COLOR_GREEN,   -1);
        init_pair(3, COLOR_BLUE,    -1);
        init_pair(4, COLOR_YELLOW,  -1);
        init_pair(5, COLOR_CYAN,    -1);
        init_pair(6, COLOR_MAGENTA, -1);
        init_pair(7, COLOR_WHITE,   -1);
    }

    winBook = new DocWindow(DocWindow::BOOK, half_height - 1, half_width, 1, 0);
    winPage = new DocWindow(DocWindow::PAGE, half_height, half_width, half_height + 1, 0);
    winText = new DocWindow(DocWindow::TEXT, height, half_width - 1, 1, half_width + 1);

    // set current window
    switchWin();
    paint();
}

Screen::~Screen()
{
    //  attroff(COLOR_PAIR(0));

    delete winText;
    delete winPage;
    delete winBook;

    endwin();
}

void Screen::paint()
{
    // --------------------------------------------------------------------------
    // paint status and menu lines
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(0, 0, (char *)menu.c_str());
    mvprintw(height + 1, 0, (char *)status.c_str());
    attroff(COLOR_PAIR(1) | A_BOLD);

    // --------------------------------------------------------------------------
    // paint splitters
    attron(COLOR_PAIR(2) | A_BOLD);

    // paint vertical splitter
    move(1, half_width);
    vline(ACS_VLINE, height);

    // paint horizontal splitter
    move(half_height, 0);
    hline(ACS_HLINE, half_width);

    // paint connector -|
    mvaddch(half_height, half_width, ACS_RTEE);
    attroff(COLOR_PAIR(2) | A_BOLD);

    wnoutrefresh(win);

    // --------------------------------------------------------------------------
    // paint all windows (order of painting important for cursor visibility)
    switch(active.wintype)
    {
        case DocWindow::BOOK:
            winPage->paint();
            winText->paint();
            winBook->paint();
            break;

        case DocWindow::PAGE:
            winBook->paint();
            winText->paint();
            winPage->paint();
            flash();
            break;

        case DocWindow::TEXT:
            winBook->paint();
            winPage->paint();
            winText->paint();
            break;
    }

    // --------------------------------------------------------------------------
    // refresh window
    doupdate();
}

void Screen::nextWin()
{
    ++active.count;
    switchWin();
}

void Screen::prevWin()
{
    --active.count;
    switchWin();
}

void Screen::switchWin()
{
    switch(active.count % 3)
    {
        case DocWindow::BOOK:
            active.win = winBook;
            active.wintype = DocWindow::BOOK;
            break;

        case DocWindow::PAGE:
            active.win = winPage;
            active.wintype = DocWindow::PAGE;
            break;

        case DocWindow::TEXT:
            active.win = winText;
            active.wintype = DocWindow::TEXT;
            break;
    }

    paint();
}
