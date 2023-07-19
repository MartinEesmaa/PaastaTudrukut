#include "raylib.h"

void ToggleFullScreenWindow(int akenLaius, int akenKõrgus)
{
    if (!IsWindowFullscreen())
    {
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
    }
    else
    {
        ToggleFullscreen();
        SetWindowSize(akenLaius, akenKõrgus);
    }
}

int main()
{
    int ekraanLaius = 1280;
    int ekraanKõrgus = 720;

    InitWindow(ekraanLaius, ekraanKõrgus, "Päästa tüdrukut");
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);

    bool exitWindowRequested = false;
    bool exitWindow = false;

    while (!exitWindow)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            ToggleFullScreenWindow(ekraanLaius, ekraanKõrgus);
        }

        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;

        if (exitWindowRequested)
        {
            if (IsKeyPressed(KEY_J)) exitWindow = true;
            else if (IsKeyPressed(KEY_E)) exitWindowRequested = false;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Päästa tüdrukut", 450, 50, 50, BLACK);
        DrawText("Alusta mängu", 475, 175, 50, BLACK);
        DrawText("2023 Martin Eesmaa", GetScreenWidth() / 45, GetScreenHeight() / 1.1, 50, BLACK);
        DrawRectangleLines(350, 150, 600, 100, BLACK);
        DrawRectangleLines(350, 300, 600, 100, BLACK);

        if (exitWindowRequested)
        {
            ClearBackground(BLACK);
            DrawText("Oled sa kindel, et tahad väljuda mängu ära? J/E?", GetScreenWidth() / 4, GetScreenHeight() / 2, 30, WHITE);
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}