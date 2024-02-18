#pragma once

enum ENT_TYPE : unsigned int
{
    NULL_ENT      = 0u,
    DEFAULT       = 1u,
    PLAYER        = 2u,
    COMP_GROUP    = 3u  // single entity with multiple separate components of the same type
};

struct Entity
{
    unsigned int id;
    ENT_TYPE type;
};