//
// Created by Remi Genin on 17/06/2021.
//

#ifndef BETTERTHANGIMP_BRIGHTNESS_H
#define BETTERTHANGIMP_BRIGHTNESS_H

#include "../Manipulation.h"
#include "../../display/workspace/Workspace.h"

class Brightness : public Manipulation {
public:
    Brightness(Workspace &workspace);
    Mat applyManipulation() override;

private:
    double percentChange;

    Mat brightness(Mat &image, double percentChange);
};

#endif //BETTERTHANGIMP_BRIGHTNESS_H
