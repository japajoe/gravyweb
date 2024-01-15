#include "HttpApplication.hpp"

static void OnHttpResponse(unsigned char *data, size_t size, void *userData)
{
    std::cout << data;
}

int main(int argc, char **argv)
{
    HttpConfig config;
    
    if(!config.LoadFromFile("config.ini"))
        return 1;

    HttpApplication application(config);
    application.Run();
    return 0;
}