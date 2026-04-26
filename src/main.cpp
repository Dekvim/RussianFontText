#include "raylib.h"
#include <stdlib.h>

static void AddCodepointRange(Font *font, const char *fontPath, int start, int stop);

int main()
{
    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "3D Игра от первого лица - Raylib");
    SetTargetFPS(60);

    Font font = LoadFont("../../assets/Roboto-Medium.ttf");
    AddCodepointRange(&font, "../../assets/Roboto-Medium.ttf", 0x400, 0x4ff);
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(SKYBLUE);

        DrawTextEx(font, "Русский Текст",
            {static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2)}, 26, 0, BLACK);


        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}

static void AddCodepointRange(Font *font, const char *fontPath, int start, int stop)
{
    int rangeSize = stop - start + 1;
    int currentRangeSize = font->glyphCount;

    // TODO: Load glyphs from provided vector font (if available),
    // add them to existing font, regenerating font image and texture

    int updatedCodepointCount = currentRangeSize + rangeSize;
    int *updatedCodepoints = (int *)RL_CALLOC(updatedCodepointCount, sizeof(int));

    // Get current codepoint list
    for (int i = 0; i < currentRangeSize; i++) updatedCodepoints[i] = font->glyphs[i].value;

    // Add new codepoints to list (provided range)
    for (int i = currentRangeSize; i < updatedCodepointCount; i++)
        updatedCodepoints[i] = start + (i - currentRangeSize);

    UnloadFont(*font);
    *font = LoadFontEx(fontPath, 32, updatedCodepoints, updatedCodepointCount);
    RL_FREE(updatedCodepoints);
}