#include <raylib.h>
#include <iostream>
#include "../headers/player.h"
#include "../headers/planet.h"
#include "../headers/meteor.h"
#include <time.h>
#include <cmath>
#include <string>

void GameplayManager(float* speedPtr, float* speedTime, float* meteorTimer, std::vector<Meteor>* meteors, Player* player);

enum Scene
{
    Menu, Game
};
Sound end;
Music music;
Scene scene = Menu;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "uufo");
    Image favicon = LoadImage("../data/images/ufo.png");
    SetWindowIcon(favicon);

    SetTargetFPS(60);           

    Player player({20, 20}, 1.0f, 10, 0);   
    Planet planet; 

    float score;

    Texture2D logo = LoadTexture("../data/images/ufo.png");
    Sound start = LoadSound("../data/audio/start.wav");
    music = LoadMusicStream("../data/audio/music.mp3");
    end = LoadSound("../data/audio/end.wav");
    logo.width /= 4;
    logo.height /= 4;

    float speed;
    float speedTime;
    float meteorTimer;

    std::vector<Meteor> meteors;
    while (!WindowShouldClose())   
    {   
        UpdateMusicStream(music);
        BeginDrawing();

        ClearBackground({255,255,255});
        std::string s = std::to_string((int)score);
        char const *pchar = s.c_str(); 

        switch(scene)
        {
            case Menu:
                DrawText("uufo", 310, 280, 80, {200, 200, 200, 255});
                DrawText("Click To Play!", 260, 390 + sin(GetTime()*10)*1.2, 40, {200, 200, 200, 255});
                DrawText("Score: ", 260, 690 , 40, {200, 200, 200, 255});
                DrawText(pchar, 410, 670 , 70, {200, 200, 200, 255});
                DrawTexture(logo, 335, 210, WHITE);
                if(IsMouseButtonDown(0) || IsKeyDown(KEY_SPACE)){
                    scene = Game;
                    //Reset
                    meteors.clear();
                    speed = 1;
                    speedTime = GetTime();
                    meteorTimer = GetTime();
                    score = 0;
                    InitAudioDevice();
                    PlaySound(start);
                    PlayMusicStream(music);
                }
                break;
            case Game:
                GameplayManager(&speed, &speedTime, &meteorTimer, &meteors, &player);
                player.Move();
                planet.SetRotation(1*speed);
                if(planet.CheckCollision(player))
                {
                    score++;
                }
                s = std::to_string((int)score);
                pchar = s.c_str(); 
                player.Draw();
                planet.Draw();
                DrawText(pchar, 20, 20, 150, {200, 200, 200, 255});
                break;
        }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void GameplayManager(float* speedPtr, float* speedTime, float* meteorTimer, std::vector<Meteor>* meteors, Player* player)
{
    if(GetTime() > *speedTime + 20)
    {
        *speedTime = GetTime();
        *speedPtr *= -1.5f;
    }
    if(GetTime() > *meteorTimer + 5)
    {
        *meteorTimer = GetTime();
        int meteorAmount = GetRandomValue(0, 5);
        for(int i = 0; i < meteorAmount; i++)
        {
            Meteor m;
            (*meteors).push_back(m);
        }
    }

    for(int i = 0; i < (*meteors).size(); i++)
    {
        (*meteors)[i].Draw();
        (*meteors)[i].Move();
        float xPos = (*meteors)[i].position.x;
        float yPos = (*meteors)[i].position.y;
        if(xPos > 850 || xPos < -50 || yPos > 850 || yPos < -50)
        {
            (*meteors).erase((*meteors).begin() + i);
        }
        if(CheckCollisionCircles((*meteors)[i].position, 20, {400,400}, 140))
        {
            (*meteors).erase((*meteors).begin() + i);
            PlaySound((*meteors)[i].hit);
        }
        if(CheckCollisionCircles((*meteors)[i].position, 20, (*player).position, 25))
        {
            StopMusicStream(music);
            PlaySound(end);
            scene = Menu;
            (*meteors).erase((*meteors).begin() + i);
        }
    }
}