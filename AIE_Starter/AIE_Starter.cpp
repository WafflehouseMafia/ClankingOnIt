/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "Pathfinding.h"
#include "NodeMap.h"
#include "PathAgent.h"
#include <map>
#include <iostream>

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 400;
    int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------


    AIForGames::Node* a = new AIForGames::Node();
    a->position = glm::vec2(125.0f, 75.0f);
    AIForGames::Node* b = new AIForGames::Node();
    b->position = glm::vec2(250.0f, 75.0f);


    std::vector<std::string> asciiMap;
    asciiMap.push_back("0000000000000000");
    asciiMap.push_back("0111111111111110");
    asciiMap.push_back("0110111110111110");
    asciiMap.push_back("0111111100001110");
    asciiMap.push_back("0001110100000000");
    asciiMap.push_back("0000011111110000");
    asciiMap.push_back("0000005011111110");
    asciiMap.push_back("0000005000001110");
    asciiMap.push_back("0110005000000110");
    asciiMap.push_back("0111115000000110");
    asciiMap.push_back("0111111111110110");
    asciiMap.push_back("0100111111111110");
    asciiMap.push_back("0100000001111110");
    asciiMap.push_back("0100000001111110");
    asciiMap.push_back("0111000001001110");
    asciiMap.push_back("0111111111000000");
    asciiMap.push_back("0111111111000000");
    asciiMap.push_back("0011111111110000");
    asciiMap.push_back("0111111111111110");
    asciiMap.push_back("0000000000000000");

    NodeMap map;
    map.Initialise(asciiMap, 25);



    AIForGames::Node* start = map.GetNode(1, 1);
    AIForGames::Node* end = map.GetNode(10, 18);
    PathAgent agent;
    agent.SetNode(start);
    agent.PathToNode(end);
    agent.SetSpeed(25);
    Color agentColor = { 30, 110, 20, 255 };

    AIForGames::Node* wanderStart = map.GetRandomNode();
    Agent dudeGuy( &map, new WanderBehaviour() );
    dudeGuy.SetNode(wanderStart);
    dudeGuy.SetSpeed(12.5);
    Color wanderColor = { 200, 80, 10, 255 };

    AIForGames::Node* stalkStart = map.GetNode(10, 2);
    Agent stalker(&map, new FollowBehaviour());
    stalker.SetNode(stalkStart);
    stalker.SetSpeed(20);
    stalker.SetTarget(&agent);
    Color stalkColor = { 145, 25, 90, 255 };
    
    Color lineColor = { 110, 10, 50, 255 };

    float time = (float)GetTime();
    float deltaTime;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKGRAY);
        map.Draw();
        map.DrawPath(agent.m_path, lineColor);
        //map.DrawPath(enemy.m_path, { 255,0,0,255 });
        
        if (IsMouseButtonPressed(0))
        {
            Vector2 mousePos = GetMousePosition();
            if (map.GetClosestNode(glm::vec2(mousePos.x, mousePos.y)) != nullptr)
            {
                start = end;
                end = map.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
                //nodeMapPath = DijkstrasSearch(start, end);
                agent.PathToNode(end);
            }
        }

        agent.Update(deltaTime);
        agent.Draw(agentColor);

        
        dudeGuy.Update(deltaTime);
        dudeGuy.Draw(wanderColor);

        stalker.Update(deltaTime);
        stalker.Draw(stalkColor);

        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}