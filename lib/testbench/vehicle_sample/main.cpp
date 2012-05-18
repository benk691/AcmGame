#include "application.h"
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char* argv[])
{
    application app;
    app.init(argc, argv, WIDTH, HEIGHT);
    app.run();
}
