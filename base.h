#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#endif // BASE_H_INCLUDED

struct vector2D{
float x;
float y;
};

extern float getDistance(float x1, float y1, float x2, float y2){
    float output = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    return output;
}
extern vector2D getNormalized(float x1, float y1, float x2, float y2){
    float distance = getDistance(x1,y1,x2,y2);
    vector2D output;

    if(distance!=0){
        output.x = (x2-x1)/distance;
        output.y = (y2-y1)/distance;
    }
    else{
        output.x = 0;
        output.y = 0;
    }
    return output;
}
