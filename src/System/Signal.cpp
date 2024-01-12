#include "Signal.hpp"
#include "gravy_tcp.h"
#include "Console.hpp"
#include <signal.h>

static void HandleSignal(int signum)
{
#ifdef _WIN32
    switch(signum)
    {
        case SIGINT:
        {
            gravy_tcp_library_uninit();
            exit(signum);
            break;
        }
        //Windows does not have SIGPIPE
    }
#else
    switch(signum)
    {
        case SIGINT:
        {
            gravy_tcp_library_uninit();
            exit(signum);
            break;
        }
        case SIGPIPE:
        {
            Console::WriteError("Unable to write data to the transport connection: Broken pipe");
            break;    
        }
    }
#endif
}

void Signal::RegisterHandler()
{
#ifdef _WIN32
    //Needed to handle an interrupt request and shut down the library
    if (signal(SIGINT, HandleSignal) == SIG_ERR) 
    {
        Console::WriteError("Error setting up SIGINT handler");
        exit(1);
    }
    //Windows does not have SIGPIPE signal
#else
    //Needed to handle an interrupt request and shut down the library
    if (signal(SIGINT, HandleSignal) == SIG_ERR) 
    {
        Console::WriteError("Error setting up SIGINT handler");
        exit(1);
    }

    //Needed to handle a broken pipe signal, otherwise the program just closes
    //Disconnected sockets can cause this signal to be fired so we must capture it
    if (signal(SIGPIPE, HandleSignal) == SIG_ERR)
    {
        Console::WriteError("Error setting up SIGPIPE handler");
        exit(1);
    }
#endif
}