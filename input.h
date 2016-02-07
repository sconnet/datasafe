//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : input.h
// Author           : Steve Connet
//
// File Overview    : handle input from keyboard and mouse
//
//*****************************************************************************

#ifndef _INPUT_H_
#define _INPUT_H_

#include "screen.h"

class Input
{
public:

    Input();
    ~Input();

    void read();

private:

    bool quit;
    Screen *screen;
};

#endif // _INPUT_H_
