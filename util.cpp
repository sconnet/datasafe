//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : utils.c
// Author           : Steve Connet
//
// File Overview    : Commonly used C functions
//
//*****************************************************************************

#include "util.h"
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// safely convert a byte to lower-case
int utils::safetolower(int c)
{
    // don't convert if not upper
    if(isupper(c))
    {
        return tolower(c);
    }

    return c;
}

// Reverse the passed character string. The passed string must be NULL
// terminated. Returns a pointer to the beginning of the reversed
// string.
char *utils::strrev(char *str)
{
    char *p1, *p2;

    if(! str || ! *str)
    {
        return str;
    }

    for(p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }

    return str;

} // strrev

// Moves the passed pointer forward until there are no more
// spaces. Returns the incremented pointer. Do not use this with
// dynamically allocted strings.
char *utils::trimleft(char *p)
{
    while(isspace(*p))
    {
        ++p;
    }

    return p;

} // trimleft


// Reverses the string then calles trim_left. Returns the incremented
// pointer.
char *utils::trimright(char *p)
{
    return strrev(trimleft(strrev(p)));

} // trimright

