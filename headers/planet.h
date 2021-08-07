#pragma once
#include"player.h"
class Node
{
public:
    Texture2D texture;
    Vector2 position;
    float rotation;

    Node();

    void Draw();
};

class Planet
{
public:
    Sound shot;
    Texture2D texture;
    float rotation;
    float speed;
    Node node;
    Planet();

    void Draw();

    void SetRotation(float value);

    bool CheckCollision(Player player);
};