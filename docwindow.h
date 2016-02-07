//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : docwindow.h
// Author           : Steve Connet
//
// File Overview    : window that can contain a document
//
//*****************************************************************************

#ifndef _DOCWINDOW_H_
#define _DOCWINDOW_H_

#include "window.h"
#include <string>
#include <vector>

class DocWindow : public Window
{
public:

    enum DOCTYPE { BOOK, PAGE, TEXT };

    DocWindow(DOCTYPE doctype, int height, int width, int starty, int startx);
    ~DocWindow();

    virtual void paint();
    virtual void cursorMove(DIRECTION dir);

private:

    DocWindow(); // not allowed
    DOCTYPE const doctype;

    // TODO, somehow, map the text to cursor positions and/or indexes so
    // we can edit the text
    //
    //  std::vector<std::string> data;
};

#endif // _DOCWINDOW_H_
