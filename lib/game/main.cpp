#include "application.h"

#define WIDTH 720
#define HEIGHT 540

int main(int argc, char* argv[])
{
    application app;
    app.init(argc, argv, WIDTH, HEIGHT);
    app.run();
}
