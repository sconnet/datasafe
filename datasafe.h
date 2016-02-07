//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : datasafe.h
// Author           : Steve Connet
//
// File Overview    : common application items
//
//*****************************************************************************

#ifndef _DATASAFE_H_
#define _DATASAFE_H_

#include <ncurses.h>
#include "document.h"
#include "screen.h"
#include "input.h"
#include "config.h"

extern Document *document;
extern Screen *screen;
extern Input *input;
extern Config *config;

#endif // _DATASAFE_H_
