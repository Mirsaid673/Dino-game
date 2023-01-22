#include <iostream>

#include "dino/game.h"

Application *app;

int main()
{
    Game mp;
    app = &mp;
    return app->run();
}