//
// Created by Hugues Baratgin on 16/06/2021.
//

#ifndef BETTERTHANGIMP_BRUSH_H
#define BETTERTHANGIMP_BRUSH_H


#include "../Drawing.h"

class Brush : public Drawing {
public:
    Brush(Workspace &);

    Mat applyManipulation() override;
};


#endif //BETTERTHANGIMP_BRUSH_H
