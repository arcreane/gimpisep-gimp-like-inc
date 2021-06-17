//
// Created by Louis Felli on 17/06/2021.
//

#ifndef BETTERTHANGIMP_RESIZING_H
#define BETTERTHANGIMP_RESIZING_H
#include "../Manipulation.h"

class Resizing : public Manipulation {
public:
    Resizing(Workspace &workspace);

    Mat applyManipulation();

private:
    QWidget *parametersToDisplay;

    double scaleX;
    double scaleY;
    bool factor;

    void updateParametersToDisplay();
};

#endif //BETTERTHANGIMP_RESIZING_H
