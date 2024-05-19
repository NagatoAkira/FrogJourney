#include<graphics.h>
#include<stdio.h>
#include<conio.h>

#include<iostream>

#include<math.h>

#include"deltatime.h"
#include"base.h"
#include"player.h"
#include"mobs.h"
#include"decoration.h"
#include"camera.h"
#include"uiux.h"


int main(void) {
   float deltatime;

   // Initiate window
   float windowWidth = 800;
   float windowHeight = 800;
   initwindow(windowWidth,windowHeight);

   // Player configuration
   player Player;
   Player.x = windowWidth/2-Player.width/2;
   Player.y = windowHeight/2-Player.height/2;

   Mob Bug;
   Bug.x = 150;
   Bug.y = 150;
   Bug.radiusCollision = 35;

   int amountCreatures = 1;
   Mob Creatures[amountCreatures];
   Creatures[0] = Bug;


   EnvironmentObject tree;
   tree.x = 50;
   tree.y = 150;
   tree.width = 20;
   tree.height = 100;

   int amountSceneObjects = 5;
   EnvironmentObject Scene[amountSceneObjects];
   for(int i=0; i<amountSceneObjects; i++){
    Scene[i] = tree;
    Scene[i].x += i*35;
   }

   int page = 0;
   while(true){
    setactivepage(page);
    setvisualpage(1-page);

    deltatime = getDeltaTime();
    cleardevice(); // Clear screen
    rectangle(Player.x,Player.y, Player.x+Player.width, Player.y+Player.height); // draw Player as rectangle



    Shoot(&Player); // function for shooting by tongue
    if(Player.isShoot){ // draw if you clicked mouse
    circle(Player.tongue.x, Player.tongue.y, 10);
    }

    // Food Points
    drawFoodPoints(Player);
    if(Player.foodPoints <= 0){
        closegraph();
    }
    Player.foodPoints--;
    Player.defaultFoodPoints = 1500;
    //std::cout << Player.defaultFoodPoints << std::endl;


    for(int i=0; i<amountSceneObjects; i++){
    rectangle(Scene[i].x, Scene[i].y, Scene[i].x+Scene[i].width, Scene[i].y+Scene[i].height);
    }

    for(int i=0; i<amountCreatures; i++){
        //Creatures[i].speed = Creatures[i].defaultSpeed * deltatime;

        if(Creatures[i].isExist){
            circle(Creatures[i].x, Creatures[i].y, Creatures[i].radiusCollision);
        }

        MobCalmMovement(Creatures, i);
        LootMob(Creatures, i, &Player);
        MobResistance(Creatures, i, &Player);

        updateFoodPoints(Creatures, i, &Player);
    }
    updateCreaturesList(Creatures);


    vector2D dir = inputKey(); // get input keys
    Player.x += dir.x * Player.speed; // move in axis x
    Player.y += dir.y * Player.speed; // move in axis y
    cameraMovement(Scene, Creatures, &Player, windowWidth, windowHeight); // Camera follow to player


    delay(10);
    page = 1 - page;
   }
}
