#ifndef ASSETS_PATH
#define ASSETS_PATH
#endif

#include <iostream>
#include "raylib.h"
#include "app.h"
#include "appConfig.h"
#include "entt/entt.hpp"

int main(void)
{
    std::cout << "init" << std::endl;
    AppConfig cfg;
    Core::App app(cfg);
    app.Run();

    return 0;
}
