#include<graphics.h>
#include<stdio.h>
#include<conio.h>

#include<iostream>

#include<math.h>
#include<chrono>

#include"base.h"
#include"player.h"
#include"mobs.h"
#include"decoration.h"
#include"camera.h"
#include"uiux.h"

int main(void) {

   // Initiate window
   float windowWidth = 800;
   float windowHeight = 800;
   initwindow(windowWidth,windowHeight);

   // Player configuration
   player Player;
   Player.x = windowWidth/2-Player.width/2;
   Player.y = windowHeight/2-Player.height/2;

   // Creating Mob template
   Mob Bug;
   Bug.x = -1024;
   Bug.y = -1024;
   Bug.radiusCollision = 35;

   int amountCreatures = 25;
   Mob Creatures[amountCreatures];


   // Creating Decoration template
   EnvironmentObject tree;
   tree.x = -1024;
   tree.y = -1024;
   tree.width = 20;
   tree.height = 100;

   int amountSceneObjects = 40;
   EnvironmentObject Scene[amountSceneObjects];

   int page = 0;
   while(true){
    setactivepage(page);
    setvisualpage(1-page);

    cleardevice(); // Clear screen
    drawPlayer(Player); // Draw Player



    Shoot(&Player); // Function for shooting by tongue
    drawBullet(Player); // Draw Player

    // Food Points
    updateFoodPoints(&Player);

    // Spawn Decoration
    SpawnAroundDecoration(Scene, tree, windowWidth, windowHeight);
    drawDecoration(amountSceneObjects, Scene);

    // Spawn Creatures
    SpawnAroundCreatures(Creatures, Bug, windowWidth, windowHeight);
    for(int i=0; i<amountCreatures; i++){
        if(Creatures[i].isExist){
            circle(Creatures[i].x, Creatures[i].y, Creatures[i].radiusCollision);
        }

        MobCalmMovement(Creatures, i);
        LootMob(Creatures, i, &Player);
        MobResistance(Creatures, i, &Player);

        updateFoodPointsMob(Creatures, i, &Player);
    }
    updateCreaturesList(Creatures); // Update List to clean "dead" creatures


    vector2D dir = inputKey(); // get input keys
    Player.x += dir.x * Player.speed; // move in axis x
    Player.y += dir.y * Player.speed; // move in axis y
    cameraMovement(Scene, Creatures, &Player, windowWidth, windowHeight); // Camera follow to player


    delay(10);
    page = 1 - page;
   }
}
