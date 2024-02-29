#include <iostream>
#include <string>
#include "config.h"

#include "Engine/Engine.h"
#include "Engine/Scene.h"

#include "Game/Scenes.h"

#include <memory>

#define SW 1920
#define SH 1080

int main(int argc, char** argv)
{
    Engine game(argc, argv, SW, SH);
    
    init_all_scenes();   
    game.load_scene(Scene_1::scene);

    game.run();

    return 0;
}
