#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


const int HUD_WIDTH = 120;
const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;

#define MAX_FRAME_DELAY 20
#define MIN_FRAME_DELAY 1
#define MAX_ENEMIES 50
#define MAX_BULLETS 100
#define MAX_LEVELS 10

typedef struct LevelData{
    int rows;
    int cols;
    float enemySpeedMultiplier;
    float enemyShootCooldown;
    int shieldHealth;
}LevelData;

LevelData levels[MAX_LEVELS] = {
    {4, 4, 1.0f, 1.6f, 6},//level1
    {4, 5, 1.2f, 1.4f, 6},//level2
    {5, 6, 1.4f, 1.2f, 5},//level3
    {6, 6, 1.6f, 1.0f, 5},//level4
};

typedef struct Bullets {
    Vector2 position;
    Vector2 prevPosition;
    bool active;
} Bullets;

typedef struct Shield {
    Vector2 position;
    int health;
    bool active;
}Shield;

#define MAX_SHIELDS 3
Shield shields[MAX_SHIELDS];

typedef struct Enemy {
    Vector2 position;
    int type;
    bool active;
    bool exploding;
    float explodeTimer;
} Enemy;

   //enemy score 
int GetEnemyScore(int type) {
    switch(type) {
        case 1: return 10;
        case 2: return 20;
        case 3: return 20;
        case 4: return 30;
        default: return 0;
    }
}



void levelssetup(int levelIndex, Enemy enemies[], int *enemyCount, Vector2 playerPos){
    LevelData L = levels[levelIndex];

    float startY = 60;
    float spacingX = 40;
    float spacingY = 30;
    float totalWidth = (L.cols -1)* spacingX;
    float playableWidth = GetScreenWidth() - HUD_WIDTH;
    float startX = (playableWidth - totalWidth) / 2;

    *enemyCount = 0;

    for (int row = 0; row < L.rows; row++) {
        for (int col = 0; col < L.cols; col++) {

            enemies[*enemyCount].position = (Vector2){
                startX + col * spacingX,
                startY + row * spacingY
            };

            enemies[*enemyCount].type = (row % 4) + 1; // cycle enemy types
            enemies[*enemyCount].active = true;
            enemies[*enemyCount].exploding = false;

            (*enemyCount)++;
        }
    }


    float shieldY = playerPos.y - 80; // above player

    for (int i = 0; i < MAX_SHIELDS; i++) {
        shields[i].position = (Vector2){
            80 + i * 120,  // spacing across screen
            shieldY
        };
        shields[i].health = L.shieldHealth;
        shields[i].active = true;
    }


}



int main(void) {
   InitWindow(512, 512, "POP Raylib Starter");
   Texture2D players_rocket = LoadTexture("resources/playerrocket.png");
   Texture2D enemy1_idle = LoadTexture("resources/enemy1idle.png");
   Texture2D enemy1_walk = LoadTexture("resources/enemy1walk.png");
   Texture2D enemy2_idle = LoadTexture("resources/enemy2idle.png");
   Texture2D enemy2_walk = LoadTexture("resources/enemy2walk.png");
   Texture2D enemy3_idle = LoadTexture("resources/enemy3idle.png");
   Texture2D enemy3_walk = LoadTexture("resources/enemy3walk.png");
   Texture2D enemy4_idle = LoadTexture("resources/enemy4idle.png");
   Texture2D enemy4_walk = LoadTexture("resources/enemy4walk.png");
   Texture2D shield_full = LoadTexture("resources/fullhealthshield.png");
   Texture2D shield_low = LoadTexture("resources/lowhealthshield.png");

   Texture2D explosion = LoadTexture("resources/explosion.png");

   //bullets
    //should free -->
   Bullets *mybullets = (Bullets *)malloc(MAX_BULLETS*sizeof(Bullets));
   for (int i=0;i<MAX_BULLETS;i++){
    mybullets[i].active = false;
    mybullets[i].position = (Vector2){0,0};
   }

   //enemybullets
   Bullets enemyBullets[MAX_BULLETS];
   for (int i=0;i<MAX_BULLETS;i++){
    enemyBullets[i].active = false;
   }
   
   
   Texture2D player_bullet = LoadTexture("resources/playerbullet.png");
   Texture2D enemy_bullet = LoadTexture("resources/enemybullet.png");

   Texture2D game_over = LoadTexture("resources/game_over.png");

   //animation of the gif background
   int bgFrames = 0;
   int frameDelay = 5;
   int frameCounter = 0;
   unsigned int frameOffset = 0;
   Image bgImage = LoadImageAnim("resources/twinkletwinklelittlestar.gif", &bgFrames);
   int currentFrame = 0;

   Texture2D bgTexture = LoadTextureFromImage(bgImage);

   float scale = 1.2f;
   float rocketWidth = players_rocket.width * scale;
   float rocketHeight = players_rocket.height * scale;



   float rocketspeed = 200;
   SetTargetFPS(60);
   
   Vector2 pos = {250,470};

   //Vector2 enemy2_pos = {10,50};
   //Vector2 enemy3_pos = {10,90};
   //Vector2 enemy4_pos = {10,130};

   //shared movement so they go to the left and right and down together
   int enemy_dir = 1;
   float enemy_speed = 30;
   float drop = 20;
   float stepInterval = 0.2f; //time between each step
   int enemyState = 0;
   float stateTimer = 0.0f;

   float shootCooldown = 0.70f;
   float shootTimer = 0.0f;

   float enemyshootCooldown = 1.6f;
   float enemyshootTimer = 0.0f;

   float idleTime = 0.80f;
   float walkTime = 0.4f;

   int lives = 3;
   int score = 0;

   bool gameOver = false;
   bool stepTaken = false;

   bool showLevelIntro = true;
   float levelIntroTimer = 2.0f;

   bool waitforstarting = true;




   //levels
   Enemy enemies[MAX_ENEMIES];
   int enemyCount = 0;
   int CurrentLevel = 1;
   levelssetup(CurrentLevel, enemies, &enemyCount, pos);
   LevelData current = levels[CurrentLevel];
   showLevelIntro = true;
   levelIntroTimer = 1.0f;
   enemy_speed = 50 * current.enemySpeedMultiplier;
   enemyshootCooldown = current.enemyShootCooldown;




    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (waitforstarting) {
            DrawTexture(bgTexture, 0, 0, WHITE);

            DrawText("PRESS ENTER TO PLAY",
            SCREEN_WIDTH/2 - MeasureText("PRESS ENTER TO PLAY", 30)/2,
            SCREEN_HEIGHT/2 - 20,
            30, YELLOW);

            if (IsKeyPressed(KEY_ENTER)) {
                waitforstarting = false;
            }
            
            EndDrawing();
            continue;
        }


        float dt = GetFrameTime();
        enemyshootTimer += dt;

        if (gameOver) {
            DrawTexture(bgTexture, 0, 0, WHITE);

            DrawTextureEx(game_over, (Vector2){85, 0}, 0.0f, 0.4f, WHITE);

            DrawText("PRESS ENTER TO RESTART",
            SCREEN_WIDTH/2 - MeasureText("PRESS ENTER TO RESTART", 30)/2,
            SCREEN_HEIGHT/2 + 80,
            30, YELLOW);

    
            if (IsKeyPressed(KEY_ENTER)) {
                lives = 3;
                score = 0;
                CurrentLevel = 1;

                pos = (Vector2){250, 470};

                for (int i = 0; i < MAX_BULLETS; i++) {
                    mybullets[i].active = false;
                    enemyBullets[i].active = false;
                }

                shootTimer = shootCooldown;
                enemyshootTimer = 0;

                levelssetup(CurrentLevel, enemies, &enemyCount, pos);

                gameOver = false;

                showLevelIntro = true;
                levelIntroTimer = 1.0f;
            }

            EndDrawing();
            continue;
        }
        
        DrawTexture(bgTexture, 0, 0, WHITE);

        char lifeText[32];
        sprintf(lifeText, "LIVES: %d", lives);

        DrawText(lifeText, SCREEN_WIDTH - HUD_WIDTH + 10, 20, 20, WHITE);

        char scoreText[32];
        sprintf(scoreText, "SCORE: %d", score);
        DrawText(scoreText, SCREEN_WIDTH - HUD_WIDTH + 10, 60, 20, WHITE);


        //updating intro timer
        if (showLevelIntro){
            levelIntroTimer -= dt;
            if (levelIntroTimer <= 0){
                showLevelIntro = false;
            }
        }

        //draw intro text
        if (showLevelIntro){

            for (int i = 0; i < MAX_BULLETS; i++)
            {
                mybullets[i].active = false;
                enemyBullets[i].active = false;
            }
            
            char buffer[64];
            sprintf(buffer, "LEVEL %d", CurrentLevel);

            DrawText(buffer, SCREEN_WIDTH/2 - MeasureText(buffer, 40)/2, SCREEN_HEIGHT/2 - 20, 40, YELLOW);
            EndDrawing();
            continue;
        }

        
        
        
        //bullet part
        //enemybullets
       for (int i=0;i<MAX_BULLETS;i++){
            if(enemyBullets[i].active){
            DrawTextureEx(enemy_bullet, enemyBullets[i].position, 0.0f, 1.0f, RED);
            }
        } 

        for (int i=0;i<MAX_BULLETS;i++){
            if(mybullets[i].active){
            DrawTextureEx(player_bullet, mybullets[i].position, 0.0f, 1.0f, WHITE);
            }
        } 

        for(int i=0; i < MAX_BULLETS; i++){
            if(mybullets[i].active){
                mybullets[i].position.y -= 300 * dt;
                if (mybullets[i].position.y < 0)
                {
                    mybullets[i].active = false;
                }
            }
        }

        //enemy bullet movement
        for(int i=0; i < MAX_BULLETS; i++){
            if(enemyBullets[i].active){
                enemyBullets[i].prevPosition = enemyBullets[i].position;
                enemyBullets[i].position.y += 120 * dt;
                if (enemyBullets[i].position.y > SCREEN_HEIGHT)
                {
                    enemyBullets[i].active = false;
                }
            }
        }





        //bullet cooldown
        shootTimer -= dt;
        if (shootTimer < 0){
            shootTimer = 0;
        }

        //keybind for shooting
        if (IsKeyPressed(KEY_SPACE) && shootTimer <= 0){
            for(int i = 0; i<MAX_BULLETS;i++){
                if(mybullets[i].active == false){
                    mybullets[i].active = true;
                    mybullets[i].position = (Vector2){
                        pos.x + rocketWidth/2 - player_bullet.width/2,
                        pos.y + rocketHeight/2 - player_bullet.height/2
                    };
                    shootTimer = shootCooldown;
                    break;
                }
            }
        }


        //bullet collision
        for (int i= 0; i < MAX_BULLETS; i++){
            if (!mybullets[i].active){
                continue;
            }

            for (int s = 0; s < MAX_SHIELDS; s++){
                if (!shields[s].active) {
                    continue;
                }

                Rectangle shieldRect = {
                    shields[s].position.x,
                    shields[s].position.y,
                    shield_full.width,
                    shield_full.height
                };

                Rectangle bulletRect = {
                    mybullets[i].position.x,
                    mybullets[i].position.y,
                    player_bullet.width,
                    player_bullet.height
                };

                if (CheckCollisionRecs(bulletRect, shieldRect)){
                    shields[s].health--;
                    

                    if (shields[s].health <= 0){
                    shields[s].active = false;
                    }

                    mybullets[i].active = false;
                    break; // ONLY break on hit
                }
            }


            for (int j = 0; j < enemyCount; j++){
                if (!enemies[j].active){
                    continue;
                }

                //float width = enemy1_idle.width * 0.6f;
                //float height = enemy1_idle.height * 0.6f;
                Rectangle bulletrectangle = {
                    mybullets[i].position.x,
                    mybullets[i].position.y,
                    player_bullet.width,
                    player_bullet.height
                };

                float enemyWidth = enemy1_idle.width * 0.5f;
                float enemyHeight = enemy1_idle.height * 0.5f;

                Rectangle enemyrectangle = {
                    enemies[j].position.x,
                    enemies[j].position.y,
                    enemyWidth,
                    enemyHeight
                };

                if (CheckCollisionRecs(bulletrectangle, enemyrectangle)){
                    enemies[j].exploding = true;
                    enemies[j].explodeTimer = 0.20f;
                    mybullets[i].active = false;
                    break;

                    score += GetEnemyScore(enemies[j].type);

                    break;
                }
    
            }
            
        }
    

        Rectangle playerRect = {
            pos.x,
            pos.y,
            rocketWidth,
            rocketHeight
        };

        for (int k = 0; k < MAX_BULLETS; k++){
                    if (!enemyBullets[k].active) {
                        continue;
                    }

                    Rectangle bulletRect = {
                        enemyBullets[k].position.x,
                        enemyBullets[k].position.y,
                        enemy_bullet.width,
                        enemy_bullet.height
                    };

                    for (int s = 0; s < MAX_SHIELDS; s++){
                        if (!shields[s].active) {
                            continue;
                        }

                        Rectangle shieldRect = {
                            shields[s].position.x,
                            shields[s].position.y,
                            shield_full.width,
                            shield_full.height
                        };

                        if (CheckCollisionRecs(bulletRect, shieldRect)){
                            shields[s].health--;

                            if (shields[s].health <= 0){
                                shields[s].active = false;
                            }

                            enemyBullets[k].active = false;
                            break;
                        }
                    }

                    // skip player if bullet died
                    if (!enemyBullets[k].active) continue;

                    if (CheckCollisionRecs(playerRect, bulletRect)){
                        enemyBullets[k].active = false;
                        lives--;
                        if(lives <= 0){
                            gameOver = true;
                            score = 0;
                            shootTimer = shootCooldown;
                            enemyshootTimer = 0;

                            for (int i = 0; i < MAX_BULLETS; i++){
                                mybullets[i].active = false;
                                enemyBullets[i].active = false;
                            } 
                            
                        }
                        else{
                            pos = (Vector2){250, 470};
                            showLevelIntro = true;
                            levelIntroTimer = 1.0f;
                        }
                    }

                }

        //so the explosion disappears after the collision
        for (int i =0; i< enemyCount; i++){
            if (enemies[i].exploding){
                enemies[i].explodeTimer -= dt;
                
                if (enemies[i].explodeTimer <= 0){
                    enemies[i].exploding = false;
                    enemies[i].active = false;
                }
                    
            }
        }



        //check when a level is finished
        bool alldead = true;
        for (int i = 0; i < enemyCount; i++) {
            if (enemies[i].active) {
                alldead = false;
                break;
            }
        }
        if (alldead) {
            CurrentLevel++;

            if (CurrentLevel >= MAX_LEVELS){
                gameOver = true;
            }
            else {
                levelssetup(CurrentLevel, enemies, &enemyCount, pos);
                showLevelIntro = true;
                levelIntroTimer = 2.0f;
            }
        }

        

        //background gif animation
        frameCounter++;
        if (frameCounter >= frameDelay){
            currentFrame++;
            if (currentFrame >= bgFrames)
            {
                currentFrame = 0;
            }

            frameOffset = bgImage.width * bgImage.height * 4 * currentFrame;

            UpdateTexture(
                bgTexture,
                ((unsigned char *)bgImage.data) + frameOffset
            );

            frameCounter = 0;
        }


        //game over once the enemy reaches the player
        for (int i=0;i<enemyCount;i++){
            if (!enemies[i].active){
                continue;
            }
            float enemyHeight = enemy1_idle.height * 0.6f;
            float enemyBottom = enemies[i].position.y + enemyHeight;

            if (enemyBottom >= pos.y){
                gameOver = true;
            }
        }
        
        // if (enemy2_pos.y + enemy2_idle.height * 0.6f >= pos.y){
        //     gameOver = true;
        // }

        


        //keybinds
        if(IsKeyDown(KEY_RIGHT)){
            pos.x += rocketspeed * dt;
        }

        if(IsKeyDown(KEY_LEFT)){
            pos.x -= rocketspeed * dt;
        }
        
        

        //wasd keybinds
         if(IsKeyDown(KEY_D)){
            pos.x += rocketspeed * dt;
        }

        if(IsKeyDown(KEY_A)){
            pos.x -= rocketspeed * dt;
        }
        
        


        
        // invisible barrier to keep rocket in screen
        if (pos.x < 0){
            pos.x = 0;
        }
        if (pos.y < 0){
            pos.y = 0;
        }

        if (pos.x > GetScreenWidth() - HUD_WIDTH - rocketWidth){
            pos.x = GetScreenWidth() - HUD_WIDTH - rocketWidth;
        }

        if (pos.y > GetScreenHeight() - rocketHeight){
            pos.y = GetScreenHeight() - rocketHeight;
        }

        //enemy movement
        stateTimer += dt;
        float nextStep = enemy_speed * enemy_dir * stepInterval;
        float enemyWidth = enemy1_idle.width * 0.6f;

        float leftMost = SCREEN_WIDTH;
        float rightMost = 0;
        for (int i=0; i < enemyCount; i++){
            if (!enemies[i].active){
                continue;
            }
            if (enemies[i].position.x < leftMost){
                leftMost = enemies[i].position.x;
            }
            if(enemies[i].position.x + enemyWidth > rightMost){
                rightMost = enemies[i].position.x + enemyWidth;
            }
        }

        bool ifHitRight = (rightMost + nextStep > SCREEN_WIDTH - HUD_WIDTH);
        bool ifHitLeft = (leftMost + nextStep < 0);

        if (ifHitRight || ifHitLeft){
            enemy_dir *= -1;
            for (int i=0;i<enemyCount;i++){
                if (!enemies[i].active){
                    continue;
                }
                enemies[i].position.y += drop;
            }
            enemy_speed += 10;
            enemyState = 0;
            stateTimer = 0.0f;
        }
        else{
            if (enemyState == 1 && !stepTaken){
                for (int i=0; i<enemyCount;i++){
                    if (!enemies[i].active){
                        continue;
                    }
                    enemies[i].position.x += nextStep;
                }
                stepTaken = true;
            }
        }


        if (enemyState == 0){//not walking/idle
            if (stateTimer >= idleTime) {
                stateTimer = 0.0f;
                enemyState = 1;
                stepTaken = false;
            }
        }
        else if (enemyState == 1){//walking
            if (!stepTaken){
                for (int i = 0; i < enemyCount; i++)
                {
                    if (!enemies[i].active){
                        continue;   
                    }
                    enemies[i].position.x += enemy_speed * enemy_dir * stepInterval;
                }
                stepTaken = true;
            }

            if (stateTimer >= walkTime) {
                stateTimer = 0.0f;
                enemyState = 0;
            }
        }

        if (enemyshootTimer >= enemyshootCooldown){
            int columns = 4 + CurrentLevel;

            for (int col = 0; col < columns; col++){
                Enemy *lowest = NULL;

                //finding the bottom enemy in the column
                for(int i = 0; i < enemyCount; i++){
                    if (!enemies[i].active){
                        continue;
                    }
                    if (i % columns == col){
                        if (lowest == NULL || enemies[i].position.y > lowest -> position.y){
                            lowest = &enemies[i];
                        }
                    }
                }


                //if enemy finds player, shoot
                if (lowest != NULL && GetRandomValue(0,100)< 30){
                    for (int b = 0; b < MAX_BULLETS; b++){
                        if (!enemyBullets[b].active){
                            enemyBullets[b].active = true;

                            enemyBullets[b].position = (Vector2){
                                lowest->position.x + (enemy1_idle.width * 0.25f),
                                lowest->position.y + (enemy1_idle.height * 0.5f)
                            };
                            break;
                        }
                    }
                }
            }

            enemyshootTimer = 0;
        }



        //enemy2_pos.x += enemy_speed * enemy_dir * dt;
        //enemy3_pos.x += enemy_speed * enemy_dir * dt;
        //enemy4_pos.x += enemy_speed * enemy_dir * dt;


        //invisible barrier for the aliens
        bool hitRight = false;
        bool hitLeft = false;

        for (int i=0; i < enemyCount; i++){
            if (!enemies[i].active){
                continue;
            }
            float width = enemy1_idle.width * 0.6f;

            if(enemies[i].position.x + width >= GetScreenWidth() - HUD_WIDTH){
                hitRight = true;
            }
            if(enemies[i].position.x <= 0){
                hitLeft = true;
            }
        }





        //enemy movement
        if ((enemy_dir == 1 && hitRight) || (enemy_dir == -1 && hitLeft)) {
            enemy_dir *= -1;

            float rightLimit = GetScreenWidth() - HUD_WIDTH;
            float width = enemy1_idle.width * 0.6f;

            for (int i=0; i <enemyCount; i++){
                if (!enemies[i].active){
                    continue;
                }

                //clamping to left wall
                if (enemies[i].position.x < 0){
                    enemies[i].position.x = 0;
                }
                //clamping to 'right wall' which is just before the hud
                if (enemies[i].position.x + width > rightLimit){
                    enemies[i].position.x = rightLimit - width;
                }
                enemies[i].position.y += drop;
            }

            
            enemy_speed += 10;

            //gap when they touch the wall because i realised, half of the sprite is going through the wall

            enemyState = 0;
            stateTimer = 0.0f;
        }

        
        DrawTextureEx(players_rocket, pos, 0.0f, 1.2f, WHITE);

        for (int i = 0; i < MAX_SHIELDS; i++){
            if (!shields[i].active){ 
                continue;
            }

            Texture2D tex;

            if (shields[i].health > 3) {
                tex = shield_full;      //6 hp to 4 hp
            }       
            else {
                tex = shield_low;       // 3hp to 1 hp
            }

            DrawTexture(tex, shields[i].position.x, shields[i].position.y, WHITE);
        }

        for (int i=0; i < enemyCount; i++){
            if (!enemies[i].active){
                continue;
            }

            Texture2D tex;

            if (enemyState == 1){
                if(enemies[i].type == 1){
                    tex = enemy1_walk;
                }
                else if(enemies[i].type == 2){
                    tex = enemy2_walk;
                }
                else if(enemies[i].type == 3){
                    tex = enemy3_walk;
                }
                else{
                    tex = enemy4_walk;
                }
            }
            else {
                if (enemies[i].type == 1){
                    tex = enemy1_idle;
                }
                else if(enemies[i].type == 2){
                    tex = enemy2_idle;
                }
                else if(enemies[i].type == 3){
                    tex = enemy3_idle;
                }
                else{
                    tex = enemy4_idle;
                }
            }
            if (enemies[i].exploding){
                DrawTextureEx(explosion, enemies[i].position, 0.0f, 1.2f, WHITE);
            }
            else if (enemies[i].active){
                DrawTextureEx(tex, enemies[i].position, 0.0f, 0.5f, WHITE);
            }
        }





        //DrawTextureEx(enemy2_idle, (Vector2){10,50},0.8f, 0.8f,WHITE);
        //DrawTextureEx(enemy2_walk, (Vector2){15 + enemy2_idle.width,50},0.8f, 0.8f,WHITE);
        //DrawTextureEx(enemy3_idle, (Vector2){10,90},0.8f, 0.8f,WHITE);
        //DrawTextureEx(enemy3_walk, (Vector2){15 + enemy3_idle.width,90},0.8f, 0.8f,WHITE);
        //DrawTextureEx(enemy4_idle, (Vector2){10,130},0.8f, 0.8f,WHITE);
        //DrawTextureEx(enemy4_walk, (Vector2){15 + enemy4_idle.width,130},0.8f, 0.8f,WHITE);

        EndDrawing();
    }



    UnloadTexture(players_rocket);
    UnloadTexture(enemy1_idle);
    UnloadTexture(enemy1_walk);
    UnloadTexture(game_over);
    UnloadTexture(bgTexture);
    UnloadImage(bgImage);

    free(mybullets);

    CloseWindow();
    return 0;
}