#pragma once

enum ENT_TYPE : unsigned int
{
    NULL_ENT = 0u,
    DEFAULT = 1u,
    PLAYER   = 2u
};

struct Entity
{
    unsigned int id;
    ENT_TYPE type;
};