//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : input.cpp
// Author           : Steve Connet
//
// File Overview    : handle input from keyboard and mouse
//
//*****************************************************************************

#include "datasafe.h"
#include "input.h"
#include <errno.h>

#define KEY_TAB  0x09

Input::Input() :
    quit(false)
{
    screen = new Screen;

    cbreak();
    keypad(*screen, TRUE);
    nodelay(*screen, FALSE);  // blocking getch
    noecho();
    nonl();
}

Input::~Input()
{
    keypad(*screen, FALSE);
    echo();
    nocbreak();
    nl();

    delete screen;
}

void Input::read()
{
    int keypress;

    while(!quit)
    {
        // check for keypress
        keypress = wgetch(*screen);
        switch(keypress)
        {
            // 0.1 sec timeout with no keypress
            case ERR:
                if(EINTR == errno)
                {
                    doupdate();
                }
                break;

            // SIGWINCH
            case KEY_RESIZE:
                delete screen;
                screen = new Screen;
                break;

            case 'q':
                quit = true;
                break;

            case KEY_TAB:
                screen->nextWin();
                break;

            case KEY_BTAB:  // back tab
                screen->prevWin();
                break;

            case KEY_DOWN:
                screen->getActive()->cursorMove(Window::DOWN);
                screen->paint();
                /*
                  if current win on screen is book; then
                    if next book
                       move text highlight in docwindow
                 */
                break;

            case KEY_UP:
                screen->getActive()->cursorMove(Window::UP);
                screen->paint();
                break;

            case KEY_RIGHT:
                screen->getActive()->cursorMove(Window::RIGHT);
                screen->paint();
                break;

            case KEY_LEFT:
                screen->getActive()->cursorMove(Window::LEFT);
                screen->paint();
                break;

#if 0
            case KEY_ENTER:
            case 0x0D:
            {
                char str[80];
                echo();
                wgetstr(*screen->getActive(), str);
                noecho();
            }
            break;
#endif

            default:
                screen->paint();
                break;
        }
    }
}
