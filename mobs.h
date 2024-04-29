#ifndef MOBS_H_INCLUDED
#define MOBS_H_INCLUDED

#endif // MOBS_H_INCLUDED

struct Mob{
// Base variables for mob
float x;
float y;
float radiusCollision;
float defaultSpeed = 250;
float speed = defaultSpeed;

//Special variables for mob
// Directions where mob must move
float goalDirX;
float goalDirY;
float defaultGoalDistance = 200; // Distance which must be went by mob in calm state
float goalDistance = 0; // Don't change
int defaultWaitTime = 1000; // Wait time for calm state between movement in space
int waitTime = 0; // Don't change

bool isCatched = false; // State of catching mob by tongue
bool isExist = true; // State of existing mob
};


void updateCreaturesList(Mob Creatures[]){
    Mob newList[sizeof(Creatures)];
    for(int i=0; i<sizeof(Creatures); i++){
        if(Creatures[i].isExist){
            newList[i] = Creatures[i];
        }
    }
    Creatures = newList;
}


void DetectTongueTouch(Mob Creatures[], int index,  player *Player){
if((*Player).isShoot){
    if(getDistance((*Player).tongue.x, (*Player).tongue.y, Creatures[index].x, Creatures[index].y) <= Creatures[index].radiusCollision){
            Creatures[index].isCatched = true;
        }
}
}

void LootMob(Mob Creatures[], int index,  player *Player){


    DetectTongueTouch(Creatures, index, &(*Player));

    if(Creatures[index].isCatched){
    Creatures[index].x = (*Player).tongue.x;
    Creatures[index].y = (*Player).tongue.y;

    if(Creatures[index].isCatched && !(*Player).isShoot){
        Creatures[index].isExist = false;
    }
    }
}

void MobResistance(Mob Creatures[], int index, player *Player){
vector2D vectorForFluctuation = getNormalized(0,0, rand()%10*pow(-1, rand()%3), rand()%10*pow(-1, rand()%3));


if(Creatures[index].isCatched && Creatures[index].isExist){
    Creatures[index].x += vectorForFluctuation.x*5;
    Creatures[index].y += vectorForFluctuation.y*5;

    if(GetAsyncKeyState(VK_LBUTTON)){
        (*Player).shootSpeed=(*Player).defaultShootSpeed*0.33;
        return;
    }

    (*Player).shootSpeed = 1;
    (*Player).speed = 0;
}else{
   (*Player).shootSpeed = (*Player).defaultShootSpeed;
   (*Player).speed = (*Player).defaultSpeed;
}

}

void MobCalmMovement(Mob Creatures[], int index){
if(Creatures[index].waitTime <= 0){
if(Creatures[index].goalDistance > 0){
Creatures[index].x += Creatures[index].goalDirX*Creatures[index].speed;
Creatures[index].y += Creatures[index].goalDirY*Creatures[index].speed;
Creatures[index].goalDistance -= Creatures[index].speed;
}
else if(!Creatures[index].isCatched){
vector2D goalDirection = getNormalized(0,0, rand()%10*pow(-1, rand()%2), rand()%10*pow(-1, rand()%2));
Creatures[index].goalDirX = goalDirection.x;
Creatures[index].goalDirY = goalDirection.y;

Creatures[index].goalDistance = Creatures[index].defaultGoalDistance;
Creatures[index].waitTime = Creatures[index].defaultWaitTime;
}
}

if(Creatures[index].waitTime > 0){
    Creatures[index].waitTime--;
}

}




