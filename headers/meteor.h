#pragma once
#include "raylib.h"


class Meteor
{
public:
    Sound hit;
    Vector2 position;
    Vector2 velocity;

    Meteor();

    void Draw();

    void Move();
};