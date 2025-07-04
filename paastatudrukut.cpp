#include "raylib.h"
#include <string.h>

#ifdef __SWITCH__
#include <switch.h>
#endif

#define MAX_LANGUAGES 2
#define LANGUAGE_ESTONIAN 0
#define LANGUAGE_ENGLISH 1

const char* languageNames[MAX_LANGUAGES] = {
    "Eesti",
    "English",
};

const char* textStrings[MAX_LANGUAGES][34] = {
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
        "Kuidas mängida mängu?",
        "Enne kui sa alustad mängima, sul on vaja klaviatuuril või juhtmed, et mängida arvutis.",
        "Klahvid:",
        "Hüppa",
        "Vasakule",
        "Alla",
        "Paremale",
        "Paus",
        "Punktid:",
        "Tase:",
        "Aeg jäänud: %.1f sekundid",
        "Aeg lõppes",
        "Krediidid",
        "Tehtud, kujundatud & programmeeritud:",
        "Muusika:",
        "Hääle effektid kasutatud freesound.org veebil",
        "Tase üks",
        "Tase kaks",
        "Abiekraan",
        "Sätted"
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
        "How to play the game?",
        "Before you play the game, you need keyboard or controller to play in computer.",
        "Keys:",
        "Jump",
        "Left",
        "Down",
        "Right",
        "Pause",
        "Score:",
        "Level:",
        "Time Remaining: %.1f seconds",
        "Time's up!",
        "Credits",
        "Created, designed & developed:",
        "Music:",
        "Sound effects used at freesound.org",
        "Level one",
        "Level two",
        "Help screen",
        "Settings"
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

        BeginDrawing();
        ClearBackground(WHITE);

        for (int i = 0; i < MAX_LANGUAGES; ++i) {
            int buttonY = startY + i * (buttonHeight + spacing);
            Rectangle buttonRect = { ((float)screenWidth - (float)buttonWidth) / 2, (float)buttonY, (float)buttonWidth, (float)buttonHeight };

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
    return 0;
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
    return 0;
}

bool Tased() {
    SetWindowTitle(GetText(4));
    Texture2D tasetaust = LoadTexture("pilt/tasetaust.png");
    Font britanic = LoadFontEx("fondid/BRITANIC.TTF", 100, 0, 250);
    while (!WindowShouldClose())
    {   
        Rectangle tagasinupp = { 75, 45, 200, 70 };
        Rectangle esitase = { 212.5, 200, 150, 150 };
        Rectangle teinetase = { 390, 200, 150, 150 };
        Rectangle kolmtase = { 590, 200, 150, 150 };
        Rectangle nelitase = { 790, 200, 150, 150 };
        Rectangle viistase = { 990, 200, 150, 150 };
        Rectangle kuustase = { 212.5, 400, 150, 150 };
        Rectangle seitstase = { 390, 400, 150, 150 };
        Rectangle kahetase = { 590, 400, 150, 150 };
        Rectangle uhektase = { 790, 400, 150, 150 };
        Rectangle kummtase = { 990, 400, 150, 150 };
        
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(tasetaust, 0, 0, WHITE);
        DrawRectangleRec(tagasinupp, ORANGE);
        DrawTextEx(britanic, GetText(4), (Vector2) { 475.0f, 45.0f }, britanic.baseSize, 10, BLACK);
        DrawTriangle((Vector2) { 75, 45 }, (Vector2) { 75, 45 }, (Vector2) { 75, 45 }, ORANGE);
        DrawTextEx(britanic, GetText(13), (Vector2) { 100.0f, 45.0f }, 60, 1, WHITE);
        DrawRectangleLinesEx(esitase, 15, BLACK);
        DrawRectangleGradientH(225, 215, 125, 125, GREEN, LIME);
        DrawTextEx(britanic, "1", (Vector2) { 240, 200 }, 150, 0, BLACK);
        DrawRectangleLinesEx(teinetase, 15, BLACK);
        DrawRectangleGradientH(400, 215, 125, 125, DARKGREEN, LIME);
        DrawTextEx(britanic, "2", (Vector2) { 415, 200 }, 150, 0, BLACK);
        DrawRectangleLinesEx(kolmtase, 15, BLACK);
        DrawRectangleGradientH(600, 215, 125, 125, GREEN, DARKGREEN);
        DrawTextEx(britanic, "3", (Vector2) { 615, 200 }, 150, 0, BLACK);
        DrawRectangleLinesEx(nelitase, 15, BLACK);
        DrawRectangleGradientH(800, 215, 125, 125, GREEN, YELLOW);
        DrawTextEx(britanic, "4", (Vector2) { 815, 200 }, 150, 0, BLACK);
        DrawRectangleLinesEx(viistase, 15, BLACK);
        DrawRectangleGradientH(1000, 215, 125, 125, YELLOW, ORANGE);
        DrawTextEx(britanic, "5", (Vector2) { 1015, 200 }, 150, 0, BLACK);
        DrawRectangleGradientH(225, 415, 125, 125, ORANGE, BROWN);
        DrawRectangleLinesEx(kuustase, 15, BLACK);
        DrawTextEx(britanic, "6", (Vector2) { 240, 400 }, 150, 0, BLACK);
        DrawRectangleGradientH(400, 415, 125, 125, BROWN, DARKBROWN);
        DrawRectangleLinesEx(seitstase, 15, BLACK);
        DrawTextEx(britanic, "7", (Vector2) { 415, 400 }, 150, 0, BLACK);
        DrawRectangleGradientH(600, 415, 125, 125, DARKBROWN, MAROON);
        DrawRectangleLinesEx(kahetase, 15, BLACK);
        DrawTextEx(britanic, "8", (Vector2) { 615, 400 }, 150, 0, BLACK);
        DrawRectangleGradientH(800, 415, 125, 125, MAROON, RED);
        DrawRectangleLinesEx(uhektase, 15, BLACK);
        DrawTextEx(britanic, "9", (Vector2) { 815, 400 }, 150, 0, BLACK);
        DrawRectangleLinesEx(kummtase, 15, BLACK);
        DrawRectangleGradientH(1000, 415, 125, 125, RED, BLACK);
        DrawTextEx(britanic, "10", (Vector2) { 1000, 425 }, 100, 0, BLACK);

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), tagasinupp))
        {
            UnloadTexture(tasetaust);
            UnloadFont(britanic);
            SetWindowTitle(GetText(0));
            return 0;
        }

        if (CheckCollisionPointRec(GetMousePosition(), tagasinupp))
        {
            SetMouseCursor(4);
        }
        else {
            SetMouseCursor(1);
        }

        EndDrawing();
    }
    UnloadTexture(tasetaust);
    UnloadFont(britanic);
    SetWindowTitle(GetText(0));
    return 0;
}

bool AlustaMangija()
{       
        typedef enum ManguEkraan { TASE1 = 0, TASE2 } ManguEkraan;

        Image mangija1 = LoadImage("pilt/mangija.png");
        ImageResize(&mangija1, 32, 64);
        Texture2D mangija = LoadTextureFromImage(mangija1);
        UnloadImage(mangija1);
        //Texture2D huppa = LoadTexture("");
        //Texture2D vasak = LoadTexture("");
        //Texture2D parem = LoadTexture("");

        Image vaen1 = LoadImage("pilt/vaenlane.png");
        ImageResize(&vaen1, 32, 32);
        Texture2D vaen = LoadTextureFromImage(vaen1);
        UnloadImage(vaen1);

        Image vaen2 = LoadImage("pilt/Slimo.png");
        ImageResize(&vaen2, 32, 64);
        Texture2D slimo = LoadTextureFromImage(vaen2);
        UnloadImage(vaen2);

        Image mund1 = LoadImage("pilt/ring.png");
        ImageResize(&mund1, 32, 32);
        Texture2D mund = LoadTextureFromImage(mund1);
        UnloadImage(mund1);

        Image ruut1 = LoadImage("pilt/Ruut.png");
        ImageResize(&ruut1, 32, 32);
        Texture2D ruut = LoadTextureFromImage(ruut1);
        UnloadImage(ruut1);

        Image platvorm1 = LoadImage("pilt/platvorm.png");
        ImageResize(&platvorm1, 100, 22);
        Texture2D platvorm = LoadTextureFromImage(platvorm1);
        UnloadImage(platvorm1);

        Image finislipp1 = LoadImage("pilt/Finislipp.png");
        ImageResize(&finislipp1, 64, 128);
        Texture2D finislipp = LoadTextureFromImage(finislipp1);
        UnloadImage(finislipp1);

        Texture2D taust = LoadTexture("pilt/taust.png");

        Music alusta = LoadMusicStream("muusika/mangu.mp3");
        Sound huppamine = LoadSound("sfx/362328__jofae__platform-jump.mp3");
        Sound manglabi = LoadSound("sfx/495541__matrixxx__retro-death.wav");
        Sound lohutud = LoadSound("sfx/506546__matrixxx__pop-01.wav");
        Sound klapsu = LoadSound("sfx/209792__alterr__applause-mono-24bit-48khz.wav");

        Vector2 positsioon = { 20.0f, GetScreenHeight() - 100.0f };
        Vector2 vaensioon = { 400.0f, GetScreenHeight() - 75.0f };
        Vector2 manguLiik = { 0.0f, GetScreenHeight() - 100.0f};
        Vector2 finislippPos = { GetScreenWidth() - 100.0f, GetScreenHeight() - 160.0f };
        Vector2 platvormPos = { 450.0f, GetScreenHeight() - 225.0f };
        float raskus = 1600.0f;
        float huppaKesk = 800.0f;
        bool kasHuppa = false;

        double alusAeg = GetTime();
        double loppAeg = alusAeg + 180.0;

        float kiirus = 200.0f;

        bool pause = true;
        bool kasVaenAktiiv = true;
        bool finisloppu = true;

        float platvormKiirus = 100.0f;
        bool liiguParemale = true;

        ManguEkraan vaikneEkraan = TASE1;

        while (!WindowShouldClose())
        {
            switch (vaikneEkraan)
            {
                case TASE1:
                {
                    if (!finisloppu) vaikneEkraan = TASE2;
                } break;
                case TASE2:
                {

                } break;
                default: break;
            }

            double currentTime = GetTime();
            double jaanuAeg = loppAeg - currentTime;

            if (jaanuAeg <= 0) {
                positsioon.y += 500;
                DrawText(GetText(25), GetScreenWidth() / 2 + 100, GetScreenHeight() / 2 - 50, 48, WHITE);
                StopMusicStream(alusta);
                PlaySound(manglabi);
                UnloadTexture(mangija);
                UnloadTexture(taust);
                UnloadTexture(mund);
                UnloadTexture(ruut);
                UnloadTexture(platvorm);
                UnloadTexture(finislipp);
                UnloadTexture(vaen);
                UnloadTexture(slimo);
                UnloadMusicStream(alusta);
                UnloadSound(lohutud);
                UnloadSound(klapsu);
                UnloadSound(huppamine);
                return 0;
            }

            if (kasVaenAktiiv && CheckCollisionRecs(
                (Rectangle) {
                positsioon.x, positsioon.y, (float)mangija.width, (float)mangija.height
            },
                (Rectangle) {
                vaensioon.x, vaensioon.y, (float)vaen.width, (float)vaen.height
            }))
            {
                if (positsioon.y < vaensioon.y)
                {
                    kasVaenAktiiv = false;
                }
                else
                {

                }
            }

            if (!kasVaenAktiiv)
            {
                vaensioon.x = -vaen.width;
            }
            else
            {
            }

            if (finisloppu && CheckCollisionRecs(
                (Rectangle) {
                positsioon.x, positsioon.y, (float)mangija.width, (float)mangija.height
            },
                (Rectangle) {
                finislippPos.x, finislippPos.y, (float)finislipp.width, (float)finislipp.height
            }))
            {
                if (positsioon.x < finislippPos.x)
                {
                    finisloppu = false;
                }
                else
                {

                }
            }

            BeginDrawing();
            ClearBackground(WHITE);

            switch (vaikneEkraan)
            {
                case TASE1:
                {
                    SetWindowTitle(GetText(30));
                    DrawTexture(taust, 0, 0, WHITE);
                    DrawRectangle(0, GetScreenHeight() - 25, GetScreenWidth() / 2 - 140, 30, DARKBROWN);
                    DrawRectangle(0, GetScreenHeight() - 40, GetScreenWidth() / 2 - 140, 30, LIME);
                    DrawRectangle(GetScreenWidth() - 580, GetScreenHeight() - 25, GetScreenWidth() / 2 - 50, 30, DARKBROWN);
                    DrawRectangle(GetScreenWidth() - 580, GetScreenHeight() - 40, GetScreenWidth() / 2 - 50, 30, LIME);
                    DrawTextureV(mangija, positsioon, WHITE);
                    DrawTextureV(vaen, vaensioon, WHITE);
                    DrawTexture(ruut, 200, GetScreenHeight() - 150 - ruut.height, WHITE);
                    DrawTexture(ruut, 200 + ruut.width, GetScreenHeight() - 150 - ruut.height, WHITE);
                    DrawTexture(ruut, 200 + ruut.width * 2, GetScreenHeight() - 150 - ruut.height, WHITE);
                    DrawTexture(mund, 200, GetScreenHeight() - 200 - mund.height, WHITE);
                    DrawTexture(mund, 200 + mund.width, GetScreenHeight() - 200 - mund.height, WHITE);
                    DrawTexture(mund, 200 + mund.width * 2, GetScreenHeight() - 200 - mund.height, WHITE);
                    DrawRectangle(400, GetScreenHeight() - 190, 100, 150, MAROON);
                    DrawRectangle(400 * 1.75, GetScreenHeight() - 190, 100, 150, MAROON);
                    DrawTexture(platvorm, platvormPos.x, platvormPos.y, WHITE);
                    DrawTexture(finislipp, finislippPos.x, finislippPos.y, WHITE);
                    DrawText(GetText(22), 0, 0, 32, WHITE);
                    DrawText(GetText(23), GetScreenWidth() - 125, 0, 32, BLACK);
                    DrawText("1", GetScreenWidth() - 25, 0, 32, BLACK);
                    int tekstisuur = MeasureText(GetText(24), 32);
                    DrawText(TextFormat(GetText(24), jaanuAeg), GetScreenWidth() - tekstisuur - 20, 40, 32, BLACK);
                    UpdateMusicStream(alusta);
                    PlayMusicStream(alusta);
                } break;
                case TASE2:
                {
                    SetWindowTitle(GetText(31));
                    DrawTexture(taust, 0, 0, WHITE);
                    DrawTextureV(mangija, positsioon, WHITE);
                    DrawTexture(finislipp, finislippPos.x, finislippPos.y, WHITE);
                    DrawRectangle(0, GetScreenHeight() - 25, GetScreenWidth(), 30, DARKBROWN);
                    DrawRectangle(0, GetScreenHeight() - 40, GetScreenWidth(), 30, LIME);
                    DrawRectangle(200, GetScreenHeight() - 190, 30, 120, MAROON);
                    DrawRectangle(200 * 2, GetScreenHeight() - 190, 30, 120, MAROON);
                    DrawRectangle(200, GetScreenHeight() - 70, 230, 30, MAROON);
                    DrawRectangle(600, GetScreenHeight() - 160, 40, 120, MAROON);
                    DrawRectangle(640, GetScreenHeight() - 220, 40, 180, MAROON);
                    DrawRectangle(680, GetScreenHeight() - 260, 40, 220, MAROON);
                    DrawRectangle(720, GetScreenHeight() - 300, 40, 260, MAROON);
                    DrawRectangle(760, GetScreenHeight() - 340, 40, 300, MAROON);
                    DrawRectangle(800, GetScreenHeight() - 550, 40, 510, MAROON);
                    DrawRectangle(500, 0, 40, 200, MAROON);
                    DrawRectangle(500, 200, 120, 40, MAROON);
                    DrawRectangle(800, GetScreenHeight() - 560, 400, 20, MAROON);
                    DrawRectangle(1000, GetScreenHeight() - 450, 280, 20, MAROON);
                    DrawText(GetText(22), 0, 0, 32, WHITE);
                    DrawText(GetText(23), GetScreenWidth() - 125, 0, 32, BLACK);
                    DrawText("2", GetScreenWidth() - 25, 0, 32, BLACK);
                    int tekstisuur = MeasureText(GetText(24), 32);
                    DrawText(TextFormat(GetText(24), jaanuAeg), GetScreenWidth() - tekstisuur - 20, 40, 32, BLACK);
                } break;
                default: break;
            }

            if (positsioon.y >= GetScreenHeight() - 100.0f)
            {
                positsioon.y = GetScreenHeight() - 100.0f;
                manguLiik.y = 0.0f;
                kasHuppa = false;
            }

            if (IsKeyDown(KEY_W) && pause && !kasHuppa)
            {
                manguLiik.y = -huppaKesk;
                kasHuppa = true;
            }

            if (IsKeyPressed(KEY_W) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && pause) PlaySound(huppamine);

            if (IsKeyDown(KEY_S) && pause)
            {
                positsioon.y += kiirus * GetFrameTime();
            }

            if (IsKeyDown(KEY_A) && pause)
            {
                positsioon.x -= kiirus * GetFrameTime();
            }

            if (IsKeyDown(KEY_D) && pause)
            {
                positsioon.x += kiirus * GetFrameTime();
            }

            if (IsKeyPressed(KEY_P) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)) pause = !pause;

            if (!pause)
            {
                PauseMusicStream(alusta);
                positsioon.x += 0;
                positsioon.y += 0;
                vaensioon.x += 0;
                DrawText(GetText(21), GetScreenWidth() / 2 + 100, GetScreenHeight() / 2 - 50, 48, WHITE);
            }
            else vaensioon.x -= 1;

            if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && pause && !kasHuppa)
            {
                manguLiik.y = -huppaKesk;
                kasHuppa = true;
            }

            if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) && pause)
            {
                positsioon.x -= kiirus * GetFrameTime();
            }

            if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) && pause)
            {
                positsioon.x += kiirus * GetFrameTime();
            }

            if (liiguParemale)
            {
                platvormPos.x += platvormKiirus * GetFrameTime();
                if (platvormPos.x >= 600)
                {
                    liiguParemale = false;
                }
            }
            else
            {
                platvormPos.x -= platvormKiirus * GetFrameTime();
                if (platvormPos.x <= 450)
                {
                    liiguParemale = true;
                }
            }

            manguLiik.y += raskus * GetFrameTime();
            positsioon.x += manguLiik.x * GetFrameTime();
            positsioon.y += manguLiik.y * GetFrameTime();

            EndDrawing();
        }
        UnloadTexture(mangija);
        UnloadTexture(taust);
        UnloadTexture(mund);
        UnloadTexture(ruut);
        UnloadTexture(platvorm);
        UnloadTexture(finislipp);
        UnloadTexture(vaen);
        UnloadTexture(slimo);
        UnloadMusicStream(alusta);
        UnloadSound(lohutud);
        UnloadSound(klapsu);
        UnloadSound(huppamine);
        UnloadSound(manglabi);
        SetWindowTitle(GetText(0));
        return 0;
}

bool Krediidid()
{
    SetWindowTitle(GetText(26));
    Texture2D taust = LoadTexture("pilt/taust.png");
    //Texture2D github = LoadTexture("pilt/GitHub_Invertocat_Logo.svg.png");
    Image githubImage = LoadImage("pilt/GitHub_Invertocat_Logo.svg.png");
    ImageResize(&githubImage, 100, 100);
    Texture2D github = LoadTextureFromImage(githubImage);
    UnloadImage(githubImage);
    Font fontTtf = LoadFontEx("fondid/MAIAN.TTF", 72, 0, 250);
    while (!WindowShouldClose())
    {
        Rectangle tagasinupp = { 75, 45, 200, 70 };
        //Rectangle githubbtn1 = {550, 45, 50, 50};
        Rectangle githubbtn = { GetScreenWidth() - 100, GetScreenHeight() - 100, 100, 100 };

        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(taust, 0, 0, WHITE);
        DrawRectangleRec(tagasinupp, ORANGE);
        DrawTexture(github, GetScreenWidth() - 100, GetScreenHeight() - 100, WHITE);
        DrawTextEx(fontTtf, GetText(13), (Vector2) { 100, 45 }, fontTtf.baseSize, 0, BLACK);
        DrawTextEx(fontTtf, GetText(26), (Vector2) { 500.0f, 45.0f }, fontTtf.baseSize, 0, WHITE);
        DrawTextEx(fontTtf, GetText(27), (Vector2) { 240.0f, 110.0f }, fontTtf.baseSize, 0, WHITE);
        DrawText("Martin Eesmaa", 450, 200, fontTtf.baseSize, WHITE);
        DrawTextEx(fontTtf, GetText(28), (Vector2) { 240.0f, 275.0f }, fontTtf.baseSize, 0, WHITE);
        DrawText("Kevin Macleod", 450, 350, fontTtf.baseSize, WHITE);
        DrawTextEx(fontTtf, GetText(29), (Vector2) { 100.0f, 450.0f }, fontTtf.baseSize, 0, WHITE);

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), tagasinupp))
        {
            UnloadTexture(taust);
            UnloadFont(fontTtf);
            SetWindowTitle(GetText(0));
            return 0;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), githubbtn))
        {
            OpenURL("https://github.com/MartinEesmaa/PaastaTudrukut");
        }

        if (CheckCollisionPointRec(GetMousePosition(), githubbtn) ||
            CheckCollisionPointRec(GetMousePosition(), tagasinupp))
        {
            SetMouseCursor(4);
        }
        else
        {
            SetMouseCursor(1);
        }

        EndDrawing();
    }
    UnloadTexture(taust);
    UnloadFont(fontTtf);
    SetWindowTitle(GetText(0));
    return 0;
}

bool Abiekraan()
{
    SetWindowTitle(GetText(32));
    Font GLECB = LoadFontEx("fondid/GLECB.TTF", 72, 0, 100);
    while (!WindowShouldClose())
    {
        Rectangle tagasinupp = { 75, 45, 200, 70 };

        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextEx(GLECB, GetText(14), (Vector2) { GetScreenWidth() / 3.0f, GetScreenHeight() / 8.0f }, GLECB.baseSize, 0, BLACK);
        DrawTextEx(GLECB, GetText(15), (Vector2) { GetScreenWidth() / 8.0f, GetScreenHeight() / 4.0f }, 48, 0, BLACK);
        DrawTextEx(GLECB, GetText(16), (Vector2) { GetScreenWidth() / 2.25f, GetScreenHeight() / 4.0f + 50.0f }, GLECB.baseSize, 0, BLACK);
        DrawTextEx(GLECB, "W -", (Vector2) { GetScreenWidth() / 2.25f, GetScreenHeight() / 4.0f + 100 }, GLECB.baseSize, 0, BLACK);
        DrawTextEx(GLECB, "A -", (Vector2) { GetScreenWidth() / 2.25f, GetScreenHeight() / 4.0f + 150 }, GLECB.baseSize, 0, BLACK);
        DrawTextEx(GLECB, "S -", (Vector2) { GetScreenWidth() / 2.25f, GetScreenHeight() / 4.0f + 200 }, GLECB.baseSize, 0, BLACK);
        DrawTextEx(GLECB, "D -", (Vector2) { GetScreenWidth() / 2.25f, GetScreenHeight() / 4.0f + 250 }, GLECB.baseSize, 0, BLACK);
        DrawTextEx(GLECB, "P -", (Vector2) { GetScreenWidth() / 2.25f, GetScreenHeight() / 4.0f + 300 }, GLECB.baseSize, 0, BLACK);
        DrawTextEx(GLECB, GetText(17), (Vector2) { GetScreenWidth() / 2.25f + 75, GetScreenHeight() / 4.0f + 100 }, GLECB.baseSize, 0, BLACK);
        DrawTextEx(GLECB, GetText(18), (Vector2) { GetScreenWidth() / 2.25f + 75, GetScreenHeight() / 4.0f + 150 }, GLECB.baseSize, 0, BLACK);
        DrawTextEx(GLECB, GetText(19), (Vector2) { GetScreenWidth() / 2.25f + 75, GetScreenHeight() / 4.0f + 200 }, GLECB.baseSize, 0, BLACK);
        DrawTextEx(GLECB, GetText(20), (Vector2) { GetScreenWidth() / 2.25f + 75, GetScreenHeight() / 4.0f + 250 }, GLECB.baseSize, 0, BLACK);
        DrawTextEx(GLECB, GetText(21), (Vector2) { GetScreenWidth() / 2.25f + 75, GetScreenHeight() / 4.0f + 300 }, GLECB.baseSize, 0, BLACK);
        DrawRectangleRec(tagasinupp, ORANGE);
        DrawTextEx(GLECB, GetText(13), (Vector2) { 125, 45 }, GLECB.baseSize, 0, BLACK);

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), tagasinupp))
        {
            UnloadFont(GLECB);
            SetWindowTitle(GetText(0));
            return 0;
        }

        if (CheckCollisionPointRec(GetMousePosition(), tagasinupp))
        {
            SetMouseCursor(4);
        }
        else
        {
            SetMouseCursor(1);
        }

        EndDrawing();
    }
    UnloadFont(GLECB);
    SetWindowTitle(GetText(0));
    return 0;
}

bool Satted()
{
    SetWindowTitle(GetText(33));
    Texture2D sattedtaust = LoadTexture("pilt/taust.png");
    Font GLECB = LoadFontEx("fondid/GLECB.TTF", 72, 0, 0);
    while (!WindowShouldClose())
    {
        Rectangle tagasinupp = { 75, 45, 200, 70 };

        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(sattedtaust, 0, 0, WHITE);
        DrawRectangleRec(tagasinupp, ORANGE);
        DrawTextEx(GLECB, GetText(13), (Vector2) { 125, 45 }, GLECB.baseSize, 0, BLACK);
        EndDrawing();
    }
    return 0;
}

int main() {
    int screenWidth = 1280;
    int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Päästa tüdrukut");
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);

    ShowLanguageSelectionScene();
    SetWindowTitle(GetText(0));

    bool exitWindowRequested = false;
    bool exitWindow = false;

    Texture2D xnupp = LoadTexture("pilt/cross1.png");
    Texture2D abi = LoadTexture("pilt/help1.png");
    Texture2D taust = LoadTexture("pilt/taust.png");
    Font fontTtf = LoadFontEx("fondid/MAIAN.TTF", 72, 0, 250);
    Font fontTtf1 = LoadFontEx("fondid/CHILLER.TTF", 100, 0, 250);
    Music muusika = LoadMusicStream("muusika/esialgne.mp3");

    Image taht1 = LoadImage("pilt/taht.png");
    ImageResize(&taht1, 70, 70);
    Texture2D taht = LoadTextureFromImage(taht1);
    UnloadImage(taht1);

    Image joon1 = LoadImage("pilt/joon.png");
    ImageResize(&joon1, 275, 24);
    Texture2D joon = LoadTextureFromImage(joon1);
    UnloadImage(joon1);

    Image suda1 = LoadImage("pilt/suda.png");
    ImageResize(&suda1, 70, 70);
    Texture2D suda = LoadTextureFromImage(suda1);
    UnloadImage(suda1);

    Image heli1 = LoadImage("pilt/helijavaikne.png");
    Texture2D heli = LoadTextureFromImage(heli1);
    UnloadImage(heli1);

#define NUMBRI_FRAAMI 2

    float frameHeight = (float)heli.height / NUMBRI_FRAAMI;
    Rectangle heliRec = { GetScreenWidth() / 1.06f - heli.width, GetScreenHeight() / 1.01f, (float)heli.width, frameHeight };
    Rectangle helibounds = { GetScreenWidth() / 1.06f - heli.width, GetScreenHeight() / 1.01f - heli.height / NUMBRI_FRAAMI / 1.01f, (float)heli.width, frameHeight };

    Rectangle imageRect = { GetScreenWidth() - (float)xnupp.width, GetScreenHeight() / 12.0f - xnupp.height,
                            static_cast<float>(xnupp.width), static_cast<float>(xnupp.height) };
    Rectangle imageRect1 = { GetScreenWidth() - (float)heli.width, GetScreenHeight() / 12.0f - heli.width,
                            static_cast<float>(heli.width), static_cast<float>(heli.height) };

    int nuppHeli = 0;
    bool nuppHelivajutanud = false;

    bool paus = false;

    while (!exitWindow) {
        if (IsKeyPressed(KEY_SPACE)) {
            ToggleFullScreenWindow(screenWidth, screenHeight);
        }

        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;
        if (IsGamepadButtonReleased(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) exitWindowRequested = true;

        if (exitWindowRequested) {
            SetMouseCursor(1);
            exitWindow = ShowExitConfirmation();
            exitWindowRequested = false;
        }

        Rectangle ristkulik1 = { 350.0f, 150.0f, 600.0f, 100.0f };
        Rectangle ristkulik2 = { 350.0f, 300.0f, 600.0f, 100.0f };
        Rectangle abil = { 0, 0, 50, 50 };
        Rectangle krediid = { GetScreenWidth() - 250.0f, GetScreenHeight() - 75.0f, 250, 75 };

        UpdateMusicStream(muusika);
        PlayMusicStream(muusika);

        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(taust, 0, 0, WHITE);
        DrawTexture(taht, 590, 65, WHITE);
        DrawTexture(joon, 650, 120, WHITE);
        DrawTexture(suda, 900, 20, WHITE);
        DrawRectangleRounded(ristkulik1, 1, 0, WHITE);
        DrawRectangleRounded(ristkulik2, 1, 0, WHITE);
        DrawTextEx(fontTtf1, GetText(0), (Vector2) { 400.0f, 45.0f }, (float)fontTtf1.baseSize, 10, BLACK);
        DrawTextEx(fontTtf, GetText(1), (Vector2) { 475.0f, 160.0f }, (float)fontTtf.baseSize, 2, BLACK);
        DrawTextEx(fontTtf, GetText(4), (Vector2) { 550.0f, 315.0f }, (float)fontTtf.baseSize, 2, BLACK);
        DrawTextEx(fontTtf, GetText(2), (Vector2) { 0.0f, GetScreenHeight() / 1.1f }, (float)fontTtf.baseSize, 2, BLACK);
        DrawTextEx(fontTtf, "v0.0.1", (Vector2) {0.0f, GetScreenHeight() / 1.2f}, fontTtf.baseSize, 0, BLACK);
        DrawRectangleRoundedLines(ristkulik1, 1, 0, 10, BLACK);
        DrawRectangleRoundedLines(ristkulik2, 1, 0, 10, BLACK);
        DrawTexture(xnupp, GetScreenWidth() - xnupp.width, GetScreenHeight() / 12 - xnupp.height, WHITE);
        DrawTexture(abi, 0, 0, WHITE);
        //DrawTextureRec(heli, heliRec, (Vector2) { helibounds.x, helibounds.y }, WHITE);
        DrawTextEx(fontTtf, GetText(26), (Vector2) { GetScreenWidth() - 250.0f, GetScreenHeight() - 75.0f }, fontTtf.baseSize, 0, BLACK);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), imageRect))
        {
            SetMouseCursor(1);
            exitWindowRequested = true;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && !nuppHelivajutanud && !paus &&
            CheckCollisionPointRec(GetMousePosition(), helibounds))
        {
            nuppHeli = 1;
            nuppHelivajutanud = true;

            paus = !paus;
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
        }
        heliRec.y = nuppHeli * frameHeight;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), ristkulik1))
        {
            SetMouseCursor(1);
            AlustaMangija();
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), ristkulik2))
        {
            SetMouseCursor(1);
            Tased();
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), abil))
        {
            SetMouseCursor(1);
            Abiekraan();
        }

        if (IsGamepadButtonReleased(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) AlustaMangija();

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), krediid))
        {
            SetMouseCursor(1);
            Krediidid();
        }

        if (CheckCollisionPointRec(GetMousePosition(), ristkulik1) ||
            CheckCollisionPointRec(GetMousePosition(), ristkulik2) ||
            CheckCollisionPointRec(GetMousePosition(), abil) ||
            CheckCollisionPointRec(GetMousePosition(), imageRect) ||
            CheckCollisionPointRec(GetMousePosition(), krediid))
        {
            SetMouseCursor(4);
        }
        else {
            SetMouseCursor(1);
        }

        EndDrawing();
    }
    UnloadFont(fontTtf);
    UnloadFont(fontTtf1);
    UnloadMusicStream(muusika);
    UnloadTexture(xnupp);
    UnloadTexture(taust);
    UnloadTexture(abi);
    UnloadTexture(heli);
    UnloadTexture(taht);
    UnloadTexture(joon);
    UnloadTexture(suda);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
