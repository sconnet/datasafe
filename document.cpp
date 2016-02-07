//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : document.cpp
// Author           : Steve Connet
//
// File Overview    : Contains the main document data
//
// Format of file   :
//
// <book bookname>
// <page pagename>
// text on page 1 of book 1
// <page pagename>
// text on page 2 of book 1
// <book bookname>
// <page pagename>
// text on page 1 of book 2
// <page pagename>
// text on page 2 of book 2
//*****************************************************************************

#include "datasafe.h"
#include "document.h"
#include <fstream>
#include <sstream>

// recognized keywords in markup
#define BOOK "BOOK"
#define PAGE "PAGE"
#define EMPTY "Untitled"

Document::Document(std::string const &filename) :
    filename(filename)
//  iBook(NULL),
//  iPage(NULL)
{
    // open the file
    std::ifstream infile(filename.c_str(), std::ios::in);
    if(!infile)
    {
        std::cerr << "error opening file " << filename << std::endl;
        exit(-2);
    }

    std::string line;
    std::string currentBook = EMPTY;
    std::string currentPage = EMPTY;

    // read each line in the file
    while(std::getline(infile, line))
    {
        std::string keyword;
        std::string name;

        // is this a markup line?
        if(markedUp(line, keyword, name))
        {
            // new book?
            if(BOOK == keyword)
            {
                currentBook = name;
                currentPage = EMPTY;
            }

            // or new page?
            else if(PAGE == keyword)
            {
                currentPage = name;
            }
        }

        // page text
        else
        {
            // use reference to text
            Sentences &text = books[currentBook][currentPage];

            // add text to page of book
            text.push_back(line);
        }
    }

    infile.close();

    // set current book and page iterators to first book and page available
    iBook = books.begin();
    if(iBook != books.end())
    {
        Pages &pages = iBook->second;
        iPage = pages.begin();
        if(iPage != pages.end())
        {
            Sentences &sentences = iPage->second;
            iSentence = sentences.begin();
        }
    }
}

Document::~Document()
{
    std::ofstream outfile(filename.c_str(), std::ios::out);
    if(!outfile)
    {
        std::cerr << "error creating file " << filename << std::endl;
    }
    else
    {
        write(outfile);
    }
}

// returns true if line is marked up, returns keyword and name
bool Document::markedUp(std::string const &line, std::string &keyword,
                        std::string &name)
{
    std::istringstream ss(line);

    // skip whitespace
    ss >> keyword >> name;

    // find starting marker '<'
    if('<' == keyword[0])
    {
        // is end marker in the right place? any text after this is
        // ignored
        if('>' == name[name.length() - 1])
        {
            // remove '>' marker off start and end of strings
            keyword.erase(keyword.begin());
            name.erase(name.end() - 1);

            // this line was a marked up line
            return true;
        }
    }

    // this line wasn't a marked up line
    return false;
}

void Document::write(std::ostream &out)
{
    // for each book
    for(Books::iterator bi = books.begin(); bi != books.end(); ++bi)
    {
        Pages &pages = bi->second;

        // write book title
        out << "<BOOK " << bi->first << '>' << std::endl;

        // for each page in this book
        for(Pages::iterator pi = pages.begin(); pi != pages.end(); ++pi)
        {
            Sentences &sentences = pi->second;

            // write page title
            out << "<PAGE " << pi->first << '>' << std::endl;

            // for each sentence
            for(Sentences::iterator si = sentences.begin(); si != sentences.end();
                    ++si)
            {
                // write sentence
                out << *si << std::endl;
            }
        }
    }
}

bool Document::nextBook()
{
    if(iBook != books.end())
    {
        std::advance(iBook, 1);
        if(iBook == books.end())
        {
            std::advance(iBook, -1);
            return false;
        }

        iPage = iBook->second.begin();
        return true;
    }

    return false;
}

bool Document::prevBook()
{
    if(iBook != books.begin())
    {
        std::advance(iBook, -1);

        iPage = iBook->second.begin();
        return true;
    }

    return false;
}

bool Document::nextPage()
{
    Pages &pages = iBook->second;
    if(iPage != pages.end())
    {
        std::advance(iPage, 1);
        if(iPage == pages.end())
        {
            std::advance(iPage, -1);
            return false;
        }

        iSentence = iPage->second.begin();
        return true;
    }

    return false;
}

bool Document::prevPage()
{
    Pages &pages = iBook->second;
    if(iPage != pages.begin())
    {
        std::advance(iPage, -1);

        iSentence = iPage->second.begin();
        return true;
    }

    return false;
}

