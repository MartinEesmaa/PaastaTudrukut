#include "raylib.h"
#include <string.h>

#define MAX_LANGUAGES 2
#define LANGUAGE_ESTONIAN 0
#define LANGUAGE_ENGLISH 1

const char* languageNames[MAX_LANGUAGES] = {
    "Eesti",
    "English",
};

const char* textStrings[MAX_LANGUAGES][4] = {
    {
        "Päästa tüdrukut",
        "Alusta mängu",
        "2023 Martin Eesmaa",
        "Oled sa kindel, et tahad väljuda mängu ära? J/E?",
    },
    {
        "Save the Girl",
        "Start Game",
        "2023 Martin Eesmaa",
        "Are you sure you want to exit the game? J/E?",
    },
};

int selectedLanguage = LANGUAGE_ESTONIAN;

const char* GetText(int index) {
    return textStrings[selectedLanguage][index];
}

void ToggleFullScreenWindow(int windowWidth, int windowHeight) {
    if (!IsWindowFullscreen()) {
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
    }
    else {
        ToggleFullscreen();
        SetWindowSize(windowWidth, windowHeight);
    }
}

bool MyCheckCollisionPointRec(Vector2 point, Rectangle rec) {
    return (point.x >= rec.x && point.x <= (rec.x + rec.width) &&
        point.y >= rec.y && point.y <= (rec.y + rec.height));
}

bool ShowLanguageSelectionScene() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int buttonWidth = 200;
    int buttonHeight = 50;
    int spacing = 10;
    int totalButtonsHeight = (buttonHeight + spacing) * MAX_LANGUAGES - spacing;
    int startY = (screenHeight - totalButtonsHeight) / 2;
    int gamepad = 0;

    int selectedButton = 0;
    bool languageSelected = false;

    while (!WindowShouldClose() && !languageSelected) {
        if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN) || IsKeyPressed(KEY_DOWN)) {
            selectedButton = (selectedButton + 1) % MAX_LANGUAGES;
        }
        else if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP) || IsKeyPressed(KEY_UP)) {
            selectedButton = (selectedButton - 1 + MAX_LANGUAGES) % MAX_LANGUAGES;
        }

        Vector2 mousePosition = GetMousePosition();

        BeginDrawing();
        ClearBackground(WHITE);

        for (int i = 0; i < MAX_LANGUAGES; ++i) {
            int buttonY = startY + i * (buttonHeight + spacing);
            Rectangle buttonRect = { (screenWidth - buttonWidth) / 2, buttonY, buttonWidth, buttonHeight };

            if (i == selectedButton) {
                DrawRectangleRec(buttonRect, LIGHTGRAY);
                if ((IsGamepadButtonReleased(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) || IsMouseButtonReleased(MOUSE_LEFT_BUTTON))) {
                    selectedLanguage = i;
                    languageSelected = true;
                    break;
                }
            }
            else {
                DrawRectangleRec(buttonRect, WHITE);
            }

            DrawText(languageNames[i], (screenWidth - MeasureText(languageNames[i], 30)) / 2, buttonY + 15, 30, BLACK);
        }

        EndDrawing();
    }

    return WindowShouldClose();
}

bool ShowExitConfirmation() {
    while (!WindowShouldClose()) {
        int gamepad = 0;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(GetText(3), GetScreenWidth() / 4, GetScreenHeight() / 2, 30, WHITE);
        EndDrawing();

        if (WindowShouldClose()) {
            return false;
        }

        if (IsGamepadButtonReleased(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) || IsKeyPressed(KEY_J)) {
            return true;
        }
        else if (IsGamepadButtonReleased(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT) || IsKeyPressed(KEY_E)) {
            return false;
        }
    }

    return false;
}

int main() {
    int screenWidth = 1280;
    int screenHeight = 720;

    int gamepad = 0;

    InitWindow(screenWidth, screenHeight, "Päästa tüdrukut");
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);

    if (ShowLanguageSelectionScene()) {
        CloseWindow();
        return 0;
    }

    bool exitWindowRequested = false;
    bool exitWindow = false;

    while (!exitWindow) {
        if (IsKeyPressed(KEY_SPACE)) {
            ToggleFullScreenWindow(screenWidth, screenHeight);
        }

        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;
        if (IsGamepadButtonReleased(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) exitWindowRequested = true;

        if (exitWindowRequested) {
            exitWindow = ShowExitConfirmation();
            exitWindowRequested = false;
        }

        BeginDrawing();
        ClearBackground(WHITE);
        DrawText(GetText(0), 450, 50, 50, BLACK);
        DrawText(GetText(1), 475, 175, 50, BLACK);
        DrawText(GetText(2), GetScreenWidth() / 45, GetScreenHeight() / 1.1, 50, BLACK);
        DrawRectangleLines(350, 150, 600, 100, BLACK);
        DrawRectangleLines(350, 300, 600, 100, BLACK);

        if (exitWindowRequested) {
            ClearBackground(BLACK);
            DrawText(GetText(3), GetScreenWidth() / 4, GetScreenHeight() / 2, 30, WHITE);
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
