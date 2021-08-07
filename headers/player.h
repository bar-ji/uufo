#pragma once
#include<vector>

class Bullet
{
public:
    Sound shot; 
    Vector2 position;
    float speed;
    Vector2 direction;

    Bullet(Vector2 position);

    void Move();

    void Draw();
};

class Player
{
private:  
    float speed;
    int size;
    int rotation;
    float lastShotTime;


public:
    Sound shot; 
    Vector2 position;
    Texture2D texture;
    std::vector<Bullet> bullets;

    Player(Vector2 _position, float _speed, int _size, float _rotation);

    void Move();

    void Draw();

    void Shoot();
};