#include <conio.h>
#include <ctime>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

// ----- GAME VARIABLES -----
int dinoY = 0;     // 0 = ground, 1 = in air
int jumpTimer = 0; // 0 = ground, 1 = jumping
int obstacleX = 40;
int health = 5;
int score = 0;
bool gameOver = false;
int stamina = 5;
const int maxStamina = 5;
int birdX = 60;
bool isDucking = false;
int duckTimer = 0;
int level = 1;
int gameSpeed = 150; // lower = faster
int powerX = -1;
int powerType = 0; // 0 = none, 1 = shield, 2 = stamina
bool shieldActive = false;
bool isPaused = false;
time_t lastStaminaUse = 0;

const int GAME_WIDTH = 60;
const int HUD_HEIGHT = 10;
const int GAME_HEIGHT = 6;

void setConsoleColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//-------START MENU FUNCTION-------
void startMenu()
{
    system("cls");
    setConsoleColor(11); // Cyan theme

    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║   ██████╗ ██╗███╗   ██╗ ██████╗                      ║\n";
    cout << "  ║   ██╔══██╗██║████╗  ██║██╔═══██╗                     ║\n";
    cout << "  ║   ██║  ██║██║██╔██╗ ██║██║   ██║                     ║\n";
    cout << "  ║   ██║  ██║██║██║╚██╗██║██║   ██║                     ║\n";
    cout << "  ║   ██████╔╝██║██║ ╚████║╚██████╔╝                     ║\n";
    cout << "  ║   ╚═════╝ ╚═╝╚═╝  ╚═══╝ ╚═════╝                      ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║    ██████╗  █████╗ ███╗   ███╗███████╗               ║\n";
    cout << "  ║   ██╔════╝ ██╔══██╗████╗ ████║██╔════╝               ║\n";
    cout << "  ║   ██║  ███╗███████║██╔████╔██║█████╗                 ║\n";
    cout << "  ║   ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝                 ║\n";
    cout << "  ║   ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗               ║\n";
    cout << "  ║    ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝               ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ╠══════════════════════════════════════════════════════╣\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║               [ 1 ]  Start Game                      ║\n";
    cout << "  ║               [ 2 ]  Instructions                    ║\n";
    cout << "  ║               [ 3 ]  Exit                            ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ╚══════════════════════════════════════════════════════╝\n";

    setConsoleColor(14); // Yellow
    cout << "\n              Enter your choice: ";
}

//------PAUSE MENU FUNCTION------
// This function displays the Pause screen and waits for input
char showPauseMenu() {
    system("cls");
    setConsoleColor(14); // Yellow color for Pause
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║   ██████╗  █████╗ ███╗   ███╗███████╗                ║\n";
    cout << "  ║  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝                ║\n";
    cout << "  ║  ██║  ███╗███████║██╔████╔██║█████╗                  ║\n";
    cout << "  ║  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝                  ║\n";
    cout << "  ║  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗                ║\n";
    cout << "  ║   ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝                ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║     ██████╗  █████╗ ██╗   ██╗███████╗███████╗        ║\n";
    cout << "  ║     ██╔══██╗██╔══██╗██║   ██║██╔════╝██╔════╝        ║\n";
    cout << "  ║     ██████╔╝███████║██║   ██║███████╗█████╗          ║\n";
    cout << "  ║     ██╔═══╝ ██╔══██║██║   ██║╚════██║██╔══╝          ║\n";
    cout << "  ║     ██║     ██║  ██║╚██████╔╝███████║███████╗        ║\n";
    cout << "  ║     ╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝        ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ╠══════════════════════════════════════════════════════╣\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║          Current Score: " << score << "                            ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║        [ R ] Resume Game                             ║\n";
    cout << "  ║        [ M ] Main Menu                               ║\n";
    cout << "  ║        [ Q ] Quit                                    ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ╚══════════════════════════════════════════════════════╝\n";

    // Wait for specific input inside the pause menu
    while (true) {
        char ch = _getch();
        if (ch == 'r' || ch == 'R') return 'r';
        if (ch == 'm' || ch == 'M') return 'm';
        if (ch == 'q' || ch == 'Q') return 'q';
    }
}

//------GAME OVER MENU FUNCTION------
char showGameOverMenu() {
    system("cls");
    setConsoleColor(12); // Red theme for Game Over

    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║   ██████╗  █████╗ ███╗   ███╗███████╗                ║\n";
    cout << "  ║  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝                ║\n";
    cout << "  ║  ██║  ███╗███████║██╔████╔██║█████╗                  ║\n";
    cout << "  ║  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝                  ║\n";
    cout << "  ║  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗                ║\n";
    cout << "  ║   ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝                ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║     ██████╗ ██╗   ██╗███████╗██████╗                 ║\n";
    cout << "  ║    ██╔════╝ ██║   ██║██╔════╝██╔══██╗                ║\n";
    cout << "  ║    ██║  ███╗██║   ██║█████╗  ██████╔╝                ║\n";
    cout << "  ║    ██║   ██║██║   ██║██╔══╝  ██╔══██╗                ║\n";
    cout << "  ║    ╚██████╔╝╚██████╔╝███████╗██║  ██║                ║\n";
    cout << "  ║     ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝                ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ╠══════════════════════════════════════════════════════╣\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║          Final Score: " << score << "                              ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║        [ R ] Restart Game                            ║\n";
    cout << "  ║        [ M ] Main Menu                               ║\n";
    cout << "  ║        [ Q ] Quit                                    ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ╚══════════════════════════════════════════════════════╝\n";

    // Wait for input
    while (true) {
        char ch = _getch();
        if (ch == 'r' || ch == 'R') return 'r';
        if (ch == 'm' || ch == 'M') return 'm';
        if (ch == 'q' || ch == 'Q') return 'q';
    }
}
//------INSTRUCTIONS FUNCTION------
void instructions() {
    system("cls");
    cout << "╔═══════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                               🎮 HOW TO PLAY                              ║\n";
    cout << "╠═══════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║                                                                           ║\n";
    cout << "║ SPACE  → Jump 🦖⬆️ (uses stamina)                                         ║\n";
    cout << "║ S      → Duck 🦎⬇️ (2 seconds)                                           ║\n";
    cout << "║                                                                           ║\n";
    cout << "║ 🌵 Tree  → Jump over                                                      ║\n";
    cout << "║ 🐦 Bird  → Duck under                                                     ║\n";
    cout << "║                                                                           ║\n";
    cout << "║ 🍀 Power-Ups:                                                             ║\n";
    cout << "║ 🛡️ Shield → Blocks one hit                                                 ║\n";
    cout << "║ 🔋 Battery → Refill stamina                                               ║\n";
    cout << "║                                                                           ║\n";
    cout << "╚═══════════════════════════════════════════════════════════════════════════╝\n";
    cout << "Press any key to go back...";
    _getch();
}

//-----RESET FUNCTION-----
void resetGame() {
    dinoY = 0;
    jumpTimer = 0;
    duckTimer = 0;
    isDucking = false;

    obstacleX = 40;
    birdX = 60;
    powerX = -1;

    health = 5;
    stamina = maxStamina;
    shieldActive = false;

    score = 0;
    level = 1;
    gameSpeed = 150;

    gameOver = false;
    isPaused = false;
}

// ----- CURSOR UTILS -----
void setCursor(int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hOut, coord);
}

void hideCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

// ----- DRAW GAME -----
void drawGame()
{
    setCursor(0, 0);

    // ===== HUD =====
    cout << "❤️  Health: ";
    for (int i = 0; i < health; i++) cout << "❤️ ";
    for (int i = health; i < 5; i++) cout << "🖤 ";
    cout << "\n";

    cout << "⚡  Stamina: ";
    for (int i = 0; i < stamina; i++) cout << "⚡ ";
    for (int i = stamina; i < maxStamina; i++) cout << "▫ ";
    cout << "\n";

    cout << "🏆  Score: " << score << "    🎮 Level: " << level << "\n";

    cout << "🛡️  Shield: " << (shieldActive ? "ACTIVE" : "INACTIVE") << "\n";

    cout << "------------------------------------------------------------\n";

    // ===== SKY (Jump line) =====
    for (int i = 0; i < GAME_WIDTH; i++)
    {
        if (i == 5 && dinoY == 1) cout << "🦖";
        else cout << " ";
    }
    cout << "\n";

    // ===== AIR (Bird / Shield power) =====
    for (int i = 0; i < GAME_WIDTH; i++)
    {
        if (i == birdX)
            cout << "🐦";
        else
            cout << " ";
    }
    cout << "\n";

    // ===== OBJECT LINE (Above ground) =====
    for (int i = 0; i < GAME_WIDTH; i++)
    {
        if (i == 5 && dinoY == 0 && !isDucking)
            cout << "🦖";
        else if (i == 5 && isDucking)
            cout << "🦎";
        else if (i == obstacleX)
            cout << "🌵";
        else if (i == powerX && powerType == 1)
            cout << "🛡️";
        else if (i == powerX && powerType == 2)
            cout << "🔋";
        else
            cout << " ";
    }
    cout << "\n";

    // ===== GROUND LINE =====
    for (int i = 0; i < GAME_WIDTH; i++)
    {
        cout << "━";
    }
    cout << "\n";

    cout << "Theme: "
         << (level == 1 ? "🌞 Day" : level == 2 ? "🌙 Night" : "🌋 Volcano")
         << "\n";
}


// ----- INPUT -----
void input() {
    if (_kbhit()) {
        char ch = _getch();
        // ---- PAUSE TOGGLE ----
        if (ch == 'p' || ch == 'P') {
            isPaused = !isPaused;
            return; // Exit input to handle pause immediately
        }

        if (isPaused)
            return;

        // Jump
        if (ch == ' ' && dinoY == 0 && stamina > 0 && duckTimer == 0) {
            dinoY = 1;
            jumpTimer = 4;
            stamina--;
            lastStaminaUse = time(0); // record usage time
            Beep(800, 100);
        }

        // Duck (2 seconds)
        if ((ch == 's' || ch == 'S') && duckTimer == 0 && dinoY == 0) {
            duckTimer = 3; // ≈ 2 seconds
            isDucking = true;
            Beep(600, 100);
        }
    }
}

void update() {
    if (isPaused)
        return;

    obstacleX--;
    if (level >= 2)
        birdX--;

    // Reset tree
    if (obstacleX < 0) {
        obstacleX = 40;
        score += 10;
    }

    // Spawn power-up randomly
    if (powerX == -1 && rand() % 60 == 0) {
        powerX = 40;
        powerType = (rand() % 2) + 1; // 1 or 2
    }
    if (powerX != -1)
        powerX--;

    if (powerX < 0)
        powerX = -1;

    // Power-up collection (Only collect if on ground)
    if (powerX == 5 && dinoY == 0) {
        if (powerType == 1) {
            shieldActive = true;
            Beep(900, 200);
        } else if (powerType == 2) {
            stamina = maxStamina;
            Beep(700, 200);
        }
        powerX = -1;
    }

    // Reset bird
    if (birdX < 0) {
        birdX = 60;
        score += 15;
    }

    // --- FIX IS HERE (Tree Collision) ---
    // Removed "&& !isDucking". 
    // Now, if the obstacle is at X=5 and you are on the ground (dinoY=0),
    // you get hit, even if you are ducking.
    if (obstacleX == 5 && dinoY == 0) { 
        if (shieldActive) {
            shieldActive = false;
        } else {
            health -= (level == 3 ? 2 : 1);
        }
        obstacleX = 40;
        Beep(400, 200);
        if (health <= 0)
            gameOver = true;
    }
    // ------------------------------------

    // Bird collision (You CAN duck under birds, so keep !isDucking here)
    if (level >= 2 && birdX == 5 && !isDucking) {
        if (shieldActive) {
            shieldActive = false;
        } else {
            health -= (level == 3 ? 2 : 1);
        }
        birdX = 60;
        Beep(300, 200);
        if (health <= 0)
            gameOver = true;
    }

    // Jump physics
    if (dinoY == 1) {
        jumpTimer--;
        if (jumpTimer <= 0)
            dinoY = 0;
    }

    // Regenerate stamina
    if (stamina < maxStamina) {
        if (difftime(time(0), lastStaminaUse) >= 5) {
            stamina++;
            lastStaminaUse = time(0); 
        }
    }
    // Duck timer logic
    if (duckTimer > 0) {
        duckTimer--;
        isDucking = true;
    } else {
        isDucking = false;
    }
    // Level progression
    if (score >= 50 && level == 1) {
        level = 2;
        gameSpeed = 110;
    }
    if (score >= 120 && level == 2) {
        level = 3;
        gameSpeed = 80;
    }
}

// ----- MAIN -----
int main() {
    SetConsoleOutputCP(CP_UTF8);
    hideCursor(); 
    srand(time(0));

    string choice;

    while (true) {
        startMenu();
        cin >> choice;

        if (choice == "1") {
            // --- GAME LOOP START ---
            do {
                resetGame();
                system("cls"); 
                bool exitToMenu = false; 

                while (!gameOver) {
                    input();
                    
                    if (isPaused) {
                        char pauseChoice = showPauseMenu();
                        if (pauseChoice == 'r') {
                            isPaused = false;
                            system("cls");
                        } 
                        else if (pauseChoice == 'm') {
                            gameOver = true;
                            exitToMenu = true; 
                        }
                        else if (pauseChoice == 'q') {
                            exit(0);
                        }
                        continue; 
                    }

                    update();
                    drawGame();
                    Sleep(gameSpeed);
                }

                // --- GAME OVER LOGIC ---
                // Only show Game Over menu if we died (didn't quit manually)
                if (!exitToMenu) {
                    char gameOverChoice = showGameOverMenu();

                    if (gameOverChoice == 'r') {
                        // The loop 'do...while' will restart the game automatically
                        continue; 
                    }
                    else if (gameOverChoice == 'm') {
                        break; // Breaks the 'do...while', goes back to Start Menu
                    }
                    else if (gameOverChoice == 'q') {
                        exit(0);
                    }
                } else {
                    break; // Break if we chose "Main Menu" from pause screen
                }

            } while (true); // This inner loop keeps restarting the game if 'r' is chosen

        } 
        else if (choice == "2") {
            instructions();
        } 
        else if (choice == "3") {
            cout << "Thanks for playing!\n";
            break;
        } 
        else {
            system("cls");
            cout << "❌ Invalid choice!\n";
            _getch();
        }
    }

    return 0;
}