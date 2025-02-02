// classy-clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"

int main()
{
    InitWindow(800, 450, "Classy Clash");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //Perform Business Logic
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //Render Here
        DrawText("Classy Clash", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

}
