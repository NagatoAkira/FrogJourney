#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#endif // PLAYER_H_INCLUDED


struct player{
float x;
float y;
float width = 50;
float height = 50;
float defaultSpeed = 7;
float speed = defaultSpeed;

vector2D tongue;
vector2D shootDir;

bool isShoot = false;
bool isUsedAllLengthOfTongue = false;


float defaultShootDistance = 200;
float shootDistance = defaultShootDistance;
float defaultShootSpeed = 20;
float shootSpeed = defaultShootSpeed;

float distanceForLootingMobByTongue = 25;
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
if (!(*Player).isShoot && mousePos.x > 0 && mousePos.y > 0){
    // Check process of shooting tongue
    (*Player).isShoot = true;

    // Get direction where tongue will be shoot
    (*Player).shootDir = getNormalized((*Player).x+(*Player).width/2, (*Player).y+(*Player).height/2, mousePos.x, mousePos.y);

    // Start position of tongue
    (*Player).tongue.x = (*Player).x + (*Player).width/2 + (*Player).shootDir.x * (*Player).shootSpeed;
    (*Player).tongue.y = (*Player).y + (*Player).height/2 + (*Player).shootDir.y * (*Player).shootSpeed;
}
else if ((*Player).isShoot &&  !(*Player).isUsedAllLengthOfTongue){
    (*Player).shootDir = getNormalized(0, 0, (*Player).shootDir.x*1.1, (*Player).shootDir.y*1.1);

    // Define tongue position
    (*Player).tongue.x += (*Player).shootDir.x * (*Player).shootSpeed;
    (*Player).tongue.y += (*Player).shootDir.y * (*Player).shootSpeed;



    // Decreasing distance between tongue and player
    (*Player).shootDistance -= (*Player).shootSpeed;
    if((*Player).shootDistance <= 0){
        (*Player).isUsedAllLengthOfTongue = true;
        (*Player).shootDistance = (*Player).defaultShootDistance;
    }
}
else if ((*Player).isShoot && (*Player).isUsedAllLengthOfTongue){

    // Get direction where tongue was shoot
    (*Player).shootDir = getNormalized((*Player).x+(*Player).width/2, (*Player).y+(*Player).height/2, (*Player).tongue.x, (*Player).tongue.y);

    // Define tongue position
    (*Player).tongue.x -= (*Player).shootDir.x*(*Player).shootSpeed;
    (*Player).tongue.y -= (*Player).shootDir.y*(*Player).shootSpeed;

    if(getDistance((*Player).tongue.x, (*Player).tongue.y, (*Player).x+(*Player).width/2, (*Player).y+(*Player).height/2) <= (*Player).distanceForLootingMobByTongue){
        (*Player).isShoot = false;
        (*Player).isUsedAllLengthOfTongue = false;
    }

}
}


