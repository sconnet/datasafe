//*****************************************************************************
//
// Copyright (C) 2005 Steve Connet.  All rights reserved.
//
// Source File Name : ds.cpp
// Author           : Steve Connet
//
// File Overview    : Main entry point
//
//*****************************************************************************

#include "datasafe.h"
#include <signal.h>

// global variables
Document *document;
Input *input;
Config *config;

static char const *version = "0.1a (01/13/05)";

int help()
{
    char const *use =
        "DataSafe v%s  Copyright (C) 2005 Steve Connet.  All rights reserved.\n"
        "Usage: ds [-h] [-f datafile]\n\n"
        "Options:\n"
        "  h\tThis help screen\n";

    printf(use, version);
    exit(0);
}

int main(int argc, char *argv[])
{
    // create and load config file
    config = new Config("dsconfig");

    // parse command line argument for options
    while(argc--)
    {
        if('-' == argv[argc][0])
        {
            switch(argv[argc][1])
            {
                case 'h':
                    help();
                    break;

                case 'f':
                    if(argv[argc + 1])
                    {
                        config->modify("datafile", argv[argc + 1]);
                    }
                    break;
            }
        }
    }

    // create a new document with which to load the datafile
    document = new Document(config->get("datafile"));

#if DEBUG
    document->write(std::cout);
    exit(1);
#endif

    // keyboard & mouse interface object
    input = new Input;

    // handle input (main loop here)
    input->read();

    // perform cleanup
    delete input;
    delete document;
    delete config;

    return EXIT_SUCCESS;
}

