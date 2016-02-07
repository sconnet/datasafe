//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : document.h
// Author           : Steve Connet
//
// File Overview    : Contains the main document data
//
//*****************************************************************************

#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <ncurses.h>

typedef std::vector<std::string> Sentences;

// each page name has a page consisting of lines of text
// <page title, page text>
typedef std::map<std::string, Sentences> Pages;

// each book name has a map of pagenames <book title, page titles>
typedef std::map<std::string, Pages> Books;

class Document
{
public:

    Document(std::string const &filename);
    ~Document();

    void write(std::ostream &out);

    bool nextBook();
    bool prevBook();

    bool nextPage();
    bool prevPage();

private:

    Document();  // not allowed

    bool markedUp(std::string const &line, std::string &keyword,
                  std::string &name);

    void generateBookTitles();
    void generatePageTitles();
    void generatePageText();

    std::string filename;

public:

    // iterators to current book & page
    Books::iterator iBook;
    Pages::iterator iPage;
    Sentences::iterator iSentence;

    Books books;
};

#endif // _DOCUMENT_H_
