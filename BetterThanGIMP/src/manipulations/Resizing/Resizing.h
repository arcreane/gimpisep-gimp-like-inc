//
// Created by louis on 17/06/2021.
//

#ifndef BETTERTHANGIMP_RESIZING_H
#define BETTERTHANGIMP_RESIZING_H
#include "../Manipulation.h"

class Resizing : public Manipulation {
public:
    Resizing(Workspace &workspace);

    Mat applyManipulation();

private:
    double scaleX;
    double scaleY;
    bool factor;

    Mat resizing(Mat &image, double scaleX, double scaleY, bool factor);
};

#endif //BETTERTHANGIMP_RESIZING_H
