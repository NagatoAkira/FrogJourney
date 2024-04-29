#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED



#endif // CAMERA_H_INCLUDED


void cameraMovement(EnvironmentObject Scene[], Mob Creatures[], player *Player, float windowWidth, float windowHeight){
  vector2D screenCenter;
  screenCenter.x = windowWidth/2;
  screenCenter.y = windowHeight/2;

  float accessMovementDistance = 120;

  vector2D barrier = getNormalized(screenCenter.x, screenCenter.y, (*Player).x+(*Player).width/2, (*Player).y+(*Player).height/2);
  float currentRadius = getDistance(screenCenter.x,
                                    screenCenter.y,
                                    (*Player).x+(*Player).width/2,
                                    (*Player).y+(*Player).height/2);

  if(currentRadius > accessMovementDistance){
    (*Player).x = screenCenter.x + barrier.x*(accessMovementDistance-2)-(*Player).width/2;
    (*Player).y = screenCenter.y + barrier.y*(accessMovementDistance-2)-(*Player).height/2;

    (*Player).tongue.x -= barrier.x*(*Player).speed;
    (*Player).tongue.y -= barrier.y*(*Player).speed;

     for(int i=0; i<=sizeof(Scene); i++){
        Scene[i].x -= barrier.x*(*Player).speed;
        Scene[i].y -= barrier.y*(*Player).speed;
     }

     for(int i=0; i<=sizeof(Creatures); i++){
        Creatures[i].x -= barrier.x*(*Player).speed;
        Creatures[i].y -= barrier.y*(*Player).speed;
     }
  }
}
