#ifndef DECORATION_H_INCLUDED
#define DECORATION_H_INCLUDED



#endif // DECORATION_H_INCLUDED


struct EnvironmentObject{
float x;
float y;
float width;
float height;
};

void SpawnAroundDecoration(EnvironmentObject decorations[], EnvironmentObject template_, int scrW, int scrH){
srand(time(NULL));
int rand_x, rand_y;

int addition_Distance = 50;

for(int i=0; i<sizeof(decorations); i++){
    if(decorations[i].x < scrW + addition_Distance &&
       decorations[i].y < scrH + addition_Distance &&
       decorations[i].x > addition_Distance &&
       decorations[i].y > addition_Distance){
       continue;
    }


    decorations[i] = template_;

    // Create random number from square side around Player
    rand_x = addition_Distance + rand()%(scrW+addition_Distance);
    rand_y = addition_Distance + rand()%(scrH+addition_Distance);


    decorations[i].x = rand_x;
    decorations[i].y = rand_y;
}
}

void drawDecoration(int amountSceneObjects, EnvironmentObject Scene[]){
    for(int i=0; i<amountSceneObjects; i++){
        rectangle(Scene[i].x, Scene[i].y, Scene[i].x+Scene[i].width, Scene[i].y+Scene[i].height);
    }
}
