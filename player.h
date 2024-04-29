#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#endif // PLAYER_H_INCLUDED


struct player{
float x;
float y;
float width = 50;
float height = 50;
float defaultSpeed = 5;
float speed = defaultSpeed;

vector2D tongue;
vector2D shootDir;
bool isShoot = false;
int defaultShootTime = 1500;
int shootTimer = defaultShootTime;
int defaultShootSpeed = 75;
int shootSpeed = defaultShootSpeed;

float distanceForLootingMobByTongue = 30;
};



vector2D inputKey(){

vector2D direction;
direction.x = 0;
direction.y = 0;

if(GetAsyncKeyState(VK_RIGHT)){
    direction.x = 1;
}
if(GetAsyncKeyState(VK_LEFT)){
    direction.x = -1;
}
if(GetAsyncKeyState(VK_UP)){
    direction.y = -1;
}
if(GetAsyncKeyState(VK_DOWN)){
    direction.y = 1;
}

direction = getNormalized(0,0,direction.x,direction.y);

return direction;
}

vector2D inputMouse(){
int x,y;
getmouseclick(WM_LBUTTONDOWN, x, y);

vector2D output;

if(x > 0 && y > 0){
output.x = (float)x;
output.y = (float)y;
}
else{
output.x = -1;
output.y = -1;
}
return output;
}

void Shoot(player *Player){

vector2D mousePos = inputMouse();
if (mousePos.x > 0 && mousePos.y > 0 && !(*Player).isShoot){
    // Check process of shooting tongue
    (*Player).isShoot = true;

    // Get direction where tongue will be shoot
    (*Player).shootDir = getNormalized((*Player).x, (*Player).y, mousePos.x, mousePos.y);

    // Define tongue position
    (*Player).tongue.x = (*Player).x + (*Player).width/2 + (*Player).shootDir.x * 250 * sin(M_PI*(float)(*Player).shootTimer/(*Player).defaultShootTime);
    (*Player).tongue.y = (*Player).y + (*Player).height/2 + (*Player).shootDir.y * 250 * sin(M_PI*(float)(*Player).shootTimer/(*Player).defaultShootTime);
}
else if ((*Player).shootTimer > 0 && (*Player).isShoot){
    // Decreasing Timer
    (*Player).shootTimer-=(*Player).shootSpeed;

    // Define tongue position
    (*Player).tongue.x = (*Player).x + (*Player).width/2 + (*Player).shootDir.x * 250 * sin(M_PI*(float)(*Player).shootTimer/(*Player).defaultShootTime);
    (*Player).tongue.y = (*Player).y + (*Player).height/2 + (*Player).shootDir.y * 250 * sin(M_PI*(float)(*Player).shootTimer/(*Player).defaultShootTime);
}
else if ((*Player).isShoot){
    (*Player).shootTimer = (*Player).defaultShootTime;
    (*Player).isShoot = false;
}
}


