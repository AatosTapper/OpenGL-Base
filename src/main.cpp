#include "config.h"
#include "Engine/Engine.h"
#include "Engine/Scene.h"
#include "Game/Scenes.h"

int main(int argc, char** argv)
{
    Engine game(argc, argv, 1920, 1080);
    
    init_all_scenes();   
    game.set_scene(Scene_1::scene);
    game.run();

    return 0;
}
