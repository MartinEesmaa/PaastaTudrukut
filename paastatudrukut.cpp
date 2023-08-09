#include "raylib.h"
#include <string.h>

#define MAX_LANGUAGES 2
#define LANGUAGE_ESTONIAN 0
#define LANGUAGE_ENGLISH 1

const char* languageNames[MAX_LANGUAGES] = {
    "Eesti",
    "English",
};

const char* textStrings[MAX_LANGUAGES][11] = {
    {
        "Päästa tüdrukut",
        "Alusta mäng",
        "2023 Martin Eesmaa",
        "Oled sa kindel, et tahad väljuda mängu ära? J/E?",
        "Tased",
        "Resolutsioon",
        "Helitugevus",
        "SFX tugevus",
        "Teema",
        "Keel",
        "Heledus",
    },
    {
        "Save the Girl",
        "Start Game",
        "2023 Martin Eesmaa",
        "Are you sure you want to exit the game? J/E?",
        "Levels",
        "Resolution",
        "Sound volume",
        "SFX volume",
        "Theme",
        "Language",
        "Brightness",
    },
};

int selectedLanguage = LANGUAGE_ESTONIAN;
int gamepad = 0;

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
                if ((IsGamepadButtonReleased(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) || IsKeyPressed(KEY_ENTER))) {
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
}

bool ShowExitConfirmation() {
    while (!WindowShouldClose()) {
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

    InitWindow(screenWidth, screenHeight, "Päästa tüdrukut");
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);

    if (ShowLanguageSelectionScene()) {
        CloseWindow();
        return 0;
    }

    bool exitWindowRequested = false;
    bool exitWindow = false;

    Texture2D xnupp = LoadTexture("pilt/cross1.png");
    Font fontTtf = LoadFontEx("fondid/MAIAN.TTF", 72, 0, 250);
    Font fontTtf1 = LoadFontEx("fondid/CHILLER.TTF", 100, 0, 250);

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
        DrawTextEx(fontTtf1, GetText(0), (Vector2) { 400.0f, 45.0f }, (float)fontTtf1.baseSize, 10, BLACK);
        DrawTextEx(fontTtf, GetText(1), (Vector2) { 475.0f, 160.0f }, (float)fontTtf.baseSize, 2, BLACK);
        DrawTextEx(fontTtf, GetText(4), (Vector2) { 550.0f, 315.0f }, (float)fontTtf.baseSize, 2, BLACK);
        DrawTextEx(fontTtf, GetText(2), (Vector2) { GetScreenWidth() / 45.0f, GetScreenHeight() / 1.1f }, (float)fontTtf.baseSize, 2, BLACK);
        DrawRectangleLines(350, 150, 600, 100, BLACK);
        DrawRectangleLines(350, 300, 600, 100, BLACK);
        DrawTexture(xnupp, GetScreenWidth() - xnupp.width, GetScreenHeight() / 12 - xnupp.height, WHITE);
        DrawCircle(GetScreenWidth() - 50, GetScreenHeight() - 50, 30, BLACK);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePos1;

            if (mousePos1.x >= GetScreenWidth() - xnupp.width
                && mousePos1.x <= GetScreenWidth()
                && mousePos1.y >= GetScreenHeight() - xnupp.height
                && mousePos1.y <= GetScreenHeight())
            {
                break;
            }
        }

        EndDrawing();
    }
    UnloadFont(fontTtf);
    UnloadFont(fontTtf1);
    CloseWindow();
    return 0;
}
