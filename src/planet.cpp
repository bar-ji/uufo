#include<raylib.h>
#include<iostream>
#include<cmath>
#include"../headers/planet.h"

Node::Node()
{
    rotation = GetRandomValue(0, 360);
    position.x = 400 + cos(rotation)*155;
    position.y = 400 + sin(rotation)*155;
}

void Node::Draw()
{
    if(rotation < 0) {rotation += 360;}
    position.x = 400 + cos(rotation)*155;
    position.y = 400 + sin(rotation)*155;
    DrawCircle(position.x, position.y, 20, ORANGE);
}

Planet::Planet()
{
    texture = LoadTexture("../data/images/planet.png");
    shot = LoadSound("../data/audio/hitnode.wav");
    texture.width /= 3.0f;
    texture.height /= 3.0f;
    speed = .5f;
}

void Planet::Draw()
{
    node.Draw();
    int frameWidth = texture.width;
    int frameHeight = texture.height;

    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    Rectangle destRec = { 400.0f, 400.0f, frameWidth*2, frameHeight*2 };
    Vector2 origin = { (float)frameWidth, (float)frameHeight};
    DrawTexturePro(texture, sourceRec, destRec, origin, (float)rotation, WHITE);
}

void Planet::SetRotation(float value)
{
    rotation += value * speed;
    node.rotation += value / 57 * speed;
}

bool Planet::CheckCollision(Player player)
{
    for(int i = 0; i < player.bullets.size(); i++)
    {
        if(CheckCollisionCircles(player.bullets[i].position, 5, node.position, 20))
        {
            PlaySound(shot);
            node = Node();
            player.bullets.erase(player.bullets.begin() + i);
            return true;
        }
    }
    return false;
}