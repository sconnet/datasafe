//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : config.cpp
// Author           : Steve Connet
//
// File Overview    : Implementation of the config object
//
//*****************************************************************************

#include "config.h"
#include "util.h"
#include <fstream>
#include <algorithm>

// reads the config file and parses each line
Config::Config(std::string const &filename)
{
    std::string buf;
    char *name;
    char *value;

    data.clear();

    // open the file
    std::ifstream infile(filename.c_str(), std::ios::in);
    if(!infile)
    {
        std::cerr << "error opening " << filename << std::endl;
        exit(-1);
    }

    // read each line in the file
    while(std::getline(infile, buf))
    {
        // make sure we have valid data for this line
        if(buf.length() && isalpha(buf[0]))
        {
            // convert to lower case
            std::transform(buf.begin(), buf.end(), buf.begin(), utils::safetolower);

            // find the equal (=) char
            std::string::size_type pos = buf.find_first_of('=');

            // capture the name and value
            name = new char[buf.length()];
            value = new char[buf.length()];

            strcpy(name, buf.substr(0, pos).c_str());
            strcpy(value, buf.substr(pos + 1).c_str());

            // insert into the map
            data[ utils::trimleft(utils::trimright(name)) ] =
                utils::trimleft(utils::trimright(value));

            delete []name;
            delete []value;
        }
    }

    infile.close();
}
