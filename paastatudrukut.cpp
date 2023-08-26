#include "raylib.h"
#include <string.h>

#define MAX_LANGUAGES 2
#define LANGUAGE_ESTONIAN 0
#define LANGUAGE_ENGLISH 1

const char* languageNames[MAX_LANGUAGES] = {
    "Eesti",
    "English",
};

const char* textStrings[MAX_LANGUAGES][14] = {
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
        "Vali tegelane",
        "Vajuta S klõhvu, et jätkada vahele",
        "Tagasi",
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
        "Choose character",
        "Press S to skip the cutscene",
        "Back",
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

    InitAudioDevice();

    Sound ding = LoadSound("sfx/ding.mp3");

    int selectedButton = 0;
    bool languageSelected = false;

    while (!WindowShouldClose() && !languageSelected) {
        if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN) || IsKeyPressed(KEY_DOWN)) {
            selectedButton = (selectedButton + 1) % MAX_LANGUAGES;
            PlaySound(ding);
        }
        else if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP) || IsKeyPressed(KEY_UP)) {
            selectedButton = (selectedButton - 1 + MAX_LANGUAGES) % MAX_LANGUAGES;
            PlaySound(ding);
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
    UnloadSound(ding);
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

bool ValiTegelane() {
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText(GetText(11), GetScreenWidth() / 4, GetScreenHeight() / 2, 30, BLACK);
        EndDrawing();
    }
}

bool Tased() {
    while (!WindowShouldClose())
    {
        Texture2D tasetaust = LoadTexture("pilt/tasetaust.png");
        Font britanic = LoadFontEx("fondid/BRITANIC.TTF", 100, 0, 250);
        
        Rectangle tagasinupp = { 75, 45, 200, 70 };
        
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(tasetaust, 0, 0, WHITE);
        DrawTextEx(britanic, GetText(4), (Vector2) { 475.0f, 45.0f }, britanic.baseSize, 10, BLACK);
        DrawRectangleRec(tagasinupp, ORANGE);
        DrawTriangle((Vector2) { 75, 45 }, (Vector2) { 75, 45 }, (Vector2) { 75, 45 }, ORANGE);
        DrawTextEx(britanic, GetText(13), (Vector2) { 85.0f, 45.0f }, 60, 1, BLACK);

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), tagasinupp))
        {
            return 0;
        }

        EndDrawing();
        UnloadTexture(tasetaust);
        UnloadFont(britanic);
    }
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
    Texture2D taust = LoadTexture("pilt/taust.png");
    Font fontTtf = LoadFontEx("fondid/MAIAN.TTF", 72, 0, 250);
    Font fontTtf1 = LoadFontEx("fondid/CHILLER.TTF", 100, 0, 250);
    Music muusika = LoadMusicStream("muusika/esialgne.mp3");

    Image heli1 = LoadImage("pilt/helijavaikne.png");
    Texture2D heli = LoadTextureFromImage(heli1);
    UnloadImage(heli1);

#define NUMBRI_FRAAMI 2

    float frameHeight = (float)heli.height / NUMBRI_FRAAMI;
    Rectangle heliRec = { GetScreenWidth() / 1.06f - heli.width, GetScreenHeight() / 1.01f, (float)heli.width, frameHeight };
    Rectangle helibounds = { GetScreenWidth() / 1.06f - heli.width, GetScreenHeight() / 1.01f - heli.height / NUMBRI_FRAAMI / 1.01f, (float)heli.width, frameHeight };

    Rectangle imageRect = { GetScreenWidth() - xnupp.width, GetScreenHeight() / 12.0f - xnupp.height,
                            static_cast<float>(xnupp.width), static_cast<float>(xnupp.height) };
    Rectangle imageRect1 = { GetScreenWidth() - heli.width, GetScreenHeight() / 12.0f - heli.width,
                            static_cast<float>(heli.width), static_cast<float>(heli.height) };

    int nuppHeli = 0;
    bool nuppHelivajutanud = false;

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

        Rectangle ristkulik1 = { 350.0f, 150.0f, 600.0f, 100.0f };
        Rectangle ristkulik2 = { 350.0f, 300.0f, 600.0f, 100.0f };

        UpdateMusicStream(muusika);
        PlayMusicStream(muusika);

        bool paus = false;

        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(taust, 0, 0, WHITE);
        DrawRectangleRounded(ristkulik1, 1, 0, WHITE);
        DrawRectangleRounded(ristkulik2, 1, 0, WHITE);
        DrawTextEx(fontTtf1, GetText(0), (Vector2) { 400.0f, 45.0f }, (float)fontTtf1.baseSize, 10, BLACK);
        DrawTextEx(fontTtf, GetText(1), (Vector2) { 475.0f, 160.0f }, (float)fontTtf.baseSize, 2, BLACK);
        DrawTextEx(fontTtf, GetText(4), (Vector2) { 550.0f, 315.0f }, (float)fontTtf.baseSize, 2, BLACK);
        DrawTextEx(fontTtf, GetText(2), (Vector2) { GetScreenWidth() / 45.0f, GetScreenHeight() / 1.1f }, (float)fontTtf.baseSize, 2, BLACK);
        DrawRectangleRoundedLines(ristkulik1, 1, 0, 10, BLACK);
        DrawRectangleRoundedLines(ristkulik2, 1, 0, 10, BLACK);
        DrawTexture(xnupp, GetScreenWidth() - xnupp.width, GetScreenHeight() / 12 - xnupp.height, WHITE);
        //DrawTextureRec(heli, heliRec, (Vector2) { helibounds.x, helibounds.y }, WHITE);
        DrawCircle(GetScreenWidth() - 50, GetScreenHeight() - 50, 30, BLACK);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), imageRect))
        {
            exitWindowRequested = true;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), helibounds))
        {
            nuppHeli = 1;
            nuppHelivajutanud = true;

            if (nuppHelivajutanud)
            {
                if (paus)
                {
                    PauseMusicStream(muusika);
                }
                else
                {
                    ResumeMusicStream(muusika);
                    nuppHeli = 0;
                }
            }
            paus = !paus;
        }
        heliRec.y = nuppHeli * frameHeight;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), ristkulik1))
        {
            ValiTegelane();
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), ristkulik2))
        {
            Tased();
        }
        EndDrawing();
    }
    UnloadFont(fontTtf);
    UnloadFont(fontTtf1);
    UnloadMusicStream(muusika);
    UnloadTexture(xnupp);
    UnloadTexture(taust);
    UnloadTexture(heli);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
