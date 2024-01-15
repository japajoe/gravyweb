#include "HttpApplication.hpp"

int main(int argc, char **argv)
{
    HttpConfig config;
    
    if(!config.LoadFromFile("config.ini"))
        return 1;

    HttpApplication application(config);
    application.Run();
    return 0;
}