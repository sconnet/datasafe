//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : config.h
// Author           : Steve Connet
//
// File Overview    : Reads in the configuration file once and puts
//                    each name value pair into a map for quick
//                    hashing and retrieval. This is thread-safe.
//
//*****************************************************************************

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <map>
#include <string>
#include <iostream>

class Config
{
public:

    Config(std::string const &filename);

    inline void modify(std::string const &name, std::string const &val)
    {
        data[name] = val;
    }

    inline void write(std::ostream &out)
    {
        for(DataMap::iterator p = data.begin(); p != data.end(); ++p)
        {
            out << p->first << '=' << p->second << std::endl;
        }
    }

    inline std::string const &get(std::string const &name)
    {
        return data[name];
    }

    inline int getInt(std::string const &name)
    {
        return atoi(get(name).c_str());
    }

private:

    Config(); // not allowed

    typedef std::map<std::string, std::string> DataMap;
    DataMap data;
};

#endif // _CONFIG_H_

