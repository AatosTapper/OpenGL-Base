#pragma once

#include "../Shader/Shader.h"
#include "Texture.h"

struct Material
{
    Shader Shader;
    Texture texture;
};
