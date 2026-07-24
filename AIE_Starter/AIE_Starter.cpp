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


using namespace AIForGames;



int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 400;
    int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------


    Node* a = new Node();
    a->position = glm::vec2(125.0f, 75.0f);
    Node* b = new Node();
    b->position = glm::vec2(250.0f, 75.0f);


    std::vector<std::string> asciiMap;
    asciiMap.push_back("0000000000000000");
    asciiMap.push_back("0111111111111110");
    asciiMap.push_back("0110111100011110");
    asciiMap.push_back("0111111100001110");
    asciiMap.push_back("0001110100000000");
    asciiMap.push_back("0000011111110000");
    asciiMap.push_back("0000001011111110");
    asciiMap.push_back("0000001000001110");
    asciiMap.push_back("0110001000000110");
    asciiMap.push_back("0111111000000110");
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


    NodeMap yep;
    yep.Initialise(asciiMap, 25);
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(GRAY);
        yep.Draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}