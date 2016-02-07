//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : docwindow.cpp
// Author           : Steve Connet
//
// File Overview    : window that can contain a document
//
//*****************************************************************************

#include "datasafe.h"
#include "docwindow.h"
#include <cstdlib>

DocWindow::DocWindow(DOCTYPE type, int height, int width, int starty, int startx) :
    Window(height, width, starty, startx),
    doctype(type)
{
    //  wattron(win, COLOR_PAIR(7) | A_BOLD);
}

DocWindow::~DocWindow()
{
    //  wattroff(win, COLOR_PAIR(7) | A_BOLD);
}

void DocWindow::paint()
{
    wclear(win);
    wmove(win, 0, 0);

    switch(doctype)
    {
        case BOOK:
            for(Books::iterator i = document->books.begin();
                    i != document->books.end();
                    ++i)
            {
                wprintw(win, "%.*s\n", width - 1, i->first.c_str());
            }
            break;

        case PAGE:
            for(Pages::iterator i = document->iBook->second.begin();
                    i != document->iBook->second.end();
                    ++i)
            {
                wprintw(win, "%.*s\n", width - 1, i->first.c_str());
            }
            break;

        case TEXT:
            for(Sentences::iterator i = document->iPage->second.begin();
                    i != document->iPage->second.end();
                    ++i)
            {
                wprintw(win, "%.*s\n", width - 1, i->c_str());
            }
            break;
    }

    Window::paint();
}

void DocWindow::cursorMove(DIRECTION dir)
{
    bool move = false;

    switch(doctype)
    {
        case BOOK:
            if(DOWN == dir)
            {
                move = document->nextBook();
            }
            else if(UP == dir)
            {
                move = document->prevBook();
            }
            break;

        case PAGE:
            if(DOWN == dir)
            {
                move = document->nextPage();
            }
            else if(UP == dir)
            {
                move = document->prevPage();
            }
            break;

        case TEXT:
            break;
    }

    if(move)
    {
        Window::cursorMove(dir);
    }
}

