#ifndef UIUX_H_INCLUDED
#define UIUX_H_INCLUDED



#endif // UIUX_H_INCLUDED


void drawFoodPoints(player Player){
rectangle(25,25,25+(Player.foodPoints/Player.defaultFoodPoints) * 200,50);
}
