#include<raylib.h>
#include<iostream>
#include<cmath>
#include"../headers/meteor.h"


Meteor::Meteor()
{
    int rand = GetRandomValue(0, 3);
    int rand2 = GetRandomValue(1, 3);
    hit = LoadSound("../data/audio/meteorhit.wav");
    switch(rand)
    {
        case 0:
            position.x = GetRandomValue(0, 800);
            position.y = -50;
            velocity.x = GetRandomValue(-20, 20) / 20 * rand2;
            velocity.y = 1* rand2;
            break;
        case 1:
            position.x = GetRandomValue(0, 800);
            position.y = 850;
            velocity.x = GetRandomValue(-20, 20) / 20 * rand2;
            velocity.y = -1 * rand2;
            break;
        case 2:
            position.x = -50;
            position.y = GetRandomValue(0, 800);
            velocity.x = 1 * rand2;
            velocity.y = GetRandomValue(-20, 20) / 20 * rand2;
            break;
        case 3:
            position.x = 850;
            position.y = GetRandomValue(0, 800);
            velocity.x = -1 * rand2;
            velocity.y = GetRandomValue(-20, 20) / 20 * rand2;
            break;
        default:
            position.x = 850;
            position.y = GetRandomValue(0, 800);
            velocity.x = -1 * rand2;
            velocity.y = GetRandomValue(-20, 20) / 20 * rand2;
            break;
    }
}

void Meteor::Draw()
{
    DrawCircle(position.x, position.y, 20, BLACK);
}

void Meteor::Move()
{
    position.x += velocity.x;
    position.y += velocity.y;
}