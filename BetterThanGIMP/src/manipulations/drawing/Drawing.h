//
// Created by Hugues Baratgin on 17/06/2021.
//

#ifndef BETTERTHANGIMP_DRAWING_H
#define BETTERTHANGIMP_DRAWING_H


#include "../Manipulation.h"

class Drawing : public Manipulation {
public:
    Drawing(Workspace &);

protected:
    Point mouseCoordinates;
    int red;
    int green;
    int blue;
    int brushSize;
};


#endif //BETTERTHANGIMP_DRAWING_H
